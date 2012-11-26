#include "gamepadbeam.ih"

rf<Behavior::Goal> GamepadBeam::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  // con->addVar("Var", 0, 1);
    WorldModel& wm = WorldModel::getInstance();
  WorldModel::PlayMode pm = wm.getPlayMode();

// * unum 1 player(attacker)  * in right side
  con->addVar("X", d_x, d_x);
  con->addVar("Y", d_y, d_y);
  con->addVar("Z", d_z, d_z);

  return goal;
}
