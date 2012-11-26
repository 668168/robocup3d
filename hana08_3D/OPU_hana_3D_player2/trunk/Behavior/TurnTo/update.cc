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
    Vector3D pos = d_goal->getVector("Pos");
    pos.setZ(0);
    Vector3D straight(1,0,0);
    double angletoBall = straight.angle(pos);

    
    if(angleNode)
    {
      double angle = angleNode->getVar().second.mean() / M_PI * 180;
      if(pos.length() > 1.25)
	  d_committed = (angle > 10.0 || angle < -10.0);
      else
	  d_committed = (angletoBall > 10.0 || angletoBall < -10.0);

    }
    else{
      d_committed = false;

    }
  }

}
