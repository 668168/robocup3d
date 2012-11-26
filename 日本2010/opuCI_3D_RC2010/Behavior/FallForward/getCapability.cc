#include "fallforward.ih"

Behavior::ConfidenceInterval FallForward::getCapability(rf<State> s, rf<Goal> g)
{
    rf<StateVarNode> fallFNode = rf_cast<StateVarNode>(g->findDeep("FallF"));
    WorldModel& wm = WorldModel::getInstance();

    Vector3D oppPos = wm.getObjectPosition(Types::OPPONENT1).getMu();
    //    std::cout << "oppPos = " << oppPos << std::endl;

    if(!fallFNode || 
       (oppPos.length() < 0.8 && oppPos.getX() < 0.4 &&
	oppPos.getX() > 0 && fabs(oppPos.getY()) < 0.15))
    {
//	std::cout << "fall forward   : x" << std::endl;
	return ConfidenceInterval(0.0, 0.0);
    }
    else
    {
//	std::cout << "fall forward   : o" << std::endl;
	return ConfidenceInterval(0.8, 0.2);
    }

}
