#include "walkstraightto.ih"

Behavior::ConfidenceInterval WalkStraightTo::getCapability(rf<Behavior::State> s, rf<Behavior::Goal> g)
{

//  std::cout << "before getVector" << std::endl;
    Vector3D pos = g->getVector("Pos"); // <- pos = wm.getObjectPosition(Types::BALL).getMu()
  WorldModel& wm = WorldModel::getInstance();
//  Vector3D pos = wm.getObjectPosition(Types::BALL).getMu();
//  std::cout << "In WalkStraightTo::generateGoal\n pos = (" << pos.getX() << ", " << pos.getY() << ", " << pos.getZ() << ")" << std::endl;
  pos.setZ(0);
  Vector3D straight(1, 0, 0);
  
  double angleToPos = pos.angle(straight) / M_PI * 180;
//  std::cout << " angleToPos = " << angleToPos << std::endl;
  
  //double minAngle = 10.0;
  //double maxAngle = 20.0;

// ちゃんと動かすには20,デフォルト(GetUpMode)は10. no hazu...???
  double angle = 20.0;

//   int num;
//   std::cin >> num;
//   std::cout << num << std::endl;

  /*if (pos.length() < 2){
  	angle = maxAngle - (pos.length() * ((maxAngle - minAngle) / 5));
  }*/

//  WorldModel& wm = WorldModel::getInstance();

  if (angleToPos > angle || angleToPos < -angle)// || !wm.onMyFeet())
  {
//	std::cout << "WalkStraightTo:(-1.0, 0.0)" << std::endl;
  	_debugLevel3("Can't walk straight to position");
    return ConfidenceInterval(-1.0, 0.0);
  }

//  std::cout << "WalkStraightTo:(0.9, 0.0)" << std::endl;
  _debugLevel4("Capable");
  return ConfidenceInterval(0.9, 0.0);
}
