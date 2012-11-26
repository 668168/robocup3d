/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * Additionally,this program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ****************************************************************************************/

/**
 * \mainpage SEU-3D : Southeast University RoboCup Simulation 3D Team
 *
 * \section intro 引言/Introduction
 * 
 * 这里是东南大学足球机器人(<a href="http://www.robocup.org">RoboCup</a>)3D仿真队, 本项目参与<a href="http://sserver.sf.net">RoboCup仿真组</a>3D比赛.
 *
 * This is <a href="http://www.seu.edu.cn">Southeast University</a> <a href="http://www.robocup.org">RoboCup</a> simulation team, SEU-3D project for <a href="http://sserver.sf.net">RoboCup Simulation 3D league</a>.
 *
 * \section license 版权信息/License Information
 *
 * <center>东南大学RoboCup 3D 仿真组</center>
 * <center>SEU-3D: Southeast University RoboCup Simulation 3D Team</center>
 *
 * <center>-------------------------------------------------</center>
 * <li>版权所有/Copyright &copy; 2005, <a href="mailto:xychn15@yahoo.com.cn">许 元/Yuan XU</a>,<a href="mailto:evelinesce@yahoo.com.cn">时长娥/Chang'e SHI</a>\n</li>
 * <li>版权所有/Copyright &copy; 2006, <a href="mailto:xuyuan.cn@gmail.com">许 元/Yuan XU</a>,<a href="mailto:JamAceWatermelon@gmail.com">蒋春露/Chunlu JIANG</a>\n</li>
 * <li>中国东南大学/Southeast University ,China\n</li>
 * <li>保留所有权利./All rights reserved.</li>
 *
 * \section rn Release Note
 *
 * This version of SEU-3D source is released for The 3rd RoboCup Simulation League of Southeast University.<br>
 *<br>
 * This source is based the our RoboCup2006 qualification team, but with some changes:<br>
 * (1) remove the high level decision code in the Player, all situation are play the 'defaultPlayOn'<br>
 * (2) remove the neuro network for the gcc 4.0<br>
 * (3) remove the old trainer in the source code, because we can use the 'SEU-3D-TOOLKIT' instead it<br>
 * (4) update the class  Action and Agent, so it can support the new command: 'catch' and 'say'<br>
 * (5) update the Logger system, so the agent can print logs in the SEU-3D-TOOLKIT<br>
 *<br>
 * Although the agent is not strong, but we think it is good enough for the beginner.<br>
 * Note that we will use rcssserver3d-0.5.2, but with no-restrict-version and 0.5m catch margin.<br>
 *
  * \section po Package Overview
 * The different parts of this package are organized in different directories as follows:<br>
 * <br>
 * ./src  	  	Our agent source code.<br>
 * ./utility		Some useful utility library<br>
 * ./doc		the doxygen files will be generated there, by running 'make doc'<br>
 * ./build                 a script helps to build the source codes<br>
 * ./backup             a script helps to back up source code after changes<br>
 * ./mkpackage       a script helps to collect all files to a running binary tar package<br>
 * ./README          this file<br>
 * ./INSTALL          build guide, in fact you do not need install the binary<br>
 * ./AUTHORS       authors list<br>
 * ./COPYING        a copy of GNU GENERAL PUBLIC LICENSE  Version 2<br>
 * ./THANKS         a list of guys who helped us<br>
 * ./NEWS             new features of different versions<br>
 * ./ChangeLog     what we did everyday<br>
 *
 * \section Contact
 * Any comment is welcome!<br>
 * You can vist the homepage of RoboCup of Southeast University: http://172.19.10.78<br>
 * also you can post your ideas or suggestion or question in http://172.19.10.78/bbs<br>
 * and also you can send email to <a href="mailto:xuyuan.cn@gmail.com">许 元/Xu Yuan</a><br>
 *
 */

/**
 * \file            main.cpp
 *
 * \brief 主循环函数和初始化函数/the main loop and init function.
 *
 *
 * The agent reads length prefixed data (see spades manual 6.3) from fd 3 and
 * writes to fd 4. A corresponding agent DB (agentdb.list, entry
 * 'default') exists in the spadestest directory.
 *
 * LastModify:
 * $Id: main.cpp,v 1.6 2006/02/23 02:23:54 xy Exp $
 */

#include <sstream>
#include <soccer/soccertypes.h>
#include "commserver.h"
#include "Logger.h"
#include "WorldModel.h"
#include "Player.h"
#include "Parser.h"
//#include "Geometry.h"

	


using namespace std;

//------------- global values ----------------------

