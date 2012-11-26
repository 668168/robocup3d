#ifndef _BATS_MOVEJOINTTO_HH_
#define _BATS_MOVEJOINTTO_HH_

#include "behavior.hh"
#include "types.hh"

#define MAXJOINTSPEED 10
namespace bats
{
  /** Behavior: Move an arbitrary joint to an arbitrary angle
   *
   * Move an arbitrary joint to an arbitrary angle. The index of the joint to move is read from the behavior's parameters in the configuration:
   * <code><pre>
   *  \<behavior type="MoveJoint" id="moveLeftHip">
	 *    \<param>
	 *      \<joint>1\</joint>
   *    \</param>        
   *  \</behavior>
   * </pre></code>
   */
  class MoveJointTo : public Behavior
  {
      double d_gain;
      Types::Joint d_joint;
      
      /** Generate the current goal for a slot
       *
       * @param step Step number in the sequence
       * @param slot Slot number in the step
       * @returns goal: Speed - the angular velocity in radians needed to move the joint
       */
      virtual rf<Goal> generateGoal(unsigned step, unsigned slot);

      virtual rf<State> getCurrentState() { return 0; }

      /** Get the capability of the behavior to achieve goal g from state s
       *
       * @param s Expected state: none
       * @param g Expected goal: Angle - absolute angle in radians to move the joint to, MaxSpeed (optional) - maximum angular velocity to use (negative value means double normal value)
       * @returns Always medium confidence
       */
      virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g) { return ConfidenceInterval(0.5, 0.2); }

		public:
			MoveJointTo(std::string const &id, std::string const &playerClass);
  };
};

#endif
