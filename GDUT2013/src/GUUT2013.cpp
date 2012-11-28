 #include <cstdlib>
#include <iostream>
#include <signal.h>
#include <time.h>

#include "soccertypes.h"
#include "robot.h"
#include "worldmodel.h"
#include "connection.h"
#include "msgparse.h"
#include "acthandle.h"

using namespace std;

static bool gLoop = true ;
static bool bCheckTime = true;

Robot robot;
WorldModel wm;
MsgParse SenseParse;
Connection connection;
ActHandle ACT;

extern "C" void handler(int sig)
{
    if (sig == SIGINT)
        gLoop = false;
}

SysTime GetTime()
{
	time_t curti = time(NULL);
	struct tm* pTM;
	pTM = localtime(&curti);
	SysTime tmp;
	tmp.year = pTM->tm_year + 1900;
	tmp.month = pTM->tm_mon + 1;
	tmp.day = pTM->tm_mday;
	tmp.hour = pTM->tm_hour;
	tmp.minute = pTM->tm_min;
	tmp.second = pTM->tm_sec;
	return tmp;
}

void CheckTime()
{
	SysTime t = GetTime();
	//if (.year != 2007 || t.month != 10 || t.day < 21) exit(0);
}

void PrintHelp()
{
	cout << "\noptions:" << endl;
	cout << " --help      prints this message." << endl;
	cout << " --host=IP   set IP of the server, default: 127.0.0.1" << endl;
	cout << " --port=XXX  set the port to connect, default: 3100" <<endl;
	cout << " --goalier" <<endl;
	cout << " --teamname=XXX  set the teamname, default: HFUT-Engine" <<endl;
	cout << " --unum=0~11     set the num of player, default: 0" <<endl;
	cout << " --beam=a,b,c    set the init position of player" <<endl;
	cout << " --kick" <<endl;
	cout << " --walk" <<endl;
	cout << " --smallwalk" <<endl;
	cout << " --turnleft" <<endl;
	cout << " --turnright" <<endl;
	cout << " --demo" <<endl;
	cout << " --standup" <<endl;

	cout << endl;

}

void ReadOptions(int argc, char* argv[])
{

	if (argc <= 1) return;
	for( int i = 1; i < argc; i++)
	{
		if ( strcmp( argv[i], "--help" ) == 0 ) break;

		else if ( strncmp( argv[i], "--host", 6 ) == 0 )
		{
			string tmp = argv[i];
			if ( tmp.length() <= 7 ) break;
			connection.SetHostIP(tmp.substr(7).c_str());
		}

		else if ( strncmp( argv[i], "--port", 6 ) == 0 )
		{
			string tmp = argv[i];
			if ( tmp.length() <= 7 ) break;
			connection.SetHostPort((int)SenseParse.StringToFloat(tmp.substr(7)));
		}

		else if ( strncmp( argv[i], "--teamname", 10 ) == 0 )
		{
			string tmp = argv[i];
			if ( tmp.length() <= 11 ) break;
			wm.SetTeamName(tmp.substr(11).c_str());
		}

		else if ( strncmp( argv[i], "--unum", 6 ) == 0 )
		{
			string tmp = argv[i];
			if ( tmp.length() <= 7 ) break;
			wm.SetCmdUnum((int)SenseParse.StringToFloat(tmp.substr(7)));
		}

		else if ( strncmp( argv[i], "--beam", 6 ) == 0 )
		{
			string tmp = argv[i];
			if ( tmp.length() <= 11 ) break;
			tmp = tmp.substr(7);
			for( int j = 0; j < tmp.length(); j++)
			{
				if (tmp[j]==',') tmp[j]=' ';
			}
			tmp = "( " + tmp + ")";
			int iStart = 1, iEnd;
			Polar pTemp = SenseParse.GetPolar(tmp, iStart, iEnd);
			wm.SetBeamPos(pTemp.Px,pTemp.Py,pTemp.Pz);
		}

		else if ( strcmp( argv[i], "--kick" ) == 0 )
		{
			wm.SetCmdType(CMD_KICK);
		}

		else if ( strcmp( argv[i], "--walk" ) == 0 )
		{
			wm.SetCmdType(CMD_WALK);
		}

		else if ( strcmp( argv[i], "--smallwalk" ) == 0 )
		{
			wm.SetCmdType(CMD_SMALLWALK);
		}

		else if ( strcmp( argv[i], "--turnleft" ) == 0 )
		{
			wm.SetCmdType(CMD_TURNLEFT);
		}

		else if ( strcmp( argv[i], "--turnright" ) == 0 )
		{
			wm.SetCmdType(CMD_TURNRIGHT);
		}

		else if ( strcmp( argv[i], "--demo" ) == 0 )
		{
			wm.SetCmdType(CMD_DEMO);
		}

		else if ( strcmp( argv[i], "--standup" ) == 0 )
		{
			wm.SetCmdType(CMD_STANDUP);
		}

		else if ( strcmp( argv[i], "--goalier" ) == 0 )
		{
			wm.SetCmdType(CMD_GOALIER);
		}

		else if ( strcmp( argv[i], "--disablechecktime" ) == 0 )
		{
			bCheckTime = false;
		}

		if (argc-1 == i) return;
	}

	PrintHelp();
	exit(0);

}

int main(int argc, char *argv[])
{
    ReadOptions(argc, argv);
    if (bCheckTime) CheckTime();

    signal(SIGINT, handler);

	if (!robot.Create())
    {
         return 1;
    }

	cout<<"Start Playing...."<<endl;
	while (gLoop)
	{
		if (!robot.Run()) break;
	}
    return EXIT_SUCCESS;
}
