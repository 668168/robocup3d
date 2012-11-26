#include "beamto.ih"

rf<Behavior::Goal> BeamTo::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  con->addVar("X", d_x, d_x);
  con->addVar("Y", d_y, d_y);
  con->addVar("Z", d_z, d_z);
  
//  std::cout << "gGoal: (X, Y, Z) = (" << d_x << ", " << d_y << ", " << d_z << ")" << std::endl;
  
  return goal;
}
