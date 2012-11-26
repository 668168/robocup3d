//#include "kick.hh"
#include "conf.hh"
#include <iostream>
//#include "talent.hh"
//#include "zero.hh"

using namespace bats;
using namespace std;

//disabled for ccbuild
int main()
{
  
  Zero test("blaat", "default");
  test.generateConf(cout);

  Vector3D startPos(0, 0, 0);
  Vector3D startSpeed(100.0, 0, 0);

  /*Behavior::createBehaviors();
  
  rf<Behavior> test4 = Behavior::getBehavior("test4");
    
  rf<Behavior::OrNode> anOr;
  rf<Behavior::AndNode> anAnd;
  
  rf<Behavior::Goal> goal = new Behavior::Goal;

  anOr = goal->addDisjunct();
  anAnd = anOr->addConjunct();
  anAnd->addVar("a",1.0,2.0);
  anAnd->addVar("a",8.0,9.0);
  
  Behavior::ConfidenceInterval interval = test4->setGoal(goal);
  cout << interval.first << " " << interval.second << endl;
  bool achieved = test4->achieveGoal();
  cout << (achieved ? "JA!! :-)" : "NEE!! :-(") << endl;*/
//  test.addToSlot(new Test, "1-2");*/
}
