#include "msgparse.h"

MsgParse::MsgParse()
{
	m_sMsg = "";
	m_iUnum = 0;
	m_bIsLeft = true;
	m_sTeamName = "HfutEngine3D";
	m_sOppTeamName = "UNKNOWTEAM";
	InitJoint();
}

MsgParse::~MsgParse()
{
}

bool MsgParse::IsIncludeInNum(char c)
{
	return ((c>='0'&&c<='9')||c=='.'||c=='-');
}

bool MsgParse::IsNum(char c)
{
	return (c>='0'&&c<='9');
}

bool MsgParse::IsNumHead(char c)
{
	return ((c>='0'&&c<='9')||c=='-');
}

void MsgParse::InitJoint()
{
	#ifdef NAO_MODEL
	m_HJ[JID_HEAD_1].ID = JID_HEAD_1;
	m_HJ[JID_HEAD_2].ID = JID_HEAD_2;
	m_HJ[JID_LARM_1].ID = JID_LARM_1;
	m_HJ[JID_RARM_1].ID = JID_RARM_1;
	m_HJ[JID_LARM_2].ID = JID_LARM_2;
	m_HJ[JID_RARM_2].ID = JID_RARM_2;
	m_HJ[JID_LARM_3].ID = JID_LARM_3;
	m_HJ[JID_RARM_3].ID = JID_RARM_3;
	m_HJ[JID_LARM_4].ID = JID_LARM_4;
	m_HJ[JID_RARM_4].ID = JID_RARM_4;
	m_HJ[JID_LLEG_1].ID = JID_LLEG_1;
	m_HJ[JID_RLEG_1].ID = JID_RLEG_1;
	m_HJ[JID_LLEG_2].ID = JID_LLEG_2;
	m_HJ[JID_RLEG_2].ID = JID_RLEG_2;
	m_HJ[JID_LLEG_3].ID = JID_LLEG_3;
	m_HJ[JID_RLEG_3].ID = JID_RLEG_3;
	m_HJ[JID_LLEG_4].ID = JID_LLEG_4;
	m_HJ[JID_RLEG_4].ID = JID_RLEG_4;
	m_HJ[JID_LLEG_5].ID = JID_LLEG_5;
	m_HJ[JID_RLEG_5].ID = JID_RLEG_5;
	m_HJ[JID_LLEG_6].ID = JID_LLEG_6;
	m_HJ[JID_RLEG_6].ID = JID_RLEG_6;

    m_HJ[JID_HEAD_1].sPerceptorName = "hj1";
    m_HJ[JID_HEAD_2].sPerceptorName = "hj2";
    m_HJ[JID_LLEG_1].sPerceptorName = "llj1";
    m_HJ[JID_LLEG_2].sPerceptorName = "llj2";
    m_HJ[JID_LLEG_3].sPerceptorName = "llj3";
    m_HJ[JID_LLEG_4].sPerceptorName = "llj4";
    m_HJ[JID_LLEG_5].sPerceptorName = "llj5";
    m_HJ[JID_LLEG_6].sPerceptorName = "llj6";
    m_HJ[JID_RLEG_1].sPerceptorName = "rlj1";
    m_HJ[JID_RLEG_2].sPerceptorName = "rlj2";
    m_HJ[JID_RLEG_3].sPerceptorName = "rlj3";
    m_HJ[JID_RLEG_4].sPerceptorName = "rlj4";
    m_HJ[JID_RLEG_5].sPerceptorName = "rlj5";
    m_HJ[JID_RLEG_6].sPerceptorName = "rlj6";
    m_HJ[JID_LARM_1].sPerceptorName = "laj1";
    m_HJ[JID_LARM_2].sPerceptorName = "laj2";
    m_HJ[JID_LARM_3].sPerceptorName = "laj3";
    m_HJ[JID_LARM_4].sPerceptorName = "laj4";
    m_HJ[JID_RARM_1].sPerceptorName = "raj1";
    m_HJ[JID_RARM_2].sPerceptorName = "raj2";
    m_HJ[JID_RARM_3].sPerceptorName = "raj3";
    m_HJ[JID_RARM_4].sPerceptorName = "raj4";
    
	#else
	
    m_HJ[ID_LLEG_1].ID = ID_LLEG_1;
    m_HJ[ID_RLEG_1].ID = ID_RLEG_1;
    m_HJ[ID_LLEG_4].ID = ID_LLEG_4;
    m_HJ[ID_RLEG_4].ID = ID_RLEG_4;
    m_HJ[ID_LARM_3].ID = ID_LARM_3;
    m_HJ[ID_RARM_3].ID = ID_RARM_3;
    m_HJ[ID_LARM_4].ID = ID_LARM_4;
    m_HJ[ID_RARM_4].ID = ID_RARM_4;
    	
    m_UJ[ID_LLEG_2_3].ID = ID_LLEG_2_3;
    m_UJ[ID_RLEG_2_3].ID = ID_RLEG_2_3;
    m_UJ[ID_LLEG_5_6].ID = ID_LLEG_5_6;
    m_UJ[ID_RLEG_5_6].ID = ID_RLEG_5_6;
    m_UJ[ID_LARM_1_2].ID = ID_LARM_1_2;
    m_UJ[ID_RARM_1_2].ID = ID_RARM_1_2;
	
    m_HJ[ID_LLEG_1].sPerceptorName = "llj1";
    m_HJ[ID_RLEG_1].sPerceptorName = "rlj1";
    m_HJ[ID_LLEG_4].sPerceptorName = "llj4";
    m_HJ[ID_RLEG_4].sPerceptorName = "rlj4";
    m_HJ[ID_LARM_3].sPerceptorName = "laj3";
    m_HJ[ID_RARM_3].sPerceptorName = "raj3";
    m_HJ[ID_LARM_4].sPerceptorName = "laj4";
    m_HJ[ID_RARM_4].sPerceptorName = "raj4";
    	
    m_UJ[ID_LLEG_2_3].sPerceptorName = "llj2_3";
    m_UJ[ID_RLEG_2_3].sPerceptorName = "rlj2_3";
    m_UJ[ID_LLEG_5_6].sPerceptorName = "llj5_6";
    m_UJ[ID_RLEG_5_6].sPerceptorName = "rlj5_6";
    m_UJ[ID_LARM_1_2].sPerceptorName = "laj1_2";
    m_UJ[ID_RARM_1_2].sPerceptorName = "raj1_2";

	#endif
     
}

