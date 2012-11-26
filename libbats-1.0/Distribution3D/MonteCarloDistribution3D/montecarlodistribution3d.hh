/*
 *  Little Green BATS (2008), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	November 1, 2008
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef __INC_BATS_MONTECARLODISTRIBUTION_HH_
#define __INC_BATS_MONTECARLODISTRIBUTION_HH_

#include "../distribution3d.hh"
#include <vector>

namespace bats {

  /** \brief The MonteCarloDistribution3D class
   *
   * The Monte Carlo Distribution is a distribution represented by a set of particles.
   * Advantage: can represent complex distributions. Disadvantage: more memory and computational
   */
  class MonteCarloDistribution3D : public Distribution3D
  {
  public:
    /// Particle structure
    struct Particle
    {
      Vector3D coords;  ///< Particle position
      double p;         ///< Probability
    };

  private:
    unsigned int          d_nParticles;
    std::vector<Particle> d_particles;
  
    void rouletteSelect(Particle &particle) const;
  
  public:
    /**\brief nParticles constructor
     * Create the MonteCarloDistribution with n particles.
		 *
     * \param nParticles The number of particles in the distribution
		 */
    MonteCarloDistribution3D(int nParticles = 0) : d_nParticles(nParticles), d_particles(nParticles) {}
    virtual ~MonteCarloDistribution3D() {}
    
    /** Get distribution size_t
      *
      * @return Number of particles in the distribution
      */
    unsigned int getSize() const { return d_nParticles; }
    
    /** Initialize distribution
     *
     * Initialize the distribution given a normal distribution \f$ N(\mu, \Sigma) \f$
     */
    virtual void init(Vector3D const &mu, Matrix9D const &sigma);

    /** Add particle
     *
     * Add a particle to the distribution
     */
    virtual void addParticle(Particle &particle) { d_particles.push_back(particle); d_nParticles = d_particles.size(); }

    /** Normalize distribution
     *
     * Normalize particles so the sum of their P values equals 1
     */
    void normalize();

    /** Get Mu
     *
     * Retrieve \f$ \mu \f$: the mean/average/expected value of the distribution. \f$ \mu \f$ is the particle with the highest probability
     * @param mu 3D Vector that mu will be placed into
     */
    virtual void getMu(Vector3D &mu) const;
        
    /** Get Sigma
     *
     * Retrieve \f$ \Sigma \f$: the covariance matrix/expected deviationof the distribution. This will be an estimation when the distribution is non-normal
     * @param sigma 3x3 Matrix that Sigma will be placed into
     */
    virtual void getSigma(Matrix9D &sigma) const;
        
    /** Get P(x)
     *
     * Retrieve P(x): the probability of X = x
     * @param x 3D Vector containing the coordinates of x
     * @return P(x) with \f$ 0 \leq P(x) \leq 1 \f$
     */
    virtual double getP(Vector3D const &x) const;

    /** Get X
     *
     * Retrieve a random value x dependant on the distribution. The particle is selected using roulette wheel selection: every particle gets an area of the wheel proportional to its likelyhood (P). The wheel is spun and the particle whose area it stops at wins.
     * @param x 3D Vector that the random value will be placed in
     */
    virtual void getX(Vector3D &x) const;
      
    /** Predict distribution
     *
     * Predict/move the distribution given a specific movement model
     * @param movementModel The <B>relative</B> movement model used to update the distribution.
     */
    virtual void predict(rf<Distribution3D> const& movementModel);
      
    /** Update distribution
     *
     * Update the distribution given a measurement and the measurement model for that measurement
     * @param measurementModel The measurement model where mu is the measured position (position of detected object - own position relative to object and Sigma the uncertainty of the measurement.
     */
    virtual void update(rf<Distribution3D> const &measurementModel);
  };

};

#endif // __INC_BATS_MONTECARLODISTRIBUTION_HH_
