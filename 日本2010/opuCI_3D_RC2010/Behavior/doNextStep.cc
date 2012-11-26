#include "behavior.ih"

bool Behavior::doNextStep()
{
  try
  {
    WorldModel& wm = WorldModel::getInstance();
    
    if (d_curStep < static_cast<int>(d_tree->size()) - 1)
    {
//      std::cout << "Trying next step " << d_curStep + 1 << " of behavior " << ident() << std::endl;
      rf<AST::Node> nextStepNode = d_tree->getChild(d_curStep + 1);
      bool stepHasBehaviors = false;
      // Sort all behaviors in the slots by capability
      for (unsigned i = 0; i < nextStepNode->size(); ++i)
      {
        rf<AST::Node> slot = nextStepNode->getChild(i);
        if (slot->size() == 0)
          continue;

        stepHasBehaviors = true;

        rf<Goal> g = generateGoal(d_curStep + 1, i);
        // Set goals on behaviors in slots
        // std::cout << "Setting goal on behaviors in slot " << (d_curStep + 1) << "-" << i << std::endl;
        for (unsigned j = 0; j < slot->size(); ++j)
        {
//    std::cout << "doNextStep.cc " << ident() << " - Last update: " << rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->getLastUpdate() << " " << wm.getTime() << std::endl;
          if (rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->getLastUpdate() < wm.getTime()){
//      std::cout << "B -> ";
            rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->update();
//   std::cout << " -> A" << std::endl;
          }
          rf_cast<BehaviorNode>(slot->getChild(j))->getBehavior()->setGoal(g);
        }
       
        // Sort behaviors by capability
        sort(slot->begin(), slot->end(), CapabilityCompare());
        
        // Give up when the first behavior doesnt have high enough capability
        ConfidenceInterval c = rf_cast<BehaviorNode>(*(slot->begin()))->getBehavior()->getCapability();

        // ************ for debug ****************
        std::string actname = rf_cast<BehaviorNode>(slot->getChild(0))->getBehavior()->ident();
        if(actname.find("move") == std::string::npos )
        {
//          std::cout << "Action(nextstep):  " << rf_cast<BehaviorNode>(slot->getChild(0))->getBehavior()->ident() << std::endl;
          std::stringstream ss;
          ss << " <font color=blue>" << actname << "</font>(nxt)[" << static_cast<int>(c.first*100+c.second*100) << "]";
          wm.addDebugMessage(WorldModel::COMMENT,ss.str());

          if( actname.find("_s") != std::string::npos )
          {
            ss.str("");
            ss << actname << "(nxt)";
            wm.setDebugMessage(WorldModel::BEHAVIOR, ss.str());
          }
        }

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
