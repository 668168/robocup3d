#include "gamepadinput.hh"

GamepadInput *GamepadInput::m_instance = 0;

GamepadInput::GamepadInput()
  : m_init(false)
{
  for(int i=0;i<NUM_BUTTONS;i++){
    m_buttonValue[i] = 0;
    //m_buttonPushed[i] = false;
  }
  for(int i=0;i<NUM_AXIS;i++){
    m_axisValue[i] = 0;
    //m_axisChanged[i] = false;
  }

}

GamepadInput::~GamepadInput(){
  delete m_instance;
}


void GamepadInput::initialize(std::string gamepadPath)
{
  m_fd = open( gamepadPath.c_str(), O_RDONLY );
  if( !m_fd ){
    std::cerr << "gamepad " << gamepadPath << " is not found!" << std::endl;
    exit;
  }

  m_init = true;
}

void GamepadInput::update()
{
  if(!m_init)
    return;

  struct js_event je;
  fd_set set;
  timeval t;

  FD_ZERO(&set);
  FD_SET(m_fd, &set);
  t.tv_sec  = 0;
  t.tv_usec = 0;

  while( select(m_fd+1, &set, NULL, NULL, &t) > 0 ){
    read( m_fd, &je, sizeof( struct js_event ));

    /*
    for(int i=0;i<NUM_BUTTONS;i++)
      m_buttonPushed[i] = false;
    for(int i=0;i<NUM_AXIS;i++)
      m_axisChanged[i] = false;
    */
    if( je.type == JS_EVENT_BUTTON ){
      m_buttonValue[je.number] = je.value;
      //m_buttonPushed[je.number] = true;
    }
    if( je.type == JS_EVENT_AXIS ){
      m_axisValue[je.number] = je.value;
      //m_axisChanged[je.number] = true;
    }

    FD_ZERO(&set);
    FD_SET(m_fd, &set);
    t.tv_sec  = 0;
    t.tv_usec = 0;
  }
}

GamepadInput* GamepadInput::getInstance()
{
  if( !m_instance )
    m_instance = new GamepadInput();

  return m_instance;
}
