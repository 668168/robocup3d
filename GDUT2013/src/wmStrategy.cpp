#include "worldmodel.h"
#include <string>
#include <iostream>
#include <sstream>
extern Geometry geometry;

bool WorldModel::IsMeGoalie ()
{
	return GetUnum() == 1 ;
}


bool WorldModel::IsBallInOurProcession ()
{
	
}


bool WorldModel::IsTeammateAbnormal (  int iTeammateNum )
{
	return m_TeamMate[iTeammateNum-1].vPos.GetVz() <= 0.15;
		
}


bool WorldModel::IsOppAbnormal ( int iOppNum )
{
	return m_Opponent[iOppNum-1].vPos.GetVz() <= 0.15;
}


Vector WorldModel::CalcMySpeed ()
{

}

Vector WorldModel::CalcTeammateSpeed (int iTeammateNum)
{
	
}

Vector WorldModel::CalcOppSpeed (int iOppNum)
{

}

Vector WorldModel::CalcBallSpeed ()
{
	VecPosInfo vP1,vP2;
	int iCount = BallPosQ.size();
	 BallPosQ.getAny(vP1,iCount-1);
	 BallPosQ.getLast(vP2);
	Vector vTmp1 = (vP2.vPos-vP1.vPos)/(vP2.dTime-vP1.dTime);
	return vTmp1;

}

Vector WorldModel::PredictBallPosAfterCycles (int iCycles)
{

}

double WorldModel::GetOppDistToBall ( int iOppNum )
{
	Vector vOppPos = GetOppPos( iOppNum );
	if ( vOppPos.GetVz() < 0 ) return -1;
	Vector vBallPos = GetBallPosInXY();
	vOppPos.SetVz(0.0);
	vBallPos.SetVz(0.0);
	Vector vTemp = vOppPos - vBallPos ;
	return vTemp.GetMod();
	 
}

double WorldModel::GetTeammateDistToBall ( int iTeammateNum )
{
	Vector vTeammatePos = GetTeammatePos( iTeammateNum );
	if ( vTeammatePos.GetVz() < 0 ) return -1;
	Vector vBallPos = GetBallPosInXY();
	vTeammatePos.SetVz(0.0);
	vBallPos.SetVz(0.0);
	Vector vTemp = vTeammatePos - vBallPos ;
	return vTemp.GetMod();
}

double WorldModel::GetClosestToBallTeammate( int &iTeammateNum )
{
	int iTmp1 = 0;
	int iTmp2 = 0;
	double dTmp1 = 0.0;
	double dTmp2 = -1;
	for (; iTmp1 < 11 ;iTmp1++)
	{
		dTmp1 = GetTeammateDistToBall(iTmp1+1);
		if ( (dTmp1 < dTmp2 || dTmp2 < 0) && dTmp1 >= 0.0 )
		{
			dTmp2 = dTmp1;
			iTmp2 = iTmp1;
		}
	}
	//cout<< "best id "<<iTmp2+1<<endl;
	iTeammateNum = ++iTmp2;
	return dTmp2;
}

double WorldModel::GetClosestToBallOpp ( int &iOppNum )
{
	int iTmp1 = 0;
	int iTmp2 = 0;
	double dTmp1 = 0.0;
	double dTmp2 = -1.0;
	for (; iTmp1 < 11 ;iTmp1++)
	{
		dTmp1 = GetOppDistToBall(iTmp1+1);
		if ( (dTmp1 < dTmp2 || dTmp2 < 0) && dTmp1 >= 0.0 )
		{
			dTmp2 = dTmp1;
			iTmp2 = iTmp1;
		}
	}
	iOppNum = ++iTmp2;
	return dTmp2;
}
	
double WorldModel::GetClosestToBallPlayer ( int &iPlayerNum, bool &bTeamPlayer)
{
	int iTeammate = 0;
	int iOpp = 0;
	double dDistTeammate = GetClosestToBallTeammate ( iTeammate );
	double dDistOpp = GetClosestToBallOpp ( iOpp );
	if ( iTeammate == 0)
	{
		bTeamPlayer = false;
		iPlayerNum = iOpp;
		return dDistOpp;
	}
	if ( iOpp == 0 )
	{
		bTeamPlayer = true;
		iPlayerNum = iTeammate;
		return dDistTeammate;
	}
	if ( dDistTeammate > dDistOpp )
	{
		bTeamPlayer = true;
		iPlayerNum = iTeammate;
		return dDistTeammate;
	} else 
	{
		bTeamPlayer = false;
		iPlayerNum = iOpp;
		return dDistOpp;
	}
	
}

