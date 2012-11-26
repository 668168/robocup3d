#include "canturnright.ih"

void CanTurnRight::update()
{
  Behavior::update();

  if (d_committed)
    return;
 
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  ballPos.setZ(0);
  Vector3D straight(1, 0, 0);
  double angleToBall = straight.angle(ballPos) / M_PI * 180;
//  std::cout << "canTurnRight: " << angleToBall << std::endl;
  if(angleToBall > 0)
    d_committed = false;
  else if(angleToBall <= 0 && angleToBall > -10)
    d_committed = false;
  else
    d_committed = true;
  //d_committed = !wm.onMyFeet();
  
//  std::cout << "In CanTurnRight::update()" << std::endl;
//  std::cout << "  d_committed = " << d_committed << std::endl;

}

