#include "cerebellum.hh"

using namespace bats;
using namespace std;

void Cerebellum::addAction(rf<Action> action)
{
	d_actions.push_back(action);	
//	std::cout << "ActionType = " << action << std::endl;
}
