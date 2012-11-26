#include "empty.ih"

rf<Behavior::State> Empty::getCurrentState()
{
	rf<State> s(new State);
	return s;
}
