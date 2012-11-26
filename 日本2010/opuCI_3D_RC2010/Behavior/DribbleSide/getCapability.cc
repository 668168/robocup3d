#include "dribbleside.ih"

Behavior::ConfidenceInterval DribbleSide::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

    if( ballKickableByRight(0.09, 1.0) || ballKickableByLeft(0.09, 1.0))
      return ConfidenceInterval(0.6, 0.0);

    return ConfidenceInterval(0, 0);

}
