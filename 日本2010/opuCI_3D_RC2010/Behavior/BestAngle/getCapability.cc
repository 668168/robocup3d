#include "bestangle.ih"

Behavior::ConfidenceInterval BestAngle::getCapability(rf<State> s, rf<Goal> g)
{
/*
  rf<StateVarNode> angleNode = rf_cast<StateVarNode>(g->findDeep("Angle"));
  StateVar angleVar = angleNode->getVar();
  int angle = (int)angleVar.second.mean();
  //    std::cout << "BestAngle : " << angle << std::endl;
  WorldModel& wm = WorldModel::getInstance();
  std::stringstream ss;
//  ss << " (BestAngle)BestAngle=" << angle;
  wm.addDebugMessage(WorldModel::COMMENT, ss.str());
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  
  // 目標角度との誤差が5度以上あれば方向転換
  if(angle > 5.0) // left
  {
    return ConfidenceInterval(0.7, 0.0);
  }
  else if(angle < -5.0) // right
  {
    return ConfidenceInterval(0.7, 0.0);
  }

  return ConfidenceInterval(0.2, 0.0);
*/
  return ConfidenceInterval(0.5, 0.0);
}
