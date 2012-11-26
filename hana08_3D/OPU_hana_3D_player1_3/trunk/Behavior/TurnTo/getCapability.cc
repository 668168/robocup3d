#include "turnto.ih"

Behavior::ConfidenceInterval TurnTo::getCapability(rf<State> s, rf<Goal> g)
{
	rf<StateVarNode> angleNode = rf_cast<StateVarNode>(g->findDeep("Angle"));
	StateVar angleVar = angleNode->getVar();
	double angle = angleVar.second.mean();

	rf<StateVarNode> walktoNode = rf_cast<StateVarNode>(g->findDeep("WalkTo"));
	if (walktoNode)
	{
		return ConfidenceInterval(0.5, 0.2);
	}

	Vector3D pos = g->getVector("Pos");
	pos.setZ(0.0);

	if(fabs(angle) < 10.0 && pos.length() < 0.3){

		return ConfidenceInterval(-1.0, 0.0);
	}

	else{

    	return ConfidenceInterval(0.5, 0.2);
	}

}
