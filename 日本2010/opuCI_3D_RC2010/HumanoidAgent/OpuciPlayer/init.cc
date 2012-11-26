#include "opuciplayer.ih"

void OpuciPlayer::init()
{

  WorldModel& wm = WorldModel::getInstance();

  wm.setTeamName(d_teamName);

  Conf::initialize(d_confFile);

  // Read the joint constraints from the configuration.
  XMLNodeSet constraints = Conf::getInstance().selectXPath("/conf/joints/joint");

  if (constraints) {
    for (XMLNodeSet::iterator i = constraints.begin();
	 i != constraints.end(); ++i) {
      wm.setJointConstraints(static_cast<Types::Joint>(atoi((*i).getProp("id").c_str())),
			     atof((*i).getProp("min").c_str()),
			     atof((*i).getProp("max").c_str()));
    }
  } else {
    for (unsigned i = 0; i < Types::NJOINTS; ++i)
      wm.setJointConstraints(static_cast<Types::Joint>(i),-180,180);
  }
  
  _debugLevel4("Creating behaviors");
  Behavior::createBehaviors();
   
  _debugLevel4("Initing logger");
  //  ostringstream logfile;
//  logfile << "player" << 0/*wm.getUnum()*/ << d_teamName/*wm.getTeamName()*/ << ".log";
//  logfile << "player" << d_teamName << d_unum << ".log";
  _debugLevel3("logfile: " << logfile.str());

  //  Logger::initialize(logfile.str());
  //  Logger::getInstance().disable();
  
#ifdef BATS_NO_LOGGER
  //  Logger::getInstance().disable();
#endif

  // Initialize the fitness function.
  d_fitness->initCommand(d_comm);
  d_fitness->init();

}
