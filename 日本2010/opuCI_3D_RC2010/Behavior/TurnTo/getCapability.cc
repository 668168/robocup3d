#include "turnto.ih"

Behavior::ConfidenceInterval TurnTo::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  rf<StateVarNode> angleNode = rf_cast<StateVarNode>(g->findDeep("Angle"));
  StateVar angleVar = angleNode->getVar();
  double angle = angleVar.second.mean(); // 目標角度との誤差

  // 目標角度との差をMinAngleで指定 (degree)
  double minAngle = 5;
  angleNode = rf_cast<StateVarNode>(g->findDeep("MinAngle"));
  if( angleNode )
    minAngle = angleNode->getVar().second.mean();

  rf<StateVarNode> walktoNode = rf_cast<StateVarNode>(g->findDeep("WalkTo"));
  if (walktoNode) // WalkTo実行中ならば有効？
    return ConfidenceInterval(0.75, 0.0);

  std::stringstream ss;
  ss << " (TurnTo)angle=" << angle << " ? " << minAngle;
  wm.addDebugMessage(WorldModel::COMMENT, ss.str());

  // 目標角度との誤差がminAngle以上あれば方向転換
  if(fabs(angle) > minAngle)
    return ConfidenceInterval(0.76, 0.0);

  return ConfidenceInterval(-1.0, 0.0);

}
