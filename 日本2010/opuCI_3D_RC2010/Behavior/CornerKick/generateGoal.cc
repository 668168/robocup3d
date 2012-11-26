#include "cornerkick.ih"

rf<Behavior::Goal> CornerKick::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  if( s_kickPos == FLAG1 )
    con->addVar("CornerKick", Types::FLAG1THEM, Types::FLAG1THEM);
  else if( s_kickPos == FLAG2 )
    con->addVar("CornerKick", Types::FLAG2THEM, Types::FLAG2THEM);

  return goal;
}