double MsgParse::StringToFloat(string sNum)
{
	int iStrLen = sNum.length();
	if (iStrLen<=0) return 0.0;
	int iDotPos = sNum.find(".");
	if (iDotPos<0) iDotPos = iStrLen;
	int iSign = (sNum[0]=='-'?-1:1);
	double iMultiply = 1.0;
	int iTemp = (iSign==-1?iDotPos-1:iDotPos);
	while(--iTemp) iMultiply*=10;
	double dResult = 0.0;
	int iIndex = (iSign==-1?1:0);
	while(iIndex < iStrLen)
	{
		if (sNum[iIndex]!='.')
		{
			dResult += (sNum[iIndex]-48)*iMultiply;
			iMultiply/=10.0;
		}
		iIndex++;
	}
	return dResult*iSign;
}

double MsgParse::GetFloat(string sMsg,int &iStartPos,int &iEndPos)
{
	int iIndex = iStartPos;
	int iMsgLen = sMsg.length();
	while(iIndex < iMsgLen)
	{
		iIndex = sMsg.find(" ",iIndex);
		if (iIndex<0) break;
		iIndex++;
		if (!IsNumHead(sMsg[iIndex])) continue;
		if (sMsg[iIndex]=='-'&&!IsNum(sMsg[iIndex+1])) continue;
		iEndPos = iIndex;
		while(iEndPos+1<iMsgLen&&IsIncludeInNum(sMsg[iEndPos+1])) iEndPos++;
		if (sMsg[iEndPos+1]!=' '&&sMsg[iEndPos+1]!=')')
		{
			iIndex = iEndPos;
			continue;
		}
		iStartPos = iIndex;
		return StringToFloat(sMsg.substr(iIndex,iEndPos - iIndex + 1));
	}
	iStartPos = -1;
	return 0.0;
}

