#include "gamepadplay.ih"

Behavior::ConfidenceInterval GamepadPlay::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  Vector3D rtoe = wm.getBodyConnectionPosition(Types::BC_RTOE);
  Vector3D ltoe = wm.getBodyConnectionPosition(Types::BC_LTOE);
  Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D goal = (wm.getObjectPosition(Types::GOAL1THEM).getMu()
                   + wm.getObjectPosition(Types::GOAL2THEM).getMu())/2.0;
  stringstream ss;

/*
  wm.setDebugLine(rtoe, ball);
  wm.setDebugLine(ltoe, ball);

  ss << "R-toe - ball = " << ((rtoe - ball).length())
     << "L-toe - ball = " << ((ltoe - ball).length());

  wm.addDebugMessage(WorldModel::COMMENT, ss.str());
*/

  ss << "atSameSizeOf ( ball, goalthem, me )"
     << (Math::atSameSideOf(ball, goal, Vector3D(0, 0, 0)) ? "true" : "false");

    wm.addDebugMessage(WorldModel::COMMENT,ss.str() );//"atSameSideOf: ");

  wm.setDebugLine(ball, goal);
  wm.setDebugLine(goal, Vector3D(0, 0, 0));

  return ConfidenceInterval(0.5, 0.0);
}
