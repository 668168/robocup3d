#include "block.ih"

void Block::update()
{
    Behavior::update();
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    ballPos.setZ(0);

    if(wm.visibleObject(Types::BALL) && wm.getObjectVector(Types::BALL).getMu().length() > 1.8 )
    {
	d_ballHoldTime = wm.getTime();


    }
    
}