string MsgParse::GetString(string sMsg,int &iStartPos,int &iEndPos)
{
	int iIndex = iStartPos;
	int iMsgLen = sMsg.length();
	while(iIndex < iMsgLen)
	{
		while (sMsg[iIndex]=='('||sMsg[iIndex]==')'||sMsg[iIndex]==' ')
		{
			if (++iIndex>=iMsgLen)
			{
				iStartPos = -1;
				return "";
			}
		}
		iStartPos = iIndex;
		iEndPos = iIndex;
		while (iEndPos<iMsgLen&&sMsg[iEndPos]!=')'&&sMsg[iEndPos]!=' ') iEndPos++;
		return sMsg.substr(iIndex,iEndPos - iIndex);
	}
	iStartPos = -1;
	return "";
}

Polar MsgParse::GetPolar(string sMsg,int &iStartPos,int &iEndPos)
{
	Polar pPol;
	pPol.Px = GetFloat(sMsg,iStartPos,iEndPos);
	iStartPos = iEndPos + 1;
	pPol.Py = GetFloat(sMsg,iStartPos,iEndPos);
	iStartPos = iEndPos + 1;
	pPol.Pz = GetFloat(sMsg,iStartPos,iEndPos);
	return pPol;
}

bool MsgParse::GetPolar(string sMsg,string FlagID,Polar &pResult)
{
	int iIndex = sMsg.find("(" + FlagID + " (pol");
	if (iIndex<0) return false;
	iIndex += 7;
	int iTemp;
	pResult = GetPolar(sMsg,iIndex,iTemp);
	return true;
}

void MsgParse::Parse(string sMsg)
{
	m_sMsg = sMsg;
	ParseServerTime(m_dServerTime);
	ParseGameState(m_dGameTime, m_sPlayMode);
	ParseGyro(m_Gyro);
	
	/** Parse see info */
	int iIndex = m_sMsg.find("See");

	m_bThisCycleHaveSeeInfo = (iIndex > 0);
	if (m_bThisCycleHaveSeeInfo)
	{
		ClearSeeFlag();
		ParsePlayer();
		ParseFlag("F1L", m_PolFlagPos[F_F1L]);
		ParseFlag("G1L", m_PolFlagPos[F_G1L]);
		ParseFlag("G2L", m_PolFlagPos[F_G2L]);
		ParseFlag("F2L", m_PolFlagPos[F_F2L]);
		ParseFlag("F1R", m_PolFlagPos[F_F1R]);
		ParseFlag("G1R", m_PolFlagPos[F_G1R]);
		ParseFlag("G2R", m_PolFlagPos[F_G2R]);
		ParseFlag("F2R", m_PolFlagPos[F_F2R]);
		ParseBall(m_PolBallPos);
	}
	/** Parse see info */

    #ifdef NAO_MODEL
    for(int i = 0; i < 22; i++) ParseHJ(m_HJ[i].sPerceptorName, m_HJ[i]);
    #else
    int i = 0;
    for(; i < 8; i++) ParseHJ(m_HJ[i].sPerceptorName, m_HJ[i]);
    for(i = 0; i < 6; i++) ParseUJ(m_UJ[i].sPerceptorName, m_UJ[i]);
    #endif
	
	ParseFRP("lf", m_frp_lf);
	ParseFRP("rf", m_frp_rf);
	
	ParseHearMsg();

	if (m_iUnum == 0) //have not inited yet
	{
		Parseunum(m_iUnum);
		ParseSide(m_bIsLeft);
	}
}

bool MsgParse::ParseGameState(double &dTime,string &sPm)
{
	int iIndex = m_sMsg.find("(GS");
	if (iIndex<0) return false;
	iIndex = m_sMsg.find("(t ",iIndex + 4);
	if (iIndex<0) return false;
	int iEndPos;
	dTime = GetFloat(m_sMsg,iIndex,iEndPos);
	iIndex = iEndPos + 1;
	iIndex = m_sMsg.find("pm",iIndex);
	if (iIndex<0) return false;
	iIndex+=3;
	sPm = GetString(m_sMsg,iIndex,iEndPos);
	return true;
}

