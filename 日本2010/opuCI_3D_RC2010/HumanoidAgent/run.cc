#include "humanoidagent.ih"

std::string makeDebugMessage();

void HumanoidAgent::run()
{
  // Startup agent
  startUp();

  // Get our worldmodel
  WorldModel& wm = WorldModel::getInstance();


  // Get first message
  wm.update();
  unsigned i(0);

 /// \todo Tweak to a minimum possible number of messages before sending init is ok.
  while(wm.getNumMsgReceived() < 5 && ++i < 200)
    wm.update();


  //Send init
  d_comm.init(d_unum, d_teamName);

  //wm.setFirst();

  //Wait for unum
  while(wm.getNumMsgReceived() < 10 && wm.getUnum() == 0)//Failsafe max messages
    wm.update();


  //Init behavior system
  init();


  // connect to debugger
  if( d_debugMode )
  {
    std::cout << "connect to debugger!" << std::endl;
    VD3Connector *vd3 = VD3Connector::getInstance();
    vd3->initialize(d_debuggerPort, d_debuggerHost);
  }

  // connect to gamepad
  GamepadInput* pad = GamepadInput::getInstance();

  // for output messages for debugger
  std::ofstream ofs;
  if( d_outputDebugFile )
  {
    time_t current;
    struct tm *local;
    time(&current);
    local = localtime(&current);

    std::stringstream fname;
    fname << "log/" << ( ( ( ( local->tm_mon+1)*100
                             + local->tm_mday)*100
                           + local->tm_hour )*100
                         + local->tm_min)
          << d_teamName << "_player" << d_unum << ".vd3";
    ofs.open(fname.str().c_str(), std::ios::trunc);
  }

  Localizer& loc = SLocalizer::getInstance();
  //loc.init();
  loc.update();

  while(true)
  {
    _debugLevel4("----------------------- New think cycle ------------------------");

    wm.update(); // @@First beam is performed in this line.
    loc.update();


    // for gamepad
    if( pad->isInitialized() )
    {
      // update gamepad state.
      pad->update();

      // kill myself by gamepad
      if( pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON05)
          && pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON06)
          && pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON07)
          && pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON08)
          && pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON09)
          && pad->isButtonPushed(GamepadInput::GAMEPAD_BUTTON10) )
        break;
    }

    // decision making
    think();

    // send message for Visual Debugger
    if( d_debugMode )
    {
      wm.setDebugPointWithLabel(loc.getLocationGlobal(Types::GOAL1THEM).getMu(), "Loc_BALL");
      std::string str = makeDebugMessage();
      VD3Connector::getInstance()->sendMessage(str);
      // write(d_sock, str.c_str(), str.length());
    }

    // output Visual Debugger message
    if( d_outputDebugFile )
    {
      ofs << makeDebugMessage() << std::endl;
    }
  }
  if( d_outputDebugFile )
    ofs.close();


}



