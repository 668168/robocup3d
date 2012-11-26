#include "turnto.ih"

void TurnTo::update()
{
//  std::cout << "TurnTo::update()" << std::endl;
  Behavior::update();
    
//  std::cout << "  true = " << true << ", false = " << false << std::endl;
  if (!d_goal){
    d_committed = false;
//    std::cout << "  (1) d_committed: " << d_committed << std::endl;
  }
  else
  {
    rf<StateVarNode> angleNode;
    WorldModel& wm = WorldModel::getInstance();
    
    angleNode = rf_cast<StateVarNode>(d_goal->findDeep("Angle"));
    Vector3D posBall = wm.getObjectPosition(Types::BALL).getMu();
    posBall.setZ(0);
    double distancetoBall = posBall.length();
    double angletoBall = getAngleWithStraight(posBall);
    
    if(angleNode)
    {
	    double angle = angleNode->getVar().second.mean() / M_PI * 180.0;
	    if(distancetoBall > 1.25)
        d_committed = (fabs(angle) > 10.0);
	    else
        d_committed = (fabs(angle) > 5.0);
//	    std::cout << "  (2) d_committed: " << d_committed << std::endl;
    }
    else{
	    d_committed = false;
//	    std::cout << "  (3) d_committed: " << d_committed << std::endl;
    }
  }

}
