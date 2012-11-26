
#include "talent.ih"

std::pair<double, double> Talent::kickTo(double distance, double maxHeight)
{
  double height = (maxHeight == -1 ? 4 * (WorldModel::getInstance().getAgentProperty("radius")) : maxHeight); //The diameter of all robots is 0.44m
			
  double xpower = 4.28571425813734 * distance + 6.07887239493854;
  double ypower = 1.8635808965266 * height * height * height + -13.6205829871952 * height * height + 41.1490140119435 * height + 5.39426913726159;
        
  double angle = atan(ypower / xpower);
  double power = sqrt(xpower * xpower + ypower * ypower);
        
  /*
  double g = -9.81;
	double height = (maxHeight == -1 ? 4 * (WorldModel::getInstance()->getAgentProperty("radius")) : maxHeight); //The diameter of all robots is 0.44m
	double V0y = sqrtl(-2.0 * g * height);
	double dt = - V0y / g;
	double V0x = distance / 2* dt;
			
	double ax = V0x / 0.1;
	double ay = V0y / 0.1;

  double ballMass = WorldModel::getInstance()->getBallProperty("mass");			  
  double Fx = ballMass * ax;
  double Fy = ballMass * ay;
			
  double angle = atanl(Fy / Fx);
  double power = sqrtl(Fx * Fx + Fy * Fy) / 0.7;*/
			
  return std::make_pair(angle, power);
}
