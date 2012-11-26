
#ifndef _BATS_MOVEHINGEJOINT_HH_
#define _BATS_MOVEHINGEJOINT_HH_

#include "primitivebehavior.hh"
#include "types.hh"

namespace bats
{
  /** PrimitiveBehavior: Move a hinge joint
   *
   * Moves a single hinge joint. The index of the joint to move is read from the behavior's parameters in the configuration:
   * <code><pre>
   *  \<behavior type="MoveHingeJoint" id="moveLeftHip">
	 *    \<param>
	 *      \<joint>1\</joint>
   *    \</param>        
   *  \</behavior>
   * </pre></code>
   */
  class MoveHingeJoint : public PrimitiveBehavior
  {
    Types::Joint d_joint;
    
    rf<State> getCurrentState() { return 0; }

    /** Get the capability of the behavior to achieve goal g from state s
     *
     * @param s Expected state: none
     * @param g Expected goal: Speed - desired angular motor speed in radians per second
     * @returns Always high confidence
     */
    ConfidenceInterval getCapability(rf<State> s, rf<Goal> g) { return ConfidenceInterval(1.0, 0); }

    virtual bool run();
    
  public:
    MoveHingeJoint(std::string const &id, std::string const &playerClass);
  };
};

#endif