//-*  the default team name
string teamName = "SEU-3D";

	
//float	opplythe= WM->getOppBaseLine();
//-*  the playes uniform number, if left to zero the server will allocate
//--  the next free unum
int teamUnum = 0;

//-* the default formation file
string formations_fn = "formations.conf";

//-* declare logger instance
//-- define msg logger which log the message send to & receive from the commserver
#ifdef ENABLE_LOG
FileLogger msgLog;
FileLogger localizationLog;
FileLogger ballPosLog;
#endif

//--------------------- end global values ----------------------

void
printHelp( const char* argv0)
{
    cout << "\nUsage: "<<argv0<<" [options]" << endl;
    cout << "\noptions:" << endl;
    cout << " --help      		prints this message." << endl;
    cout << " --teamname  		sets the team name. " << endl;
    cout << " --unum      		sets the uniform number." << endl;
	cout << " --formations_fn   	sets the formations file name." << endl;
    cout << "\n";
}

void
ReadOptions(int argc, char* argv[])
{
    for( int i = 1; i < argc; i++)
    {
        if( strcmp( argv[i], "--teamname" ) == 0 )
        {
            if( i+1  < argc)
            {
                teamName = argv[i+1];
                ++i;
                cout<<"setting teamname to "<<teamName<<endl;
            }
        }
        else if( strcmp( argv[i], "--help" ) == 0 )
        {
            printHelp( argv[0]);
            exit(0);
        }
		else if (strcmp( argv[i], "--unum" ) == 0 )
        {
            teamUnum = atoi(argv[i+1]);
            ++i;
            cout<<"setting uniform number to "<<teamUnum<<endl;
        }
		else if (strcmp( argv[i], "--formations_fn" ) == 0 )
        {
			if( i+1  < argc)
            {
            	formations_fn = argv[i+1];
            	++i;
            	cout<<"setting formations_fn to " << formations_fn <<endl;
			}
        }
		else
		{
            string str = argv[i];
            cout<<"unknown option: " << str <<endl;
			printHelp( argv[0]);
            exit(0);
		}
    }
}

int
Init(int argc, char* argv[])
{
	//-*  read command line options
    ReadOptions(argc,argv);

	//-* init formation
	FM->openFile();
	FM->loadFormation("22");
	FM->closeFile();
	
    PL->setTeamName(teamName);
	WM->setMyTeamName( teamName );
    PL->setTeamUnum(teamUnum);//-* teamUnum = 0 at this time
	
    return 0;
}

#ifdef ENABLE_LOG
void fileLoggerOutPut(const string& message)
{
	//--log message from server
	msgLog.log(message);
	msgLog.log("\n---------------------------\n");
	//--log localization
	if ( message[0] == 'S')
	{
		stringstream ss;
		ss << WM->getGameTime() <<' '<< WM->getMyGlobalPos()
			<< ' ' << WM->getMyGlobalVel()
			<<endl;
		localizationLog.log(ss.str());
	}
	//--log ball's position
	if ( message[0] == 'S')
	{
		stringstream ss;
		ss << WM->getGameTime() <<' '<< WM->getBallGlobalPos()
			<< ' ' << WM->getBallGlobalVel()
			<<endl;
		ballPosLog.log(ss.str());
	}
}
#endif

void
Run()
{
	
//	LOGTABLE;
	
    while (true)
    {
		LOGBEGIN;
		WRITELOG;
        if (! COMM->GetInput())
        {
			LOGERR("[Error]commserver receive nothing!!! exciting...");
            continue;
        }
		
		GL_PRINT("test","myPos[%f, %f, %f]",WM->getMyGlobalPos()[0],WM->getMyGlobalPos()[1],WM->getMyGlobalPos()[2]);
		GL_PRINT("test","ballPos[%f, %f, %f]",WM->getBallGlobalPos()[0],WM->getBallGlobalPos()[1],WM->getBallGlobalPos()[2]);

		
		//-* FileLogger out put ------------------------------------
#ifdef ENABLE_LOG
		fileLoggerOutPut(COMM->GetMsg());
#endif
		PA->parseAll(COMM->GetMsg());
	
        switch( COMM->GetMsg()[0] )
        {
        case 'D' :
            PL->processInitMessage();
            break;

        case 'K' :
            PL->processThinkTimeMessage();
            break;

        case 'S' :
		{
			if ( WM->getPlayMode() != PM_BeforeKickOff )
				PL->sendThinkTimeNotifys();
			
            PL->think();
			PL->endThink();
			GL_FLUSH;
			break;
		}
		
		case 'T' :
		{
			PL->sendAction( WM->getRealTime());
			LOG( 3,"think time set: %i",WM->isThinkTimeNow());
			PL->endThink();
			break;
		}
   
		case 'C' :
			LOG( 2, "C space loop");
			break;
		
		case 'X':
		{
			LOG(0," received 'X'\n So terminate! ");
			LOG(0," Average think time : %f",WM->getAverageThinkTime() );
			terminate();
			break;
		}
		//*TODO* 'O' and 'I' information
		//do nothing just now
		case 'O':
			break;
		case 'I':
			break;
        default:
		{
            LOGERR("received unknown data: ");
            LOGERR(COMM->GetMsg());
            LOGERR("\n");
			PL->endThink();
            break;
		}
        }
    }
}

