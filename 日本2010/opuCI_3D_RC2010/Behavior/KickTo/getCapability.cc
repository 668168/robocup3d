#include "kickto.ih"

Behavior::ConfidenceInterval KickTo::getCapability(rf<State> s, rf<Goal> g)
{
//    rf<StateVarNode> defenseNode = rf_cast<StateVarNode>(g->findDeep("DF"));
//    if(defenseNode)
//   return ConfidenceInterval(0.0, 0.0);

  WorldModel& wm = WorldModel::getInstance();  
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  // ボールが見えててボールまで1m以内ならKickTo実行
  if(ballPos.length() <= 1.0 && wm.visibleObject(Types::BALL)){
    return ConfidenceInterval(0.55, 0.2);
  }
  else{
    return ConfidenceInterval(0.0, 0.0);
  }
}
