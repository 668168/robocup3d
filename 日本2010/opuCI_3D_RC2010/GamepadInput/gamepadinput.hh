#ifndef GAMEPAD_INPUT_HH
#define GAMEPAD_INPUT_HH

#include <iostream>
#include <linux/joystick.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

class GamepadInput {

public :
  static GamepadInput* getInstance();
  ~GamepadInput();

  enum ButtonID{
    GAMEPAD_BUTTON01 = 0,
    GAMEPAD_BUTTON02,
    GAMEPAD_BUTTON03,
    GAMEPAD_BUTTON04,
    GAMEPAD_BUTTON05,
    GAMEPAD_BUTTON06,
    GAMEPAD_BUTTON07,
    GAMEPAD_BUTTON08,
    GAMEPAD_BUTTON09,
    GAMEPAD_BUTTON10,
    GAMEPAD_BUTTON11,
    GAMEPAD_BUTTON12,
    GAMEPAD_BUTTON13,
    GAMEPAD_BUTTON14,
    GAMEPAD_BUTTON15,
    GAMEPAD_BUTTON16,
    GAMEPAD_BUTTON17,
    GAMEPAD_BUTTON18,
    GAMEPAD_BUTTON19,

    GAMEPAD_BUTTON_UNKNOWN,

    NUM_BUTTONS,
  };

  enum AxisID{
    GAMEPAD_AXIS01 = 0,
    GAMEPAD_AXIS02,
    GAMEPAD_AXIS03,
    GAMEPAD_AXIS04,
    GAMEPAD_AXIS05,
    GAMEPAD_AXIS06,
    GAMEPAD_AXIS07,
    GAMEPAD_AXIS08,
    GAMEPAD_AXIS09,

    GAMEPAD_AXIS_UNKNOWN,

    NUM_AXIS,
  };

  void initialize(std::string gamepadPath="/dev/input/js0");
  bool isInitialized(){
    return m_init;
  }

  bool isButtonPushed();
  bool isAxisChanged();

  bool isButtonPushed(ButtonID i){
    // return m_buttonPushed[i];
    return (m_buttonValue[i] != 0);
  }

  bool isButtonPushed(int i){
    // return m_buttonPushed[i];
    return isButtonPushed(static_cast<ButtonID>(i));
  }

  bool isAxisChanged(AxisID i){
    // return m_axisChanged[i];
    return (m_axisValue[i] != 0);
  }

  bool isAxisChanged(int i){
    // return m_axisChanged[i];
    return isAxisChanged(static_cast<AxisID>(i));
  }

  __s16 getButtonValue(ButtonID i){
    return m_buttonValue[i];
  }

  __s16 getButtonValue(int i){
    return getButtonValue(static_cast<ButtonID>(i));
  }

  __s16 getAxisValue(AxisID i){
    return m_axisValue[i];
  }

  __s16 getAxisValue(int i){
    return getAxisValue(static_cast<AxisID>(i));
  }

  void update();
  //  void setJoyStickNum(int i);
  //  int  getJoyStickNum();

  //  void setGemapad(std::string gamepadPath);

private :
  GamepadInput();

  static GamepadInput* m_instance;
  bool m_init;
  int m_fd;
  __s16 m_buttonValue[NUM_BUTTONS];
  __s16 m_axisValue[NUM_AXIS];
//  bool m_buttonPushed[NUM_BUTTONS];
//  bool m_axisChanged[NUM_AXIS];
  //  int m_joyStickNumber;

};

#endif // GAMEPAD_INPUT_HH
