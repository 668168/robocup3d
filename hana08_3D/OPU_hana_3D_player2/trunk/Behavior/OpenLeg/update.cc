#include "openleg.ih"

void OpenLeg::update()
{
//  std::cout << " -> OpenLeg::update()" << std::endl;
  Behavior::update();
  
  WorldModel& wm = WorldModel::getInstance();
//  std::cout << " -> " << wm.getJointAngle(Types::RLEG3).getMu() << " " << wm.getJointAngle(Types::LLEG3).getMu() << std::endl;
  d_committed = d_committed || ( (wm.getJointAngle(Types::RLEG3).getMu() >= -0.49 * M_PI) || (wm.getJointAngle(Types::LLEG3).getMu() <= 0.49 * M_PI) );
}