double WorldModel::GetTeammateDistToOwnGoal (int iTeammateNum)
{
	Vector vTeammatePos = GetTeammatePos( iTeammateNum );
	if ( vTeammatePos.GetVz() < 0 ) return -1;
	Vector vGoalPos = GetMyGoalPos();
	vTeammatePos.SetVz(0.0);
	vGoalPos.SetVz(0.0);
	Vector vTemp = vTeammatePos - vGoalPos ;
	return vTemp.GetMod();
}

double WorldModel::GetOppDistToOwnGoal ( int iOppNum)
{
	Vector vOppPos = GetOppPos( iOppNum );
	if ( vOppPos.GetVz() < 0 ) return -1;
	Vector vGoalPos = GetMyGoalPos();
	vOppPos.SetVz(0.0);
	vGoalPos.SetVz(0.0);
	Vector vTemp = vOppPos - vGoalPos ;
	return vTemp.GetMod();
}

double WorldModel::GetClosestToOwnGoalTeammate( int &iTeammateNum )
{
	int iTmp1 = 0;
	int iTmp2 = 0;
	double dTmp1 = 0.0;
	double dTmp2 = -1;
	for (; iTmp1 < 11 ;iTmp1++)
	{
		dTmp1 = GetTeammateDistToOwnGoal(iTmp1+1);
		if ( (dTmp1 < dTmp2 || dTmp2 < 0) && dTmp1 >= 0.0 )
		{
			dTmp2 = dTmp1;
			iTmp2 = iTmp1;
		}
	}
	//cout<< "best id "<<iTmp2+1<<endl;
	iTeammateNum = ++iTmp2;
	return dTmp2;
}
	
double WorldModel::GetClosestToOwnGoalOpp( int &iOppNum )
{
	int iTmp1 = 0;
	int iTmp2 = 0;
	double dTmp1 = 0.0;
	double dTmp2 = -1.0;
	for (; iTmp1 < 11 ;iTmp1++)
	{
		dTmp1 = GetOppDistToOwnGoal(iTmp1+1);
		if ( (dTmp1 < dTmp2 || dTmp2 < 0) && dTmp1 >= 0.0 )
		{
			dTmp2 = dTmp1;
			iTmp2 = iTmp1;
		}
	}
	iOppNum = ++iTmp2;
	return dTmp2;
}
	
double WorldModel::GetClosestToOwnGoalPlayer ( int &iPlayerNum, bool &bTeamPlayer)
{
	int iTeammate = 0;
	int iOpp = 0;
	double dDistTeammate = GetClosestToOwnGoalTeammate ( iTeammate );
	double dDistOpp = GetClosestToOwnGoalOpp ( iOpp );
	if ( iTeammate == 0)
	{
		bTeamPlayer = false;
		iPlayerNum = iOpp;
		return dDistOpp;
	}
	if ( iOpp == 0 )
	{
		bTeamPlayer = true;
		iPlayerNum = iTeammate;
		return dDistTeammate;
	}
	if ( dDistTeammate > dDistOpp )
	{
		bTeamPlayer = true;
		iPlayerNum = iTeammate;
		return dDistTeammate;
	} else 
	{
		bTeamPlayer = false;
		iPlayerNum = iOpp;
		return dDistOpp;
	}
}

double WorldModel::GetTeammateDistToOppGoal (int iTeammateNum)
{
	Vector vTeammatePos = GetTeammatePos( iTeammateNum );
	if ( vTeammatePos.GetVz() < 0 ) return -1;
	Vector vGoalPos = GetOppGoalPos();
	vTeammatePos.SetVz(0.0);
	vGoalPos.SetVz(0.0);
	Vector vTemp = vTeammatePos - vGoalPos ;
	return vTemp.GetMod();
}

double WorldModel::GetOppDistToOppGoal ( int iOppNum)
{
	Vector vOppPos = GetOppPos( iOppNum );
	if ( vOppPos.GetVz() < 0 ) return -1;
	Vector vGoalPos = GetOppGoalPos();
	vOppPos.SetVz(0.0);
	vGoalPos.SetVz(0.0);
	Vector vTemp = vOppPos - vGoalPos ;
	return vTemp.GetMod();
}

double WorldModel::GetClosestToOppGoalTeammate( int &iTeammateNum )
{
	int iTmp1 = 0;
	int iTmp2 = 0;
	double dTmp1 = 0.0;
	double dTmp2 = -1;
	for (; iTmp1 < 11 ;iTmp1++)
	{
		dTmp1 = GetTeammateDistToOppGoal(iTmp1+1);
		if ( (dTmp1 < dTmp2 || dTmp2 < 0) && dTmp1 >= 0.0 )
		{
			dTmp2 = dTmp1;
			iTmp2 = iTmp1;
		}
	}
	//cout<< "best id "<<iTmp2+1<<endl;
	iTeammateNum = ++iTmp2;
	return dTmp2;
}
	
