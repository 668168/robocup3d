#include "worldmodel.h"


WorldModel::WorldModel()
{
    #ifdef NAO_MODEL
	m_dFieldLength = 30.0;
	m_dFieldWidth = 20.0;
	m_dGoalWidth = 2.1;
	m_dGoalHeight = 0.6;
	m_dBallRadius = 0.042;
	m_dBallMass = 0.026;
    #else
	m_dFieldLength = 50.0;
	m_dFieldWidth = 32.0;
	m_dGoalWidth = 9.0;
	m_dGoalHeight = 4.0;
	m_dBallRadius = 0.4;
	m_dBallMass = 0.43;
	#endif

	m_vOppGoalPos = Vector(m_dFieldLength/2.0,0,0);
	m_vMyGoalPos = Vector(-m_dFieldLength/2.0,0,0);
			
	m_dServerTime = 0.0;
	m_dGameTime = 0.0;

	m_sTeamName = "GDUT2013";
	m_sOppTeamName = "UNKNOWTEAM";
	m_bIsLeft = true;
	m_iUnum = 0;
	m_iCmdUnum = 0;
	m_CmdType = CMD_NONE;
	m_FallState = FALL_NONE;
	m_bIsKicking = false;
	m_iMyScore = 0;
	m_iOppScore = 0;

    #ifdef NAO_MODEL
	m_vBeamPos = Vector(-1, -0.5, 180);
	m_dStandHeight = 0.37;
	#else
	m_vBeamPos = Vector(-4.6, 0, 0);
	#endif

	m_dFaceAng = 0;
	m_dBodyAng = 0;

	
}


WorldModel::~WorldModel()
{
}


void WorldModel::UpdateBasicInfo()
{
	if (m_iUnum == 0)
	{
		if (SenseParse.m_iUnum > 0)
		{
			m_iUnum = SenseParse.m_iUnum;
			m_bIsLeft = SenseParse.m_bIsLeft;
			InitFlagPos();
		}
	}
	if (m_sOppTeamName == "UNKNOWTEAM") m_sOppTeamName = SenseParse.m_sOppTeamName;

	m_dServerTime = SenseParse.m_dServerTime;
	m_dGameTime = SenseParse.m_dGameTime;
	m_sPlayMode = SenseParse.m_sPlayMode;
	m_Gyro = SenseParse.m_Gyro;
	m_frp_lf = SenseParse.m_frp_lf;
	m_frp_rf = SenseParse.m_frp_rf;

	int i = 0;
    #ifdef NAO_MODEL
    for(; i < 22; i++) m_HJ[i] = SenseParse.m_HJ[i];
    #else
    for(; i < 8; i++) m_HJ[i] = SenseParse.m_HJ[i];
    for(i = 0; i < 6; i++) m_UJ[i] = SenseParse.m_UJ[i];
    #endif
	
}


void WorldModel::UpdateAll()
{
	UpdateBasicInfo();
	UpdateScore();
	UpdateSelfPos();
	UpdateAngle();
	UpdatePlayerPos();
	UpdateBallPos();
	if(!m_bIsKicking) UpdateFallState();
	UpdateHearMsg();
	
}


void WorldModel::UpdateScore()
{
	static bool bUpdated = false;

	if (IsGoalUs())
	{
		if (!bUpdated)
		{
			m_iMyScore++;
			bUpdated = true;
		}
	}
	else if (IsGoalOpp())
	{
		if (!bUpdated)
		{
			m_iOppScore++;
			bUpdated = true;
		}
	}
	else bUpdated = false;
}


double WorldModel::Round(double dNum, int i)
{
	double d = 1;
	for(int j = 0; j < i; j++) d *= 10;
	return int(dNum * d + 0.50000001) / d;
}


bool WorldModel::IsKickOff()
{
	return m_sPlayMode == "KickOff_Left" || m_sPlayMode == "KickOff_Right";
}


bool WorldModel::IsKickOffUs()
{
	return (m_bIsLeft && m_sPlayMode == "KickOff_Left") || (!m_bIsLeft && m_sPlayMode == "KickOff_Right");
}


bool WorldModel::IsKickOffOpp()
{
	return (m_bIsLeft && m_sPlayMode == "KickOff_Right") || (!m_bIsLeft && m_sPlayMode == "KickOff_Left");
}


