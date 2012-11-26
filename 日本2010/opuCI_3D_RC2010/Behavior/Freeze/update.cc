#include "freeze.ih"

void Freeze::update()
{
    Behavior::update();

    WorldModel& wm = WorldModel::getInstance();

    if(d_startCounting && wm.getTime() - d_freezingTime > 1.2)
	wm.setFreeze(false);

}
