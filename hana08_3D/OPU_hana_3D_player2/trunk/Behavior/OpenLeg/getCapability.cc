#include "openleg.ih"

Behavior::ConfidenceInterval OpenLeg::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
//  std::cout << wm.getJointAngle(Types::RLEG3).getMu() << " " << wm.getJointAngle(Types::LLEG3).getMu() << std::endl;
  bool openLeg = wm.getJointAngle(Types::RLEG3).getMu() >= -0.49 * M_PI || wm.getJointAngle(Types::LLEG3).getMu() <= 0.49 * M_PI;
//	std::cout << "FN: " << wm.getFieldNormal().getX() << " " << wm.getFieldNormal().getY() << " " << wm.getFieldNormal().getZ() << std::endl;
//	std::cout << "Gyro: " << wm.getGyro().length() << std::endl;
//	std::cout << "FL: " << wm.getForceLeftFoot().getX() << " " << wm.getForceLeftFoot().getY() << " " << wm.getForceLeftFoot().getZ() << std::endl;
//	std::cout << "FR: " << wm.getForceRightFoot().getX() << " " << wm.getForceRightFoot().getY() << " " << wm.getForceRightFoot().getZ() << std::endl << std::endl;
//	std::cout << "Dist: " << wm.getDistToField() << std::endl;	
  return openLeg ? ConfidenceInterval(0.7, 0.2) : ConfidenceInterval(0.0, 0.0);
}
