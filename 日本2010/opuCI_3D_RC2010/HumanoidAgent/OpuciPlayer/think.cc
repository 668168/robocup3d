#include "opuciplayer.ih"

void OpuciPlayer::think()
{
  d_fitness->update();
  d_fitness->print();

  Behavior::clearActionCommandBehaviors();

  mvds::TimeVal t0 = mvds::TimeVal::getTimeOfDay();

  rf<Behavior> win = Behavior::getWin();

  if (!win)
  {
    _debugLevel1("No win behavior!");
  }
  else
  {
    _debugLevel3("Setting goal");
    win->update();

    win->setGoal(new Behavior::Goal);

    _debugLevel3("Achieving goal " << win->ident());


    if (!(win->achieveGoal())){
      _debugLevel1("Win behavior was unable to achieve goal!");
// std::cout << "Win behavior was unable to achieve goal!" << std::endl;
    }
    else{
      _debugLevel3("Win behavior achieved goal!");
// std::cout << "Win behavior achieved goal!" << std::endl;
    }
  }


  /* ---------------- Collect action commands and send them to the server ------------*/
//   WorldModel& wm = WorldModel::getInstance(); 
//   if (wm.shouldSendAction())
//   {
  _debugLevel3("Send action commands");
//    std::cout << std::endl << "*** Send action commands ***" << std::endl;

  _debugLevel1("FootForce: " << WorldModel::getInstance().getForceLeftFoot().length() << ", " << WorldModel::getInstance().getForceRightFoot().length());

  Cerebellum& cer = Cerebellum::getInstance();

  set<rf<Behavior> > acBehaviors = Behavior::getActionCommandBehaviors();
  _debugLevel4("Nr of action behaviors: " << acBehaviors.size());
  for (set<rf<Behavior> >::iterator iter = acBehaviors.begin(); iter != acBehaviors.end(); ++iter)
  {
    cer.addAction((*iter)->getAction());
    // std::cout << "Added action: " << ((*iter)->getAction())->type << std::endl;
  }

  cer.outputCommands(d_comm);
//  }

  // Agent::run sends done thinking
}