bool MsgParse::ParseServerTime(double &dTime)
{
	int iIndex = m_sMsg.find("time (now");
	if (iIndex<0) return false;
	int iTemp;
	dTime = GetFloat(m_sMsg,iIndex,iTemp);
	return true;
}

bool MsgParse::Parseunum(int &iunum)
{
	int iIndex = m_sMsg.find("(unum");
	if (iIndex<0) return false;
	int iTemp;
	iunum = (int)GetFloat(m_sMsg,iIndex,iTemp);
	return true;
}

bool MsgParse::ParseSide(bool &bIsLeft)
{
	int iIndex = m_sMsg.find("(team left");
	if (iIndex > 0) { bIsLeft = true; return true; }
	iIndex = m_sMsg.find("(team right");
	if (iIndex > 0) { bIsLeft = false; return true; }
	return false;
}

bool MsgParse::ParsePlayer()
{
	int iIndex = m_sMsg.find("P (team");
	if (iIndex<0) return false;
	int iEndPos, iNum;
	string sTeamName;
	int iMsgLen = m_sMsg.length();
	while(iIndex>0 && iIndex<iMsgLen)
	{
		iIndex+=8;
		sTeamName = GetString(m_sMsg, iIndex, iEndPos);
		iIndex = m_sMsg.find("id",iEndPos+1) + 2;
		iNum = (int)GetFloat(m_sMsg,iIndex,iEndPos);
		iIndex = iEndPos+1;	
		if(iNum>=1 && iNum<=11)
		{
			iIndex = m_sMsg.find("pol",iIndex) + 3;

			if(sTeamName == m_sTeamName)
			{
				m_TeamMate[iNum-1].PolPos = GetPolar(m_sMsg,iIndex,iEndPos);
				m_TeamMate[iNum-1].dTime = m_dServerTime;
				m_TeamMate[iNum-1].bCanSee = true;
				iIndex = iEndPos+1;
			}
			else
			{
				m_sOppTeamName = sTeamName;
				m_Opponent[iNum-1].PolPos = GetPolar(m_sMsg,iIndex,iEndPos);
				m_Opponent[iNum-1].dTime = m_dServerTime;
				m_Opponent[iNum-1].bCanSee = true;
				iIndex = iEndPos+1;
			}
		}
		iIndex = m_sMsg.find("P (team",iIndex);
	}
	return true;
}

bool MsgParse::ParseGyro(GyroInfo &gyro)
{
	int iIndex = m_sMsg.find("GYR (n");
	if (iIndex<0) return false;
	iIndex += 6;
	int iEndPos;
	gyro.sName = GetString(m_sMsg,iIndex,iEndPos);
	iIndex = iEndPos + 1;
	gyro.dx = GetFloat(m_sMsg,iIndex,iEndPos);
	iIndex = iEndPos + 1;
	gyro.dy = GetFloat(m_sMsg,iIndex,iEndPos);
	iIndex = iEndPos + 1;
	gyro.dz = GetFloat(m_sMsg,iIndex,iEndPos);
	gyro.dTime = m_dServerTime;
	return true;
}

bool MsgParse::ParseFlag(string sFlag, PolPosInfo &PolFlag)
{
     bool r = GetPolar(m_sMsg, sFlag, PolFlag.PolPos);
     if (r)
     {
          PolFlag.dTime = m_dServerTime;
          PolFlag.bCanSee = true;
     }
     return r;
}

bool MsgParse::ParseBall(PolPosInfo &PolBall)
{
     bool r = GetPolar(m_sMsg, "B", PolBall.PolPos);
     if (r)
     {
          PolBall.dTime = m_dServerTime;
          PolBall.bCanSee = true;
     }
     return r;
}

