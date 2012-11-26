#include "scriptplayer.ih"

rf<Behavior::Goal> ScriptPlayer::generateGoal(unsigned step, unsigned slot)
{
  d_committed = true;
  
  vector<pair<double, pair<double, double> > > scriptLine = d_script[d_curLine];

  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  // debugLevel4("Angle for slot " << slot << ": " << scriptLine[slot].first << " (now: " << wm.getJointAngle((Types::Joint)slot).getMu() << ")");
  con->addVar("Angle", scriptLine[slot].first, scriptLine[slot].first);
  con->addVar("MaxSpeed", scriptLine[slot].second.first, scriptLine[slot].second.first);
  con->addVar("Gain", scriptLine[slot].second.second, scriptLine[slot].second.second);
  
  return goal;
}
