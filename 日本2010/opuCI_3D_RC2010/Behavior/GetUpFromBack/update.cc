#include "getupfromback.ih"

void GetUpFromBack::update()
{
//  std::cout << " -> GetUpFromBack::update()" << std::endl;
  Behavior::update();
	
  WorldModel& wm = WorldModel::getInstance();
//  d_committed = d_committed || (!wm.onMyFeet() && !wm.onMyBelly());

}

