#include "dribble.ih"

rf<Behavior::Goal> Dribble::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();

  if(step == 0) 
      return d_goal;
  else if(step == 1) 
  {

      rf<StateVarNode> angleNode = rf_cast<StateVarNode>(d_goal->findDeep("Angle"));

      StateVar angleVar = angleNode->getVar();

      double angle = angleVar.second.mean();

	  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

      con->addVar("Angle", angle, angle);
      con->addVar("Pos", ballPos);
      return goal;
  }

  return goal;

}
