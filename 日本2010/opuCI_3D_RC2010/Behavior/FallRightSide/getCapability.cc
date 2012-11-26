#include "fallrightside.ih"

Behavior::ConfidenceInterval FallRightSide::getCapability(rf<State> s, rf<Goal> g)
{
    rf<StateVarNode> fallRNode = rf_cast<StateVarNode>(g->findDeep("FallR"));
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    if(!fallRNode)
    {
//	std::cout << "fall rightside : x" << std::endl;
	if(ballPos.getY() < 0.0)
	    return ConfidenceInterval(0.2, 0.2);
	return ConfidenceInterval(0.0, 0.0);
    }
    else
    {
//	std::cout << "fall rightside : o" << std::endl;
	return ConfidenceInterval(0.8, 0.2);
    }

}