std::string makeDebugMessage()
{
  WorldModel& wm = WorldModel::getInstance();
  std::stringstream debugmessage;
  Vector3D tmpv;

  // time
  debugmessage << "time " << wm.getGameTime();

  debugmessage << " playmode " + wm.getPlayModeString();

  // position
  std::string them1,them2, us1, us2;
  if(wm.getSide() == WorldModel::LEFT){
    them1 = "2right ";
    them2 = "1right ";
    us1 = "1left ";
    us2 = "2left ";
  }
  else{
    them1 = "1left ";
    them2 = "2left ";
    us1 = "2right ";
    us2 = "1right ";
  }

  debugmessage << ((wm.visibleObject(Types::BALL)) ? " ball true" : " ball false");
  tmpv = wm.getObjectLocalPosition(Types::BALL).getMu();
  debugmessage << " " << tmpv.getX() << " " << tmpv.getY() << " " << tmpv.getZ();

  debugmessage << " flag" + them1;
  debugmessage << ((wm.visibleObject(Types::FLAG1THEM)) ? "true" : "false");
  tmpv = wm.getObjectLocalPosition(Types::FLAG1THEM).getMu();
  debugmessage << " " << tmpv.getX() << " " << tmpv.getY() << " " << tmpv.getZ();

  debugmessage << " flag" + them2;
  debugmessage << ((wm.visibleObject(Types::FLAG2THEM)) ? "true" : "false");
  tmpv = wm.getObjectLocalPosition(Types::FLAG2THEM).getMu();
  debugmessage << " " << tmpv.getX() << " " << tmpv.getY() << " " << tmpv.getZ();

  debugmessage << " goal" + them1;
  debugmessage << ((wm.visibleObject(Types::GOAL1THEM)) ? "true" : "false");
  tmpv = wm.getObjectLocalPosition(Types::GOAL1THEM).getMu();
  debugmessage << " " << tmpv.getX() << " " << tmpv.getY() << " " << tmpv.getZ();

  debugmessage << " goal" + them2;
  debugmessage << ((wm.visibleObject(Types::GOAL2THEM)) ? "true" : "false");
  tmpv = wm.getObjectLocalPosition(Types::GOAL2THEM).getMu();
  debugmessage << " " << tmpv.getX() << " " << tmpv.getY() << " " << tmpv.getZ();

  debugmessage << " flag" + us1;
  debugmessage << ((wm.visibleObject(Types::FLAG1US)) ? "true" : "false");
  tmpv = wm.getObjectLocalPosition(Types::FLAG1US).getMu();
  debugmessage << " " << tmpv.getX() << " " << tmpv.getY() << " " << tmpv.getZ();

  debugmessage << " flag" + us2;
  debugmessage << ((wm.visibleObject(Types::FLAG2US)) ? "true" : "false");
  tmpv = wm.getObjectLocalPosition(Types::FLAG2US).getMu();
  debugmessage << " " << tmpv.getX() << " " << tmpv.getY() << " " << tmpv.getZ();

  debugmessage << " goal" + us1;
  debugmessage << ((wm.visibleObject(Types::GOAL1US)) ? "true" : "false");
  tmpv = wm.getObjectLocalPosition(Types::GOAL1US).getMu();
  debugmessage << " " << tmpv.getX() << " " << tmpv.getY() << " " << tmpv.getZ();
    
  debugmessage << " goal" + us2;
  debugmessage << ((wm.visibleObject(Types::GOAL2US)) ? "true" : "false");
  tmpv = wm.getObjectLocalPosition(Types::GOAL2US).getMu();
  debugmessage << " " << tmpv.getX() << " " << tmpv.getY() << " " << tmpv.getZ();
  
  // teammate
  for(int i=Types::PLAYER1; i<=Types::PLAYER11;i++){
    if(wm.visibleObject(static_cast<Types::Object>(i)))
    {
      debugmessage << " teammate true ";
//      debugmessage << ((wm.visibleObject((Types::Object)i)) ? " teammate true " : " teammate false ");
      Vector3D tmmt = wm.getObjectLocalPosition((Types::Object)i).getMu();
      debugmessage << tmmt.getX() << " " << tmmt.getY() << " " << tmmt.getZ();
    }
  }

  for(int i=Types::OPPONENT1; i<=Types::OPPONENT11;i++){
    if(wm.visibleObject(static_cast<Types::Object>(i)))
    {
      debugmessage << " opponent true ";
      // debugmessage << ((wm.visibleObject((Types::Object)i)) ? " opponent true " : " opponent false ");
      Vector3D tmmt = wm.getObjectLocalPosition((Types::Object)i).getMu();
      debugmessage << tmmt.getX() << " " << tmmt.getY() << " " << tmmt.getZ();
    }
  }

  // behavior
  debugmessage << " behavior " << wm.getDebugMessage(WorldModel::BEHAVIOR);

  // comment
  debugmessage << " comment " << wm.getDebugMessage(WorldModel::COMMENT) << " commentend ";
  
  // gyro
  debugmessage << " gyro " << wm.getGyro().getX()
               << " " << wm.getGyro().getY() << " " << wm.getGyro().getZ();

  // fieldnormal
  debugmessage << " fieldnormal " << wm.getFieldNormal().getX()
               << " " << wm.getFieldNormal().getY() << " " << wm.getFieldNormal().getZ();

  // neck and head angle data
  debugmessage << " hj1 " << wm.getJointAngle(Types::HEAD_1).getMu();
  debugmessage << " hj2 " << wm.getJointAngle(Types::HEAD_2).getMu();
  
  // arm joint info
  debugmessage << " laj1 " << wm.getJointAngle(Types::LARM1).getMu();
  debugmessage << " laj2 " << wm.getJointAngle(Types::LARM2).getMu();
  debugmessage << " laj3 " << wm.getJointAngle(Types::LARM3).getMu();
  debugmessage << " laj4 " << wm.getJointAngle(Types::LARM4).getMu();
  debugmessage << " raj1 " << wm.getJointAngle(Types::RARM1).getMu();
  debugmessage << " raj2 " << wm.getJointAngle(Types::RARM2).getMu();
  debugmessage << " raj3 " << wm.getJointAngle(Types::RARM3).getMu();
  debugmessage << " raj4 " << wm.getJointAngle(Types::RARM4).getMu();
  
  // leg joint info
  debugmessage << " llj1 " << wm.getJointAngle(Types::LLEG1).getMu();
  debugmessage << " llj2 " << wm.getJointAngle(Types::LLEG2).getMu();
  debugmessage << " llj3 " << wm.getJointAngle(Types::LLEG3).getMu();
  debugmessage << " llj4 " << wm.getJointAngle(Types::LLEG4).getMu();
  debugmessage << " llj5 " << wm.getJointAngle(Types::LLEG5).getMu();
  debugmessage << " llj6 " << wm.getJointAngle(Types::LLEG6).getMu();
  debugmessage << " rlj1 " << wm.getJointAngle(Types::RLEG1).getMu();
  debugmessage << " rlj2 " << wm.getJointAngle(Types::RLEG2).getMu();
  debugmessage << " rlj3 " << wm.getJointAngle(Types::RLEG3).getMu();
  debugmessage << " rlj4 " << wm.getJointAngle(Types::RLEG4).getMu();
  debugmessage << " rlj5 " << wm.getJointAngle(Types::RLEG5).getMu();
  debugmessage << " rlj6 " << wm.getJointAngle(Types::RLEG6).getMu();
  
  // point, circle, line
  debugmessage << wm.getDebugDrawMessage();
  
  // if get "mypos", output mypos by comment
  //if(wm.getMyPos().length() != 0)
  debugmessage << " comment <br>accel = (" << wm.getAcceleration().getX() << " "
               << wm.getAcceleration().getY() << " " << wm.getAcceleration().getZ() << ") ";

  debugmessage << " commentend ";

  debugmessage << " \n";
  
  return debugmessage.str();
}
