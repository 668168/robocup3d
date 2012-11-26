#include "behavior.ih"

bool Behavior::achieveGoal()
{
  try {
    if (!d_tree)
      return true;

    bool succes = true;

    if (d_childrenCommitted)
    {
       //std::cout << ident() << " is committed, doing last chosen" << std::endl;
      succes = doLastChosen();
    }
    else
    {
      d_lastChosen.clear();
      succes = false;

      //Try slots in next sequence step (if there is a step left and we are not committed)
      if (d_curStep >= 0)
      {
        //std::cout << "Doing next step" << std::endl;
        succes = doNextStep();
      }
      else
        d_curStep = 0;

      if (!succes)
      {
        //std::cout << "Doing current step" << std::endl;
        succes = doCurrentStep();
      }
    }

    return succes;

  } catch (BatsException *e) {
    BATS_CATCH_FRAME(e);
  }
  d_reset = false;
}

