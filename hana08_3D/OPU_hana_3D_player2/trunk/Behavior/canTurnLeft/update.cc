#include "canturnleft.ih"

void CanTurnLeft::update()
{
  Behavior::update();
/*  
  WorldModel& wm = WorldModel::getInstance();
  d_committed = d_committed;// || !wm.onMyFeet();
*/
  if(d_committed)
    return;
    
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  ballPos.setZ(0);
  Vector3D straight(1, 0, 0);
  double angleToBall = straight.angle(ballPos) / M_PI * 180;
//  std::cout << "canTurnLeft: " << angleToBall << std::endl;
  if(angleToBall < 0)
    d_committed = false;
  else if(angleToBall >= 0 && angleToBall < 10)
    d_committed = false;
  else
    d_committed = true;
  //d_committed = !wm.onMyFeet();
  
//  std::cout << "In CanTurnLeft::update()" << std::endl;
//  std::cout << "  d_committed = " << d_committed << std::endl;

}

