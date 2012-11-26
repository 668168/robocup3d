
#include "worldmodel.ih"

Vector3D WorldModel::getDirectionOfOpponentGoal() const
{
  Vector3D goal = getObject(Types::GOAL1THEM).position.getMu();
  goal += getObject(Types::GOAL2THEM).position.getMu();
  goal = goal / 2;
  return Math::cartesianToPolar(goal, true);
}
