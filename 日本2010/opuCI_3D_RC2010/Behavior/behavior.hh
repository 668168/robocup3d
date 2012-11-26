#ifndef _BATS_BEHAVIOR_HH_
#define _BATS_BEHAVIOR_HH_

#include "rf.hh"
#include "refable.hh"
#include "ast.hh"
#include "predicate.hh"
#include "idistribution3d.hh"
#include "cerebellum.hh"
#include "commonfunction.hh"

#include "xmlnode.hh"
#include "conf.hh"

#include <ostream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
#include <map>
#include <sstream>

#define MIN_C 0.3

namespace bats
{
    /** Behavior class
     *
     * This is the Behavior class, the building block of the BATS agents. 
     * It supplies the basic architecture to set up a hierarchy of behaviors. 
     * A behavior can be given a goal to achieve. 
     * New behaviors should inherit from this class and implement the following methods:
     * <dl>
     *   <dt>rf<Goal> generateGoal(unsigned step, unsigned slot)</dt>
     *   <dd>This method is called to generate a subgoal for the subbehaviors in a slot.
     *       The goal is a State description tree containing nodes of type andType and varType.</dd>
     *   <dt>rf<State> getCurrentState()</dt>
     *   <dd>For different behaviors different descriptions of the current state are important. 
     *       Implement this method to let the behavior create it's own description. 
     *       This description will be passed to getCapability.</dd>
     *   <dt>ConfidenceInterval getCapability(State s, Goal g)</dt>
     *   <dd>With this method the behavior informs the superbehavior of the capability of achieving a certain goal starting from a certain state.</dd>
     * </dl>
     */
    class Behavior : public RefAble
    {
    public:
    
	/// Enumeration of node types for behavior tree and state tree
	enum NodeType
	{
	    NONE,
	    sequenceType,
	    andType,
	    orType,
	    behaviorType,
	    varType
	};

	///Defines a range between two values
	class Range: public std::pair<double, double> 
	{
    	public:

	    /** Range
	     *
	     * @param f Start value
	     * @param s End value
	     */
	    Range(double f, double s)
    		:
    		std::pair<double, double>(f, s)
		{}
    		
	    Range()
    		:
    		std::pair<double, double>()
		{}
    	
	    Range(Range const &other)
    		:
    		std::pair<double, double>(other.first, other.second)
		{}
    	
	    /**
	     * @returns the mean of the range: \f$ \mu \f$
	     */
	    double mean()
		{
		    return (first+second)/2.0;
		}

	    /**
	     * @returns the absolute mean of the range: <br>
	     * \f$ \mu = {{max - min} \over 2} : if max \geq min\f$ <br>
	     * \f$ \mu = -{{max - min} \over 2} : if max < min\f$ 
	     */
	    double absMean()
		{
		    return std::fabs(mean());
		}
		
	    double getFirst()
		{
		    return first;
		}
		
	    double getSecond()
		{
		    return second;
		}
    	

	}; 
  
	/// State variable consisting of a name and a range value
	typedef std::pair<std::string, Range> StateVar;
  
	/// Confidence interval. First value is the expected value/sample mean, the second the standard deviation
	typedef std::pair<double, double> ConfidenceInterval;

	/// Node to hold a state variable
	class StateVarNode : public AST::Node
	{
	    StateVar d_var;
	public:
	    StateVarNode(StateVar var) : Node(varType), d_var(var) {}

	    /**
	     *  Create a StateVarNode with StateVar(name,Range(r0,r1)).
	     */
	    StateVarNode(std::string const name, double r0, double r1) : Node(varType), d_var(StateVar(name,Range(r0,r1))) {}
        
	    bool match(std::string const &query) const { return d_var.first == query; }
        
	    /**
	     * @returns the value of the state variable
	     */
	    StateVar getVar() { return d_var; }
        
	};

	/// Conjunction Node
	class AndNode : public AST::Node {

	public:

	    AndNode() : Node(andType) {}

	    /**
	     *  Create an AndNode with one state var with name and range(r0,r1).
	     */
	    AndNode(std::string const &name, double r0, double r1) : Node(andType)
		{
		    addVar(name,r0,r1);
		}
      
	    /**
	     *  Add a state variable with name and range (r0,r1).
	     */
	    void addVar(std::string const &name, double r0, double r1)
		{
		    addChild(new StateVarNode(name,r0,r1));
		}
      
