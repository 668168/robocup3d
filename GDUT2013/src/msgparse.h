/***************************************************************************
 *   Copyright (C) 2007 by root   *
 *   ShiGuoqiang   *
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
#ifndef MSGPARSE_H
#define MSGPARSE_H

#include "soccertypes.h"

/**
@author ShiGuoqiang
*/

using namespace std;


class MsgParse{
public:
	MsgParse();
	~MsgParse();
	void Parse(string sMsg);
	string m_sMsg;
	double m_dServerTime;
	double m_dGameTime;
	int m_iUnum;
	bool m_bIsLeft;
	string m_sTeamName;
	string m_sOppTeamName;
	string m_sPlayMode;
	GyroInfo m_Gyro;
	PolPosInfo m_TeamMate[11];
	PolPosInfo m_Opponent[11];
	PolPosInfo m_PolFlagPos[8];
	PolPosInfo m_PolBallPos;
	
	#ifdef NAO_MODEL
	HJInfo m_HJ[22];
	#else
	HJInfo m_HJ[8];
	UJInfo m_UJ[6];
	#endif
	
	FRPInfo m_frp_lf;
	FRPInfo m_frp_rf;
	HearInfo m_HearMsg[22];

	bool m_bThisCycleHaveSeeInfo;
	
	double StringToFloat(string sNum);
	Polar GetPolar(string sMsg,int &iStartPos,int &iEndPos);
	void SetTeamName(string stn) { m_sTeamName = stn; }
	bool ParseHearMsg();

private:
	bool IsIncludeInNum(char c);
	bool IsNum(char c);
	bool IsNumHead(char c);
	double GetFloat(string sMsg,int &iStartPos,int &iEndPos);
	string GetString(string sMsg,int &iStartPos,int &iEndPos);
	bool GetPolar(string sMsg,string FlagID,Polar &PolResult);
	void InitJoint();
	bool ParseServerTime(double &dTime);
	bool Parseunum(int &iunum);
	bool ParseSide(bool &bIsLeft);
	bool ParsePlayer();
	bool ParseGameState(double &dTime,string &sPm);
	bool ParseGyro(GyroInfo &gyro);
	bool ParseFlag(string sFlag,PolPosInfo &PolFlag);
	bool ParseBall(PolPosInfo &PolBall);
	bool ParseHJ(string sEff,HJInfo &HJResult);
	bool ParseUJ(string sEff,UJInfo &UJResult);
	bool ParseFRP(string sID,FRPInfo &frp);
	void ClearSeeFlag();
};

#endif
