#include "humanoidagent.ih"

void HumanoidAgent::run()
{
  // Startup agent
  startUp();
  
  // Get our worldmodel and stuff
  Cochlea& cochlea = SCochlea::getInstance();
  WorldModel& wm = SWorldModel::getInstance();
  AgentSocketComm& comm = SAgentSocketComm::getInstance();
  AgentModel& am = SAgentModel::getInstance();


	// Get first message
	comm.update();
	wm.update();
	am.update();
	unsigned i(0);

	while(wm.getNumMsgReceived() < 5 && ++i < 200) /// \todo Tweak to a minimum possible number of messages before sending init is ok.
	{
  	comm.update();
  	cochlea.update();
		wm.update();
  	am.update();
  }
	
	//Send init
  comm.init(d_unum, d_teamName);

	//Wait for unum
	while(wm.getNumMsgReceived() < 10 && am.getUnum() == 0)//Failsafe max messages
	{
  	comm.update();
  	cochlea.update();
    _debugLevel1("Hoi 1");
		wm.update();
    _debugLevel1("Hoi 2");
  	am.update();
    _debugLevel1("Hoi 3");
  }
  
  _debugLevel1("Hoi 4");
	//Init behavior system
  init();
  _debugLevel1("Hoi 5");

  while(!d_die)
  {
    _debugLevel4("----------------------- New think cycle ------------------------");
  
  	comm.update();
  	cochlea.update();
    wm.update();
  	am.update();

    think();
    
  }

}