	    /**
	     * Add state variables based on a 3D distribution. The variables get the names nameX, nameY and nameZ. The range of a variable is set to \f$ (\mu - {1 over 2} \sqrt{s^2}, \mu + {1 over 2} \sqrt{s^2}) \f$
	     */
	    void addVar(std::string const &name, rf<IDistribution3D> const &pos)
		{
		    Vector3D mu = pos->getMu();
		    //			  pos->getMu(mu);
		    Matrix9D sigma = pos->getSigma();
		    //  			pos->getSigma(sigma);
		    double stdx2 = 2*sqrt(sigma.get(0,0));
		    double stdy2 = 2*sqrt(sigma.get(1,1));
		    double stdz2 = 2*sqrt(sigma.get(2,2));
		    addVar(name+"X", mu.getX() - stdx2, mu.getX() + stdx2);
		    addVar(name+"Y", mu.getY() - stdy2, mu.getY() + stdy2);
		    addVar(name+"Z", mu.getZ() - stdz2, mu.getZ() + stdz2);
		}

	    /**
	     * Add state variables based on a 3D vector. The variables get the names nameX, nameY and nameZ.
	     */
	    void addVar(std::string const &name, Vector3D const &pos)
		{

		    addVar(name+"X", pos.getX(), pos.getX());
		    addVar(name+"Y", pos.getY(), pos.getY());
		    addVar(name+"Z", pos.getZ(), pos.getZ());
		}
      

	};

	/// Disjunction Node
	class OrNode : public AST::Node {

	public:

	    OrNode() : Node(orType) {}

	    /**
	     *  @returns a new conjunction which has been appended to the children of this node
	     */
	    rf<AndNode> addConjunct()
		{
		    return rf_cast<AndNode>(addChild(new OrNode));
		}

	};

	/** A State Node
	 *
	 * Root node of a full state tree. Children should be disjuncts, grandchildren conjuncts and grandgrandchildren state variable nodes
	 */
	class StateNode : public AST::Node {

	public:

	    StateNode(unsigned type = 0) : Node(type) {}

	    /**
	     *  @returns a new disjunction which has been appended to the children of this node
	     */
	    rf<OrNode> addDisjunct()
		{
		    return rf_cast<OrNode>(addChild(new OrNode));
		}

	    /** 
	     *  @returns a new disjunction which has been appended to the children of this node, containing a new conjunction
	     */
	    rf<AndNode> addBoth()
		{
		    rf<OrNode> dis(rf_cast<OrNode>(addChild(new OrNode)));
		    return rf_cast<AndNode>(dis->addConjunct());
		}

	    /**
	     * @returns a vector containing the values of the state variables nameX, nameY and nameZ
	     */
	    Vector3D getVector(std::string const &name) const
		{
		    rf<StateVarNode> X = rf_cast<StateVarNode>(findDeep(name + "X"));
		    rf<StateVarNode> Y = rf_cast<StateVarNode>(findDeep(name + "Y"));
		    rf<StateVarNode> Z = rf_cast<StateVarNode>(findDeep(name + "Z"));

//	std::cout << "OK!!!" << std::endl;
//	std::cout << "(" << X << ", " << Y << ", " << Z << ")" << std::endl;
//	if (!X)
//	    std::cout << "!X" << std::endl;
//	if (!Y)
//	    std::cout << "!Y" << std::endl;
//	if (!Z)
//	    std::cout << "!Z" << std::endl;

		    if (!X || !Y || !Z)
			throw std::runtime_error("Vector var node not found in Goal.");

		    StateVar x = X->getVar();
		    StateVar y = Y->getVar();
		    StateVar z = Z->getVar();

		    return Vector3D(x.second.mean(), y.second.mean(), z.second.mean());
		}
      
	    /**
	     * @returns the mean of the state variable @name
	     */
	    double getMean(std::string const &name) const
		{
		    rf<StateVarNode> node = rf_cast<StateVarNode>(findDeep(name));
		    assert(node);
		    StateVar x = node->getVar();
		    return x.second.mean();
		}
	};
 
	/// A state is a conjunction of state variables, implemented as a tree
	typedef StateNode State;
  
	/// A goal is a state
	typedef State Goal;

   
	/// Node to hold a behavior
	class BehaviorNode : public AST::Node
	{
	    rf<Behavior> d_behavior;
        
