#include "behavior.ih"

void Behavior::createBehaviors()
{
  try {
    Conf& conf = Conf::getInstance();
    WorldModel& wm = WorldModel::getInstance();
  
    vector<XMLNode> players;
    string playerClass;
  
    _debugLevel3("Creating behaviors for player " << wm.getUnum());
  
    conf.getRoot().findAll(players, "player");
    for (vector<XMLNode>::iterator iter = players.begin(); iter != players.end(); ++iter)
      if (static_cast<unsigned>(atoi(iter->getProp("id").c_str())) == wm.getUnum() || atoi(iter->getProp("id").c_str()) == 0)
				playerClass = iter->getProp("class");
    _debugLevel3("Player class: " << playerClass);
  	_flog("Player class: %s", playerClass.c_str());
  
    string path = "/conf/player-class[@id='" + playerClass + "']/behaviors/behavior[@id='win']";
    _debugLevel4(path);
    XMLNodeSet set = conf.selectXPath(path);

    if (set.empty())
      throw runtime_error(string() + "createBehavior: '" + path + "' not found!");

    _debugLevel4(set.size());
    XMLNode win = set.front();
    s_win = buildTree(win, playerClass);
    
    /*vector<XMLNode> playerClasses;
    conf.getRoot().findAll(playerClasses, "player-class");
    
    for (vector<XMLNode>::iterator iter = playerClasses.begin(); iter != playerClasses.end(); ++iter)
    {
      if (iter->getProp("id") == playerClass)
      {
        XMLNode behaviors = *iter;
        
        vector<XMLNode> behaviorsNodes;
        iter->findAll(behaviorsNodes, "behaviors");
        _debugLevel4("number of behaviors nodes: " << behaviorsNodes.size());
        
        for (vector<XMLNode>::iterator bsIter = behaviorsNodes.begin(); bsIter != behaviorsNodes.end(); ++bsIter)
        {
          for(XMLNode b = bsIter->getChildren(); b; b = b.getNext())
      	  {
      	    if (b.getName() != "behavior")
              continue;
        
      	    rf<Behavior> behavior = 0;
            
      	    // --------------------------- Add new behavior types here -----------------------
      	    if (b.getProp("type") == "MoveHingeJoint")
      	      behavior = new MoveHingeJoint(b.getProp("id"), playerClass);
      	      
      	    else if (b.getProp("type") == "MoveUniversalJoint")
      	      behavior = new MoveUniversalJoint(b.getProp("id"), playerClass);
      	      
       	    else if (b.getProp("type") == "MoveJointTo")
      	      behavior = new MoveJointTo(b.getProp("id"), playerClass);

      	    else if (b.getProp("type") == "Wait")
      	      behavior = new Wait(b.getProp("id"), playerClass);
      	      
      	    else if (b.getProp("type") == "Beam")
      	      behavior = new Beam(b.getProp("id"));
      	      
       	    else if (b.getProp("type") == "ScriptPlayer")
      	      behavior = new ScriptPlayer(b.getProp("id"), playerClass);
      	      
       	    else if (b.getProp("type") == "Sine")
      	      behavior = new Sine(b.getProp("id"), playerClass);
      	      
       	    else if (b.getProp("type") == "RaiseHands")
      	      behavior = new RaiseHands(b.getProp("id"));
      	      
       	    else if (b.getProp("type") == "TestSander")
      	      behavior = new TestSander(b.getProp("id"));

       	    else if (b.getProp("type") == "Balans")
      	      behavior = new Balans(b.getProp("id"), playerClass);

       	    else if (b.getProp("type") == "Tril")
      	      behavior = new Tril(b.getProp("id"), playerClass);

       	    else if (b.getProp("type") == "Empty")
      	      behavior = new Empty(b.getProp("id"));
      	    
      	    else if (b.getProp("type") == "WalkTo")
      	      behavior = new WalkTo(b.getProp("id"), playerClass);
      	      
      	    else if (b.getProp("type") == "WalkStraightTo")
      	      behavior = new WalkStraightTo(b.getProp("id"), playerClass);
      	       
      	    else if (b.getProp("type") == "Keeper")
      	      behavior = new Keeper(b.getProp("id"), playerClass);

      	    else if (b.getProp("type") == "CanKick")
      	      behavior = new CanKick(b.getProp("id"), playerClass);  

      	    else if (b.getProp("type") == "Spread")
      	      behavior = new Spread(b.getProp("id"), playerClass);

      	    else if (b.getProp("type") == "CanTurnLeft")
      	      behavior = new CanTurnLeft(b.getProp("id"), playerClass);   
      	      
      	    else if (b.getProp("type") == "CanTurnRight")
      	      behavior = new CanTurnRight(b.getProp("id"), playerClass);   
      	      
      	      
      	      
      	      

            else if (b.getProp("type") == "BalanceLearn")
              behavior = new BalanceLearn(b.getProp("id"), playerClass);
              
      	    // --------------------------- End add new behavior types ------------------------
            if (!behavior)
            {
              throw runtime_error(string("Behavior type doesn't exist: " + b.getProp("type")));
              continue;
            }
            
           
            behavior->setPlayerClass(playerClass);
              
      	    _debugLevel2("New behavior: " << behavior->getName() << " " << behavior->getId());
              
      	    for(XMLNode s = b.getChildren(); s; s = s.getNext())
            {
              if (s.getName() != "slot")
                continue;
                
              string index = s.getProp("index");
              unsigned step = atoi(index.substr(0, index.find("-")).c_str());
              unsigned slot = atoi(index.substr(index.find("-") + 1).c_str());
                
              _debugLevel2("Adding to slot " << step << "-" << slot << ":");
              for (XMLNode sb = s.getChildren(); sb; sb = sb.getNext())
              if (sb.getName() == "behavior")
      		    {
      		      _debugLevel2("\t" << sb.getProp("refid"));
      		      try{
      			      behavior->addToSlot(s_behaviors[sb.getProp("refid")], step, slot);
      			    }
      			    catch(BatsException *e)
      			    {
      			    	cerr << "Could not find refid: " << sb.getProp("refid") << endl;
      			    	_debugLevel1("Could not find refid: " << sb.getProp("refid"));
      			    	_log("Could not find refid, see errpr logs");
      			    }
      			   
      		    }
      	    }
              
      	    s_behaviors[b.getProp("id")] = behavior;
      	  } // for behavior
      	} // for behaviors
      } // if playerClass
	  } // for playerClasses
	  */
  } catch (BatsException *e) {
    BATS_CATCH_FRAME(e);
  }
}
