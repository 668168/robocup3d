#################################################################
# Evolutionary Programming for Human Machine Interaction        #
#                                                               #
#    created by:        Hado van Hasselt                        #
#                       Tijn van der Zant                       #
#    copyright 2006                                             #
#################################################################

#    ind            stands for individual
#    pop            stands for population   
#    mut            stands for mutate or mutation
#    noSomeVars     stands for number of someVar's



import random
import copy
#import Utils.Utils

class Ind( object ):
    def __init__( self, genes, properties ):
        self.setGenes( genes )
        self.setProperties( properties )
        
    def __eq__( self, x ):
        return self._genes == x._genes
    
    def getGenes( self ):
        return self._genes
        
    def getProperties( self ):
        return self._properties
        
    def setGenes( self, genes ):
        self._genes = genes
        
    def setProperties( self, properties ):
        self._properties = properties
    
    def __str__( self ):
        return str( self._genes ) + '\n' + str( self._properties )

class EP( object ):
    def __init__( self,
                  geneTemplates,                            #dictionary of templates from which genes can be created
                  popSize = 30,
                  popType = "ea",                           #possible options at present are "ea" and "ss"
                  tournamentSize = 3,
                  mutBaseRate = 0.5,                        #base chance of mutation
                  mutRateIncrease = lambda x : x,           #increase of above chance. default: no change
                  mutRandomizeBaseRate = 0.8,               #chance of randomization when mutating
                  mutRandomizeRateIncrease = lambda x : x,  #increase of above chance. default: no change
                  crossOverBaseRate = 0.5,                  #base chance of crossover
                  crossOverRateIncrease = lambda x : x,     #increase of above chance. default: no change
                  createIndFromPopBaseRate = 0.1,           #base chance that ind is made from pop (instead of random)
                  createIndFromPopRateIncrease = lambda x : x + 0.01 ,  #increase of above chance
                  elitist = 1,
                  randomSeed=None ):
        """
        EP has one item that is mandatory. The EP can be created as:
        EP( { "proc0":[ 0 , 10, 20, 50 ], "proc1":[], "proc2":[ 10, 100 ] } )
        The argument is a dictionary of functions (the genes), the rest of the arguments are optional.
        """
        if not (popType == 'ea' or popType == 'ss'):
            error = "Population type %s is not known. Check initialisation of EP" % self._popType
            raise RuntimeError, error
        self._popType = popType
        self._setRandomSeed( randomSeed )
        self._checkGeneTemplates( geneTemplates )
        self._setGenes( geneTemplates )
        self._setPopSize( popSize )
        self._setTournamentSize( tournamentSize ) 
        self._setMutRate( mutBaseRate )
        self._setMutRateIncrease( mutRateIncrease )
        self._mutRandomizeRate = 0
        self._setMutRandomizeRate( mutRandomizeBaseRate )
        self._setMutRandomizeRateIncrease( mutRandomizeRateIncrease )
        self._setCrossOverRate( crossOverBaseRate )
        self._setCrossOverRateIncrease( crossOverRateIncrease )
        self._setCreateIndFromPopBaseRate( createIndFromPopBaseRate )
        self._setCreateIndFromPopRate( 0.0 )
        self._setCreateIndFromPopRateIncrease( createIndFromPopRateIncrease )
        self._setElistist( elitist )
        if popType == 'ea':
            self._childPop = self._createNewPop()
            self._parentPop = []
        elif popType == 'ss':
            self._parentPop = []
        self._noWinners = 0
        self._noSelections = 0
        self._noUpdates = 0
    
    def select( self ):
        """
        Returns a list of individuals with length equal to the tournament size. The higher the value of
        self._createIndFromPopRate, the fewer individuals are random and the more are based on the 
        parent population
        """
        self._noSelections += 1
        if self._popType == "ss":
            # if the algorithm is steady state-like, individuals for selection are created on the fly
            # either random or from the parent population.
            self._selection = self._createNewPop( self._parentPop, self._createIndFromPopRate, self._tournamentSize )
            # if _selection contains individuals that were also in _parentPop, remove from _parentPop:
            self._parentPop = [ ind for ind in self._parentPop if not ind in self._selection ]
        if self._popType == "ea":
            # if the algorithm based on multiple populations, individuals for selection are chosen from
            # the children population.
            if len( self._childPop ) < self._tournamentSize :
                if self._elitist:
                    self._childPop = self._parentPop
                    self._childPop += self._createNewPop( self._parentPop, 1.0, self._popSize - len( self._parentPop ) )
                else:
                    self._childPop = self._createNewPop( self._parentPop, 1.0, self._popSize ) # 1.0 means no random inds.
                random.shuffle( self._childPop )
                self._parentPop = []
            self._selection = self._childPop[ : self._tournamentSize ]
            del self._childPop[ : self._tournamentSize ]
        return self._selection
    
    def _updateParameters( self ):
        """
        Updates the variables controlling the chance of:
        - mutation
        - crossover
        - randomization when mutating
        - creating an individual from the parents population (instead of random)
        """
        self._mutRate               = self._mutRateIncrease( self._mutRate )
        self._mutRandomizeRate      = self._mutRandomizeRateIncrease( self._mutRate )
        self._crossOverRate         = self._crossOverRateIncrease( self._crossOverRate )
        self._createIndFromPopRate  = self._createIndFromPopRateIncrease( self._createIndFromPopRate )
        self._noUpdates += 1
    
    def _checkGeneTemplates( self, geneTemplates ):
        """
        Runs a check whether each gene template consists of a name and potentially an even number
        of boundries.
        """
        if not isinstance( geneTemplates, dict ):
            raise RuntimeError, "geneTemplates are not given in a dictionary."
        if len( geneTemplates ) == 0:
            raise RuntimeError, "Empty list of geneTemplates given."
        for gene in geneTemplates.keys():
            error = ""
            geneValue = geneTemplates[gene]
            if len( geneValue ) % 2 == 1 :
                error = "Incorrect number of parameter boundries in gene '" + gene + "'."
            i = 0
            while not error and i < len( geneValue ):
                if geneValue[i] > geneValue[i + 1]:
                    error = "Incorrectly speficied boundry parameters of gene '" + gene + "'."
                i += 2
            if error:
                raise RuntimeError, error

