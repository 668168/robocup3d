#include "movejoint.hh"

#include "socketcomm.hh"

#define DEBUGLEVEL 4
#include "debug.hh"

#include "normaldistribution1.hh"
#include "worldmodel.hh"

#include <iostream>

using namespace bats;
using namespace std;

bool MoveJoint::run()
{
  //_debugLevel4("MoveJoint is being run!");
  //  Parser parser;

  rf<StateVarNode> speedNode = rf_cast<StateVarNode>(d_goal->findDeep("Speed"));

  if (!speedNode)
  {
    _debugLevel4("MoveJoint doesnt have Speed node in goal.");
    return false;
  }
    
  //NormalDistribution1D curAngle = WorldModel::getInstance().getJointAngle(d_joint);

  double speed = speedNode->getVar().second.mean();

  // Predict the position in which the joint will be in the next timestep.
  //  double predictedAngle = curAngle.getMu() + speed*0.02;

  /*
  if (d_max < M_PI)
    cerr
      << "Joint: " << d_joint
      << " Current angle: " << curAngle.getMu()
      << " predictedAngle: " << predictedAngle
      << " max: " << d_max << endl;
  */

  // Calculate the force to give to reach the max angle in the next timestep.
  //  if (predictedAngle > d_max)
  //    speed = 0.0;
  //    speed = (d_max - curAngle.getMu()) / 0.02;

  // Calculate the force to give to reach the min angle in the next timestep.
  //  if (predictedAngle < d_min)
  //    speed = 0.0;
  //    speed = (d_min - curAngle.getMu()) / 0.02;

  d_action = new Cerebellum::MoveJointAction(d_joint, speed);
  
  addToActionCommandBehaviors();
  
  return true;
}
