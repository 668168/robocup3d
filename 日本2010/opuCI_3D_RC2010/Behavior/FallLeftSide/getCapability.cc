#include "fallleftside.ih"

Behavior::ConfidenceInterval FallLeftSide::getCapability(rf<State> s, rf<Goal> g)
{
    rf<StateVarNode> fallLNode = rf_cast<StateVarNode>(g->findDeep("FallL"));
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    if(!fallLNode)
    {
//	std::cout << "fall leftside  : x" << std::endl;
	if(ballPos.getY() > 0.0)
	    return ConfidenceInterval(0.2, 0.2);
	return ConfidenceInterval(0.0, 0.0);
    }
    else
    {
//	std::cout << "fall leftside  : o" << std::endl;
	return ConfidenceInterval(0.8, 0.2);
    }

}