bool WorldModel::IsKickIn()
{
	return m_sPlayMode == "KickIn_Left" || m_sPlayMode == "KickIn_Right";
}


bool WorldModel::IsKickInUs()
{
	return (m_bIsLeft && m_sPlayMode == "KickIn_Left") || (!m_bIsLeft && m_sPlayMode == "KickIn_Right");
}


bool WorldModel::IsKickInOpp()
{
	return (!m_bIsLeft && m_sPlayMode == "KickIn_Left") || (m_bIsLeft && m_sPlayMode == "KickIn_Right");
}


bool WorldModel::IsCornerKick()
{
	return m_sPlayMode == "corner_kick_left" || m_sPlayMode == "corner_kick_right";
}


bool WorldModel::IsCornerKickUs()
{
	return (m_bIsLeft && m_sPlayMode == "corner_kick_left") || (!m_bIsLeft && m_sPlayMode == "corner_kick_right");
}


bool WorldModel::IsCornerKickOpp()
{
	return (!m_bIsLeft && m_sPlayMode == "corner_kick_left") || (m_bIsLeft && m_sPlayMode == "corner_kick_right");
}


bool WorldModel::IsGoalKick()
{
	return m_sPlayMode == "goal_kick_left" || m_sPlayMode == "goal_kick_right";
}


bool WorldModel::IsGoalKickUs()
{
	return (m_bIsLeft && m_sPlayMode == "goal_kick_left") || (!m_bIsLeft && m_sPlayMode == "goal_kick_right");
}


bool WorldModel::IsGoalKickOpp()
{
	return (!m_bIsLeft && m_sPlayMode == "goal_kick_left") || (m_bIsLeft && m_sPlayMode == "goal_kick_right");
}


bool WorldModel::IsFreeKick()
{
	return m_sPlayMode == "free_kick_left" || m_sPlayMode == "free_kick_right";
}


bool WorldModel::IsFreeKickUs()
{
	return (m_bIsLeft && m_sPlayMode == "free_kick_left") || (!m_bIsLeft && m_sPlayMode == "free_kick_right");
}


bool WorldModel::IsFreeKickOpp()
{
	return (!m_bIsLeft && m_sPlayMode == "free_kick_left") || (m_bIsLeft && m_sPlayMode == "free_kick_right");
}


bool WorldModel::IsOffside()
{
	return m_sPlayMode == "offside_left" || m_sPlayMode == "offside_right";
}


bool WorldModel::IsOffsideUs()
{
	return (m_bIsLeft && m_sPlayMode == "offside_left") || (!m_bIsLeft && m_sPlayMode == "offside_right");
}


bool WorldModel::IsOffsideOpp()
{
	return (!m_bIsLeft && m_sPlayMode == "offside_left") || (m_bIsLeft && m_sPlayMode == "offside_right");
}


bool WorldModel::IsGoal()
{
	return m_sPlayMode == "Goal_Left" || m_sPlayMode == "Goal_Right";
}


bool WorldModel::IsGoalUs()
{
	return (m_bIsLeft && m_sPlayMode == "Goal_Left") || (!m_bIsLeft && m_sPlayMode == "Goal_Right");
}


bool WorldModel::IsGoalOpp()
{
	return (m_bIsLeft && m_sPlayMode == "Goal_Right") || (!m_bIsLeft && m_sPlayMode == "Goal_Left");
}


bool WorldModel::IsBeforeKickOff()
{
	return m_sPlayMode == "BeforeKickOff";
}


bool WorldModel::IsPlayOn()
{
	return m_sPlayMode == "PlayOn";
}


bool WorldModel::IsGameOver()
{
	return m_sPlayMode == "GameOver";
}


