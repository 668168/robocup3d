#include "goodposition.ih"

void GoodPosition::update()
{
    Behavior::update();
    
    if (!d_goal)
	d_committed = false;
    else
    {
	rf<StateVarNode> posNode;

	posNode = rf_cast<StateVarNode>(d_goal->findDeep("PosX"));
    
	if(posNode)
	{
	    Vector3D pos = d_goal->getVector("Pos");
 	    pos.setZ(0);
	    d_committed = pos.length() > 0.2;
	}
	else{
	    d_committed = false;
	}
    }
}

