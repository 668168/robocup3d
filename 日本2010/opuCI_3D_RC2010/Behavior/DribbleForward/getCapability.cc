#include "dribbleforward.ih"

Behavior::ConfidenceInterval DribbleForward::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    
    //std::cout << "DribbleForward: ";
    if(fabs(ballPos.getX()) > fabs(ballPos.getY() )) {
      //std::cout << "let's dribble!" << std::endl;
      return ConfidenceInterval(0.5, 0.2);
    }
    //std::cout << "|ballX| < |ballY| and I cannot Dribble" << std::endl;
    return ConfidenceInterval(0, 0);
}
