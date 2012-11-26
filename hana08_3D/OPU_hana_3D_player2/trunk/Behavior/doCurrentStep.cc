#include "behavior.ih"

#include <algorithm>

bool Behavior::doCurrentStep()
{
  try
  {
      _debugLevel3("Trying current step " << d_curStep << " of behavior " << ident());
      rf<AST::Node> curStepNode = d_tree->getChild(d_curStep);

      WorldModel& wm = WorldModel::getInstance();
      
      // Sort all behaviors in the slots by capability
      for (unsigned i = 0; i < curStepNode->size(); ++i)
      {
        rf<AST::Node> slot = curStepNode->getChild(i);
        if (slot->size() == 0)
          continue;
        _debugLevel3(ident() << " - Slot size: " << slot->size());
//		std::cout << ident() << " - Slot size: " << slot->size() << std::endl;
//        std::cout << "  Current step: " << d_curStep << std::endl; 
        
        rf<Goal> g = generateGoal(d_curStep, i);
        // Set goals on behaviors in slots
      
        _debugLevel3(ident() << " - Setting goal on behaviors in slot " << d_curStep << "-" << i);
//        std::cout << ident() << " - Setting goal on behaviors in slot " << d_curStep << "-" << i << std::endl;
        for (unsigned j = 0; j < slot->size(); ++j)
        {
//		  std::cout << std::endl;
	
          _debugLevel3(ident() << " - Behavior Node: " << slot->getChild(j));
          _debugLevel3(ident() << " - Behavior: " << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior());
      
          _debugLevel4(ident() << " - Last update: " << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->getLastUpdate() 
		       << " " << wm.getTime());
		  
//		  std::cout << ident() << " - Behavior Node: " << slot->getChild(j) << std::endl;
//          std::cout << ident() << " - Behavior: " << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior() << std::endl;

//          std::cout << ident() << " - Last update: " << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->getLastUpdate() 
//		    << " " << wm.getTime() << std::endl;
          
      	  if (rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->getLastUpdate() < wm.getTime()){
//			std::cout << "Before update" << std::endl;
  	        rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->update();
//			std::cout << " -> After update" << std::endl;
		  }
//		  std::cout << "rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior(): " 
//			    << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior() << std::endl;
          rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->setGoal(g);
//		  std::cout << std::endl;
        }
      
        _debugLevel3(ident() << " - Sorting behaviors by capability");
        // Sort behaviors by capability
//		std::cout << "Let's sort!!" << std::endl;
//		for(unsigned j = 0; j < slot->size(); ++j)
//		    std::cout << "  " << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->ident() << std::endl;
		sort(slot->begin(), slot->end(), CapabilityCompare());
//		std::cout << "Sorted!!" << std::endl;
//		for(unsigned j = 0; j < slot->size(); ++j)
//		    std::cout << "  " << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->ident() << std::endl;		
		
		_debugLevel3(ident() << " - Check confidence interval");
		// Give up when the first behavior doesnt have high enough capability
		ConfidenceInterval c = rf_cast<BehaviorNode>(*(slot->begin()))->getBehavior()->getCapability();
//		std::cout << "Get ConfidenceInterval: [" << c.first << ", " << c.second << "]" << std::endl << std::endl;
		if (c.first + c.second < MIN_C)
		    return false;
      }
      
      bool giveUp = false;
      // Run the behaviors in the slots
      _debugLevel3(ident() << " - Run the behaviors in the slots");
//	  std::cout << ident() << " - Run the behaviors in the slots" << std::endl;
      for (unsigned i = 0; i < curStepNode->size() && !giveUp; ++i)
      {
        _debugLevel3(ident() << " - Slot " << i);
//		  std::cout << ident() << " - Slot " << i << std::endl;
        rf<AST::Node> slot = curStepNode->getChild(i);
        if (slot->size() == 0)
          continue;
          
        bool behRan = false;
        for (unsigned j = 0; j < slot->size(); ++j)
        {
          rf<Behavior> behavior = rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior();
//          std::cout << "In behavior::doCurrentStep()" << std::endl;
//          std::cout << "  behavior = " << behavior->ident() << std::endl;
//          std::cout << "  behRan = " << behRan << std::endl;
          //_debugLevel1("
          if (behRan)
            behavior->reset();
          else if (behavior->achieveGoal())
          {
			_debugLevel4("Saving last chosen: " << behavior->ident());
//            std :: cout << "Saving last chosen: " << behavior->ident() << std::endl; 
            d_lastChosen.push_back(behavior);
            behRan = true;
          }
          else 
            behavior->reset();
        }
        
        if (!behRan)
        {
          giveUp = true;
          _debugLevel4(ident() << " - No behavior ran in slot " << i);
        }
      }
       
      // If nothing went wrong, we're in the next step
      if (!giveUp)
      {
        _debugLevel4(ident() << " - Current step ran succesfully!");
//		std::cout << ident() << " - Current step ran succesfully!" << std::endl;
        return true;
      }
      // Else reset every behaviour in this step
      else
      {
        _debugLevel4(ident() << " - Something went wrong, giving up and resetting...");
//        std::cout << ident() << " - Something went wrong, giving up and resetting..." << std::endl;
        for (unsigned i = 0; i < curStepNode->size(); ++i)
        {
          rf<AST::Node> slot = curStepNode->getChild(i);
          for (unsigned j = 0; j < slot->size(); ++j)
            rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->reset();
        }
        return false;
      }
     
  }
  catch (BatsException *e)
  {
    BATS_CATCH_FRAME(e);
  }
}

