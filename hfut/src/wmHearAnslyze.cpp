#include "worldmodel.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
extern Geometry geometry;

/** Abstract from User-Mannual:
 The number of messages which can be heard at the same time is bounded: Each player
 has the maximal capacity of one heard message by a speciﬁc team every two sensor cy-
 cles (thus every 0.4 seconds per team). There are separately tracked capacities for both
 teams, because teams should not be able to block the hear perceptors of their opponents
 by shouting permanently. If more messages from players of one team arrive, they are
 processed in the order of arrival; the remaining messages are simply not heard.
 Messages shouted by oneself, though, can always be noticed [Vor06].
*/

/** Say Information Map   Modified by alexbao 2008-06-26
*Byte1-4:hfut 
*Byte5-6:SayToWho
*Byte7-8:WhoAmI
*Byte9:State
Optional:
*Byte10-11:CurrentTarget
*Byte12:SuggestCMD1
*Byte13:SuggestCMD2
*Byte14:PredictOpp1State
*Byte15:PredictOpp1Action
*Byte16:PredictOpp2State
*Byte17:PredictOpp2Action
*Byte18:PredictOpp3State
*Byte19:PredictOpp3Action
InvalidFlag: 1Byte:"|"
EndingFlag: 1Byte: "~"
*/


string WorldModel::GetOthersSay ()
{
	stringstream ss("");
	int iTmp1 = 0;
	for (;iTmp1 < 22 ; iTmp1++)
	{ //!SenseParse.m_HearMsg[iTmp1].bIsHeardfromSelf
		if (  SenseParse.m_HearMsg[iTmp1].bValid ) 
			ss<<SenseParse.m_HearMsg[iTmp1].sMsg<<" game time "<<GetGameTime()<<" hear time "<<SenseParse.m_HearMsg[iTmp1].dHeardTime<<"\n";
	}
	
	return ss.str();
		
}


void WorldModel::AnslyzeTeammateSay()
{
	int iTmp1 = 0;
	int iTeammateNum = 0;
	stringstream ss("");
	for (;iTmp1 < 11 ; iTmp1++)
	{ 
		
		ss.str("");
		if (!SenseParse.m_HearMsg[iTmp1].bIsHeardfromSelf && SenseParse.m_HearMsg[iTmp1].bValid && strstr(SenseParse.m_HearMsg[iTmp1].sMsg.c_str(),OtherSayInfoTeam[iTmp1].identification.c_str())) 
		{
			
			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[6]<<SenseParse.m_HearMsg[iTmp1].sMsg[7];iTeammateNum=(ss.str() != "||")?atoi(ss.str().c_str()):-1; ss.str("");

			OtherSayInfoTeam[iTeammateNum-1].WhoAmI = iTeammateNum;

			OtherSayInfoTeam[iTeammateNum-1].bValid= true;

			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[4]<<SenseParse.m_HearMsg[iTmp1].sMsg[5];OtherSayInfoTeam[iTeammateNum-1].SayToWho = (ss.str() != "||")?atoi(ss.str().c_str()):-1; ss.str("");

			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[8];OtherSayInfoTeam[iTeammateNum-1].State = (ss.str() != "|")?atoi(ss.str().c_str()):-1;	ss.str("");
	
			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[9]<<SenseParse.m_HearMsg[iTmp1].sMsg[10];OtherSayInfoTeam[iTeammateNum-1].CurrentTar = (ss.str() != "||")?atoi(ss.str().c_str()):-1; ss.str("");

			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[11];OtherSayInfoTeam[iTeammateNum-1].SuggestMate1 = (ss.str() != "|")?atoi(ss.str().c_str()):-1;	ss.str("");

			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[12];OtherSayInfoTeam[iTeammateNum-1].SuggestMate2 = (ss.str() != "|")?atoi(ss.str().c_str()):-1;	ss.str("");

			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[13];OtherSayInfoTeam[iTeammateNum-1].PredictOpp1State = (ss.str() != "|")?atoi(ss.str().c_str()):-1;	ss.str("");

			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[14];OtherSayInfoTeam[iTeammateNum-1].PredictOpp1Act = (ss.str() != "|")?atoi(ss.str().c_str()):-1;	ss.str("");

			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[15];OtherSayInfoTeam[iTeammateNum-1].PredictOpp2State = (ss.str() != "|")?atoi(ss.str().c_str()):-1;	ss.str("");

			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[16];OtherSayInfoTeam[iTeammateNum-1].PredictOpp2Act = (ss.str() != "|")?atoi(ss.str().c_str()):-1;	ss.str("");

			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[17];OtherSayInfoTeam[iTeammateNum-1].PredictOpp3State = (ss.str() != "|")?atoi(ss.str().c_str()):-1;	ss.str("");

			ss<<SenseParse.m_HearMsg[iTmp1].sMsg[18];OtherSayInfoTeam[iTeammateNum-1].PredictOpp3Act = (ss.str() != "|")?atoi(ss.str().c_str()):-1;	ss.str("");

			OtherSayInfoTeam[iTeammateNum-1].dHeardTime = SenseParse.m_HearMsg[iTmp1].dHeardTime;
			OtherSayInfoTeam[iTeammateNum-1].dDirection = SenseParse.m_HearMsg[iTmp1].dDirection;			
		}
	}
}