void copyLeft()
{
	cout<<
				"--------------------------------------------------------------------------\n"                                                                  
				"                                                               #          \n"
				"      ###                                                    ###          \n"
				"       ##                                                    ######       \n"
				"       ##              #                  #                  ######       \n"
				"      ####             ####               #                # ######       \n"
				"     #####           ######               #              # ########       \n"
				"     #########        ###                 #              ##########       \n"
				"     #########        ##    ####          ##    #        ##########       \n"
				"    ##########        ## #######          ##  ####       ###########      \n"
				"   ## ########         # #########        #########       ############    \n"
				"   ##########         ######   ##     ############         ###########    \n"
				"   ########       #  ######   ##        ######         #   ##   #####     \n"
				"   #######        ## #####    ##         ###          ###     ###         \n"
				"     #####        ## ######   ##         ###          ##     ####         \n"
				"      ###         ##  #####   ##         ##   ##             ####         \n"
				"     #### ###     ##  ####   ##         ###    ##             ##          \n"
				"   ######  ###     #   ###  ###         ###    ###            ###         \n"
				"   # ####   ##          #   ###       #####     ###         #######       \n"
				"     ####               #              ###       #         ########       \n"
				"      ##                                                   #  ###         \n"
				"                                                            ####          \n"
				"\n"
				"--------------------------------------------------------------------------\n"
				"  RoboCup 3D Simulation Team, Southeast University, China   \n"
				"  Research Coordinator: Yingzi TAN                          \n"
				"  Team Coordinator:     Yingqiu XU                          \n"
				"  Copyright (C) 2005.   Yuan XU and Chang'e SHI             \n"
				"  Copyright (C) 2006.   Yuan XU, Chunlu JIANG and Qiang WANG\n"
				"  All rights reserved, see README for more information.     \n"
				"--------------------------------------------------------------------------\n"
				"  Version: "PACKAGE_VERSION"\n"
				"  Build Time: "__DATE__" -- "__TIME__"\n"
				"--------------------------------------------------------------------------\n"
	<<endl;
}

//-* main
int main(int argc, char* argv[])
{
	copyLeft();
	
	new CommServer;
	new Formation;//formation instance
	new Player; //Player instance
	new WorldModel; //WorldModel instance
	new Skill;
	new Logger; //logger instance

//----------------- set log level------------------------------
	//ADDLOG(1); //-* class Agent
	//ADDLOG(2); //-* seu parser

	GL_ADD_LEVEL("PlayMode");
	GL_ADD_LEVEL("test");
//------------------end set log level----------------------------

//----------- initlization ----------------------
    int ret = Init(argc, argv);

	
    if (ret > 0)
    {
        return ret;
    }

	// main loop
	Run();
}


/**
dOxygen tag	Rendering
http://www.stack.nl/~dimitri/doxygen/commands.html
*/

/***************************************/
//Doxygen 范例

//-函数说明-----------------------
/** 简要的函数说明文字 
 *  @param [in] param1 参数1说明
 *  @param [out] param2 参数2说明
 *  @return 返回值说明
 */
/** 打开文件 \n
 *  文件打开成功后，必须使用 ::CloseFile 函数关闭。
 *  @param[in] file_name 文件名字符串
 *  @param[in] file_mode 文件打开模式字符串，可以由以下几个模块组合而成：
 *  - r 读取
 *  - w 可写
 *  - a 添加
 *  - t 文本模式(不能与 b 联用)
 *  - b 二进制模式(不能与 t 联用)
 *  @return 返回文件编号
 *  - -1 表示打开文件失败
 
 *  @note 文件打开成功后，必须使用 ::CloseFile 函数关闭
 *  @par 示例:
 *  @code
    // 用文本只读方式打开文件
    int f = OpenFile("d:\\test.txt", "rt");
 *  @endcode
 
 *  @see ::ReadFile ::WriteFile ::CloseFile
 *  @deprecated 由于特殊的原因，这个函数可能会在将来的版本中取消。
 */
/****************************************/
