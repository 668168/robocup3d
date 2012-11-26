#include "getfromside.ih"

void GetFromSide::update()
{
//  std::cout << " -> GetFromSide::update()" << std::endl;
  Behavior::update();
  
  WorldModel& wm = WorldModel::getInstance();
  d_committed = d_committed || !(wm.onMyBack() || wm.onMyBelly() || wm.onMyFeet());
}

