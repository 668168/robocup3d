#include "generatingsine2action.ih"

rf<Behavior::Goal> GeneratingSine2Action::generateGoal(unsigned step, unsigned slot)
{
  WorldModel& wm = WorldModel::getInstance();

/*
  if (s_lastUpdate < wm.getTime())
  {
    updateFactor();
    s_lastUpdate = wm.getTime();
  }
*/
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  double weight1 = 1;
/*
  double weight1 = d_factor;
  stringstream ss;
  ss.str("");
  ss << "d_factor = " << d_factor;
  wm.addDebugMessage(WorldModel::COMMENT, ss.str());
*/
//  std::cout << ss.str() << std::endl;
  con->addVar("Weight1", weight1, weight1);

  return goal;
}
