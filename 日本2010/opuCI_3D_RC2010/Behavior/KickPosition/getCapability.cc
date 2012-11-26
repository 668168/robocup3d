#include "kickposition.ih"

Behavior::ConfidenceInterval KickPosition::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    
    // at least one of ball, goal1them, goal2them pos is not avairable, cant kick.
    if(!wm.visibleObject(Types::BALL) || !wm.allObjectPosAvailable() )
      return ConfidenceInterval(0.15, 0.0);

    Vector3D goalPos = ( wm.getObjectPosition(Types::GOAL1THEM).getMu() +
                         wm.getObjectPosition(Types::GOAL2THEM).getMu() ) / 2;
    goalPos.setZ(0);
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    ballPos.setZ(0);
    double ballToGoal = (ballPos - goalPos).length();

    double toeX =
      min(wm.getBodyConnectionPosition(Types::BC_RTOE).getX(), wm.getBodyConnectionPosition(Types::BC_LTOE).getX());

    wm.setDebugLine(goalPos, ballPos);

    double trytoKickDist = 3.0;

      if( (ballToGoal < trytoKickDist && ballToGoal > 1.0 )
          && ( toeX < ballPos.getX() && ballPos.getX() < goalPos.getX()) )
      {

        wm.setDebugCircle(goalPos, trytoKickDist);
        return ConfidenceInterval(0.7, 0);
      }
    return ConfidenceInterval(0.2, 0.0);
    
}