/*
#include "behavior.ih"

bool Behavior::doCurrentStep()
{
  bool giveUp = false;

  try
  {
    _debugLevel3("Trying current step " << d_curStep << " of behavior " << ident());

    // Generate goals for slots in the current sequence step
    rf<AST::Node> curStepNode = d_tree->getChild(d_curStep);
  
    // Go through all parallel slots in this step
    for (unsigned i = 0; i < curStepNode->size(); ++i)
    {
      bool subBehRan = false;

      _debugLevel3("Step " << d_curStep);
      rf<AST::Node> slot = curStepNode->getChild(i);
      //if (slot->size() == 0)
      //  continue;

      rf<Goal> g = generateGoal(d_curStep, i);
      // Set goals on behaviors in slots
      _debugLevel3("Setting goal on behaviors in slot " << (d_curStep) << "-" << i);
      for (unsigned j = 0; j < slot->size(); ++j)
        rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->setGoal(g);
    
      // Sort behaviors by capability
      sort(slot->begin(), slot->end(), CapabilityCompare());
    
      // Go through the behaviors in this slot, from high capability to low capability
      AST::Node::iterator iter;
      for (iter = slot->begin(); iter != slot->end(); ++iter)
      {
        rf<BehaviorNode> bNode = rf_cast<BehaviorNode>(*iter);
        if (giveUp || subBehRan)
          bNode->getBehavior()->reset();
        else
        {
          ConfidenceInterval c = bNode->getBehavior()->getCapability();
          _debugLevel3(bNode->getBehavior()->ident() << " has capability (" << c.first << ", " << c.second << ")");
      
          // If the capability of this behavior is too low, we have no good behaviors left, so we can't achieve our goal
          if (c.first + c.second < MIN_C)
          {
            _debugLevel3("capability not high enough");
            
            bNode->getBehavior()->reset();
            giveUp = true;
            continue;
          }
      
          // If this behavior is able to achieve it's sub goal, we are done with this slot
          if (bNode->getBehavior()->achieveGoal())
          {
            _debugLevel3(bNode->getBehavior()->ident() << " ran");
            subBehRan = true;
          }
          else
          {
            _debugLevel3(bNode->getBehavior()->ident() << " didn't run");
            bNode->getBehavior()->reset();
          }
        }
      }
      // No behavior has been run succesfully, blah, give up
      if (!subBehRan)
        giveUp = true;
    }
  
    // If all went well, some sub behaviors have been run succesfully and we arrived here and we're able to achieve our goal
    return !giveUp;
  }
  catch (BatsException *e)
  {
    BATS_CATCH_FRAME(e);
  }
}
*/
