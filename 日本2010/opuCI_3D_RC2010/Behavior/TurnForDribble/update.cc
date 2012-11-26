#include "turnfordribble.ih"

void TurnForDribble::update()
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
    
    if(angleNode)
    {
      double angle = angleNode->getVar().second.mean() / M_PI * 180.0;
      d_committed = (fabs(angle) > 10.0 
		     && ( fabs(angle) < 80 || fabs(angle) > 100) );
    }
    else
    {
      d_committed = false;
    }
  }

}
