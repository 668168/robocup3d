#include "worldmodel.h"

Geometry geometry;

void WorldModel::InitFlagPos()
{
	double dLeft = (m_bIsLeft?1.0:-1.0);
	m_vFlagPos[F_F1L] = Vector(-m_dFieldLength/2.0*dLeft, m_dFieldWidth/2.0*dLeft, 0.0);
	m_vFlagPos[F_F2L] = Vector(-m_dFieldLength/2.0*dLeft, -m_dFieldWidth/2.0*dLeft, 0.0);
	m_vFlagPos[F_F1R] = Vector(m_dFieldLength/2.0*dLeft, m_dFieldWidth/2.0*dLeft, 0.0);
	m_vFlagPos[F_F2R] = Vector(m_dFieldLength/2.0*dLeft, -m_dFieldWidth/2.0*dLeft, 0.0);
	m_vFlagPos[F_G1L] = Vector(-m_dFieldLength/2.0*dLeft, m_dGoalWidth/2.0*dLeft, m_dGoalHeight);
	m_vFlagPos[F_G2L] = Vector(-m_dFieldLength/2.0*dLeft, -m_dGoalWidth/2.0*dLeft, m_dGoalHeight);
	m_vFlagPos[F_G1R] = Vector(m_dFieldLength/2.0*dLeft, m_dGoalWidth/2.0*dLeft, m_dGoalHeight);
	m_vFlagPos[F_G2R] = Vector(m_dFieldLength/2.0*dLeft, -m_dGoalWidth/2.0*dLeft, m_dGoalHeight);
}


bool WorldModel::CalcSelfPosX(int iFlag1, int iFlag2, double &v)
{
	if (iFlag1 % 4 != iFlag2 % 4) return false;  /** 如果两个标杆不关于Y轴对称 */
	if (iFlag1 == iFlag2) return false;  /** 如果是同一个标杆， 确保2个标杆位于Y轴两侧，且Y轴坐标相等 */

	v = ((squ(SenseParse.m_PolFlagPos[iFlag1].PolPos.Px)-squ(SenseParse.m_PolFlagPos[iFlag2].PolPos.Px))/(m_vFlagPos[iFlag2].Vx - m_vFlagPos[iFlag1].Vx) + m_vFlagPos[iFlag1].Vx + m_vFlagPos[iFlag2].Vx) / 2.0;

	return true;
}


bool WorldModel::CalcSelfPosY(int iFlag1, int iFlag2, double &v)
{
	if (iFlag1 > iFlag2)
	{
		int t = iFlag1;
		iFlag1 = iFlag2;
		iFlag2 = iFlag1;
	}
	/** 注意该函数所适用的标杆 */
	if ((iFlag1 == F_F1L && iFlag2 == F_F2L) || (iFlag1 == F_F1R && iFlag2 == F_F2R))// || (iFlag1 == F_G1L && iFlag2 == F_G2L) || (iFlag1 == F_G1R && iFlag2 == F_G2R))
	{
		v = ((squ(SenseParse.m_PolFlagPos[iFlag1].PolPos.Px)-squ(SenseParse.m_PolFlagPos[iFlag2].PolPos.Px))/(m_vFlagPos[iFlag2].Vy - m_vFlagPos[iFlag1].Vy) + m_vFlagPos[iFlag1].Vy + m_vFlagPos[iFlag2].Vy) / 2.0;
		return true;
	}
	return false;
}


bool WorldModel::CalcSelfPosZ_F(int iFlag, double &v)
{
	Vector vMeToFlag = m_vSelfPos - m_vFlagPos[iFlag];
	vMeToFlag.SetVz(0);
	double d = squ(SenseParse.m_PolFlagPos[iFlag].PolPos.Px) - squ(vMeToFlag.GetMod());
	if (d < 0) return false;
	v = sqrt(d);
	return true;
}


bool WorldModel::CalcSelfPosZ_G(int iFlag, double &v)
{
	Vector vMeToFlag = m_vSelfPos - m_vFlagPos[iFlag];
	vMeToFlag.SetVz(0);
	double d = squ(SenseParse.m_PolFlagPos[iFlag].PolPos.Px) - squ(vMeToFlag.GetMod());
	if (d < 0) return false;
	v = m_vFlagPos[iFlag].Vz - sqrt(d);
	return (v >= 0);
}


