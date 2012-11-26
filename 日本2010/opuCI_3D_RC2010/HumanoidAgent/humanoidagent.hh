#ifndef _BATS_HUMANOIDAGENT_HH_
#define _BATS_HUMANOIDAGENT_HH_

#include "socketcomm.hh"
#include <cmath>
#include <ctime>

#include "gamepadinput.hh"
#include "vd3connector.hh"

namespace bats
{
  /** Humanoid agent base class
   *
   * This class forms the base of your humanoid 3D soccer simulation agent. All you need to do to create a working agent is derive from this class. For instance:
   * \code
   * class MyAgent : public bats::HumanoidAgent
   * {
   *   public:
   *     MyAgent(std::string teamName) : bats::HumanoidAgent(teamName) {}
   * };
   * \endcode
   * To start your agent, simply create an object of your agent class and call its run method:
   * \code
   * int main()
   * {
   *   MyAgent agent("MyTeam");
   *   agent.run();
   * }
   * \endcode
   * The HumanoidAgent class handles all the communication with the server and parsing of input by using SocketComm and WorldModel. You can implement the behavior for your agent by overloading the think method. If your agent needs initialization code that should be run once at start up, overload the init method.
   */
  class HumanoidAgent
  {
  protected:
    SocketComm d_comm;
    std::string d_teamName;
    unsigned d_unum;
    bool d_debugMode;
    bool d_outputDebugFile;
    int d_sock;

    unsigned d_debuggerPort;
    std::string d_debuggerHost;

    double d_deadTime;
    /** Startup agent
     *
     * Performs the communication with the server necesary to start up the agent
     */
    void startUp();
    
    /** Initialize agent
     *
     * This method is run when the agent is started up. At this point the uniform number and all object properties are known
     */
    virtual void init() {}
    
    /** Perform think cycle
     */
    virtual void think() {}

    void connectToDebugger();
    
  public:
    HumanoidAgent(std::string teamName, std::string const host = "localhost", unsigned port = 3100, unsigned unum = 0)
      : d_comm(host, port),
        d_teamName(teamName),
        d_unum(unum),
        d_debugMode(false),
        d_deadTime(-1)
      {
      }
    
    virtual ~HumanoidAgent() {}
    
    /** Run the agent
     *
     * Start an infinite loop that updates the communication with the server and the WorldModel and calls think() at every step.
     */
    void run();

    void setDebugMode( std::string host = "localhost", unsigned port = 8492) {
      d_debuggerPort = port;
      d_debuggerHost = host;
      d_debugMode = true;
    }

    void outputDebugFile(bool b){
      d_outputDebugFile = b;
    }

    void setGamepad( std::string padAddress = "/dev/input/js0") {
      GamepadInput* pad = GamepadInput::getInstance();
      if(access(padAddress.c_str(), F_OK)){
        std::cout << "(HumanoidAgent::setGamepad) JoyStick "
             << padAddress << " is Not Found!" << std::endl;
      }
      pad->initialize(padAddress.c_str());
    }

    void setDeadTime(double t) {
      d_deadTime = t;
    }

/*
  private:
      bool inTriangle(Vector3D A, Vector3D B, Vector3D C, Vector3D P){
	  // calculate line AB
	  double vertex = (C.getY() - A.getY()) * (B.getX() - A.getX()) - (B.getY() - A.getY()) * (C.getX() - A.getX());
	  double point = (P.getY() - A.getY()) * (B.getX() - A.getX()) - (B.getY() - A.getY()) * (P.getX() - A.getX());
	  if(vertex * point < 0)
	      return false;
	  // calculate line BC
	  vertex = (A.getY() - B.getY()) * (C.getX() - B.getX()) - (C.getY() - B.getY()) * (A.getX() - B.getX());
	  point = (P.getY() - B.getY()) * (C.getX() - B.getX()) - (C.getY() - B.getY()) * (P.getX() - B.getX());
	  if(vertex * point < 0)
	      return false;
	  // calculate line CA
	  vertex = (B.getY() - C.getY()) * (A.getX() - C.getX()) - (A.getY() - C.getY()) * (B.getX() - C.getX());
	  point = (P.getY() - C.getY()) * (A.getX() - C.getX()) - (A.getY() - C.getY()) * (P.getX() - C.getX());
	  if(vertex * point < 0)
	      return false;
	  return true;
      }
*/
  };
};

#endif
