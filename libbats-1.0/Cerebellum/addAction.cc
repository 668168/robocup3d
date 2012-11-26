#include "cerebellum.ih"

void Cerebellum::addAction(rf<Action> action)
{
	d_actions.push_back(action);
}
