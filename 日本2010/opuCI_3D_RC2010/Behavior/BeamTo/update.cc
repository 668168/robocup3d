#include "beamto.ih"

void BeamTo::update()
{
//  std::cout << " -> BeamTo::update()" << std::endl;
  WorldModel& wm = WorldModel::getInstance();
  WorldModel::PlayMode pm = wm.getPlayMode();

  d_committed =
    ( pm == WorldModel::UNKNOWN
      || pm == WorldModel::BEFORE_KICKOFF
      || pm == WorldModel::GOAL_US
      || pm == WorldModel::GOAL_THEM );

}