	public:
	    BehaviorNode(rf<Behavior> behavior) : Node(behaviorType), d_behavior(behavior) {}
        
	    /**
	     * @returns the behavior in this node
	     */
	    rf<Behavior> getBehavior() { return d_behavior; }
	};
      
    protected:
	/// The behavior's name
	std::string d_name;

	/// The behavior's id  
	std::string d_id;

	/** Tree describing sub behavior semantics
	 *
	 *  This tree is built up as follows:
	 *  - Root node of type sequenceType
	 *  - Sequence steps: the behavior tries to do these steps in the given sequence. These nodes have type andType, because nodes underneath these can be run together
	 *  - Slots: every sequence step has 1 or more slots. These nodes are of type orType, because only one behavior in a slot can be picked (exclusive or)
	 *  - Behaviors: in every slot there can be 1 or more behaviors. These nodes are of type behaviorType
	 */
	rf<AST::Node> d_tree;
    
	/// Current step index of the sequence
	int d_curStep;
    
	/// The goal we are trying to achieve
	rf<Goal> d_goal;
  
	/// Whether the behavior was reset before the current getCapability call, true between achieveGoal and reset, false otherwise.
	bool d_reset;
    
	/// The player class (defined in the configuration)
	std::string d_playerClass;

	/// Confidence interval showing the expected capability of achieving the goal
	ConfidenceInterval d_c;
  
	/// Action this behavior wants to perform. This is only used by primitive behaviors
	rf<Cerebellum::Action> d_action;
    
	/// Whether the behavior should commit (defined in the configuration)
	bool d_commit;
    
	/// Whether the behavior is committed
	bool d_committed;
    
	/// Whether the last ran children are committed
	bool d_childrenCommitted;
    
	/// 'Should Commit If Children Commit'
	bool d_scicc;
    
	/// Server time of the last time update is ran
	double d_lastUpdate;

	/// List of subbehaviors that this behavior chose last time step
	std::vector<rf<Behavior> > d_lastChosen;
        
	/** Generate the current goal for a slot
	 *
	 * @param step Step number in the sequence
	 * @param slot Slot number in the step
	 */
	virtual rf<Goal> generateGoal(unsigned step, unsigned slot) = 0;
    
	/// Get the current state. This state is passed to getCapability
	virtual rf<State> getCurrentState() = 0;
    
	/// Get the capability of the behavior to achieve goal g from state s
	virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g) = 0;
    
	/// Try doing the next step in the sequence
	bool doNextStep();
    
	/// Try doing the current step in the sequence
	bool doCurrentStep();
    
	/// Perform the subbehaviors that this behavior chose last time step again
	bool doLastChosen();
    
	/// Recursively generate an empty configuration template
	void generateConf(std::ostream& out, rf<AST::Node> node, unsigned& index);

	/// Add this behavior to the list of action-command behaviors, signalling that this behavior wants to perform an action
	void addToActionCommandBehaviors() { s_actionCommandBehaviors.insert(this); }
    
	/// Remove this behavior from the list of action-command behaviors
	void removeFromActionCommandBehaviors() { s_actionCommandBehaviors.erase(this); }
    
	/// Global map containing all the agent's behaviors
	static std::map<std::string, rf<Behavior> > s_behaviors;
    
	/// The root behavior of the agent's hierarchical behavior structure
	static rf<Behavior> s_win;
    
	/// list of behaviors that want to perform an action
	static std::set<rf<Behavior> > s_actionCommandBehaviors;

	/// \todo Bram: kan jij de Behavior::getParam* methodes documenteren?
	XMLNode getParam(std::string const &name) const { XMLNodeSet ns(getParams(name)); if(ns) return ns.front(); return 0; }
    
	template <typename T> T getParam(std::string const &xpath, T def) const
	    {
		XMLNodeSet ns(getParams(xpath));
		if(ns && !ns.empty())
		{
		    std::istringstream s(ns.front().getContent());
		    s >> def;
		}
		return def;
	    }
    
	XMLNode getParam() const { XMLNodeSet ns(getParams("")); if(ns) return ns.front(); return 0; }
	XMLNodeSet getParams(std::string const &path) const
	    {
		Conf& conf = Conf::getInstance();
		return conf.getParams(d_playerClass, d_id, path);
	    }
	XMLNodeSet getMyParams() const;
    
    
	/// Set the agent's agent class (defined by the configuration)
	void setPlayerClass(std::string const &pc)
	    {
		d_playerClass = pc;
	    }
		
