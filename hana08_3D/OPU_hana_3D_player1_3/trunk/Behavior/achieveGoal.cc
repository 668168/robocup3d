#include "behavior.ih"

bool Behavior::achieveGoal()
{
  try {
//    _debugLevel1("Achieving goal in behavior " << ident());
//    std::cout << "Achieving goal in behavior " << ident() << std::endl;
    if (!d_tree)
      return true;
		
    bool succes = true;

//	std::cout << "OK 3-1: " << d_childrenCommitted << std::endl;
	
	if (d_childrenCommitted)
	{
//	   _debugLevel1(ident() << " is committed, doing last chosen");
//	   std::cout << ident() << " is committed, doing last chosen" << std::endl;
	   succes = doLastChosen();
    }
    else
    {
      d_lastChosen.clear();
      succes = false;
      
//	  std::cout << "d_curStep = " << d_curStep << std::endl;
      // Try slots in next sequence step (if there is a step left and we are not committed)
      if (d_curStep >= 0)
      {
//        _debugLevel1("Doing next step");
//		std::cout << "Doing next step" << std::endl;
        succes = doNextStep();
      }
      else
        d_curStep = 0;
        
      if (!succes)
      {
//        _debugLevel1("Doing current step");
//		std::cout << "Doing current step" << std::endl;
        succes = doCurrentStep();
      }
    }
/*
    if (!succes)
    {
//      _debugLevel1(ident() << " failed!");
        std::cout << ident() << " failed!" << std::endl;
// 	int num;
// 	std::cout << "Num = ";
// 	std::cin >> num;
    }
    else
        std::cout << ident() << " succeeded!" << std::endl;
*/
    return succes;

  } catch (BatsException *e) {
    BATS_CATCH_FRAME(e);
  }
  d_reset = false;
}