bool WorldModel::FindString(string sMsg,string sFindMsg)
{
	int iIndex1 = 0;
	bool bFind = false;
	int iMsgLen = sMsg.length();
	int iFindMsgLen = sFindMsg.length();
	if (iMsgLen<iFindMsgLen) return false;
	if ((int)strstr(sMsg.c_str(),sFindMsg.c_str()) == 0) return false;
	return true;
	
}

string WorldModel::GetMySay ()
{
	int iTmp1 = 0;
	bool find = false;
	int iTmp2 = -1;
	stringstream ss("");
	for (;iTmp1 < 22 && !find;iTmp1++)
	{
		if (SenseParse.m_HearMsg[iTmp1].bIsHeardfromSelf)
		{
			iTmp2 = iTmp1;
			find = true;
		}
		
	}

	if (find)
	{
		ss<<SenseParse.m_HearMsg[iTmp2].sMsg<<SenseParse.m_HearMsg[iTmp2].dHeardTime;
		return ss.str();
		
	}
		
	
	
	return "";
}

string WorldModel::GetTeammateSay (int iTeammateNum)
{

}

string WorldModel::GetOppSay (int iOppNum)
{

}

void WorldModel::EnCodeInfo ( int iIndex)
{

}

void WorldModel::DeCodeInfo ( int iIndex)
{

}

char WorldModel::C2EC(char c)
{
	switch (c)
	{
		case '0' :  return '3';
		case '1' :  return '9';
		case '2' :  return '5';
		case '3' :  return '.';
		case '4' :  return '7';
		case '5' :  return '-';
		case '6' :  return '0';
		case '7' :  return '4';
		case '8' :  return '1';
		case '9' :  return '6';
		case '.' :  return '8';
		case '-' :  return '2';
		default : return c;
	}
}


char WorldModel::EC2C(char c)
{
	switch (c)
	{
		case '3' :  return '0' ;
		case '9' :  return '1' ;
		case '5' :  return '2' ;
		case '.' :  return '3' ;
		case '7' :  return '4' ;
		case '-' :  return '5' ;
		case '0' :  return '6' ;
		case '4' :  return '7' ;
		case '1' :  return '8' ;
		case '6' :  return '9' ;
		case '8' :  return '.' ;
		case '2' :  return '-' ;
		default  :  return c;
	}
}

string WorldModel::GenerateSayInfomation ()
{
	stringstream ss("");
	stringstream ssSayToWho("");
	stringstream ssWhoAmI("");
	stringstream ssState("");
	stringstream ssCurrentTar("");
	stringstream ssSuggestMate1("");
	stringstream ssSuggestMate2("");
	stringstream ssPredictOpp1State ("");
	stringstream ssPredictOpp1Act ("");
	stringstream ssPredictOpp2State ("");
	stringstream ssPredictOpp2Act ("");
	stringstream ssPredictOpp3State ("");
	stringstream ssPredictOpp3Act ("");
	
	if (MySayInfo.SayToWho < 10 && MySayInfo.SayToWho >= 0)
		ssSayToWho<<"0"<<MySayInfo.SayToWho;
	else if (MySayInfo.SayToWho > 10)
		ssSayToWho<<MySayInfo.SayToWho;
	else 
		ssSayToWho<<"||";

	if (MySayInfo.WhoAmI < 10 && MySayInfo.WhoAmI >= 0)
		ssWhoAmI<<"0"<<MySayInfo.WhoAmI;
	else if (MySayInfo.WhoAmI > 10)
		ssWhoAmI<<MySayInfo.WhoAmI;
	else
		ssWhoAmI<<"||";

	if (MySayInfo.CurrentTar < 10 && MySayInfo.CurrentTar >= 0)
		ssCurrentTar<<"0"<<MySayInfo.CurrentTar;
	else if (MySayInfo.CurrentTar > 10)
		ssCurrentTar<<MySayInfo.CurrentTar;
	else 
		ssCurrentTar<<"||";
	
	ssState<<MySayInfo.State;
	ssSuggestMate1<<MySayInfo.SuggestMate1;
	ssSuggestMate2<<MySayInfo.SuggestMate2;
	ssPredictOpp1State<<MySayInfo.PredictOpp1State;
	ssPredictOpp1Act<<MySayInfo.PredictOpp1Act;
	ssPredictOpp2State<<MySayInfo.PredictOpp2State;
	ssPredictOpp2Act<<MySayInfo.PredictOpp2Act;
	ssPredictOpp3State<<MySayInfo.PredictOpp3State;
	ssPredictOpp3Act<<MySayInfo.PredictOpp3Act;
	

	ss<<"hfut"<< \
	((MySayInfo.SayToWho != -1) ? ssSayToWho.str():"||") << \
	((MySayInfo.WhoAmI != -1) ? ssWhoAmI.str():"||" )<< \
	((MySayInfo.State != -1) ? ssState.str():"|")<< \
	((MySayInfo.CurrentTar != -1) ? ssCurrentTar.str():"||") << \
	((MySayInfo.SuggestMate1 != -1) ? ssSuggestMate1.str():"|")<< \
	((MySayInfo.SuggestMate2 != -1) ? ssSuggestMate2.str():"|")<< \
	((MySayInfo.PredictOpp1State != -1) ? ssPredictOpp1State.str():"|")<< \
	((MySayInfo.PredictOpp1Act != -1) ? ssPredictOpp1Act.str():"|")<< \
	((MySayInfo.PredictOpp2State != -1) ? ssPredictOpp2State.str():"|")<< \
	((MySayInfo.PredictOpp2Act != -1) ? ssPredictOpp2Act.str():"|")<< \
	((MySayInfo.PredictOpp3State != -1) ? ssPredictOpp3State.str():"|")<< \
	((MySayInfo.PredictOpp3Act != -1) ? ssPredictOpp3Act.str():"|")<<"~";

	EnCodeInfo(0);
	
	return ss.str();
}