bool WorldModel::CalcSelfPosZ(double &v)
{
	bool br[8];
	double dr[8], dTotal = 0;
	int i, m, iNum = 0;
	
	for(i = 0; i < 8; i++)
	{
		m = i % 4;
		if (m == 0 || m == 3) br[i] = CalcSelfPosZ_F(i, dr[i]);
		else if (m == 1 || m == 2) br[i] = CalcSelfPosZ_G(i, dr[i]);
		if (br[i]) { iNum++; dTotal += dr[i]; }
	}
	if (iNum) v = dTotal / iNum;
	dTotal = 0;
	iNum = 0;
	for(i = 0; i < 8; i++)
	{
		if (!br[i]) continue;
		br[i] = fabs(dr[i] - v) < 0.05;
		if (br[i]) { dTotal+=dr[i]; iNum++; }
	}
	if (iNum) v = dTotal / iNum;
	return (iNum > 0);
}


double WorldModel::NormalizeAng(double dAng)
{
	while (dAng > 180) dAng -= 360;
	while (dAng < -180) dAng += 360;
	return dAng;
}


void WorldModel::NormalizeAngle(double &dAng)
{
	while (dAng > 180) dAng -= 360;
	while (dAng < -180) dAng += 360;
}


/** first the self positon should be calculated ,then you can use this function */
double WorldModel::GetFaceAngInGlobal(int iFlagID)
{
	Vector vMeToFlag = m_vFlagPos[iFlagID] - m_vSelfPos;
	double dAng = vMeToFlag.GetXYAngle() - SenseParse.m_PolFlagPos[iFlagID].PolPos.Py;
	return NormalizeAng(dAng);
}

/** first the self positon should be calculated ,then you can use this function */
double WorldModel::GetFaceAngInGlobalEx()
{
	double dTotal = 0, dAng;
	for(int i = 0; i < 8; i++)
	{
		dAng = GetFaceAngInGlobal(i);
		if (fabs(dAng) < 5 || fabs(dAng) > 175) return dAng;
		dTotal += dAng;
	}
	return NormalizeAng(dTotal / 8.0);
}


double WorldModel::GetBodyAng(double dFaceAngInGlobal)
{
	return NormalizeAng(dFaceAngInGlobal - m_HJ[JID_HEAD_1].fAngle);
}


/** first the self positon should be calculated , then you can use this function */
/**
double WorldModel::GetHeadTiltAng_F(int iFlagID)
{
	Vector vMeToFlag = m_vFlagPos[iFlagID] - m_vSelfPos;
	vMeToFlag.SetVz(0);
	double dAng = 90 - asin(vMeToFlag.GetMod() / SenseParse.m_PolFlagPos[iFlagID].PolPos.Px) * 180.0 / PI;
	dAng = -SenseParse.m_PolFlagPos[iFlagID].PolPos.Pz - dAng;
	return NormalizeAng(dAng);
}
*/

/** first the self positon should be calculated , then you can use this function */
/**
double WorldModel::GetHeadTiltAng_G(int iFlagID)
{
	Vector vMeToFlag = m_vFlagPos[iFlagID] - m_vSelfPos;
	vMeToFlag.SetVz(0);
	double dAng = 90 - asin(vMeToFlag.GetMod() / SenseParse.m_PolFlagPos[iFlagID].PolPos.Px) * 180.0 / PI;
	dAng = dAng - SenseParse.m_PolFlagPos[iFlagID].PolPos.Pz;
	return NormalizeAng(dAng);
}
*/

/** 头部在全局坐标中的仰角，即使头部未动，身体前倾，这个函数会返回由于身体前倾导致的全局仰角的变化 */
/**
double WorldModel::GetHeadTiltAngInGlobal()
{
	int a[4] = { F_F1L, F_F2L, F_F1R, F_F2R };
	int b[4] = { F_G1L, F_G2L, F_G1R, F_G2R };
	double dTotal = 0;

	for(int i = 0; i < 4; i++)
	{
		dTotal += GetHeadTiltAng_F(a[i]);
		dTotal += GetHeadTiltAng_G(b[i]);
	}
	return NormalizeAng(dTotal / 8.0);
}
*/

/** 身体前倾的角度 */
/**
double WorldModel::GetBodyTiltAng(double dHeadTiltAngInGlobal)
{
	return NormalizeAng(dHeadTiltAngInGlobal - m_HJ[JID_HEAD_2].fAngle);
}
*/


Vector WorldModel::GetObjPos(Polar PolPos)
{
	PolPos.Py += m_dFaceAng;
	//PolPos.Pz += 仰角 
	/** 这个函数的前提是假设人的视线方向是水平的 */
	return m_vSelfPos + geometry.ChangePolarToVector(PolPos);
}


