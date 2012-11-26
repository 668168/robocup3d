#ifndef _BATS_CEREBELLUM_HH_
#define _BATS_CEREBELLUM_HH_

#include "types.hh"
#include <vector>
#include "socketcomm.hh"

namespace bats
{
  /** Cerebellum
   *
   * The cerebellum integrates different actions. Useful when different behaviors that control the same joints run in parallel
   */
  class Cerebellum
  {
  public:
    /// Base Action structure 
    struct Action : public RefAble
    {
      enum ActionType
	{
	  NONE,               ///< No action (only used internally)
	  MOVEJOINT,          ///< Move a joint (hinge joint or part of a universal joint)
	  MOVEHINGEJOINT,     ///< Move a hinge joint
	  MOVEUNIVERSALJOINT, ///< Move a universal joint
	  BEAM                ///< Beam
	};
			
      /// Type of an action
      ActionType type;

      Action(ActionType t = NONE)
	: type(t)
      {}
    };
		
    /// Move a joint (hinge joint or part of a universal joint)
    struct MoveJointAction : public Action
    {
      /// The joint (hinge joint or part of a universal joint) to move
      Types::Joint joint;
			
      /// The angular velocity to move the joint with (radians per second)
      double speed;
			
      MoveJointAction(Types::Joint j, double s)
	: Action(MOVEJOINT), joint(j), speed(s)
      {}
    };

    /// Move a hinge joint
    struct MoveHingeJointAction : public Action
    {
      /// The hinge joint to move
      Types::Joint joint;
			
      /// The angular velocity to move the joint with (radians per second)
      double speed;
			
      MoveHingeJointAction(Types::Joint j, double s)
	: Action(MOVEHINGEJOINT), joint(j), speed(s)
      {}
    };
		
    /// Move a universal joint
    struct MoveUniversalJointAction : public Action
    {
      /// The universal joint to move
      Types::Joint joint;
			
      /// The angular velocity to move the joint with along its first axis (radians per second) 
      double speed1;
			
      /// The angular velocity to move the joint with along its second axis (radians per second)
      double speed2;
			
      MoveUniversalJointAction(Types::Joint j, double s1, double s2)
	: Action(MOVEUNIVERSALJOINT), joint(j), speed1(s1), speed2(s2)
      {}
    };
		
    /// Beam
    struct BeamAction : public Action
    {
      /// The position to beam to
      Vector3D pos;
		  
      BeamAction(Vector3D const& p)
	: Action(BEAM), pos(p)
      {}
    };

  private:
    std::vector<rf<Action> > d_actions;
		

    Cerebellum(Cerebellum const &); // NI
    Cerebellum &operator=(Cerebellum const &); // NI

    Cerebellum() {}
  public:
		
    /** Add an action into the cerebellum
     *
     * @param a The action to perform
     */
    void addAction(rf<Action> a);
		
    /** Output action commands
     *
     * Integrates the stored actions and outputs the resulting commands to the given SocketComm. After sending the list of stored actions is cleared.
     * @param comm The SocketComm used to communicate with the server
     */
    void outputCommands(SocketComm& comm);
		
    /// Get a singleton instance of the Cerebellum
    static Cerebellum& getInstance()
    {
      static Cerebellum instance;
      return instance;
    }

  };
	
	
}

#endif