double WorldModel::GetClosestToOppGoalOpp ( int &iOppNum )
{
	int iTmp1 = 0;
	int iTmp2 = 0;
	double dTmp1 = 0.0;
	double dTmp2 = -1.0;
	for (; iTmp1 < 11 ;iTmp1++)
	{
		dTmp1 = GetOppDistToOppGoal(iTmp1+1);
		if ( (dTmp1 < dTmp2 || dTmp2 < 0) && dTmp1 >= 0.0 )
		{
			dTmp2 = dTmp1;
			iTmp2 = iTmp1;
		}
	}
	iOppNum = ++iTmp2;
	return dTmp2;
}
	
double WorldModel::GetClosestToOppGoalPlayer ( int &iPlayerNum, bool &bTeamPlayer)
{
	int iTeammate = 0;
	int iOpp = 0;
	double dDistTeammate = GetClosestToOppGoalTeammate ( iTeammate );
	double dDistOpp = GetClosestToOppGoalOpp ( iOpp );
	if ( iTeammate == 0)
	{
		bTeamPlayer = false;
		iPlayerNum = iOpp;
		return dDistOpp;
	}
	if ( iOpp == 0 )
	{
		bTeamPlayer = true;
		iPlayerNum = iTeammate;
		return dDistTeammate;
	}
	if ( dDistTeammate > dDistOpp )
	{
		bTeamPlayer = true;
		iPlayerNum = iTeammate;
		return dDistTeammate;
	} else 
	{
		bTeamPlayer = false;
		iPlayerNum = iOpp;
		return dDistOpp;
	}
}

double WorldModel::GetTeammateDistToMe (int iTeammateNum)
{
	Vector vTeammatePos = GetTeammatePos( iTeammateNum );
	if ( vTeammatePos.GetVz() < 0 ) return -1;
	vTeammatePos.SetVz(0.0);
	//m_vSelfPos.SetVz(0.0);
	Vector vTemp = vTeammatePos - m_vSelfPos ;
	return vTemp.GetMod();
}

double WorldModel::GetOppDistToMe ( int iOppNum)
{
	Vector vOppPos = GetOppPos( iOppNum );
	if ( vOppPos.GetVz() < 0 ) return -1;
	vOppPos.SetVz(0.0);
	//m_vSelfPos.SetVz(0.0);
	Vector vTemp = vOppPos - m_vSelfPos ;
	return vTemp.GetMod();		
}

double WorldModel::GetClosestToMeTeammate (  int &iTeammateNum )
{
	int iTmp1 = 0;
	int iTmp2 = 0;
	double dTmp1 = 0.0;
	double dTmp2 = -1;
	for (; iTmp1 < 11 ;iTmp1++)
	{
		dTmp1 = GetTeammateDistToMe(iTmp1+1);
		if ( (dTmp1 < dTmp2 || dTmp2 < 0) && dTmp1 >= 0.0 )
		{
			dTmp2 = dTmp1;
			iTmp2 = iTmp1;
		}
	}
	//cout<< "best id "<<iTmp2+1<<endl;
	iTeammateNum = ++iTmp2;
	return dTmp2;
}
	
double WorldModel::GetClosestToMeOpp ( int &iOppNum )
{
	int iTmp1 = 0;
	int iTmp2 = 0;
	double dTmp1 = 0.0;
	double dTmp2 = -1.0;
	for (; iTmp1 < 11 ;iTmp1++)
	{
		dTmp1 = GetOppDistToMe(iTmp1+1);
		if ( (dTmp1 < dTmp2 || dTmp2 < 0) && dTmp1 >= 0.0 )
		{
			dTmp2 = dTmp1;
			iTmp2 = iTmp1;
		}
	}
	iOppNum = ++iTmp2;
	return dTmp2;
}
	
double WorldModel::GetClosestToMePlayer ( int &iPlayerNum, bool &bTeamPlayer)
{
	int iTeammate = 0;
	int iOpp = 0;
	double dDistTeammate = GetClosestToMeTeammate ( iTeammate );
	double dDistOpp = GetClosestToMeOpp ( iOpp );
	if ( iTeammate == 0)
	{
		bTeamPlayer = false;
		iPlayerNum = iOpp;
		return dDistOpp;
	}
	if ( iOpp == 0 )
	{
		bTeamPlayer = true;
		iPlayerNum = iTeammate;
		return dDistTeammate;
	}
	if ( dDistTeammate > dDistOpp )
	{
		bTeamPlayer = true;
		iPlayerNum = iTeammate;
		return dDistTeammate;
	} else 
	{
		bTeamPlayer = false;
		iPlayerNum = iOpp;
		return dDistOpp;
	}
}

bool WorldModel::IsBallInOurFA()
{
	return m_vBallPos.GetVx()<-0.47 && fabs(m_vBallPos.GetVy())<2.0;

}