#################################################################################################
# mutation and randomize functions
#################################################################################################

    def _mutRatePerGene( self, ind ):
        """
        Given the probability of mutation per gene of 'ind'. This probability is determined by the number of
        genes in 'ind', so that longer individuals do not get mutated too much, compared to shorter individuals.
        When 'm' is the mutation probability parameter, the resulting probability of mutation per gene will be:
        1 - (1 - m)^(1/n), where 'n' is the number of genes.
        """
        noGenes = len( ind.getGenes() )
        if noGenes > 0:
            mutRatePerGene = 1.0 - (1.0 - self._mutRate)**(1.0/noGenes)
        else:
            mutRatePerGene = 0 # no genes, so no mutation-rate
        return mutRatePerGene

    def _mutate( self, ind ):
        """
        Returns a mutated copy of the given individual. There is a probability of self._mutRandomizeRate
        that only the parameters of the genes of the individual are mutated. Otherwise the genes themselves
        are mutated by deletion, insertion of new genes, replacement of genes or by swapping the positions
        of genes. After determining the type of mutation (randomization of parameters or of genes), the 
        probability of mutation for each gene is given by the method self._mutRatePerGene( ind ).
        """
        mutRatePerGene = self._mutRatePerGene( ind )
        mutatedInd = copy.deepcopy( ind )
        genes = mutatedInd.getGenes()
        noGenes = len( genes )
        g = 0
        if noGenes == 0:
            if random.random() < mutRatePerGene:
                genes.insert( 0, self._createRandomGene() )
        else:
            if random.random() < self._mutRandomizeRate: # can use parameter instead of 0.5 to weight chance of randomize parameters vs (swap, insert, delete)
                randomize = 1
            else:
                randomize = 0
            while g < noGenes:
                if random.random() < mutRatePerGene:
                    if randomize:
                        genes[g] = self._randomizeGene( genes[g] )    
                    else:
                        rnd = random.randint(1,4)
                        if rnd == 1: #deletion
                            del genes[g]
                            g        -= 1
                            noGenes -= 1
                        if rnd == 2: #insertion
                            genes.insert( g, self._createRandomGene() )
                            g        += 1
                            noGenes += 1
                        if rnd == 3: #swap
                            if g > 0:
                                genes[g], genes[g-1] = genes[g-1], genes[g]
                        if rnd == 4: #replace with new (random) gene
                            genes[g] = self._createRandomGene()
                g += 1
            if randomize:
                mutatedInd = Ind( genes, { 'lastMutation':'randomize' } )
            else:
                mutatedInd = Ind( genes, { 'lastMutation':'shuffle' } )
        return mutatedInd

    def _randomizeGene( self, gene ):
        name = gene[0]
        return self._createGene( name )        
        
    def _crossOver( self, ind1, ind2 ):
        """
        Returns a tuple containing two individuals. These individuals are the result of a crossover
        of the specified arguments with probability self._crossOverRate. Otherwise they are simply
        copies of these individuals.
        """
        genes1 = copy.deepcopy( ind1.getGenes() )
        genes2 = copy.deepcopy( ind2.getGenes() )
        if random.random() < self._crossOverRate:
            maxCrossOverPoint = min( len( genes1 ), len( genes2 ) )
            if maxCrossOverPoint > 1:
                crossOverPoint = random.randint( 1, maxCrossOverPoint-1 )
            else:
                crossOverPoint = maxCrossOverPoint
            
            crossedInd1 = Ind( genes1[ :crossOverPoint ] + genes2[ crossOverPoint: ], { 'lastMutation':'crossOver' } )
            crossedInd2 = Ind( genes2[ :crossOverPoint ] + genes1[ crossOverPoint: ], { 'lastMutation':'crossOver' } )
            
            del genes1, genes2
            
            return ( crossedInd1, crossedInd2 )
        else:
            return ( Ind( genes1, ind1.getProperties() ), Ind( genes2, ind2.getProperties() ) )
    

