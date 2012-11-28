/***************************************************************************
 *   Copyright (C) 2008 by root   *
 *   root@localhost.localdomain   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "worldmodel.h"

extern Geometry geometry;


double WorldModel::GetDist(Vector v1, Vector v2)
{
	Vector v = v1 - v2;
	return v.GetMod();
}


double WorldModel::GetDistInXY(Vector v1, Vector v2)
{
	Vector v = v1 - v2;
	v.SetVz(0);
	return v.GetMod();
}

double WorldModel::GetMeToBallDist()
{
	return GetDist(m_vSelfPos, m_vBallPos);
}


double WorldModel::GetMeToBallDistInXY()
{
	return GetDistInXY(m_vSelfPos, m_vBallPos);
}


double WorldModel::GetBallRelMeXYAngle()  //转到多少度才可以正对着球
{
	return m_dBodyAng + SenseParse.m_PolBallPos.PolPos.Py;
}

/** 2个点所构成的向量的水平角，v1是起点，v2是终点 */
double WorldModel::GetXYAngle(Vector v1, Vector v2)
{
	Vector v = v1 - v2;
	return v.GetXYAngle();
}

/** 人的位置和目标点所构成的向量的水平角 */
double WorldModel::GetXYAngleToPos(Vector vPos)
{
	return GetXYAngle(m_vSelfPos, vPos);
}


Vector WorldModel::GetTentativePosForOmdiWalk(Vector vDestinationPos, double dDestinationAng, Vector vCurrentPos, double dCurrentAng)
{
	Vector vMeToPos = vDestinationPos - vCurrentPos;
	vMeToPos.SetVz(0);
	double dAng = fabs(NormalizeAng(vMeToPos.GetXYAngle() - dDestinationAng));
	double dLen = (vMeToPos.GetMod() / 2.0) / (cos(dAng * PI / 180.0));
	Vector vTemp = vMeToPos.DistAndDirectionMakeVector(dLen, dDestinationAng, 0);
	Vector vResult;
	vResult.SetVx(vDestinationPos.Vx - vTemp.Vx);
	vResult.SetVy(vDestinationPos.Vy - vTemp.Vy);
cout<<"ccccccccccc               "<<vResult<<endl;
	return vResult;
}


Vector WorldModel::GetTentativePosForOmdiWalk(Vector vDestinationPos, double dDestinationAng)
{
	return GetTentativePosForOmdiWalk(vDestinationPos, dDestinationAng, m_vSelfPos, m_dBodyAng);
}

///////////////////////////////////////////////////////////
Vector WorldModel::GetMeRelBall(Vector vTarget)
{
	double dAngle;
	double mod;
	
	Vector vBallToGoal =  vTarget - m_vBallPos;
	vBallToGoal.SetVz(0);
	Vector vMeToBall = m_vSelfPos - m_vBallPos;
	vMeToBall.SetVz(0);
	dAngle = vMeToBall.GetXYAngle() - vBallToGoal.GetXYAngle();
	mod = vMeToBall.GetMod();

	double X = mod * cos(dAngle * PI / 180);
	double Y = mod * sin(dAngle * PI / 180);
	Vector vMeRelBall(X, Y, 0);
	//cout<<"X::"<<X<<endl;
	//cout<<"Y::"<<Y<<endl;
	return vMeRelBall;
}

bool WorldModel::IsKickable(Vector vTarget)
{
	Vector vBallToGoal =  vTarget - m_vBallPos;
	vBallToGoal.SetVz(0);
	
	Vector vMeRelBall = GetMeRelBall(vTarget);
	if( (vMeRelBall.Vx > -0.22 && vMeRelBall.Vx < -0.16) && ( (vMeRelBall.Vy > -0.06 && vMeRelBall.Vy <  0.06) ) && ( abs(m_dBodyAng -  vBallToGoal.GetXYAngle()) < 5) )
	return true;
	else return false;
}

/*double WorldModel::GetDisToBall()
{
	Vector vBallPos = m_vBallPos;
	vBallPos.SetVz(0);
	Vector vMySelfPos = m_vSelfPos;
	vMySelfPos.SetVz(0);
	Vector vMeToBall = vBallPos - vMySelfPos;
	vMeToBall.SetVz(0);
	double disToBall = vMeToBall.GetMod();
	return disToBall;
}*/

int WorldModel::InWhichArea(Vector vTarget)
{
	int areaType;
	Vector vBallToGoal =  vTarget - m_vBallPos;
	vBallToGoal.SetVz(0);
	Vector vMeToBall = m_vSelfPos - m_vBallPos;
	vMeToBall.SetVz(0);
	double dAngle = vMeToBall.GetXYAngle() - vBallToGoal.GetXYAngle();
	double mod = vMeToBall.GetMod();
	double X = mod * cos(dAngle * PI / 180);
	double Y = mod * sin(dAngle * PI / 180);
	//cout<<"relPos_X::::"<<X<<endl;
	//cout<<"relPos_Y::::"<<Y<<endl;
	
	//if(mod > 5) areaType = 0;
	if(X < -0.15) areaType = 1;
	else if(Y > 0.2 || Y < -0.2) areaType = 2;
	else areaType = 3;

	cout<<"areaType::::"<<areaType<<endl;
	return areaType;
}

bool WorldModel::IsFaceBall(Vector vTarget)
{
	return true;
	bool isFaceBall = false;

	Vector vBallToGoal =  vTarget - m_vBallPos;
	vBallToGoal.SetVz(0);
	Vector vMeRelBall = GetMeRelBall(vTarget);

	if( (vMeRelBall.Vx < 0) && ( (vMeRelBall.Vy > 0.01 && vMeRelBall.Vy < 0.06) || (vMeRelBall.Vy > -0.06 && vMeRelBall.Vy < - 0.01) ) && ( abs(m_dBodyAng -  vBallToGoal.GetXYAngle()) < 10) ) return true;
	else return false;
}

bool WorldModel::IsTurnToKick(Vector vTarget)
{
	return true;
	Vector vBallToGoal =  vTarget - m_vBallPos;
	vBallToGoal.SetVz(0);
	if( abs(m_dBodyAng -  vBallToGoal.GetXYAngle()) < 10) return true;
	else return false;
} 

Vector WorldModel::GetShootPos(Vector vTarget ,double dis)
{
	Vector vBallToGoal = m_vBallPos - vTarget;
	vBallToGoal.SetVz(0);
	double dDis = vBallToGoal.GetMod();
	vBallToGoal.SetMod(dDis + dis);
	Vector vKickPos = vTarget + vBallToGoal;
	return vKickPos;
}
