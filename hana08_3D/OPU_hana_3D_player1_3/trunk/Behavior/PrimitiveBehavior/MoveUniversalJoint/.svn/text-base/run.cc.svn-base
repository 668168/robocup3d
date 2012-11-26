#include "moveuniversaljoint.hh"

#include "socketcomm.hh"

#define DEBUGLEVEL 4
#include "debug.hh"

using namespace bats;

bool MoveUniversalJoint::run()
{
  //_debugLevel4("MoveJoint is being run!");
  //  Parser parser;

  rf<StateVarNode> jointNode = rf_cast<StateVarNode>(d_goal->findDeep("Joint"));
  rf<StateVarNode> speedNode = rf_cast<StateVarNode>(d_goal->findDeep("Speed"));

  if (!speedNode || !jointNode)
  {
    _debugLevel4("MoveUniversalJoint doesnt have Joint node or Speed node in goal.");
    return false;
  }
  
  d_lastSpeeds[(unsigned)(jointNode->getVar().second.mean() - d_joint)] = speedNode->getVar().second.mean();
  
  d_action = new Cerebellum::MoveUniversalJointAction(d_joint, d_lastSpeeds[0], d_lastSpeeds[1]);
  
  addToActionCommandBehaviors();
  
  return true;
}
