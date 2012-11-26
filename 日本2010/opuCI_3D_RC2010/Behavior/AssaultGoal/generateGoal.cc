#include "assaultgoal.ih"

rf<Behavior::Goal> AssaultGoal::generateGoal(unsigned step, unsigned slot)
{
  // 敵ゴールの片方とボールしか分からないので，とりあえずボールに突進する
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();
  Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();

  double angToBall = getAngleWithStraight(ball);
  double min = 10;


  con->addVar("Angle", angToBall, angToBall); // turn to ball and goal
  con->addVar("MinAngle", min, min); // acceptable error of TurnTo

  con->addVar("Pos", ball); // go to ball and goal

  return goal;
}
