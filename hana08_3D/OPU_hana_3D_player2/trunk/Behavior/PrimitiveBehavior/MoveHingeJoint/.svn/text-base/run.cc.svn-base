#include "movehingejoint.hh"

#include "socketcomm.hh"

#define DEBUGLEVEL 4
#include "debug.hh"

using namespace bats;

bool MoveHingeJoint::run()
{
  //_debugLevel4("MoveJoint is being run!");
  //  Parser parser;

  rf<StateVarNode> speedNode = rf_cast<StateVarNode>(d_goal->findDeep("Speed"));

  if (!speedNode)
  {
    _debugLevel4("MoveHingeJoint doesnt have Speed node in goal.");
    return false;
  }
    
  double speed = speedNode->getVar().second.mean();
  d_action = new Cerebellum::MoveHingeJointAction(d_joint, speed);
  
  addToActionCommandBehaviors();
  
  return true;
}
