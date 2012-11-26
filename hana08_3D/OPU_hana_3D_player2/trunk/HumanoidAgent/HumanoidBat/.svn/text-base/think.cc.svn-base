#include "humanoidbat.ih"

void HumanoidBat::think()
{
  d_fitness->update();
  d_fitness->print();
  
  Behavior::clearActionCommandBehaviors();
  
  _debugLevel3("Running behaviors");
//  std::cout << std::endl << "*** Running behaviors ***" << std::endl;
  mvds::TimeVal t0 = mvds::TimeVal::getTimeOfDay();

  rf<Behavior> win = Behavior::getWin();
//  std::cout << "getWin() = " << win << std::endl;  
  
  if (!win)
  {
    _debugLevel1("No win behavior!");

  }
  else
  {
//	std::cout << "OK 1" << std::endl;		  
    _debugLevel3("Setting goal");
    win->update();
//	std::cout << "win->update() OK" << std::endl;
//     int num;
//     std::cout << "Num1 = ";
//     std::cin >> num;

    win->setGoal(new Behavior::Goal);
//	std::cout << "OK 3" << std::endl;		  
    _debugLevel3("Achieving goal " << win->ident());
//	std::cout << "Achieving goal " << win->ident() << " OK" << std::endl;
//     std::cout << "Num2 = ";
//     std::cin >> num;

    if (!(win->achieveGoal())){
      _debugLevel1("Win behavior was unable to achieve goal!");
//	  std::cout << "Win behavior was unable to achieve goal!" << std::endl;
	}
    else{
      _debugLevel3("Win behavior achieved goal!");
//	  std::cout << "Win behavior achieved goal!" << std::endl;
	}
//     std::cout << "Num3 = ";
//     std::cin >> num;

  }
  
//  std::cout << "OK 4" << std::endl;		  
     
             
  /* ---------------- Collect action commands and send them to the server ------------*/
//   WorldModel& wm = WorldModel::getInstance(); 
//   if (wm.shouldSendAction())
//   {
    _debugLevel3("Send action commands");
//    std::cout << std::endl << "*** Send action commands ***" << std::endl;
    
    _debugLevel1("FootForce: " << WorldModel::getInstance().getForceLeftFoot().length() << ", " << WorldModel::getInstance().getForceRightFoot().length());
    
    Cerebellum& cer = Cerebellum::getInstance();
//	std::cout << "OK 5" << std::endl;		  
    set<rf<Behavior> > acBehaviors = Behavior::getActionCommandBehaviors();
    _debugLevel4("Nr of action behaviors: " << acBehaviors.size());
    for (set<rf<Behavior> >::iterator iter = acBehaviors.begin(); iter != acBehaviors.end(); ++iter)
    {
    	cer.addAction((*iter)->getAction());
//	std::cout << "Added action: " << ((*iter)->getAction())->type << std::endl;
    }
//	std::cout << "OK 6" << std::endl;		  
    cer.outputCommands(d_comm);
//  }
//	std::cout << "OK 7" << std::endl;		    
  // Agent::run sends done thinking
}
