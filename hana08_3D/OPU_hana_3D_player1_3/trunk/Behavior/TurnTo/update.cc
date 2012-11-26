#include "turnto.ih"

void TurnTo::update()
{
  Behavior::update();

  if (!d_goal){
    d_committed = false;
  }
  else
  {
    rf<StateVarNode> angleNode;
    WorldModel& wm = WorldModel::getInstance();
    
    angleNode = rf_cast<StateVarNode>(d_goal->findDeep("Angle"));
    Vector3D posBall = wm.getObjectPosition(Types::BALL).getMu();
    posBall.setZ(0);
    Vector3D straight(1,0,0);
    double distancetoBall = posBall.length();
    double angletoBall = straight.angle(posBall);

    
    if(angleNode)
    {
      double angle = angleNode->getVar().second.mean() / M_PI * 180;
      if(distancetoBall > 1.25)
	  d_committed = (angle > 10.0 || angle < -10.0);
      else
	  d_committed = (angletoBall > 10.0 || angletoBall < -10.0);
    }
    else{
      d_committed = false;
    }
  }

}
