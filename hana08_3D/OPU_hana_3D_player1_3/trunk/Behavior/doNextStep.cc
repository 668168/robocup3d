#include "behavior.ih"

bool Behavior::doNextStep()
{
  try
  {
    WorldModel& wm = WorldModel::getInstance();
    
    if (d_curStep < static_cast<int>(d_tree->size()) - 1)
    {

      _debugLevel3("Trying next step " << d_curStep + 1 << " of behavior " << ident());
//      std::cout << "Trying next step " << d_curStep + 1 << " of behavior " << ident() << std::endl;
      rf<AST::Node> nextStepNode = d_tree->getChild(d_curStep + 1);
//      std::cout << "nextstepnode end" << std::endl;
      bool stepHasBehaviors = false;      
      // Sort all behaviors in the slots by capability
      for (unsigned i = 0; i < nextStepNode->size(); ++i)
      {

//	  std::cout << "forloop 1 :" << nextStepNode->size() << std::endl;
        rf<AST::Node> slot = nextStepNode->getChild(i);
//	std::cout << "forloop 2 :" << slot->size() << std::endl;      
        if (slot->size() == 0)
          continue;
        
        stepHasBehaviors = true;
        
        rf<Goal> g = generateGoal(d_curStep + 1, i);
        // Set goals on behaviors in slots
//	std::cout << "forloop 3"  << std::endl;      
        _debugLevel3("Setting goal on behaviors in slot " << (d_curStep + 1) << "-" << i);
//        std::cout << "Setting goal on behaviors in slot " << (d_curStep + 1) << "-" << i << std::endl;
        for (unsigned j = 0; j < slot->size(); ++j)
        {
//		  std::cout << "doNextStep.cc " << ident() << " - Last update: " << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->getLastUpdate() << " " << wm.getTime() << std::endl;
      	  if (rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->getLastUpdate() < wm.getTime()){
//		    std::cout << "B -> ";
  	        rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->update();
//			std::cout << " -> A" << std::endl;
		  }
          rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->setGoal(g);
	      }
	      
        // Sort behaviors by capability
//		std::cout << "Let's sort!!" << std::endl;
//		for(unsigned j = 0; j < slot->size(); ++j)
//			std::cout << "  " << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->ident() << std::endl;
        sort(slot->begin(), slot->end(), CapabilityCompare());
//		std::cout << "Sorted!!" << std::endl;
//		for(unsigned j = 0; j < slot->size(); ++j)
//			std::cout << "  " << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->ident() << std::endl;	
      
        // Give up when the first behavior doesnt have high enough capability
        ConfidenceInterval c = rf_cast<BehaviorNode>(*(slot->begin()))->getBehavior()->getCapability();
        if (c.first + c.second < MIN_C)
          return false;
      }
      
      if (!stepHasBehaviors)
        return false;
      
      bool giveUp = false;
      // Run the behaviors in the slots
      for (unsigned i = 0; i < nextStepNode->size() && !giveUp; ++i)
      {
        rf<AST::Node> slot = nextStepNode->getChild(i);
        if (slot->size() == 0)
          continue;
          
        bool behRan = false;
        for (unsigned j = 0; j < slot->size(); ++j)
        {
          if (behRan)
            rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->reset();
          else if (rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->achieveGoal())
          {
            behRan = true;
            d_lastChosen.push_back(rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior());
          }
          else 
            rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->reset();
        }
        
        if (!behRan)
        {
          giveUp = true;
          _debugLevel4("No behavior ran in slot " << i);
        }
      }
       
      // If nothing went wrong, we're in the next step
      if (!giveUp)
      {
        _debugLevel4("Next step ran succesfully!");
        d_curStep++;
        return true;
      }
      // Else reset every behaviour in this step
      else
      {
        _debugLevel4("Something went wrong, giving up and resetting...");
        for (unsigned i = 0; i < nextStepNode->size(); ++i)
        {
          rf<AST::Node> slot = nextStepNode->getChild(i);
          for (unsigned j = 0; j < slot->size(); ++j)
            rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->reset();
        }
        return false;
      }
    }
    // There is no next step
    else
      return false;
      
  }
  catch (BatsException *e)
  {
    BATS_CATCH_FRAME(e);
  }
}
