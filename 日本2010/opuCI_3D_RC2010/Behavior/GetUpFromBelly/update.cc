#include "getupfrombelly.ih"

void GetUpFromBelly::update()
{
//  std::cout << " -> GetUpFromBelly::update()" << std::endl;
  Behavior::update();

  WorldModel& wm = WorldModel::getInstance();
//  d_committed = d_committed;// || (!wm.onMyFeet() && !wm.onMyBack());
}

