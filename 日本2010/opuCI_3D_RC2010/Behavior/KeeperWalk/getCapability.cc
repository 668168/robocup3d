#include "keeperwalk.ih"

Behavior::ConfidenceInterval KeeperWalk::getCapability(rf<State> s, rf<Goal> g)
{
//    WorldModel& wm = WorldModel::getInstance();

    return ConfidenceInterval(0.71, 0.0);

}
