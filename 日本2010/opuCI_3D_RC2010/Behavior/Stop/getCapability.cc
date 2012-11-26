#include "stop.ih"

Behavior::ConfidenceInterval Stop::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

    Vector3D target = g->getVector("Pos");

    if(!wm.visibleObject(Types::BALL))
      return ConfidenceInterval(0.2, 0.0);

    if(target.length() < 0.3)
      return ConfidenceInterval(0.8, 0.0);

    if(ballPos.length() < 2.0) // near ball
      return ConfidenceInterval(0.6, 0.0);

    // std::cout << "I will do tomorrow." << std::endl;
    return ConfidenceInterval(0.4, 0.0);
}
