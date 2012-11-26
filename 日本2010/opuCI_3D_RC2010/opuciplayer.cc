#include "opuciplayer.hh"
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <signal.h>
#include "Logger/logger.hh"
#include "fitnesswalk.hh"
#include "fitnessturn.hh"

using namespace bats;
using namespace std;

void sigINT(int a)
{
  //Logger::getInstance().destroy();
  cerr << "Caught sigint, exiting.." << endl;
  exit(1);
}

void sigTERM(int a)
{
  //Logger::getInstance().destroy();
  cerr << "Caught sigterm, exiting.." << endl;
  exit(3);
}

void sigKILL(int a)
{
  //Logger::getInstance().destroy();
  cerr << "Caught sigkill, exiting.." << endl;
  exit(2);
}

void printHelp()
{
  cerr << "****opuCI_Player****" << endl;
  cerr << "arguments:" << endl;
  cerr << " --help		: print this message" << endl;
  cerr << endl;
  cerr << " -t <TeamName>		: set team name	(opuCI_3D)" << endl;
  cerr << " -u <UniformNumber>	: set uniform number	(3)" << endl;
  cerr << " -c <ConfFile>		: set configure file	(opuCI_3D_conf.xml)" << endl;
  cerr << "			  (Gamepad_conf.xml -> playable agent)" << endl;
  cerr << " -g <PadID>		: set gamepad ID	(0)" << endl;
  cerr << endl;
  cerr << " -h <ServerHost>		: set server host	(localhost)" << endl;
  cerr << " -p <ServerPort>		: set server port	(3100)" << endl;
  cerr << endl;
  cerr << " -d 		: try to connect to Visual Debugger" << endl;
  cerr << " -dh <DebuggerHost>	: set debugger host	(localhost)" << endl;
  cerr << " -dp <DebuggerPort>	: set debugger port	(8492)" << endl;
  cerr << " -df		: output debug file" << endl;
  cerr << " -e  <TimeToDead>		: set time to dead	(-1)" << endl;

  exit(0);
}

int main(int argc, char const ** argv)
try
{
  // TODO: We need a better way to exit! (better for the cluster)

  signal(SIGINT,sigINT);
  signal(SIGKILL,sigKILL);
  signal(SIGTERM,sigTERM);

  srand(time(0));



//  cout << "This is the stdout, see others for more information." << endl;
  
  bool errorLogFile = false;
  unsigned errorBufferSize = 0;
  string teamName = "opuCI_3D";
  string conffile = "opuCI_3D_conf.xml";
  string host = "localhost";
  string fitness = "";
  unsigned unum = 3;
  unsigned port = 3100;
  bool debugMode = false;
  bool outputDebugFile = false;
  string debuggerHost = "127.0.0.1";
  unsigned debuggerPort = 8492;
  string padAddress = "0";
  double timeToDead = -1;

  for (int a = 1; a < argc; a++)
    if (string(argv[a]) == "-t")
      teamName = argv[++a];
    else if (string(argv[a]) == "-c")
      conffile = argv[++a];
    else if (string(argv[a]) == "-h")
      host = argv[++a];
    else if (string(argv[a]) == "-l")
      errorLogFile = true;
    else if (string(argv[a]) == "-b")
      errorBufferSize = atoi(argv[++a]);
    else if (string(argv[a]) == "-u")
      unum = atoi(argv[++a]);
    else if (string(argv[a]) == "-p")
      port = atoi(argv[++a]);
    else if (string(argv[a]) == "-f")
      fitness = argv[++a];
    else if ( (string(argv[a]) == "--debug-message") || string(argv[a]) == "-d")
      debugMode = true;
    else if ( string(argv[a]) == "-df")
      outputDebugFile = true;
    else if (string(argv[a]) == "-dh")
      debuggerHost = argv[++a];
    else if (string(argv[a]) == "-dp")
      debuggerPort = atoi(argv[++a]);
    else if (string(argv[a]) == "--help")
      printHelp();
    else if (string(argv[a]) == "-g")
      padAddress = argv[++a];
    else if (string(argv[a]) == "-e")
      timeToDead = atof(argv[++a]);

  OpuciPlayer a(teamName, conffile, host, port, unum);
  //, debugMode, debuggerHost, debuggerPort);
  if(debugMode)
    a.setDebugMode(debuggerHost, debuggerPort);

  if (!fitness.empty())
    if (fitness == "walk")
      a.setFitness(new FitnessWalk);
    else if (fitness == "turn")
      a.setFitness(new FitnessTurn);

  a.outputDebugFile(outputDebugFile);

  if (timeToDead > 0)
    a.setDeadTime(timeToDead);

  if (conffile == "Gamepad_conf.xml")
  {
    padAddress = "/dev/input/js"+padAddress;
    a.setGamepad(padAddress);
  }

  a.run();
  
  return 0;
}
/*catch(runtime_error e)
{
  //All is LOST... nothing to do here but die
  //Logger::getInstance().log(std::string() + "Caught std::runtime_error (" + typeid(e).name() + "): " + e.what());
  //Logger::destroy();
  cerr << "Caught std::runtime_error (" << typeid(e).name() << "): " << e.what();
}
catch(exception e)
{
  //All is LOST... nothing to do here but die
  //Logger::getInstance().log(std::string() + "Caught std::exception (" + typeid(e).name() + "): " + e.what());
  //Logger::destroy();
  cerr << "Caught std::exception (" << typeid(e).name() << "): " << e.what();
 }*/
 catch (BatsException *e)
   {
     cerr << "Bats exception trace: " << endl << e->messages().str() << endl;
   }