FALLTYPE WorldModel::DetectFallState_GYRO(bool bClear)
{
	static int iNumX = 0;
	static int iNumY = 0;
	static int iLastSignX = 0;
	static int iLastSignY = 0;

	int iSignX = 0;
	int iSignY = 0;

	double dAbsAccX = fabs(m_Gyro.dx);
	double dAbsAccY = fabs(m_Gyro.dy);

	if (bClear)
	{
		iNumX = 0;
		iNumY = 0;
		iLastSignX = 0;
		iLastSignY = 0;
		return m_FallState;
	}


	if (m_Gyro.dx > 0) iSignX = 1;
	else if (m_Gyro.dx < 0) iSignX = -1;

	if (m_Gyro.dy > 0) iSignY = 1;
	else if (m_Gyro.dy < 0) iSignY = -1;

	if (iLastSignX == iSignX)
	{
		if (dAbsAccX > 130.0) iNumX += 12;
		else if (dAbsAccX > 100.0) iNumX += 10;
		else if (dAbsAccX > 80.0) iNumX += 7;
		else if (dAbsAccX > 65.0) iNumX += 6;
		else if (dAbsAccX > 50.0) iNumX += 5;
		else if (dAbsAccX > 35.0) iNumX += 4;
		else if (dAbsAccX > 20.0) iNumX += 2;
		else if (dAbsAccX > 10.0) iNumX += 1;
	}
	else
	{
		if (iNumX >= 20) iNumX -= 20;
		else iNumX = 0;
	}

	if (iLastSignY == iSignY)
	{
		if (dAbsAccY > 80.0) iNumY += 7;
		else if (dAbsAccY > 65.0) iNumY += 6;
		else if (dAbsAccY > 50.0) iNumY += 5;
		else if (dAbsAccY > 35.0) iNumY += 4;
		else if (dAbsAccY > 20.0) iNumY += 2;
		else if (dAbsAccY > 10.0) iNumY += 1;
	}
	else
	{
		if (iNumY >= 20) iNumY -= 20;
		else iNumY = 0;
	}


	iLastSignX = iSignX;
	iLastSignY = iSignY;


	int iMaxX = 200;//180;//(iSign == -1 ? 150 : 80);
	int iMaxY = 200;//180;//(iSign == -1 ? 150 : 80);

//cout<<"Gyro_Info    "<<m_Gyro.dx<<"  "<<m_Gyro.dy<<"  "<<m_Gyro.dz<<endl;

	if( iNumX >= iMaxX)
	{
		if (dAbsAccX < 15) { iNumX -= 15; goto NEXT; }
		iNumX = 0;
		if (iSignX == 1) return FALL_UP;
		else return FALL_DOWN;
	}

NEXT:

	if( iNumY >= iMaxY) 
	{
		if (dAbsAccY < 15) { iNumY -= 15; return FALL_NONE; }
//cout<<"Gyro Y Gyro Y Gyro Y Gyro Y Gyro Y Gyro Y Gyro Y Gyro Y Gyro Y Gyro Y Gyro Y Gyro Y Gyro Y "<<endl;
		iNumY = 0;
		return FALL_UP;
	}

	return FALL_NONE;
}


