#include "keeperkickposition.ih"

Behavior::ConfidenceInterval KeeperKickPosition::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    
    // at least one of ball, goal1them, goal2them pos is not avairable, cant kick.
    if(!wm.visibleObject(Types::BALL) || !wm.allObjectPosAvailable() )
      return ConfidenceInterval(0.15, 0.0);

    Vector3D goalPos = ( wm.getObjectPosition(Types::GOAL1US).getMu() +
                         wm.getObjectPosition(Types::GOAL2US).getMu() ) / 2;
    goalPos.setZ(0);
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    ballPos.setZ(0);
    double angleBallAndGoal = ballPos.angle(goalPos) / M_PI * 180.0; // degree

    wm.setDebugLine(goalPos, ballPos);

    double trytoKickDist = 3.0;

    // 向いてる方向に蹴っても良さそうなら0.7
    if( angleBallAndGoal > 90 ) // ちょーてきとー
    {
      return ConfidenceInterval(0.7, 0);
    }
    return ConfidenceInterval(0.2, 0.0);
    
}