bool MsgParse::ParseHJ(string sEff,HJInfo &HJResult)
{
	int iIndex = m_sMsg.find(sEff);
	if (iIndex<0) return false;
	iIndex = m_sMsg.find("ax",iIndex + 6);
	if (iIndex<0) return false;
	iIndex += 2;
	int iTemp;
	HJResult.fAngle = GetFloat(m_sMsg,iIndex,iTemp);
	return true;
}

bool MsgParse::ParseUJ(string sEff,UJInfo &UJResult)
{
	int iIndex = m_sMsg.find(sEff);
	if (iIndex<0) return false;
	int iEndPos;
	iIndex = m_sMsg.find("ax1",iIndex + 8);
	if (iIndex<0) return false;
	iIndex += 3;
	UJResult.fAngle1 = GetFloat(m_sMsg,iIndex,iEndPos);
	iIndex = iEndPos + 1;
	iIndex = m_sMsg.find("ax2",iIndex);
	if (iIndex<0) return false;
	iIndex += 3;
	UJResult.fAngle2 = GetFloat(m_sMsg,iIndex,iEndPos);
	return true;
}

bool MsgParse::ParseFRP(string sID, FRPInfo &frp)
{
	if ((sID!="lf")&&(sID!="rf")) return false;
	string sTemp;
	if (sID=="lf") sTemp = "FRP (n lf)";
		else sTemp = "FRP (n rf)";
	int iIndex = m_sMsg.find(sTemp);
	if (iIndex<0) return false;
	int iEndPos;
	Polar pTemp;

	iIndex = m_sMsg.find("c",iIndex + 10);
	if (iIndex<0) return false;
	pTemp = GetPolar(m_sMsg,iIndex,iEndPos);
	frp.cx = pTemp.GetPx();
	frp.cy = pTemp.GetPy();
	frp.cz = pTemp.GetPz();

	iIndex = m_sMsg.find("f",iEndPos + 2);
	if (iIndex<0) return false;
	pTemp = GetPolar(m_sMsg,iIndex,iEndPos);
	frp.dx = pTemp.GetPx();
	frp.dy = pTemp.GetPy();
	frp.dz = pTemp.GetPz();
	frp.dTime = m_dServerTime;

	return true;
}

void MsgParse::ClearSeeFlag()
{
	int i = 0;
	for(; i < 11; i++)
	{
          m_Opponent[i].bCanSee = false;
          m_TeamMate[i].bCanSee = false;
    }
    for(i = 0; i < 8; i++) m_PolFlagPos[i].bCanSee = false;
    m_PolBallPos.bCanSee = false;
}

bool MsgParse::ParseHearMsg()
{
	int iIndex = m_sMsg.find("hear");
	if (iIndex<0) return false;
	int iEndPos;
	int iArrayIndex = 0;
	string t;
	
	for(int i = 0; i < 22; i++)
	{
           m_HearMsg[i].bValid = false;
           m_HearMsg[i].sMsg = "";
           m_HearMsg[i].dDirection = 0;
           m_HearMsg[i].bIsHeardfromSelf = false;
           m_HearMsg[i].dHeardTime = -1;
        }
	
	while(iIndex > 0 && iIndex < m_sMsg.length())
	{
                 iIndex += 4;
                 m_HearMsg[iArrayIndex].bValid = true;
                 m_HearMsg[iArrayIndex].dHeardTime = GetFloat(m_sMsg, iIndex, iEndPos);
                 iIndex = iEndPos + 1;
                 t = GetString(m_sMsg, iIndex, iEndPos);
                 if (t == "self") m_HearMsg[iArrayIndex].bIsHeardfromSelf = true;
                 else m_HearMsg[iArrayIndex].dDirection = StringToFloat(t);
                 iIndex = iEndPos + 1;
                 m_HearMsg[iArrayIndex].sMsg = GetString(m_sMsg, iIndex, iEndPos);

                 iArrayIndex++;

                 if (iArrayIndex >= 22) break;  /** ---------------------------*/

                 iIndex = m_sMsg.find("hear", iEndPos);
        }
    return true;
}