FALLTYPE WorldModel::CheckIsFall(bool bClear)
{
	static int iNum_C = 0;
	static int iNum_L = 0;
	static int iNum_R = 0;
//	static int iNum_FRPNONE = 0;
	static	FRPInfo LastLFrp ;
	static	FRPInfo LastRFrp ;

	if (bClear)
	{
		 iNum_C = 0;
		 iNum_L = 0;
		 iNum_R = 0;
		 FRPInfo LastLFrp=m_frp_lf;
		 FRPInfo LastRFrp=m_frp_rf;
		 return FALL_NONE;
	}

// 	if(!m_frp_lf.bValid && !m_frp_rf.bValid)
// 		iNum_FRPNONE ++;
// 	else
// 		iNum_FRPNONE = 0;
// 	//cout<<m_frp_lf.bValid<<"	"<<m_frp_rf.bValid <<endl;
// 	if(iNum_FRPNONE == 5)
// 		return FALL_UP;
	
	///0.07
	if ((m_frp_lf.cy >= 0.08&&LastLFrp.cy>=0.08)||(m_frp_lf.cy <= -0.08&&LastLFrp.cy<=-0.08)) 
	{	
		if(m_frp_lf.cy >= 0.08) iNum_L++;
		if(m_frp_lf.cy <= -0.08) iNum_L--;
	}
	else
	{
		iNum_L = 0;
// 		iNum_L -= 4;
// 		if (iNum_L < 0) iNum_L = 0;
	}
	///0.07
	if ((m_frp_rf.cy >= 0.08&&LastRFrp.cy>=0.08)||(m_frp_rf.cy <= -0.08&&LastRFrp.cy<=-0.08)) 
	{	
		if(m_frp_rf.cy >= 0.08) iNum_R++;
		if(m_frp_rf.cy <= -0.08) iNum_R--;
	}
	else
	{
		iNum_R = 0;
// 		iNum_R -= 4;
// 		if (iNum_R < 0) iNum_R = 0;
	}
	if((fabs(m_frp_rf.dz)<0.0001||fabs(m_frp_lf.dz)<0.0001)&&(fabs(LastLFrp.dz)<0.0001||fabs(LastRFrp.dz)<0.0001))
	{
		iNum_C++;
	}
	else
	{
		iNum_C = 0;
// 		iNum_C -= 4;
// 		if (iNum_C < 0) iNum_C = 0;
	}
	LastLFrp.cy=m_frp_lf.cy;
	LastRFrp.cy=m_frp_rf.cy;
	LastLFrp.dz=m_frp_lf.dz;
	LastRFrp.dz=m_frp_rf.dz;
///	cout<<"LastLFrp.cy............"<<LastLFrp.cy<<endl;
///	cout<<"LastRFrp.cy............"<<LastRFrp.cy<<endl;
///	cout<<"LastLFrp.dz............"<<LastLFrp.dz<<endl;
///	cout<<"LastRFrp.dz............"<<LastRFrp.dz<<endl;

//cout<<"Frp_info_left   "<<m_frp_lf.cx<<" "<<m_frp_lf.cy<<" "<<m_frp_lf.cz<<"  ---  "<<m_frp_lf.dx<<" "<<m_frp_lf.dy<<" "<<m_frp_lf.dz<<endl;
//cout<<"Frp_info_right   "<<m_frp_rf.cx<<" "<<m_frp_rf.cy<<" "<<m_frp_rf.cz<<"  ---  "<<m_frp_rf.dx<<" "<<m_frp_rf.dy<<" "<<m_frp_rf.dz<<endl;

	if ((iNum_L >= 50 && iNum_R >= 50))// || (iNum_L >= 70 && iNum_R >= 70))
	{
		cout<<"CheckIsFall_____frp   falldown"<<m_dGameTime<<endl;
		goto FALL_DOWN;
	}
	if ((iNum_L <= -50 && iNum_R <= -50))// || (iNum_L <= -70 && iNum_R <= -70))
	{
		cout<<"CheckIsFall_____frp   fallup"<<m_dGameTime<<endl;
		goto FALL_UP;
	}
	if(iNum_C>=40)//80)
	{
		cout<<"CheckIsFall_____frp   fallup    iNum_C"<<m_dGameTime<<endl;
		goto FALL_UP;
	}
	return FALL_NONE;

FALL_UP:
	iNum_C = 0;
	iNum_L = 0;
	iNum_R = 0;
	LastLFrp=m_frp_lf;
	LastRFrp=m_frp_rf;
	return FALL_UP;

FALL_DOWN:
	iNum_L = 0;
	iNum_R = 0;
	iNum_C = 0;
	LastLFrp=m_frp_lf;
	LastRFrp=m_frp_rf;
	return FALL_DOWN;
}

void WorldModel::UpdateFallState(int iClearType)
{
	static FALLTYPE sr1 = FALL_NONE;
	static FALLTYPE sr2 = FALL_NONE;

	if (iClearType > 0)
	{
		if (iClearType == 1) m_FallState = FALL_NONE;
		sr1 = FALL_NONE;
		sr2 = FALL_NONE;
		CheckIsFall(true);
		DetectFallState_GYRO(true);
		return;
	}

	if (m_FallState != FALL_NONE) return;

	FALLTYPE r1 = CheckIsFall() ? FALL : FALL_NONE;
	FALLTYPE r2 = DetectFallState_GYRO();
	
	if (sr1 == FALL_NONE) sr1 = r1;
	if (sr2 == FALL_NONE) sr2 = r2;

	if (sr1 == FALL && sr2 == FALL_NONE)
	{
		if (m_vSelfPos.Vz < 0.15) m_FallState = SenseParse.m_PolBallPos.PolPos.Pz > 0 ? FALL_DOWN : FALL_UP;
		else m_FallState = m_Gyro.dx > 0 ? FALL_UP : FALL_DOWN;
		cout<<"CheckIsFall"<<endl;
	}
	else
	{
		m_FallState = sr2;
		if (sr2 == FALL_UP || sr2 == FALL_DOWN) cout<<"Fall_Gyro"<<endl;
	}
}

