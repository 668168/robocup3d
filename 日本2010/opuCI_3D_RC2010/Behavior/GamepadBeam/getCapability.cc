#include "gamepadbeam.ih"

Behavior::ConfidenceInterval GamepadBeam::getCapability(rf<State> s, rf<Goal> g)
{
  rf<StateVarNode> node = rf_cast<StateVarNode>(g->findDeep("GamepadBeam"));
  if(node)
  {
    GamepadInput* pad = GamepadInput::getInstance();
    WorldModel& wm = WorldModel::getInstance();

    if(wm.getUnum() == 11)
    {
      // 背番号11はカオス
      static double sumX=0.1, sumY=0.1;
      if( d_x < -wm.fieldLength() / 2.0 || d_x > -0.1)
      {
        sumX *= -1.1;
      }
      if( fabs(d_y) > wm.fieldWidth() / 2.0 )
      {
        sumY *= -1.1;
      }
      if( fabs(sumX) > 1.0 ) sumX *= 1.0 / fabs(sumX);
      if( fabs(sumY) > 1.0 ) sumY *= 1.0 / fabs(sumY);
      d_x += sumX;
      d_y += sumY;

    }
    else
    {
      // 左スティックで位置，右スティックで向きを変更可能
      d_x -= pad->getAxisValue(GamepadInput::GAMEPAD_AXIS02) / 163840.0;
      d_y -= pad->getAxisValue(GamepadInput::GAMEPAD_AXIS01) / 163840.0;
      d_z -= pad->getAxisValue(GamepadInput::GAMEPAD_AXIS04) / 32768.0;

      // ビーム先制限
      if(d_x > -0.1) d_x = -0.1;
      if(d_x < -wm.fieldLength()/2.0) d_x = -wm.fieldLength()/2.0;
      if(d_y > wm.fieldWidth()/2.0) d_y = wm.fieldWidth()/2.0;
      if(d_y < -wm.fieldWidth()/2.0) d_y = -wm.fieldWidth()/2.0;
      if(fabs(d_z) > 360) d_z = 0;
    }

    return ConfidenceInterval(node->getVar().second.mean(), 0.0);
  }
  return ConfidenceInterval(0, 0.2);
}
