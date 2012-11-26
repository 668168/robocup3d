#include "gamepadplay.ih"

rf<Behavior::Goal> GamepadPlay::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  GamepadInput* pad = GamepadInput::getInstance();
  WorldModel& wm = WorldModel::getInstance();
  if(!pad->isInitialized())
    return goal;

  int threshould = 1000; // スティック入力の閾値

  int stick_LV = pad->getAxisValue(GamepadInput::GAMEPAD_AXIS02); // 左スティック上下
  int stick_LH = pad->getAxisValue(GamepadInput::GAMEPAD_AXIS01); // 左スティック左右
  int stick_RV = pad->getAxisValue(GamepadInput::GAMEPAD_AXIS03); // 右スティック上下
  int stick_RH = pad->getAxisValue(GamepadInput::GAMEPAD_AXIS04); // 右スティック左右

  // 軸認識
  // 左スティック
  double weight1=0,weight2=0, weight3=0,weight4=0;
  double yoko = stick_LH / 32767.0;
  double tate = stick_LV / 32767.0;

  if(stick_LH > threshould) // 右
  {
    if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON04) )
      con->addVar("GamepadStrafeRight", 0.57, 0.57);
    else
    {
      con->addVar("GamepadTurnRight", 0.54, 0.54);
    }
    con->addVar("Weight1", yoko, yoko);
    con->addVar("Weight2", 0, 0);
  }
  else if(stick_LH < -threshould) // 左
  {
    if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON04) )
      con->addVar("GamepadStrafeLeft", 0.57, 0.57);
    else
    {
      con->addVar("GamepadTurnLeft", 0.54, 0.54);
    }
    con->addVar("Weight1", 0, 0);
    con->addVar("Weight2", -yoko, -yoko);
  }
  if(stick_LV > threshould) // 下
  {
    if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON04) )
      con->addVar("GamepadMiniWalkBackward", 0.58, 0.58);
    else
      con->addVar("GamepadWalkBackward", 0.55, 0.55);
  }
  else if(stick_LV < -threshould) // 上
  {
    if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON04) )
      con->addVar("GamepadMiniWalkForward", 0.58, 0.58);
    else
      con->addVar("GamepadWalk", 0.55, 0.55);
  }

  // 右スティック
  // for OmnidirectionalWalk
  weight1=0,weight2=0, weight3=0,weight4=0;
  tate = stick_RV / 32767.0; // 下が＋
  yoko = stick_RH / 32767.0;  // 右が＋

  if(tate > 0){
    weight1 = 0;
    weight4 = tate;
  } else {
    weight1 = -tate;
    weight4 = 0;
  }
  if(yoko > 0){
    weight2 = 0;
    weight3 = yoko;
  } else {
    weight2 = -yoko;
    weight3 = 0;
  }

  if( fabs(stick_RV) > threshould || fabs(stick_RH) > threshould )
  {
    con->addVar("GamepadOmnidirectionalWalk", 0.80, 0.80);
    con->addVar("Weight1", weight1, weight1); // forward
    con->addVar("Weight2", weight2, weight2); // rightside
    con->addVar("Weight3", weight3, weight3); // leftside
    con->addVar("Weight4", weight4, weight4); // backward

    stringstream ss;
    ss << "<br>forward x " << weight1
       << ", backward x " << weight4
       << ", right x " << weight2
       << ", left x " << weight3 << "<br>";
    wm.addDebugMessage(WorldModel::COMMENT, ss.str() );
  }

/* // 正規の設定はこっちで行いたい
  if(stick_RV > threshould) // 右
  {
    con->addVar("GamepadOmnidirectionalWalk", 0.80, 0.80);
    weight2 = 1;
  }
  else if(stick_RV < -threshould) // 左
  {
    con->addVar("GamepadOmnidirectionalWalk", 0.80, 0.80);
    weight2 = -1;
    //con->addVar("GamepadTurnLeft", 0, 0);
  }
  if(stick_RH > threshould) // 下
  {
    con->addVar("GamepadOmnidirectionalWalk", 0.80, 0.80);
    //con->addVar("GamepadWalk", 0, 0);
  }
  else if(stick_RH < -threshould) // 上
  {
    con->addVar("GamepadOmnidirectionalWalk", 0.80, 0.80);
    //con->addVar("GamepadMiniWalkBackward", 0, 0);
  }
*/

  // 十字キー
  if(pad->getAxisValue(GamepadInput::GAMEPAD_AXIS06) > 0) // 右
  {
    con->addVar("GamepadFallRightside", 0.70, 0.70);
  }
  else if(pad->getAxisValue(GamepadInput::GAMEPAD_AXIS06) < 0) // 左
  {
    con->addVar("GamepadFallLeftside", 0.70, 0.70);
  }
  else if(pad->getAxisValue(GamepadInput::GAMEPAD_AXIS07) > 0) // 下
  {
    con->addVar("GamepadFallBackward", 0.70, 0.70);
  }
  else if(pad->getAxisValue(GamepadInput::GAMEPAD_AXIS07) < 0) // 上
  {
    con->addVar("GamepadFallForward", 0.70, 0.70);

  }
  // ボタン認識
/*
  if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON01)) // X
  con->addVar("Dummy",0,0);
*/
  if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON02)) // A
    con->addVar("GamepadJoy", 0.60, 0.60);

  else if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON03)) // B
    con->addVar("GamepadGetUp", 0.95, 0.95);

  else if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON04)) // Y
    con->addVar("GamepadStepping", 0.50, 0.50);

  else if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON05)) // L2
    con->addVar("GamepadKickLeft", 0.91, 0.91);

  else if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON06)) // R2
    con->addVar("GamepadKickRight", 0.90, 0.90);
/*
  else if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON07)) // L1
  con->addVar("Dummy",0,0);

  else if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON08)) // R1
  con->addVar("Dummy",0,0);

  else if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON09)) // Select
    con->addVar("GamepadNantoka", 0.1, 0.1);
*/

  else if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON10)) // Start
    con->addVar("GamepadBeam", 1.00, 1.00);

/*
  else if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON11)) // L-stick
  con->addVar("Dummy",0,0);
*/
  else if(pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON12)) // R-stick
  con->addVar("GamepadStepping",0.50,0.50);

  return goal;
}