    public:
	Behavior(std::string const &name, std::string const &id);
	Behavior(std::string const &name, std::string const &id, std::string const &playerClass);
    
	virtual ~Behavior() {}
    
	/** Get the behavior's name
	 *
	 * @returns the behavior's type name
	 */
	std::string getName() { return d_name; }
    
	/** Get the behavior's ID
	 *
	 * @returns the behavior's ID
	 */
	std::string getId() { return d_id; }
    
	/** Add a behavior to one of the behavior's slots
	 *
	 * @param behavior The behavior to add
	 * @param step Step number of the slot in the sequence
	 * @param slot Slot number in the step
	 */
	void addToSlot(rf<Behavior> behavior, unsigned step, unsigned slot);

	/// Called at the beginning of a timestep in which the behavior might be run to update it's internal state
	virtual void update();
    
	/// Set goal, returns the capability of achieving it from the current state
	ConfidenceInterval setGoal(rf<Goal> g);
        
	/// Get the capability of this behavior of achieving the last set goal
	ConfidenceInterval getCapability() const { return d_c; }
    
	/** Try to achieve the goal previously set
	 *
	 * First tries to go to the next step in the sequence. Generates goals for the slots in the next step and checks the capability of the behaviors in the slots of achieving those goals.
	 * If this fails, the current slot is tried.
	 * \todo This method is virtual so primitive behaviors can overload it, perhaps main loop should check the type instead?
	 * @returns False if neither the next nor the current step in the sequence can be done, true otherwise
	 */
	virtual bool achieveGoal();
    
	/// Get the action command that this behavior wants to send to the server
	rf<Cerebellum::Action> getAction() const { return d_action; }
    
	/// Generate an empty configuration template describing the slots that this behavior has
	void generateConf(std::ostream& out);
    
	/// Reset the behavior to his initial state. Called when behavior is not (longer) chosen by its superbehavior
	virtual void reset();
    
	/// Tell this behavior whether he should commit when possible
	void shouldCommit(bool c) { d_commit = c; }
    
	/// Check whether this behavior should commit when possible
	bool shouldCommit() { return d_commit; }
    
	/// Tell this behavior whether he should commit when its last chosen children are committed
	void shouldCommitIfChildrenCommitted( bool c) { d_scicc = c; }
    
	/// Check whether this behavior should commit when its last chosen children are committed
	bool shouldCommitIfChildrenCommitted() { return d_scicc; }
    
	/// Check whether the behavior is committed (should be ignored if shouldCommit returns false)
	bool isCommitted() { return d_committed; }
    
    
    
	/// Identify yourself
	std::string ident() { return d_id; }
    
	/// Get last server time at which update was called
	double getLastUpdate() { return d_lastUpdate; }
    
	/// Get the root behavior of the agent's hierarchical behavior structure 
	static rf<Behavior> getWin() { return s_win; }
    
	/// Build a tree of behaviors based on an XML node and a player class. Calls itself recursively
	static rf<Behavior> buildTree(XMLNode& b, std::string playerClass);
    
	/// Create the behaviors that are defined in Conf. Uses buildTree
	static void createBehaviors();
    
	/// Get a behavior from the global behaviors list
	static rf<Behavior> getBehavior(std::string id) { return s_behaviors[id]; }
    
	/// Get the set of behaviors that want to perform action commands
	static std::set<rf<Behavior> > getActionCommandBehaviors() { return s_actionCommandBehaviors; }
    
	/// Clear the set of behaviors that want to perform action commands
	static void clearActionCommandBehaviors() { s_actionCommandBehaviors.clear(); }
    };
  
    /// A simple class used to sort BehaviorNodes by descending capability
    class CapabilityCompare
    {
    public:
	CapabilityCompare() {}
	bool operator()(rf<AST::Node> a, rf<AST::Node> b)
	    {
		Behavior::ConfidenceInterval c1 = rf_cast<Behavior::BehaviorNode>(a)->getBehavior()->getCapability();
		Behavior::ConfidenceInterval c2 = rf_cast<Behavior::BehaviorNode>(b)->getBehavior()->getCapability();
		return c1.first + c1.second > c2.first + c2.second;
	    }
    };

    typedef rf<Behavior> RBehavior;
          
};

#endif