Vector WorldModel::GetBallPosInXY()
{
	/** 这里假设球在地面上，即球的高度就是它的半径 */
	Polar PolBallPos = SenseParse.m_PolBallPos.PolPos;
	double dt = squ(PolBallPos.Px) - squ(m_vSelfPos.Vz - m_dBallRadius);
	if (dt < 0) return Vector(110, 110, -100);
	double dMarkLen = sqrt(dt);
	double dXYAngle = m_dFaceAng + PolBallPos.Py;
	NormalizeAngle(dXYAngle);
	double dDeltaInX = dMarkLen * cos( dXYAngle * PI / 180.0 );
	double dDeltaInY = dMarkLen * sin( dXYAngle * PI / 180.0 );
	return Vector(m_vSelfPos.Vx + dDeltaInX, m_vSelfPos.Vy + dDeltaInY, m_dBallRadius);
}


void WorldModel::Location()
{
	double dt, dTotalX = 0, dTotalY = 0;
	int iNumX = 0, iNumY = 0;
	bool br;
	int XF1[4] = { F_F1L, F_F2L, F_G1L, F_G2L };
	int XF2[4] = { F_F1R, F_F2R, F_G1R, F_G2R };
	int YF1[4] = { F_F1L, F_F1R, F_G1L, F_G1R };
	int YF2[4] = { F_F2L, F_F2R, F_G2L, F_G2R };

	for(int i = 0; i < 4; i++)
	{
		br = CalcSelfPosX(XF1[i], XF2[i], dt);
		if (br) { dTotalX += dt; iNumX++; }
		br = CalcSelfPosY(YF1[i], YF2[i], dt);
		if (br) { dTotalY += dt; iNumY++; }
	}

	m_vSelfPos = Vector(dTotalX / iNumX, dTotalY / iNumY, 0);
	
	if (CalcSelfPosZ(dt)) m_vSelfPos.Vz = dt;
	else m_vSelfPos.Vz = m_dStandHeight;
}


void WorldModel::UpdateAngle()
{
	m_dFaceAng = GetFaceAngInGlobalEx();
	m_dBodyAng = GetBodyAng(m_dFaceAng);
/** 这里的人的仰角和身体的倾斜角没有算 */
}


void WorldModel::UpdateSelfPos()
{
	Location();
/** 为了避免算出的人的位置发生跳变，如果跳变就恢复到原来的值 */

	static int iErrNum = 0;
	VecPosInfo vP;
	MyPosQ.getLast(vP);
	double dDeltaMod = (m_vSelfPos - vP.vPos).GetMod();
	if (dDeltaMod < 0.8 || iErrNum > 5)
	{
		vP.vPos = m_vSelfPos;
		//vP.bValid = true;
		vP.dTime = m_dServerTime;
		MyPosQ.enQueueEx(vP);
		iErrNum = 0;
	}
	else
	{
		iErrNum++;
		m_vSelfPos = vP.vPos;
	}

	m_TeamMate[m_iUnum-1].bValid = true;
	m_TeamMate[m_iUnum-1].vPos = m_vSelfPos;
	m_TeamMate[m_iUnum-1].dTime = m_dServerTime;

}


void WorldModel::UpdatePlayerPos()
{
	for(int i = 0; i < 11; i++)
	{
		if (SenseParse.m_TeamMate[i].bCanSee)
		{
			m_TeamMate[i].bValid = true;
			m_TeamMate[i].vPos = GetObjPos(SenseParse.m_TeamMate[i].PolPos);
			m_TeamMate[i].dTime = SenseParse.m_TeamMate[i].dTime;
		}
		else if ( i != m_iUnum-1 ) //Dunqiao Bao
			m_TeamMate[i].bValid = false;

		if (SenseParse.m_Opponent[i].bCanSee)
		{
			m_Opponent[i].bValid = true;
			m_Opponent[i].vPos = GetObjPos(SenseParse.m_Opponent[i].PolPos);
			m_Opponent[i].dTime = SenseParse.m_Opponent[i].dTime;
		}
		else m_Opponent[i].bValid = false;
	}
}


void WorldModel::UpdateBallPos()
{
	Vector vBallPos = GetObjPos(SenseParse.m_PolBallPos.PolPos);//GetBallPosInXY();
	static int iErrNum = 0;
	VecPosInfo vP;
	BallPosQ.getLast(vP);
	double dDeltaMod = (vBallPos - vP.vPos).GetMod();
	if (dDeltaMod < 0.5 || iErrNum > 5)
	{
		vP.vPos = vBallPos;
		//vP.bValid = true;
		vP.dTime = m_dServerTime;
		BallPosQ.enQueueEx(vP);
		iErrNum = 0;
		m_vBallPos = vBallPos;
	}
	else iErrNum++;
}