#################################################################################################
# creation functions
#################################################################################################

    def _createNewPop( self, sourcePop=None, fromPopRate=0.0, newPopSize=None, ):
        """
        Creates a new list of individuals.
        Optional arguments:
        - sourcePop: the population from which individuals can be made (default None)
        - fromPopRate: chance for each individual of begin made from sourcePop (default 0.0)
        - newPopSize: the size of the resulting population (default self._popSize)
        By default, the resulting population contains self._popSize random individuals.
        """
        if newPopSize == None:
            newPopSize = self._popSize
        if sourcePop == None:
            newPop = [ self._createRandomInd() for i in xrange( newPopSize ) ]   
        else:
            newPop = [ random.random() > fromPopRate and self._createRandomInd() or self._createIndFromPop( sourcePop ) for i in xrange( newPopSize ) ]
            # remove doubles:
            newPop = [ newPop[i] for i in xrange( newPopSize ) if newPop[i] not in newPop[:i] ]
            # if doubles are removed, fill gaps:
            while len( newPop ) < newPopSize:
                newPop.extend( [ random.random() > fromPopRate and self._createRandomInd() or self._createIndFromPop( sourcePop ) for i in xrange( newPopSize - len( newPop ) ) ] )
                newPop = [ newPop[i] for i in xrange( newPopSize ) if newPop[i] not in newPop[:i] ]
                # in case individuals from sourcePop are not divers enough, increase the probability of random individuals:
                fromPopRate /= 2.0
        return newPop
    
    def _createGene( self, name ):
        """
        Returns a gene from the template in self._geneTemplates with name 'name'. The parameters
        of the resulting gene are chosen from the boundries given in the template.
        """
        gene = [name]
        parameters = self._geneTemplates[ name ]
        for s in range( 0, len( parameters ), 2 ):
            if isinstance( parameters[s], int ):
                randNum = random.randint( parameters[s], parameters[s+1] )
            elif isinstance( parameters[s], float ):
                randNum = random.random()*( parameters[s+1] - parameters[s] ) + parameters[s]
            else:
                raise ValueError, "Function has incorrectly speficied parameters!"
            gene.append( randNum )
        return gene

    def _createRandomGene( self ):
        """
        Returns a gene create from a random chosen template from self._geneTemplates. Uses
        _createGene to return a gene with randomized parameters.
        """
        randomTemplate = random.choice( self._geneTemplates.keys()[:] )
        return self._createGene( randomTemplate ) 
    
    def _createIndFromPop( self, pop ):
        """
        Returns a new individual by crossover and mutation of two random individuals from the
        given population.
        """
        if len( pop ) == 0:
            newInd = self._createRandomInd()
        else:
            if len( pop ) == 1:
                ind1Index = 0
                ind2Index = 0
            else:
                ind1Index = random.randint( 0, len( pop ) - 1 )
                ind2Index = random.randint( 0, len( pop ) - 1 )
            
            newInd = random.choice( self._crossOver( pop[ ind1Index ], pop[ ind2Index ] ) )
            newInd = self._mutate( newInd )
        
        return newInd
    
    def _createRandomInd( self, noGenes=None ):
        """
        Returns a new random individual. The individual is a tuple containing:
        - a list of 1 to len( self._geneTemplates ) genes and
        - a dictionary of properties.
        If noGenes is set, that is the number of genes the individual will have.
        """
        if noGenes == None:
            noGenes = random.randint( 1, len( self._geneTemplates ) )
            #noGenes = int((random.random()**2)*len( self._geneTemplates )) # bias towards lower numbers of functions
        return Ind([ self._createRandomGene() for x in xrange( noGenes ) ], { 'lastMutation':None } )

