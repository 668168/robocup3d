#include "kickto.ih"

Behavior::ConfidenceInterval KickTo::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();


  Vector3D straight(1.0, 0.0, 0.0);
  double angleGoal1 = straight.angle(wm.getObjectPosition(Types::GOAL1US).getMu()) / M_PI * 180.0;
  if(wm.getObjectPosition(Types::GOAL1US).getMu().getY() < 0.0)
      angleGoal1 *= -1.0;
  double angleGoal2 = straight.angle(wm.getObjectPosition(Types::GOAL2US).getMu()) / M_PI * 180.0;  
  if(wm.getObjectPosition(Types::GOAL2US).getMu().getY() < 0.0)
      angleGoal2 *= -1.0;
  
  if(ballPos.length() < 0.5 && angleGoal1 * angleGoal2 > 0){

	return ConfidenceInterval(0.6, 0.2);
  }
  else{

	return ConfidenceInterval(0.0, 0.0);
  }
}
