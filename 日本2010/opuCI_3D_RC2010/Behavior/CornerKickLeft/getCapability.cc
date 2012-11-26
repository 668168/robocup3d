#include "cornerkickleft.ih"

Behavior::ConfidenceInterval CornerKickLeft::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  rf<StateVarNode> node = rf_cast<StateVarNode>(g->findDeep("CornerKick"));
  Types::Object corner;
  if( ! ballKickableByLeft() || ! node )
    return ConfidenceInterval(0.0, 0.0);

  // corner = FLAG1THEM or FLAG2THEM (ボールがある方)
  corner = static_cast<Types::Object>(node->getVar().second.mean());

  Vector3D goal1them = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D goal2them = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();

  if( corner == Types::FLAG1THEM )
  {
    if( goal1them.getY() < ball.getY() && goal2them.getY() < ball.getY() )
      return ConfidenceInterval(0.8, 0.0);
  }
  else if ( corner == Types::FLAG2THEM )
  {
    if( goal1them.getY() > ball.getY() && goal2them.getY() > ball.getY() )
      return ConfidenceInterval(0.8, 0.0);
  }
  else
    std::cerr << "(CornerKickLeft) error... unknown corner" <<std::endl;

  return ConfidenceInterval(0.2, 0.0);
}
