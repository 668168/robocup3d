#include "behavior.ih"

void Behavior::update()
{
//  std::cout << " -> Behavior::update()" << std::endl;
  WorldModel& wm = WorldModel::getInstance();
  
	// Check if the last chosen subbehaviors are committed
	d_childrenCommitted = false;
	for (unsigned i = 0; i < d_lastChosen.size(); ++i)
	{
	  if (d_lastChosen[i]->getLastUpdate() < wm.getTime())
        d_lastChosen[i]->update();
  	  
//	  _debugLevel4(ident() << ": " << d_lastChosen[i]->ident() << " -> " << (d_lastChosen[i]->isCommitted() ? "yes" : "no"));
//      std::cout << ident() << ": " << d_lastChosen[i]->ident() << " -> " << (d_lastChosen[i]->isCommitted() ? "yes" : "no") << std::endl;
	  if (d_lastChosen[i]->shouldCommit() && d_lastChosen[i]->isCommitted())
	    d_childrenCommitted = true;
	}
  
  d_committed = false;
  if (d_scicc && d_childrenCommitted)
  {
    _debugLevel4("Scicc! " << ident());
    d_committed = true;
  }
//  std::cout << "Behavior::update()" << std::endl;
//  std::cout << "  d_scicc: " << d_scicc << std::endl;
//  std::cout << "  d_childrenCommitted: " << d_childrenCommitted << std::endl;
//  std::cout << "  d_committed: " << d_committed << std::endl;
  
  d_lastUpdate = wm.getTime();
}

