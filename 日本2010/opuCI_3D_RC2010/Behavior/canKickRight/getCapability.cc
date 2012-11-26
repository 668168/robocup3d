#include "cankickright.ih"

Behavior::ConfidenceInterval CanKickRight::getCapability(rf<Behavior::State> s, rf<Behavior::Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  // check toe and ball position
  if ( ! ballKickableByRight(0.06, 0.1) )
    return ConfidenceInterval(0.2, 0.0);

  // the vector from right toe to ball
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  Vector3D goalPos = (wm.getObjectPosition(Types::GOAL1THEM).getMu()
                      + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2.0;

  bool diepoint = false; // 自殺点を入れる可能性

//  wm.setDebugPoint(wm.getBodyConnectionPosition(Types::BC_LTOE));
//  wm.setDebugLine(Vector3D(0,0,0), wm.getBodyConnectionPosition(Types::BC_RTOE));

  Vector3D ourGoal1 = wm.getObjectPosition(Types::GOAL1US).getMu();
  Vector3D ourGoal2 = wm.getObjectPosition(Types::GOAL2US).getMu();

  if( wm.allObjectPosAvailable()) {
    // if our goal is in front of agent, NOT kick.

    if( (ourGoal1.getY() < ballPos.getY() && ballPos.getY() < ourGoal2.getY())
        || (ourGoal1.getY() > ballPos.getY() && ballPos.getY() > ourGoal2.getY()) )
    {
      diepoint = true;
    }
  }
  else if( wm.visibleObject(Types::GOAL1US) ) // only goal1us is in the sight
  {
    if( ourGoal1.getY() < ballPos.getY() )
      diepoint = true;
  }
  else if( wm.visibleObject(Types::GOAL2US) ) // only goal2us is in the sight
  {
    if( ourGoal2.getY() > ballPos.getY() )
      diepoint = true;
  }
  // Keeper and Defender kick ball when there are no our goal in front of them
  if( wm.getPlayerType(wm.getUnum()) != Types::ATTACKER
      && !diepoint )
    return ConfidenceInterval(0.65, 0.0);

//  Vector3D straight(1,0,0);
//  if(straight.angle(goalPos)/M_PI*180.0 > 5)
//    return ConfidenceInterval(0.0, 0.0);
  Vector3D theirGoal1 = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D theirGoal2 = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  if( (theirGoal1.getY() > ballPos.getY() && ballPos.getY() < theirGoal2.getY())
      || (theirGoal1.getY() < ballPos.getY() && ballPos.getY() > theirGoal2.getY()) )
    return ConfidenceInterval(0.25, 0.0);

// check orientation
// check ball position (agent can kick or not)
  if( goalPos.length() < 2.8 && goalPos.length() > 1.0 && !diepoint)
  {
    wm.setNeckDirUpdate(false);
    return ConfidenceInterval(1-ballPos.length(), 0.0);
  }
  
  return ConfidenceInterval(0.13, 0.0);

}

