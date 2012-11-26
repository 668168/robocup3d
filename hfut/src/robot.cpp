#include "robot.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "soccertypes.h"
#include "worldmodel.h"
#include "connection.h"
#include "msgparse.h"
#include "decision.h"
#include "acthandle.h"
#include "timer.h"
#include "skill.h"

extern Timer timer;
extern ActHandle ACT;
extern MsgParse SenseParse;
extern WorldModel wm;
extern Connection connection;
Skill skill;
Decision decision;


Robot::Robot()
{
	m_bInit = false;
}


Robot::~Robot()
{
}


bool Robot::Create()
{
	cout << "connecting to TCP " << string(connection.GetHostIP()) << ":" << connection.GetHostPort() << "\n";
	if (!connection.Connect())
	{
		cout <<"connecting refused "<<endl;
		return false;
	}
	#ifdef NAO_MODEL
	if (!connection.SendMsg("(scene rsg/agent/nao/nao.rsg)")) return false;
	#else
	if (!connection.SendMsg("(scene rsg/agent/soccerbot056.rsg)")) return false;
	#endif
	return true;
}


bool Robot::Init()
{
	m_bInit = true;
	stringstream ss("");
	ss<<"(init (unum "<<wm.GetCmdUnum()<<")(teamname "<<wm.GetTeamName()<<"))";
	return connection.SendMsg(ss.str());
}


bool Robot::Say(string msg)
{
	stringstream ss("");
	ss << "(say "<<msg<<")";
	return connection.SendMsg(ss.str());
}


bool Robot::Run()
{

	string MsgFromServer;
	if (!connection.ReceiveMsg(MsgFromServer)) return false;
	SenseParse.Parse(MsgFromServer);
	bool bContinueTrain=false;

	wm.UpdateAll();
	ACT.ClearControl();
	timer.CheckTimer();
	if (!m_bInit) Init();
	switch (wm.GetCmdType())
	{
		case CMD_NONE:  bContinueTrain=decision.Do(); break;
		//case CMD_KICK: decision.Demo_Kick(); break;
		//case CMD_WALK: decision.Demo_Walk(); break;
		//case CMD_TURNLEFT: decision.Demo_TurnLeft(); break;
		//case CMD_TURNRIGHT: decision.Demo_TurnRight(); break;
		//case CMD_DEMO: decision.Demo(); break;
		//case CMD_STANDUP: decision.Demo_StandUp(); break;
		//case CMD_GOALIER: decision.GoalieBehave(); break;
		//case CMD_SMALLWALK : decision.Demo_SmallWalk(); break;
		//case CMD_GOALIER: decision.GoalieBehave_Tradition(); break;
		
	}
	connection.SendMsg(ACT.MakeCommand());
	return true;
}


bool Robot::LogFile(char cFileName[], char cMsg[])
{
	char cAddress[100]="/home/";
	int iResult=-1;
	int iMsgLenth=strlen(cMsg);
	strcpy (cAddress+sizeof("/home"),cFileName);
	FILE *fp=fopen(cAddress,"a+");
	iResult=fprintf (fp,"%s",cMsg);
	fprintf (fp,"\n");
	fclose (fp);
	return iResult>=0;
}