#################################################################################################
# internal setters functions
#################################################################################################
    
    def _setRandomSeed( self, seed ):
        random.seed( seed )
    
    def _setCreateIndFromPopRate( self, createIndFromPopRate ):
        self._createIndFromPopRate = createIndFromPopRate
    
    def _setCreateIndFromPopRateIncrease( self, increaseFunction ):
        self._createIndFromPopRateIncrease = increaseFunction
    
    def _setCrossOverRate( self, crossOverRate ):
        self._crossOverRate = crossOverRate
        
    def _setCrossOverRateIncrease( self, crossOverRateIncrease ):
        self._crossOverRateIncrease = crossOverRateIncrease
        
    def _setCreateIndFromPopBaseRate( self, bRate ):
        self._createIndFromPopBaseRate = bRate
        
    def _setPopSize( self, popSize ):
        self._popSize = popSize
    
    def _setGenes( self, geneTemplates ):
        self._geneTemplates = geneTemplates
            
    def _setTournamentSize( self, tSize ):
        self._tournamentSize = tSize
        
    def _setMutRate( self, mutRate ):
        self._mutRate = mutRate
    
    def _setMutRateIncrease( self, mutRateIncrease ):
        self._mutRateIncrease = mutRateIncrease
    
    def _setMutRandomizeRate( self, mutRRate ):
        self._mutRandomizeRate = mutRRate
        
    def _setMutRandomizeRateIncrease( self, mutRIncrease ):
        self._mutRandomizeRateIncrease= mutRIncrease
        
    def _setElistist( self, elitist ):
        self._elitist = elitist
        
        
#################################################################################################
# interface functions
#################################################################################################

    def getPopSize( self ):
        return self._popSize
        
    def getCreateIndFromPopRate( self ):
        return self._createIndFromPopRate

    def setWinner( self, winner ):
        """
        Needs the winner of the selection as input.
        (Take note: the index, not the individuals, is required!)
        """
        if self._noWinners == 0:
            self._setCreateIndFromPopRate( self._createIndFromPopBaseRate )
        self._noWinners += 1
        if self._selection[ winner ] in self._parentPop:
            self.setNoWinner()
        else:
            self._parentPop.append( self._selection[ winner ] )
            self._updateParameters()
    
    def setNoWinner( self ):
        if self._popType == 'ea':
            pop = copy.deepcopy( self._childPop + self._parentPop ) # copy to ensure no individuals disappear from _childPop or _parentPop
            self._childPop.extend( self._createNewPop( pop, self._createIndFromPopRate, self._tournamentSize ) )
            # at this moment there are possibly doubles in _childPop, maybe fix?
            random.shuffle( self._childPop )
        elif self._popType == 'ss':
            pass

    def getMutRate( self ):
        return self._mutRate
    
    def setCreateIndFromPopRateIncrease( self, increaseFunction ):
        self._setCreateIndFromPopRateIncrease( increaseFunction )


#################################################################################################
# EP for the soccer 3D
#################################################################################################

class EP4S3D( EP ):
	def _createRandomInd( self, noGenes=None ):
		"""
		Returns a new random individual. The individual is a tuple containing:
		- a list of 1 to len( self._geneTemplates ) genes and
		- a dictionary of properties.
		If noGenes is set, that is the number of genes the individual will have.
		"""
		if noGenes == None:
			noGenes = len( self._geneTemplates ) 
			#noGenes = int((random.random()**2)*len( self._geneTemplates )) # bias towards lower numbers of functions
		return Ind([ self._createGene( name ) for name in self._geneTemplates ], { 'lastMutation':None } )

	def _createGene( self, name ):
		"""
		Returns a gene from the template in self._geneTemplates with name 'name'. The parameters
		of the resulting gene are chosen from the boundries given in the template.
		"""
		gene = [name]
		parameters = self._geneTemplates[ name ]
		for s in range( 0, len( parameters ), 2 ):
			if isinstance( parameters[s], int ):
				randNum = random.randint( parameters[s], parameters[s+1] )
			elif isinstance( parameters[s], float ):
				randNum = random.random()*( parameters[s+1] - parameters[s] ) + parameters[s]
			else:
				raise ValueError, "Function has incorrectly speficied parameters!"
			gene.append( randNum )
		return gene

	def _mutate( self, ind ):
		"""
		Returns a mutated copy of the given individual. There is a probability of self._mutRandomizeRate
		that only the parameters of the genes of the individual are mutated. Otherwise the genes themselves
		are mutated by deletion, insertion of new genes, replacement of genes or by swapping the positions
		of genes. After determining the type of mutation (randomization of parameters or of genes), the 
		probability of mutation for each gene is given by the method self._mutRatePerGene( ind ).
		"""
		mutRatePerGene = self._mutRatePerGene( ind )
		mutatedInd = copy.deepcopy( ind )
		genes = mutatedInd.getGenes()
		noGenes = len( genes )
		g=0
		while g < noGenes:
			if random.random() < mutRatePerGene:
				genes[g] = self._randomizeGene( genes[g] )    
			g += 1            
		mutatedInd = Ind( genes, { 'lastMutation':'randomize' } )
		return mutatedInd
