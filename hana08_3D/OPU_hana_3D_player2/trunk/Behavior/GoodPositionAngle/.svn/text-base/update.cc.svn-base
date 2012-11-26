#include "goodpositionangle.ih"

void GoodPositionAngle::update()
{
  Behavior::update();
  
  if (d_committed)
    return;
    
  if (!d_goal)
    d_committed = false;
  else
  {
    rf<StateVarNode> posNode, angleNode;
    
    posNode = rf_cast<StateVarNode>(d_goal->findDeep("PosX"));
    angleNode = rf_cast<StateVarNode>(d_goal->findDeep("Angle"));
    _debugLevel4((posNode ? "yes " : "no "));
    _debugLevel4((angleNode ? "yes " : "no "));
    if(posNode && angleNode)
    {
	Vector3D pos = d_goal->getVector("Pos"); 
//      double angle = angleNode->getVar().second.mean();
      Vector3D straight(1,0,0);
      double angle = straight.angle(pos) / M_PI * 180.0;
      
      //WorldModel& wm = WorldModel::getInstance();
      
      pos.setZ(0);
      _debugLevel4(pos << " " << angle / M_PI * 180.0);
      switch(d_curStep){
      case 0:
        d_committed = (pos.length() > 0.2 && pos.length() < 1.5);// || fabs(angle) / M_PI * 180.0 > 5.0;
        break;
      case 1:
	  if(pos.length() <= 0.2 || pos.length() >= 1.5)
          d_committed = false;
        else
          d_committed = fabs(angle) / M_PI * 180.0 > 5.0;
        break;
      }
    }
    else
      d_committed = false;
  }
}

