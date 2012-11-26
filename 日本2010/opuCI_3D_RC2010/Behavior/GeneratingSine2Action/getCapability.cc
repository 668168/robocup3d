#include "generatingsine2action.ih"

Behavior::ConfidenceInterval GeneratingSine2Action::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  if(( wm.onMyBack() || wm.onMySide() || wm.onMyBelly())  // 転倒している
//     || ( wm.getDeadTime() < wm.getTime() + 5.0)  // 自殺5秒前
     || ( wm.getDeadTime() > wm.getTime() + 9000))  // 初期位置記憶前
    return ConfidenceInterval(0.2, 0.0);

  return ConfidenceInterval(1.9, 0.0);
}
