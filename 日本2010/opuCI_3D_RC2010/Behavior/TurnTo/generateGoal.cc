#include "turnto.ih"

rf<Behavior::Goal> TurnTo::generateGoal(unsigned step, unsigned slot)
{
//  if (step == 0)//1)
//    return d_goal;
    WorldModel& wm = WorldModel::getInstance();
    
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();


  rf<StateVarNode> angleNode = rf_cast<StateVarNode>(d_goal->findDeep("Angle"));
  StateVar angleVar = angleNode->getVar();
  double angle = angleVar.second.mean();
/*
   con->addVar("Angle", angle, angle);
   wm.setDebugLine(Vector3D(0,0,0),
                   Vector3D(cos(angle/180.0*M_PI), sin(angle/180.0*M_PI),0));
*/
  double weight1=0, weight2=0;

  if( angle < 0 )
  {
    weight1 = 1;
    wm.addDebugMessage(WorldModel::COMMENT, "Turn Right!");
  }
  else
  {
    weight2 = 1;
    wm.addDebugMessage(WorldModel::COMMENT, "Turn Left!");
  }

  con->addVar("Weight1", weight1, weight1);
  con->addVar("Weight2", weight2, weight2);

  return goal;
}