void WorldModel::UpdateHearMsg ()
{
	MySayInfo.identification = "hfut";
	MySayInfo.SayToWho = 0;
	MySayInfo.WhoAmI = m_iUnum;
	MySayInfo.State = -1;
	MySayInfo.CurrentTar = -1;
	MySayInfo.SuggestMate1 = MySayInfo.SuggestMate1 = MySayInfo.PredictOpp1State = MySayInfo.PredictOpp1Act = \
	MySayInfo.PredictOpp2State = MySayInfo.PredictOpp2Act = MySayInfo.PredictOpp3State = MySayInfo.PredictOpp3Act = -1;
	
	int iTmp1 = 0;
	for (;iTmp1 < 11 ; iTmp1++)
	{
		//OtherSayInfoTeam[iTmp1].bValid = false;
		OtherSayInfoTeam[iTmp1].identification = "hfut";
		//OtherSayInfoTeam[iTmp1].SayToWho = 0;
		//OtherSayInfoTeam[iTmp1].WhoAmI = 0;
		//OtherSayInfoTeam[iTmp1].State = -1;
		//OtherSayInfoTeam[iTmp1].CurrentTar = -1;
		//OtherSayInfoTeam[iTmp1].SuggestMate1 = OtherSayInfoTeam[iTmp1].SuggestMate1 = \
		//OtherSayInfoTeam[iTmp1].PredictOpp1State = OtherSayInfoTeam[iTmp1].PredictOpp1Act = \
		//OtherSayInfoTeam[iTmp1].PredictOpp2State = OtherSayInfoTeam[iTmp1].PredictOpp2Act = \
		//OtherSayInfoTeam[iTmp1].PredictOpp3State = OtherSayInfoTeam[iTmp1].PredictOpp3Act = 0;
		DeCodeInfo(0);
	}
	
	AnslyzeTeammateSay();
}

bool WorldModel::LogTeammateSay (bool bToFile, string FileName )
{
	int iTmp1 = 0;
	int iTeammateNum = 0;
	stringstream ss("");
	for (;iTmp1 < 11 ; iTmp1++)
	{ 
		if (OtherSayInfoTeam[iTmp1].bValid) 
		{
			ss<<" At time: "<<OtherSayInfoTeam[iTmp1].dHeardTime<<" Teammate "<<OtherSayInfoTeam[iTmp1].WhoAmI<<" Say To "<<OtherSayInfoTeam[iTmp1].SayToWho<<" : his state is "<<OtherSayInfoTeam[iTmp1].State<<"; His target is "<<OtherSayInfoTeam[iTmp1].CurrentTar<<"; SuggestMate1 "<<OtherSayInfoTeam[iTmp1].SuggestMate1<<"; SuggestMate2 "<<OtherSayInfoTeam[iTmp1].SuggestMate2<<"; PredictOpp1State: "<<OtherSayInfoTeam[iTmp1].PredictOpp1State<<"; PredictOpp1Act:"<<OtherSayInfoTeam[iTmp1].PredictOpp1Act<<"; PredictOpp2State: "<<OtherSayInfoTeam[iTmp1].PredictOpp2State<<"; PredictOpp2Act:"<<OtherSayInfoTeam[iTmp1].PredictOpp2Act<<"; PredictOpp3State: "<<OtherSayInfoTeam[iTmp1].PredictOpp3State<<"; PredictOpp3Act:"<<OtherSayInfoTeam[iTmp1].PredictOpp3Act<<endl;
			cout<<ss.str();
			if (bToFile)
			{
				std::stringstream filepath ("");
    				filepath<<"/"<<FileName;
   				int iResult=0;
    				FILE *fp  =fopen(filepath.str().c_str(),"a+");
    				if (!fp)
				{
					cout<<" Can't create file\n";
					return false;   
				}				
    				iResult=fprintf (fp,"%s",ss.str().c_str());
    				fclose (fp);
    				if (!iResult)
				{
					cout<<" Write file error \n";
					return false;   
				}
			}//end if
			ss.str("");
		}
	}//end for
	return true;
}




