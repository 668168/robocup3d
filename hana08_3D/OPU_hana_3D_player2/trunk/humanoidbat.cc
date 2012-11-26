/* GPL */

#include "humanoidbat.hh"
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
	Logger::getInstance().destroy();
  cerr << "Caught sigint, exiting.." << endl;
  exit(1);
}

void sigTERM(int a)
{
	Logger::getInstance().destroy();
  cerr << "Caught sigterm, exiting.." << endl;
  exit(3);
}

void sigKILL(int a)
{
	Logger::getInstance().destroy();
  cerr << "Caught sigkill, exiting.." << endl;
  exit(2);
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
  string teamName = "OPU_hana_3D";
  string conffile = "conf.xml";
  string host = "localhost";
  string fitness = "";
  unsigned unum = 0;
  unsigned port = 3100;
  double exitTime = 0.0;
  
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
	else if (string(argv[a]) == "-e")
	  exitTime = atof(argv[++a]);

  ostringstream logfile;
  logfile << "player" << teamName << unum << ".log";
  Logger::initialize(logfile.str());
  //  cerr << "Unum: " << unum << endl;

  HumanoidBat a(teamName, conffile, host, port, unum, exitTime);

  if (!fitness.empty())
    if (fitness == "walk")
      a.setFitness(new FitnessWalk);
    else if (fitness == "turn")
      a.setFitness(new FitnessTurn);

  a.run();
  
//  std::cout << teamName << " #" << unum << " Finished!!" << std::endl;

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
