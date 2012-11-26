#include "acthandle.h"
#include <sstream>
#include <string.h>
#include "connection.h"
#include "worldmodel.h"
#include "timer.h"

extern Connection connection;
extern WorldModel wm;
Timer timer;

ActHandle::ActHandle()
{
	#ifdef NAO_MODEL
	HJControl[JID_HEAD_1].sName = "he1";
	HJControl[JID_HEAD_2].sName = "he2";
	
	HJControl[JID_LLEG_1].sName = "lle1";
	HJControl[JID_LLEG_2].sName = "lle2";
	HJControl[JID_LLEG_3].sName = "lle3";
	HJControl[JID_LLEG_4].sName = "lle4";
	HJControl[JID_LLEG_5].sName = "lle5";
	HJControl[JID_LLEG_6].sName = "lle6";
	HJControl[JID_RLEG_1].sName = "rle1";
	HJControl[JID_RLEG_2].sName = "rle2";
	HJControl[JID_RLEG_3].sName = "rle3";
	HJControl[JID_RLEG_4].sName = "rle4";
	HJControl[JID_RLEG_5].sName = "rle5";
	HJControl[JID_RLEG_6].sName = "rle6";
	HJControl[JID_LARM_1].sName = "lae1";
	HJControl[JID_LARM_2].sName = "lae2";
	HJControl[JID_LARM_3].sName = "lae3";
	HJControl[JID_LARM_4].sName = "lae4";
	HJControl[JID_RARM_1].sName = "rae1";
	HJControl[JID_RARM_2].sName = "rae2";
	HJControl[JID_RARM_3].sName = "rae3";
	HJControl[JID_RARM_4].sName = "rae4";
	
	#else
	
	HJControl[0].sName = "lle1";
	HJControl[1].sName = "rle1";
	HJControl[2].sName = "lle4";
	HJControl[3].sName = "rle4";
	HJControl[4].sName = "lae3";
	HJControl[5].sName = "rae3";
	HJControl[6].sName = "lae4";
	HJControl[7].sName = "rae4";
	
	UJControl[0].sName = "lle2_3";
	UJControl[1].sName = "rle2_3";
	UJControl[2].sName = "lle5_6";
	UJControl[3].sName = "rle5_6";
	UJControl[4].sName = "lae1_2";
	UJControl[5].sName = "rae1_2";

	#endif
	
}

ActHandle::~ActHandle()
{
}

void ActHandle::Beam(Vector vPos)
{
	stringstream ss("");
	ss<<"(beam "<<vPos.Vx<<" "<<vPos.Vy<<" "<<vPos.Vz<<")";
	connection.SendMsg(ss.str());
}


bool ActHandle::ActHandle::Beam(Vector vPos, int BeamNum, bool Clear)
{
	static int iBeamedNum = 0;
	if (Clear)
	{
		BeamNum = 0;
		return true;
	}

	if (iBeamedNum < BeamNum)
	{
		Beam(vPos);
		iBeamedNum++;
		if (iBeamedNum < BeamNum) return false;
	}

	iBeamedNum = 0;
	return true;
}


bool ActHandle::BeamAfterDelay(Vector vPos, int DelayTime, int BeamNum, bool Clear)
{
     static double dTime = 0;
     if (Clear)
     {
         dTime = 0;
         return true;
     }
     if (fabs(dTime) < 0.001)
     {
        dTime = wm.GetServerTime() + 0.01 * DelayTime;
     }

     if (wm.GetServerTime() < dTime) return false;

     if (!Beam(vPos, BeamNum)) return false;

     dTime = 0;
     return true;
}


bool ActHandle::AdjustHJ(int iID, double dNewAng, double dSpeed, double dAccurate)
{
	double dCurAng = wm.m_HJ[iID].fAngle;
	if (fabs(dCurAng - dNewAng) > dAccurate)
	{
		HJControl[iID].bCtrled = true;
		HJControl[iID].fAngle = dSpeed*(dNewAng - dCurAng);
		return false;
	}
	return true;
}

#ifndef NAO_MODEL
bool ActHandle::AdjustUJ_1(int iID, double dNewAng, double dSpeed, double dAccurate)
{
	double dCurAng = wm.m_UJ[iID].fAngle1;
	if (fabs(dCurAng - dNewAng) > dAccurate)
	{
		UJControl[iID].bCtrled = true;
		UJControl[iID].fAngle1 = dSpeed*(dNewAng - dCurAng);
		return false;
	}
	return true;
}

bool ActHandle::AdjustUJ_2(int iID, double dNewAng, double dSpeed, double dAccurate)
{
	double dCurAng = wm.m_UJ[iID].fAngle2;
	if (fabs(dCurAng - dNewAng) > dAccurate)
	{
		UJControl[iID].bCtrled = true;
		UJControl[iID].fAngle2 = dSpeed*(dNewAng - dCurAng);
		return false;
	}
	return true;
}
#endif

void ActHandle::ClearControl()
{
    int iUJNum = 0, iHJNum = 0;
     
	#ifdef NAO_MODEL
    iHJNum = 22;
    #else
    iHJNum = 8;
	iUJNum = 6;
	#endif
     
    int i = 0;
	for (; i < iHJNum; i++)
	{
		HJControl[i].fAngle = 0.0;
		HJControl[i].bCtrled = false;
	}
	
	#ifndef NAO_MODEL
	for (i = 0; i < iUJNum; i++)
	{
		UJControl[i].fAngle1 = 0.0;
		UJControl[i].fAngle2 = 0.0;
		UJControl[i].bCtrled = false;
	}
	#endif
}

string ActHandle::MakeCommand()
{
    int iUJNum = 0, iHJNum = 0;
     
	#ifdef NAO_MODEL
    iHJNum = 22;
    #else
    iHJNum = 8;
	iUJNum = 6;
	#endif

	stringstream ss("");
	int i = 0;
	for(; i < iHJNum; i++)
	{
            if (!HJControl[i].bCtrled)
            {
               if (HJControl[i].bChanged)
               {
                  ss<<"("<<HJControl[i].sName<<" 0)";
                  HJControl[i].bChanged = false;                       
               }
            }
            else
            {
                HJControl[i].bChanged = true;
                ss<<"("<<HJControl[i].sName<<" "<<HJControl[i].fAngle<<")";
            }
    }
    
    #ifndef NAO_MODEL
	for(i = 0; i < iUJNum; i++)
	{
            if (!UJControl[i].bCtrled)
            {
               if (UJControl[i].bChanged)
               {
                  ss<<"("<<UJControl[i].sName<<" 0 0)";
                  UJControl[i].bChanged = false;                       
               }
            }
            else
            {
                UJControl[i].bChanged = true;
                ss<<"("<<UJControl[i].sName<<" "<<UJControl[i].fAngle1<<" "<<UJControl[i].fAngle1<<")";
            }
    }
    #endif
    return ss.str();   
}


/*
bool ActHandle:: Squat()
{
     if(!timer.IsTimerRun())  timer.SetTimer();
     if(timer.GetTime()>0&& timer.GetTime()<100)
     {
	 AdjustHJ(JID_HEAD_1,0,0.07);
	 AdjustHJ(JID_HEAD_2,0,0.07);// �0�5�1�7�1�7�1�7�0�5�0�8�1�7�1�7�1�7�1�7�1�7

	AdjustHJ( JID_LARM_1,-80,0.04);      	AdjustHJ( JID_RARM_1,-80,0.04);
	AdjustHJ( JID_LARM_2,0,0.1);	   	AdjustHJ( JID_RARM_2,0,0.1);
	AdjustHJ( JID_LARM_3,-0,0.1);         AdjustHJ( JID_RARM_3,0,0.1);
	AdjustHJ( JID_LARM_4,-0,0.1);		AdjustHJ( JID_RARM_4,0,0.1);// �1�7�0�2�1�7�1�7�0�5�0�8�1�7�1�7�1�7�1�7�1�7

	AdjustHJ(JID_LLEG_1,0,0.1);            AdjustHJ(JID_RLEG_1,0,0.1);
	AdjustHJ(JID_LLEG_2,0,0.1);           AdjustHJ(JID_RLEG_2,0,0.1);
	AdjustHJ(JID_LLEG_3,35,0.04);            AdjustHJ(JID_RLEG_3,35,0.04);
	AdjustHJ(JID_LLEG_4,-70,0.04);		AdjustHJ(JID_RLEG_4,-70,0.04);
	AdjustHJ(JID_LLEG_5,50,0.04);		AdjustHJ(JID_RLEG_5,50,0.04);
	AdjustHJ(JID_LLEG_6,0,0.1);		AdjustHJ(JID_RLEG_6,0,0.1);//�1�7�0�7�1�7�1�7�0�5�0�8�1�7�1�7�1�7�1�7�1�7
     }
     if (timer.GetTime() < 100) return false;
     timer.ClearTimer();
     return true;
}
*/

 
bool ActHandle :: FallDownForTest(double speed,bool forward)
{
	if(!timer.IsTimerRun())  timer.SetTimer(-50);
	if(timer.GetTime()>0&& timer.GetTime()<100)
	{
		AdjustHJ(JID_HEAD_1,0,0.07);
		AdjustHJ(JID_HEAD_2,0,0.07);

		AdjustHJ( JID_LARM_1,-80,0.37);      	AdjustHJ( JID_RARM_1,-80,0.37);
		AdjustHJ( JID_LARM_2, 0,0.37);	   	AdjustHJ( JID_RARM_2,0,0.37);
		AdjustHJ( JID_LARM_3,-0,0.37);         AdjustHJ( JID_RARM_3,0,0.37);
		AdjustHJ( JID_LARM_4,-0,0.37);		AdjustHJ( JID_RARM_4,0,0.37);// �ֲ��ĽǶ�����



		AdjustHJ(JID_LLEG_1,0,0.1);            AdjustHJ(JID_RLEG_1,0,0.1);
		AdjustHJ(JID_LLEG_2,0,0.1);           AdjustHJ(JID_RLEG_2,0,0.1);
		AdjustHJ(JID_LLEG_3,0,0.04);            AdjustHJ(JID_RLEG_3,0,0.04);
		AdjustHJ(JID_LLEG_4,-0,0.04);		AdjustHJ(JID_RLEG_4,-0,0.04);
		AdjustHJ(JID_LLEG_6,0,0.04);		AdjustHJ(JID_RLEG_6,0,0.04);
		if(forward)
		{
			AdjustHJ(JID_LLEG_5,45,speed);		AdjustHJ(JID_RLEG_5,45,speed);
		}
		else
		{
			AdjustHJ(JID_LLEG_5,-30,speed);		AdjustHJ(JID_RLEG_5,-30,speed);
		}
	}
	if (timer.GetTime() < 150) return false;
	timer.ClearTimer();
	return true;
}

/*
bool ActHandle :: PrepareToGetUp()
{
	if(!timer.IsTimerRun())  timer.SetTimer();

	if(timer.GetTime()>0&& timer.GetTime()<60)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,0,0.1);// ͷ���ĽǶ�����

		AdjustHJ( JID_LARM_1,-0,0.1);      	AdjustHJ( JID_RARM_1,-0,0.1);
		AdjustHJ( JID_LARM_2,0,0.1);	 	AdjustHJ( JID_RARM_2,-0,0.1);
		AdjustHJ( JID_LARM_3,-0,0.1);              AdjustHJ( JID_RARM_3,0,0.1);
		AdjustHJ( JID_LARM_4,-0,0.1);		AdjustHJ( JID_RARM_4,0,0.1);// �ֲ��ĽǶ�����

		AdjustHJ(JID_LLEG_1,-0,0.2);               AdjustHJ(JID_RLEG_1,-0,0.2);
		AdjustHJ(JID_LLEG_2,0,0.2);                AdjustHJ(JID_RLEG_2,-0,0.2);
		AdjustHJ(JID_LLEG_3,0,0.2);                AdjustHJ(JID_RLEG_3,0,0.2);
		AdjustHJ(JID_LLEG_4,-0,0.2);		AdjustHJ(JID_RLEG_4,-0,0.2);
		AdjustHJ(JID_LLEG_5,-0,0.2);		AdjustHJ(JID_RLEG_5,-0,0.2);
		AdjustHJ(JID_LLEG_6,-0,0.2);		AdjustHJ(JID_RLEG_6,0,0.2);//�Ȳ��ĽǶ�����
	}
	if (timer.GetTime() < 60) return false;
	timer.ClearTimer();
	return true;
}
*/


bool ActHandle :: PrepareToGetUp()
{
	if(!timer.IsTimerRun())  timer.SetTimer();
	if(timer.GetTime()>0&& timer.GetTime()<70)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,0,0.1);// 头部的角度配置

		AdjustHJ( JID_LARM_1,-0,0.1);      	AdjustHJ( JID_RARM_1,-0,0.1);
		AdjustHJ( JID_LARM_2,0,0.1);	 	AdjustHJ( JID_RARM_2,-0,0.1);
		AdjustHJ( JID_LARM_3,-0,0.1);              AdjustHJ( JID_RARM_3,0,0.1);
		AdjustHJ( JID_LARM_4,-0,0.1);		AdjustHJ( JID_RARM_4,0,0.2);// 手部的角度配置

		AdjustHJ(JID_LLEG_1,-0,0.2);               AdjustHJ(JID_RLEG_1,-0,0.2);
		AdjustHJ(JID_LLEG_2,40,0.2);                AdjustHJ(JID_RLEG_2,-40,0.2);
		AdjustHJ(JID_LLEG_3,40,0.2);                AdjustHJ(JID_RLEG_3,40,0.2);
		AdjustHJ(JID_LLEG_4,-100,0.2);		AdjustHJ(JID_RLEG_4,-100,0.2);
		AdjustHJ(JID_LLEG_5,-0,0.2);		AdjustHJ(JID_RLEG_5,-0,0.2);
		AdjustHJ(JID_LLEG_6,-0,0.2);		AdjustHJ(JID_RLEG_6,0,0.2);//腿部的角度配置
	}
	if (timer.GetTime() < 70) return false;
	timer.ClearTimer();
	return true;
}


///maoyuxi 2009-12-11
bool ActHandle :: Climb_FaceDown()             ///2009-12-11
{
	if(!timer.IsTimerRun())  timer.SetTimer();
	if(timer.GetTime()>0&& timer.GetTime()<36)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,-30,0.1);


		AdjustHJ( JID_LARM_1,-50,0.6);      	AdjustHJ( JID_RARM_1,-50,0.6);
		AdjustHJ( JID_LARM_2,30,0.4);	 	AdjustHJ( JID_RARM_2,-30,0.4);
		AdjustHJ( JID_LARM_3,-90,0.1);           AdjustHJ( JID_RARM_3,90,0.1);
		AdjustHJ( JID_LARM_4,-75,0.4);		AdjustHJ( JID_RARM_4,75,0.4);


		AdjustHJ(JID_LLEG_1,-70,0.2);           AdjustHJ(JID_RLEG_1,-70,0.2);
		AdjustHJ(JID_LLEG_2,-0,0.2);            AdjustHJ(JID_RLEG_2,0,0.2);


		AdjustHJ(JID_LLEG_3,90,0.2);            AdjustHJ(JID_RLEG_3,90,0.2);
		AdjustHJ(JID_LLEG_4,-0,0.2);		AdjustHJ(JID_RLEG_4,-0,0.2);
		AdjustHJ(JID_LLEG_5,-0,0.2);		AdjustHJ(JID_RLEG_5,-0,0.2);

		AdjustHJ(JID_LLEG_6,-0,0.2);		AdjustHJ(JID_RLEG_6,0,0.2);
	}
	if(timer.GetTime()>36&& timer.GetTime()<72)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,30,0.1);

		AdjustHJ( JID_LARM_1,-50,0.6);      	AdjustHJ( JID_RARM_1,-50,0.6);
		AdjustHJ( JID_LARM_2,30,0.4);	 	AdjustHJ( JID_RARM_2,-30,0.4);
		AdjustHJ( JID_LARM_3,-90,0.1);           AdjustHJ( JID_RARM_3,90,0.1);
		AdjustHJ( JID_LARM_4,-75,0.4);		AdjustHJ( JID_RARM_4,75,0.4);


		AdjustHJ(JID_LLEG_1,-90,0.4);           AdjustHJ(JID_RLEG_1,-90,0.4);
		AdjustHJ(JID_LLEG_2,-100,0.4);          AdjustHJ(JID_RLEG_2,100,0.4);

		AdjustHJ(JID_LLEG_3,65,0.4);               AdjustHJ(JID_RLEG_3,65,0.4);
		AdjustHJ(JID_LLEG_4,-130,0.4);             AdjustHJ(JID_RLEG_4,-130,0.4);
		AdjustHJ(JID_LLEG_5,50,0.2);               AdjustHJ(JID_RLEG_5,50,0.2);

		AdjustHJ(JID_LLEG_6,-5,0.4);		AdjustHJ(JID_RLEG_6,5,0.4);
	} 
	if(timer.GetTime()>72&&timer.GetTime()<100)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,0,0.1);

		AdjustHJ( JID_LARM_1,-34,0.1);      	AdjustHJ( JID_RARM_1,-34,0.1);
		AdjustHJ( JID_LARM_2,0,0.1);	 	AdjustHJ( JID_RARM_2,-0,0.1);
		AdjustHJ( JID_LARM_3,-0,0.1);              AdjustHJ( JID_RARM_3,0,0.1);
		AdjustHJ( JID_LARM_4,-0,0.1);		AdjustHJ( JID_RARM_4,0,0.1);

		AdjustHJ(JID_LLEG_1,-90,0.1);               AdjustHJ(JID_RLEG_1,-90,0.1);
		AdjustHJ(JID_LLEG_2,0,0.1);                AdjustHJ(JID_RLEG_2,-0,0.1);


		AdjustHJ(JID_LLEG_3,100,0.1);                AdjustHJ(JID_RLEG_3,100,0.1);
		AdjustHJ(JID_LLEG_4,-130,0.1);		AdjustHJ(JID_RLEG_4,-130,0.1);
		AdjustHJ(JID_LLEG_5,5,0.15);		AdjustHJ(JID_RLEG_5,5,0.15);

		AdjustHJ(JID_LLEG_6,-20,0.15);		AdjustHJ(JID_RLEG_6,20,0.15);
	}
 
	if(timer.GetTime()>100&&timer.GetTime()<136)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,0,0.1);

		AdjustHJ( JID_LARM_1,-80,0.1);      	AdjustHJ( JID_RARM_1,-80,0.1);
		AdjustHJ( JID_LARM_2,0,0.1);	 	AdjustHJ( JID_RARM_2,-0,0.1);
		AdjustHJ( JID_LARM_3,-90,0.1);              AdjustHJ( JID_RARM_3,90,0.1);
		AdjustHJ( JID_LARM_4,-95,0.1);		AdjustHJ( JID_RARM_4,95,0.1);

		AdjustHJ(JID_LLEG_1,-0,0.1);               AdjustHJ(JID_RLEG_1,-0,0.1);
		AdjustHJ(JID_LLEG_2,0,0.2);                AdjustHJ(JID_RLEG_2,-0,0.2);
		AdjustHJ(JID_LLEG_3,40.9,0.2);                AdjustHJ(JID_RLEG_3,40.9,0.2);
		AdjustHJ(JID_LLEG_4,-65.9,0.15);		AdjustHJ(JID_RLEG_4,-65.9,0.2);
		AdjustHJ(JID_LLEG_5,35,0.15);		AdjustHJ(JID_RLEG_5,35,0.15);
		AdjustHJ(JID_LLEG_6,-0,0.22);		AdjustHJ(JID_RLEG_6,0,0.22);  
	}
	if (timer.GetTime() <136) return false;
	timer.ClearTimer();
	 
	return true;
}


bool ActHandle :: Climb_FaceUp()              ///binzhenhua1009 周期105
{
	
	if(!timer.IsTimerRun())  timer.SetTimer(); 
	if(timer.GetTime()>0&& timer.GetTime()<50)//仿东南的初始动作
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,0,0.1);


		AdjustHJ( JID_LARM_1,-90,0.4);		 AdjustHJ( JID_RARM_1,-90,0.4);
		AdjustHJ( JID_LARM_2,30,0.4);		 AdjustHJ( JID_RARM_2,-30,0.4);
		AdjustHJ( JID_LARM_3,-90,0.4);		 AdjustHJ( JID_RARM_3,90,0.4);
		AdjustHJ( JID_LARM_4,-0,0.4);		AdjustHJ( JID_RARM_4,0,0.4);


		AdjustHJ(JID_LLEG_1,0,0.4);			 AdjustHJ(JID_RLEG_1,0,0.4);
		AdjustHJ(JID_LLEG_2,0,0.4);			 AdjustHJ(JID_RLEG_2,-0,0.4);


		AdjustHJ(JID_LLEG_3,0,0.1);			AdjustHJ(JID_RLEG_3,0,0.1);
		AdjustHJ(JID_LLEG_4,-0,0.4);		AdjustHJ(JID_RLEG_4,-0,0.4);
		AdjustHJ(JID_LLEG_5,0,0.1);			AdjustHJ(JID_RLEG_5,0,0.1);

		AdjustHJ(JID_LLEG_6,-0,0.4);			AdjustHJ(JID_RLEG_6,0,0.4);
	} 
	if(timer.GetTime()>50&& timer.GetTime()<85)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,0,0.1);



		AdjustHJ( JID_LARM_1,30,0.4);			AdjustHJ( JID_RARM_1,30,0.4);
		AdjustHJ( JID_LARM_2,0,0.4);			AdjustHJ( JID_RARM_2,-0,0.4);
		AdjustHJ( JID_LARM_3,-90,0.4);		 AdjustHJ( JID_RARM_3,90,0.4);
		AdjustHJ( JID_LARM_4,-0,0.4);		AdjustHJ( JID_RARM_4,0,0.4);


		AdjustHJ(JID_LLEG_1,0,0.4);			AdjustHJ(JID_RLEG_1,0,0.4);
		AdjustHJ(JID_LLEG_2,0,0.4);			AdjustHJ(JID_RLEG_2,-0,0.4);

		AdjustHJ(JID_LLEG_3,100,0.1);		AdjustHJ(JID_RLEG_3,100,0.1);
		AdjustHJ(JID_LLEG_4,-0,0.4);		AdjustHJ(JID_RLEG_4,-0,0.4);
		AdjustHJ(JID_LLEG_5,0,0.1);		 	AdjustHJ(JID_RLEG_5,0,0.1);

		AdjustHJ(JID_LLEG_6,-0,0.4);			AdjustHJ(JID_RLEG_6,0,0.4);
	} 
	if(timer.GetTime()>85&&timer.GetTime()<115)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,0,0.1);


		AdjustHJ( JID_LARM_1,35,0.25);      	AdjustHJ( JID_RARM_1,35,0.25);
		AdjustHJ( JID_LARM_2,0,0.15);	 	AdjustHJ( JID_RARM_2,-0,0.15);
		AdjustHJ( JID_LARM_3,-0,0.1);              AdjustHJ( JID_RARM_3,0,0.1);
		AdjustHJ( JID_LARM_4,-0,0.1);	        AdjustHJ( JID_RARM_4,0,0.1);


		AdjustHJ(JID_LLEG_1,-50,0.2);               AdjustHJ(JID_RLEG_1,-50,0.2);
		AdjustHJ(JID_LLEG_2,-30,0.2);                AdjustHJ(JID_RLEG_2,30,0.2);

		AdjustHJ(JID_LLEG_3,100,0.2);                AdjustHJ(JID_RLEG_3,100,0.2);
		AdjustHJ(JID_LLEG_4,-0,0.2);		AdjustHJ(JID_RLEG_4,-0,0.2);
		AdjustHJ(JID_LLEG_5,-0,0.2);		AdjustHJ(JID_RLEG_5,-0,0.2);

		AdjustHJ(JID_LLEG_6,-0,0.2);		AdjustHJ(JID_RLEG_6,0,0.2);
	}
	if(timer.GetTime()>115&&timer.GetTime()<145)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,0,0.1);

		AdjustHJ( JID_LARM_1,-24,0.1);      	AdjustHJ( JID_RARM_1,-24,0.1);
		AdjustHJ( JID_LARM_2,0,0.1);	 	AdjustHJ( JID_RARM_2,-0,0.1);
		AdjustHJ( JID_LARM_3,-0,0.1);              AdjustHJ( JID_RARM_3,0,0.1);
		AdjustHJ( JID_LARM_4,-0,0.1);		AdjustHJ( JID_RARM_4,0,0.1);

		AdjustHJ(JID_LLEG_1,-90,0.1);               AdjustHJ(JID_RLEG_1,-90,0.1);
		AdjustHJ(JID_LLEG_2,50,0.1);                AdjustHJ(JID_RLEG_2,-50,0.1);

		AdjustHJ(JID_LLEG_3,100,0.1);                AdjustHJ(JID_RLEG_3,100,0.1);
		AdjustHJ(JID_LLEG_4,-130,0.1);		AdjustHJ(JID_RLEG_4,-130,0.1);
		AdjustHJ(JID_LLEG_5,-45,0.15);		AdjustHJ(JID_RLEG_5,-45,0.15);

		AdjustHJ(JID_LLEG_6,-0,0.15);		AdjustHJ(JID_RLEG_6,0,0.15);
	}
	if(timer.GetTime()>145&&timer.GetTime()<180)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,0,0.1);


		AdjustHJ( JID_LARM_1,-34,0.1);      	AdjustHJ( JID_RARM_1,-34,0.1);
		AdjustHJ( JID_LARM_2,0,0.1);	 	AdjustHJ( JID_RARM_2,-0,0.1);
		AdjustHJ( JID_LARM_3,-0,0.1);              AdjustHJ( JID_RARM_3,0,0.1);
		AdjustHJ( JID_LARM_4,-0,0.1);		AdjustHJ( JID_RARM_4,0,0.1);


		AdjustHJ(JID_LLEG_1,-90,0.1);               AdjustHJ(JID_RLEG_1,-90,0.1);
		AdjustHJ(JID_LLEG_2,0,0.1);                AdjustHJ(JID_RLEG_2,-0,0.1);

		AdjustHJ(JID_LLEG_3,100,0.1);                AdjustHJ(JID_RLEG_3,100,0.1);
		AdjustHJ(JID_LLEG_4,-130,0.1);		AdjustHJ(JID_RLEG_4,-130,0.1);
		AdjustHJ(JID_LLEG_5,5,0.15);		AdjustHJ(JID_RLEG_5,5,0.15);


		AdjustHJ(JID_LLEG_6,-20,0.15);		AdjustHJ(JID_RLEG_6,20,0.15);
	}
	if(timer.GetTime()>180&&timer.GetTime()<225)
	{
		AdjustHJ(JID_HEAD_1,0,0.05);
		AdjustHJ(JID_HEAD_2,0,0.1);


		AdjustHJ( JID_LARM_1,-80,0.06);      	AdjustHJ( JID_RARM_1,-80,0.06);
		AdjustHJ( JID_LARM_2,0,0.06);	 	AdjustHJ( JID_RARM_2,-0,0.06);
		AdjustHJ( JID_LARM_3,-90,0.06);              AdjustHJ( JID_RARM_3,90,0.06);
		AdjustHJ( JID_LARM_4,-95,0.06);		AdjustHJ( JID_RARM_4,95,0.06);


		AdjustHJ(JID_LLEG_1,0,0.06);               AdjustHJ(JID_RLEG_1,0,0.06);
		AdjustHJ(JID_LLEG_2,0,0.06);                AdjustHJ(JID_RLEG_2,-0,0.06);


		AdjustHJ(JID_LLEG_3,40.9,0.1);                AdjustHJ(JID_RLEG_3,40.9,0.1);
		AdjustHJ(JID_LLEG_4,-65.9,0.1);		AdjustHJ(JID_RLEG_4,-65.9,0.1);
		AdjustHJ(JID_LLEG_5,35,0.08);		AdjustHJ(JID_RLEG_5,35,0.08);

		AdjustHJ(JID_LLEG_6,0,0.065);		AdjustHJ(JID_RLEG_6,0,0.065);  
	}
	if (timer.GetTime() <225) return false;
	timer.ClearTimer();
	 
	return true;
}


/*
bool ActHandle:: Squat()
{
     if(!timer.IsTimerRun())  timer.SetTimer();
     if(timer.GetTime()>0&& timer.GetTime()<100)
     {
         AdjustHJ(JID_LLEG_3,30,0.07);
         AdjustHJ(JID_RLEG_3,30,0.07);
         AdjustHJ(JID_LLEG_4,-60,0.07);
         AdjustHJ(JID_RLEG_4,-60,0.07);
         AdjustHJ(JID_LLEG_5,32,0.07);
         AdjustHJ(JID_RLEG_5,32,0.07);
         //AdjustHJ(JID_LARM_1,-80,0.045);
         //AdjustHJ(JID_RARM_1,-80,0.045);
     }
     if (timer.GetTime() < 100) return false;
     timer.ClearTimer();
     return true;
}
*/


bool ActHandle:: Squat()
{
     if(!timer.IsTimerRun())  timer.SetTimer();

     if(timer.GetTime()>0&& timer.GetTime()<30)
     {
	 AdjustHJ(JID_HEAD_1,0,0.07);
	 AdjustHJ(JID_HEAD_2,0,0.07);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-125,0.1);      	AdjustHJ( JID_RARM_1,-125,0.1);
	AdjustHJ( JID_LARM_2,0,0.1);	   	AdjustHJ( JID_RARM_2,0,0.1);
	AdjustHJ( JID_LARM_3,-90,0.1);         AdjustHJ( JID_RARM_3,90,0.1);
	AdjustHJ( JID_LARM_4,-45,0.1);		AdjustHJ( JID_RARM_4,45,0.1);// 手部的角度配置
	AdjustHJ(JID_LLEG_1,0,0.1);            AdjustHJ(JID_RLEG_1,0,0.1);
	AdjustHJ(JID_LLEG_2,0,0.1);           AdjustHJ(JID_RLEG_2,0,0.1);

	AdjustHJ(JID_LLEG_3,30,0.1);            AdjustHJ(JID_RLEG_3,30,0.1);
	AdjustHJ(JID_LLEG_4,-70,0.1);		AdjustHJ(JID_RLEG_4,-70,0.1);
	AdjustHJ(JID_LLEG_5,40,0.1);		AdjustHJ(JID_RLEG_5,40,0.1);

	AdjustHJ(JID_LLEG_6,0,0.1);		AdjustHJ(JID_RLEG_6,0,0.1);//腿部的角度配置
     }
     if (timer.GetTime() < 30) return false;
	cout<<"Squat over Squat over Squat over Squat over Squat over Squat over "<<endl;
     timer.ClearTimer();
     return true;
}


/*
bool ActHandle::TurnRight()
{
	if(!timer.IsTimerRun()) timer.SetTimer();

	double speed = 0.33;

	if(timer.GetTime() < 3.5)
	{
		//DoAction(0,0,0,0,0,0,0,0,
		//	5.00,0.00,40.00,-80.00,42.00,0.00,
		//	5.00,0.00,30.00,-60.00,32.00,0.00,speed);
		AdjustHJ( JID_LLEG_3, 37, speed);
		AdjustHJ( JID_LLEG_4, -80,speed);
		AdjustHJ( JID_LLEG_5, 42, speed);

		AdjustHJ(JID_LLEG_1, 5, speed);
	}

	if(timer.GetTime() > 3.5 && timer.GetTime() < 7)
	{

		//DoAction(0,0,0,0,0,0,0,0,
		//	5.00,0.00,30.00,-60.00,32.00,0.00,
		//	5.00,0.00,30.00,-60.00,32.00,0.00,speed);
		AdjustHJ( JID_LLEG_3, 30, speed);
		AdjustHJ( JID_LLEG_4, -60,speed );
		AdjustHJ( JID_LLEG_5, 32, speed);

		AdjustHJ(JID_RLEG_1, 5, speed);
	}

	if(timer.GetTime() > 7 && timer.GetTime() < 10.5)
	{
		//DoAction(0,0,0,0,0,0,0,0,
		//	-5.00,0.00,30.00,-60.00,32.00,0.00,
		//	-5.00,0.00,40.00,-80.00,42.00,0.00,speed);
		AdjustHJ( JID_RLEG_3, 37, speed);
		AdjustHJ( JID_RLEG_4, -80,speed);
		AdjustHJ( JID_RLEG_5, 42, speed);

		AdjustHJ(JID_RLEG_1, -5, speed);
	}

	if(timer.GetTime() > 10.5 && timer.GetTime() < 14)
	{

		//DoAction(0,0,0,0,0,0,0,0,
		//	-5.00,0.00,30.00,-60.00,32.00,0.00,
		//	-5.00,0.00,30.00,-60.00,32.90,0.00,speed);
		AdjustHJ( JID_RLEG_3, 30, speed);
		AdjustHJ( JID_RLEG_4, -60,speed );
		AdjustHJ( JID_RLEG_5, 32, speed);

		AdjustHJ(JID_LLEG_1, -5, speed);
	}

	if(timer.GetTime() < 14) return false;
	timer.ClearTimer();
	return true;
}


bool ActHandle::TurnLeft()
{
	if(!timer.IsTimerRun()) timer.SetTimer();

	double speed = 0.33;

	if(timer.GetTime() < 3.5)
	{
		//DoAction(0,0,0,0,0,0,0,0,
		//	5.00,0.00,40.00,-80.00,42.00,0.00,
		//	5.00,0.00,30.00,-60.00,32.00,0.00,speed);
		AdjustHJ( JID_LLEG_3, 37, speed);
		AdjustHJ( JID_LLEG_4, -80,speed);
		AdjustHJ( JID_LLEG_5, 42, speed);

		AdjustHJ(JID_LLEG_1, -5, speed);
	}

	if(timer.GetTime() > 3.5 && timer.GetTime() < 7)
	{

		//DoAction(0,0,0,0,0,0,0,0,
		//	5.00,0.00,30.00,-60.00,32.00,0.00,
		//	5.00,0.00,30.00,-60.00,32.00,0.00,speed);
		AdjustHJ( JID_LLEG_3, 30, speed);
		AdjustHJ( JID_LLEG_4, -60,speed );
		AdjustHJ( JID_LLEG_5, 32, speed);

		AdjustHJ(JID_RLEG_1, -5, speed);
	}

	if(timer.GetTime() > 7 && timer.GetTime() < 10.5)
	{
		//DoAction(0,0,0,0,0,0,0,0,
		//	-5.00,0.00,30.00,-60.00,32.00,0.00,
		//	-5.00,0.00,40.00,-80.00,42.00,0.00,speed);
		AdjustHJ( JID_RLEG_3, 37, speed);
		AdjustHJ( JID_RLEG_4, -80,speed);
		AdjustHJ( JID_RLEG_5, 42, speed);

		AdjustHJ(JID_RLEG_1, 5, speed);
	}

	if(timer.GetTime() > 10.5 && timer.GetTime() < 14)
	{

		//DoAction(0,0,0,0,0,0,0,0,
		//	-5.00,0.00,30.00,-60.00,32.00,0.00,
		//	-5.00,0.00,30.00,-60.00,32.90,0.00,speed);
		AdjustHJ( JID_RLEG_3, 30, speed);
		AdjustHJ( JID_RLEG_4, -60,speed );
		AdjustHJ( JID_RLEG_5, 32, speed);

		AdjustHJ(JID_LLEG_1, 5, speed);
	}

	if(timer.GetTime() < 14) return false;
	timer.ClearTimer();
	return true;
}


*/

bool ActHandle::TurnLeft(int iType)
{
	if(!timer.IsTimerRun()) timer.SetTimer();

	double speed = 0.3;
	
	AdjustHJ(JID_HEAD_1,0,0.37);
	AdjustHJ(JID_HEAD_2,0,0.37);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-125,0.37);      	AdjustHJ( JID_RARM_1,-125,0.37);
	AdjustHJ( JID_LARM_2, 0,0.37);	   	AdjustHJ( JID_RARM_2,0,0.37);
	AdjustHJ( JID_LARM_3,-90,0.37);         AdjustHJ( JID_RARM_3,90,0.37);
	AdjustHJ( JID_LARM_4,-75,0.37);		AdjustHJ( JID_RARM_4,75,0.37);// 手部的角度配置

	
	AdjustHJ(JID_LLEG_2, 0,  speed);     AdjustHJ(JID_RLEG_2,0,speed);
	
	AdjustHJ(JID_LLEG_6, 0, speed);  AdjustHJ(JID_RLEG_6, 0,speed);//腿部的角度配置
	//AdjustHJ(JID_LLEG_1, 0, speed);   AdjustHJ(JID_RLEG_1, 0,speed);


	if(timer.GetTime() >= 0 && timer.GetTime() < 3)
	{
		AdjustHJ( JID_LLEG_3, 40, speed);
		AdjustHJ( JID_LLEG_4, -100,speed);
		AdjustHJ( JID_LLEG_5, 58, speed);

		if (iType == 1) AdjustHJ(JID_LLEG_1, -7.5, speed);
		else AdjustHJ(JID_LLEG_1, -5, speed);
	}

	if(timer.GetTime() >=3 && timer.GetTime() < 6)
	{

		AdjustHJ( JID_LLEG_3, 30, speed);
		AdjustHJ( JID_LLEG_4, -70,speed );
		AdjustHJ( JID_LLEG_5, 42, speed);

		if (iType == 1) AdjustHJ(JID_RLEG_1, -7.5, speed);
		else AdjustHJ(JID_RLEG_1, -5, speed);
	}

	if(timer.GetTime() >=6 && timer.GetTime() < 9)
	{
		AdjustHJ( JID_RLEG_3, 40, speed);
		AdjustHJ( JID_RLEG_4, -100,speed);
		AdjustHJ( JID_RLEG_5, 58, speed);

		if (iType == 1) AdjustHJ(JID_RLEG_1, 9.5, speed);
		else  AdjustHJ(JID_RLEG_1, 5, speed);

	}

	if(timer.GetTime() >=9 && timer.GetTime() < 12)
	{

		AdjustHJ( JID_RLEG_3, 30, speed);
		AdjustHJ( JID_RLEG_4, -70,speed );
		AdjustHJ( JID_RLEG_5, 42, speed);

		if (iType == 1) AdjustHJ(JID_LLEG_1, 9.5, speed);
		else  AdjustHJ(JID_LLEG_1, 5, speed);
	}

	if(timer.GetTime() < 12) return false;
	timer.ClearTimer();
cout<<"BodyAng   "<<wm.m_dBodyAng<<endl;
	return true;
}


bool ActHandle::TurnRight(int iType)
{
	if(!timer.IsTimerRun()) timer.SetTimer();

	double speed = 0.33;
	
	AdjustHJ(JID_HEAD_1,0,0.37);
	AdjustHJ(JID_HEAD_2,0,0.37);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-125,0.37);      	AdjustHJ( JID_RARM_1,-125,0.37);
	AdjustHJ( JID_LARM_2, 0,0.37);	   	AdjustHJ( JID_RARM_2,0,0.37);
	AdjustHJ( JID_LARM_3,-90,0.37);         AdjustHJ( JID_RARM_3,90,0.37);
	AdjustHJ( JID_LARM_4,-75,0.37);		AdjustHJ( JID_RARM_4,75,0.37);// 手部的角度配置

	
	AdjustHJ(JID_LLEG_2, 0,  speed);     AdjustHJ(JID_RLEG_2,0,speed);
	
	AdjustHJ(JID_LLEG_6, 0, speed);  AdjustHJ(JID_RLEG_6, 0,speed);//腿部的角度配置
	//AdjustHJ(JID_LLEG_1, 0, speed);   AdjustHJ(JID_RLEG_1, 0,speed);


	if(timer.GetTime() >= 0 && timer.GetTime() < 3)
	{
		AdjustHJ( JID_RLEG_3, 40, speed);
		AdjustHJ( JID_RLEG_4, -100,speed);
		AdjustHJ( JID_RLEG_5, 55, speed);

		if (iType == 1) AdjustHJ(JID_RLEG_1, -7.5, speed);
		else AdjustHJ(JID_RLEG_1, -5, speed);
	}

	if(timer.GetTime() >=3 && timer.GetTime() < 6)
	{

		AdjustHJ( JID_RLEG_3, 30, speed);
		AdjustHJ( JID_RLEG_4, -70,speed );
		AdjustHJ( JID_RLEG_5, 42, speed);
		if (iType == 1) AdjustHJ(JID_LLEG_1, -7.5, speed);
		else AdjustHJ(JID_LLEG_1, -5, speed);
	}

	if(timer.GetTime() >=6 && timer.GetTime() < 9)
	{
		AdjustHJ( JID_LLEG_3, 40, speed);
		AdjustHJ( JID_LLEG_4, -100,speed);
		AdjustHJ( JID_LLEG_5, 55, speed);
		if (iType == 1) AdjustHJ(JID_LLEG_1, 8.5, speed);
		else AdjustHJ(JID_LLEG_1, 5, speed);
	}

	if(timer.GetTime() >=9 && timer.GetTime() < 12)
	{

		AdjustHJ( JID_LLEG_3, 30, speed);
		AdjustHJ( JID_LLEG_4, -70,speed );
		AdjustHJ( JID_LLEG_5, 42, speed);
		if (iType == 1) AdjustHJ(JID_RLEG_1, 8.5, speed);
		else AdjustHJ(JID_RLEG_1, 5, speed);
	}

	if(timer.GetTime() < 12) return false;
	timer.ClearTimer();
cout<<"BodyAng   "<<wm.m_dBodyAng<<endl;
	return true;
}


bool ActHandle :: TestAct()
{
	if(!timer.IsTimerRun())  timer.SetTimer(); 
	if(timer.GetTime()>0&& timer.GetTime()<60)
	{
		AdjustHJ(JID_LLEG_1,-40,0.02);

	}

	if(timer.GetTime()>60&& timer.GetTime()<100)
	{
		//AdjustHJ(JID_LLEG_3,50,0.02);
		AdjustHJ(JID_LLEG_2,-10,0.02);

	}

	if(timer.GetTime()>100&& timer.GetTime()<150)
	{
		AdjustHJ(JID_LLEG_1,30,0.02);

	}

	if(timer.GetTime()>150&& timer.GetTime()<200)
	{
		AdjustHJ(JID_LLEG_5,70,0.02);

	}


	if (timer.GetTime() < 150) return false;
	timer.ClearTimer();
	return true;
}


bool ActHandle::Walk(int iWalkType, bool bClear)
{
//	cout<<"I am Walk!!!!!!!"<<endl;
	static double speedL = 10;
	static double speedR = 10;
	if (bClear)
	{
		speedL = 10;
		speedR = 10;
		return true;
	}

	if(!timer.IsTimerRun())  timer.SetTimer();

	AdjustHJ(JID_HEAD_1,0,0.37);
	AdjustHJ(JID_HEAD_2,0,0.37);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-125,0.37);      	AdjustHJ( JID_RARM_1,-125,0.37);
	AdjustHJ( JID_LARM_2, 0,0.37);	   	AdjustHJ( JID_RARM_2,0,0.37);
	AdjustHJ( JID_LARM_3,-90,0.37);         AdjustHJ( JID_RARM_3,90,0.37);
	AdjustHJ( JID_LARM_4,-75,0.37);		AdjustHJ( JID_RARM_4,75,0.37);// 手部的角度配置


	AdjustHJ(JID_LLEG_2, 0, 0.005* speedL);     AdjustHJ(JID_RLEG_2,0,0.005* speedR);
	
	AdjustHJ(JID_LLEG_6, 0,   0.005* speedL);  AdjustHJ(JID_RLEG_6, 0,0.005* speedR);//腿部的角度配置
	AdjustHJ(JID_LLEG_1, 0,  0.005 * speedL );   AdjustHJ(JID_RLEG_1, 0,0.005* speedR);

	if (iWalkType > 0)
	{
		AdjustHJ(JID_LLEG_6, 2.8,   0.005* speedL);  AdjustHJ(JID_RLEG_6, 2.8,0.005* speedR);//腿部的角度配置
	}
	else
	if (iWalkType < 0)
	{
		AdjustHJ(JID_LLEG_6, -2.3,   0.005* speedL);  AdjustHJ(JID_RLEG_6, -2.3,0.005* speedR);//腿部的角度配置
	}


	if(timer.GetTime()>=0 && timer.GetTime()<3)
	{
		
	AdjustHJ(JID_LLEG_3, 30,  0.01* speedL );    AdjustHJ(JID_RLEG_3, 35,0.01* speedR);
	AdjustHJ(JID_LLEG_4, -90, 0.01* speedL);     AdjustHJ(JID_RLEG_4,-65,0.01* speedR);
	AdjustHJ(JID_LLEG_5, 55 ,0.01* speedL);      AdjustHJ(JID_RLEG_5, 38,0.01* speedR);
	
	
	}

	if(timer.GetTime()>=3&& timer.GetTime()<6)
	{
	
	AdjustHJ(JID_LLEG_3, 50,0.01* speedL);        AdjustHJ(JID_RLEG_3,26,0.01* speedR);
	AdjustHJ(JID_LLEG_4, -70,0.01* speedL);       AdjustHJ(JID_RLEG_4, -70,0.01* speedR);
	AdjustHJ(JID_LLEG_5, 35,0.01* speedL);        AdjustHJ(JID_RLEG_5,  47,0.01* speedR);
	
	}

	if(timer.GetTime()>=6&& timer.GetTime()<9)
	{
	
	AdjustHJ(JID_LLEG_3, 35,0.01* speedL);     AdjustHJ(JID_RLEG_3,30,0.01* speedR);
	AdjustHJ(JID_LLEG_4, -65,0.01* speedL);	    AdjustHJ(JID_RLEG_4,-90,0.01* speedR);
	AdjustHJ(JID_LLEG_5, 38,0.01* speedL);	    AdjustHJ(JID_RLEG_5, 55,0.01* speedR);
	
	}

	if(timer.GetTime()>=9&& timer.GetTime()<12)
	{
		

	AdjustHJ(JID_LLEG_3, 26,0.01* speedL);   AdjustHJ(JID_RLEG_3,50,0.01* speedR);
	AdjustHJ(JID_LLEG_4, -70,0.01* speedL);  AdjustHJ(JID_RLEG_4,-70,0.01* speedR);
	AdjustHJ(JID_LLEG_5, 47,0.01* speedL);   AdjustHJ(JID_RLEG_5,35,0.01* speedR);
	
	}

	if (iWalkType != 10)
	{
		if (timer.GetTime() >=12)
		{
			if(speedL <30)
				speedL = speedL +10;
			//else speedL = 40;
			if(speedR < 30)
				speedR = speedR +10;
			//else speedR = 40;
			timer.ClearTimer();
			return true;
		}
		else return false;
	}

	if (iWalkType == 10)
	{
		if (timer.GetTime() >=12)
		{
			if(speedL > 10)
				speedL = speedL -10;
			//else speedL = 40;
			if(speedR > 10)
				speedR = speedR -10;
			//else speedR = 40;
			timer.ClearTimer();
			if(speedL == 10 && speedR ==10 )
			{
				return true;
			}
			else return false;
		}
		else return false;
	}
}


bool ActHandle::WalkBack(double & speed)//这个版本的直线性很好 
{
	if(!timer.IsTimerRun())  timer.SetTimer();

	AdjustHJ(JID_HEAD_1,0,0.37);
	AdjustHJ(JID_HEAD_2,0,0.37);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-105,0.37);      	AdjustHJ( JID_RARM_1,-105,0.37);
	AdjustHJ( JID_LARM_2, 0,0.37);	   	AdjustHJ( JID_RARM_2,0,0.37);
	AdjustHJ( JID_LARM_3,-90,0.37);         AdjustHJ( JID_RARM_3,90,0.37);
	AdjustHJ( JID_LARM_4,-45,0.37);		AdjustHJ( JID_RARM_4,45,0.37);// 手部的角度配置
	
	//AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	AdjustHJ(JID_LLEG_2, 1.22,  0.5* speed );    AdjustHJ(JID_RLEG_2,1.22,0.5* speed);
	AdjustHJ(JID_LLEG_6,2,   0.5* speed);	   AdjustHJ(JID_RLEG_6,2,0.5* speed);//腿部的角度配置



	if(timer.GetTime()>=0 && timer.GetTime()<3)
	{
	AdjustHJ(JID_LLEG_3, 28.5, 0.95* speed);     AdjustHJ(JID_RLEG_3,0,0.95* speed);
	AdjustHJ(JID_LLEG_4, -85, 0.95* speed);    AdjustHJ(JID_RLEG_4,-58,0.95* speed);
	AdjustHJ(JID_LLEG_5, 53, 0.95* speed);     AdjustHJ(JID_RLEG_5,43,0.95* speed);
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	}

	if(timer.GetTime()>=3&& timer.GetTime()<6)
	{
	AdjustHJ(JID_LLEG_3, 0,0.95* speed);      AdjustHJ(JID_RLEG_3,23,0.95* speed);
	AdjustHJ(JID_LLEG_4, -75,0.95* speed);     AdjustHJ(JID_RLEG_4,-60,0.95* speed);
	AdjustHJ(JID_LLEG_5, 63,0.95* speed);      AdjustHJ(JID_RLEG_5,35,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,-0,0.5* speed);
	}

	if(timer.GetTime()>=6&& timer.GetTime()<9)
	{
	
	AdjustHJ(JID_LLEG_3, 0,0.95* speed);       AdjustHJ(JID_RLEG_3,28.5,0.95* speed);
	AdjustHJ(JID_LLEG_4, -58,0.95* speed);	    AdjustHJ(JID_RLEG_4,-85,0.95* speed);
	AdjustHJ(JID_LLEG_5, 43,0.95* speed);	    AdjustHJ(JID_RLEG_5, 53,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,-0,0.5* speed);
	}

	if(timer.GetTime()>=9&& timer.GetTime()<12)
	{
	AdjustHJ(JID_LLEG_3, 23,0.95* speed);   AdjustHJ(JID_RLEG_3,0,0.95* speed);
	AdjustHJ(JID_LLEG_4, -60,0.95* speed);  AdjustHJ(JID_RLEG_4,-75,0.95* speed);
	AdjustHJ(JID_LLEG_5, 35,0.95* speed);   AdjustHJ(JID_RLEG_5,63,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	
	}

   	if (timer.GetTime() >=12)
	{
		if(speed <0.3)
			speed = speed +0.1;
		else speed = 0.3;
		timer.ClearTimer();
		return true;
	} 
	else return false;
	
} 

bool ActHandle::WalkBackRight(double & speed)//这个是倒折走且右柺的 
{
	if(!timer.IsTimerRun())  timer.SetTimer();
//	static double speed = 0.1;
cout<<"Walk------------1-------1------1--------1"<<endl;
	
	AdjustHJ(JID_HEAD_1,0,0.37);
	AdjustHJ(JID_HEAD_2,0,0.37);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-105,0.37);      	AdjustHJ( JID_RARM_1,-105,0.37);
	AdjustHJ( JID_LARM_2, 0,0.37);	   	AdjustHJ( JID_RARM_2,0,0.37);
	AdjustHJ( JID_LARM_3,-90,0.37);         AdjustHJ( JID_RARM_3,90,0.37);
	AdjustHJ( JID_LARM_4,-45,0.37);		AdjustHJ( JID_RARM_4,45,0.37);// 手部的角度配置
	
	//AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	AdjustHJ(JID_LLEG_2, -2.5,  0.5* speed );    AdjustHJ(JID_RLEG_2,-2.5,0.5* speed);
	AdjustHJ(JID_LLEG_6,2,   0.5* speed);	   AdjustHJ(JID_RLEG_6,2,0.5* speed);//腿部的角度配置



	if(timer.GetTime()>=0 && timer.GetTime()<3)
	{
	AdjustHJ(JID_LLEG_3, 28.5, 0.95* speed);     AdjustHJ(JID_RLEG_3,0,0.95* speed);
	AdjustHJ(JID_LLEG_4, -85, 0.95* speed);    AdjustHJ(JID_RLEG_4,-58,0.95* speed);
	AdjustHJ(JID_LLEG_5, 53, 0.95* speed);     AdjustHJ(JID_RLEG_5,43,0.95* speed);
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	}

	if(timer.GetTime()>=3&& timer.GetTime()<6)
	{
	AdjustHJ(JID_LLEG_3, 0,0.95* speed);      AdjustHJ(JID_RLEG_3,23,0.95* speed);
	AdjustHJ(JID_LLEG_4, -75,0.95* speed);     AdjustHJ(JID_RLEG_4,-60,0.95* speed);
	AdjustHJ(JID_LLEG_5, 63,0.95* speed);      AdjustHJ(JID_RLEG_5,35,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,-0,0.5* speed);
	}

	if(timer.GetTime()>=6&& timer.GetTime()<9)
	{
	
	AdjustHJ(JID_LLEG_3, 0,0.95* speed);       AdjustHJ(JID_RLEG_3,28.5,0.95* speed);
	AdjustHJ(JID_LLEG_4, -58,0.95* speed);	    AdjustHJ(JID_RLEG_4,-85,0.95* speed);
	AdjustHJ(JID_LLEG_5, 43,0.95* speed);	    AdjustHJ(JID_RLEG_5, 53,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,-0,0.5* speed);
	}

	if(timer.GetTime()>=9&& timer.GetTime()<12)
	{
	AdjustHJ(JID_LLEG_3, 23,0.95* speed);   AdjustHJ(JID_RLEG_3,0,0.95* speed);
	AdjustHJ(JID_LLEG_4, -60,0.95* speed);  AdjustHJ(JID_RLEG_4,-75,0.95* speed);
	AdjustHJ(JID_LLEG_5, 35,0.95* speed);   AdjustHJ(JID_RLEG_5,63,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	
	}

   	if (timer.GetTime() >=12)
	{
		if(speed <0.3)
			speed = speed +0.1;
		else speed = 0.3;
		timer.ClearTimer();
		return true;
	} 
	else return false;
	
} 

bool ActHandle::WalkBackLeft(double & speed)//这个版本可以左转
{
	if(!timer.IsTimerRun())  timer.SetTimer();
//	static double speed = 0.1;
	
cout<<"Walk1111111111111111111111"<<endl;

	AdjustHJ(JID_HEAD_1,0,0.37);
	AdjustHJ(JID_HEAD_2,0,0.37);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-105,0.37);      	AdjustHJ( JID_RARM_1,-105,0.37);
	AdjustHJ( JID_LARM_2, 0,0.37);	   	AdjustHJ( JID_RARM_2,0,0.37);
	AdjustHJ( JID_LARM_3,-90,0.37);         AdjustHJ( JID_RARM_3,90,0.37);
	AdjustHJ( JID_LARM_4,-45,0.37);		AdjustHJ( JID_RARM_4,45,0.37);// 手部的角度配置
	
	//AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	AdjustHJ(JID_LLEG_2, 2.0,  0.5* speed );    AdjustHJ(JID_RLEG_2,2.0,0.5* speed);
	AdjustHJ(JID_LLEG_6,2, 0.8* speed);	   AdjustHJ(JID_RLEG_6,2,0.8* speed);//腿部的角度配置



	if(timer.GetTime()>=0 && timer.GetTime()<3)
	{
	AdjustHJ(JID_LLEG_3, 28.5, 0.95* speed);     AdjustHJ(JID_RLEG_3,0,0.95* speed);
	AdjustHJ(JID_LLEG_4, -85, 0.95* speed);    AdjustHJ(JID_RLEG_4,-58,0.95* speed);
	AdjustHJ(JID_LLEG_5, 53, 0.95* speed);     AdjustHJ(JID_RLEG_5,43,0.95* speed);
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	}

	if(timer.GetTime()>=3&& timer.GetTime()<6)
	{
	AdjustHJ(JID_LLEG_3, 0,0.95* speed);      AdjustHJ(JID_RLEG_3,23,0.95* speed);
	AdjustHJ(JID_LLEG_4, -75,0.95* speed);     AdjustHJ(JID_RLEG_4,-60,0.95* speed);
	AdjustHJ(JID_LLEG_5, 63,0.95* speed);      AdjustHJ(JID_RLEG_5,35,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,-0,0.5* speed);
	}

	if(timer.GetTime()>=6&& timer.GetTime()<9)
	{
	
	AdjustHJ(JID_LLEG_3, 0,0.95* speed);       AdjustHJ(JID_RLEG_3,28.5,0.95* speed);
	AdjustHJ(JID_LLEG_4, -58,0.95* speed);	    AdjustHJ(JID_RLEG_4,-85,0.95* speed);
	AdjustHJ(JID_LLEG_5, 43,0.95* speed);	    AdjustHJ(JID_RLEG_5, 53,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,-0,0.5* speed);
	}

	if(timer.GetTime()>=9&& timer.GetTime()<12)
	{
	AdjustHJ(JID_LLEG_3, 23,0.95* speed);   AdjustHJ(JID_RLEG_3,0,0.95* speed);
	AdjustHJ(JID_LLEG_4, -60,0.95* speed);  AdjustHJ(JID_RLEG_4,-75,0.95* speed);
	AdjustHJ(JID_LLEG_5, 35,0.95* speed);   AdjustHJ(JID_RLEG_5,63,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	
	}

   	if (timer.GetTime() >=12)
	{
		if(speed <0.3)
			speed = speed +0.1;
		else speed = 0.3;
		timer.ClearTimer();
		return true;
	} 
	else return false;
	
}


bool ActHandle::StopWalkBack(double & speed)
{
	cout<<"Timer::::"<<timer.GetTime()<<endl;
	if(!timer.IsTimerRun())  timer.SetTimer();
//	static double speed = 0.3;
	AdjustHJ(JID_HEAD_1,0,0.37);
	AdjustHJ(JID_HEAD_2,0,0.37);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-125,0.37);      	AdjustHJ( JID_RARM_1,-125,0.37);
	AdjustHJ( JID_LARM_2, 0,0.37);	   	AdjustHJ( JID_RARM_2,0,0.37);
	AdjustHJ( JID_LARM_3,-90,0.37);         AdjustHJ( JID_RARM_3,90,0.37);
	AdjustHJ( JID_LARM_4,-75,0.37);		AdjustHJ( JID_RARM_4,75,0.37);// 手部的角度配置
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	AdjustHJ(JID_LLEG_2, 0,  0.5* speed );    AdjustHJ(JID_RLEG_2,0,0.5* speed);
	AdjustHJ(JID_LLEG_6, 0,   0.5* speed);	   AdjustHJ(JID_RLEG_6,0,0.5* speed);//腿部的角度配置



	if(timer.GetTime()>=0 && timer.GetTime()<3)
	{
	AdjustHJ(JID_LLEG_3, 30, 0.95* speed);     AdjustHJ(JID_RLEG_3,20,0.95* speed);
	AdjustHJ(JID_LLEG_4, -85, 0.95* speed);    AdjustHJ(JID_RLEG_4,-58,0.95* speed);
	AdjustHJ(JID_LLEG_5, 53, 0.95* speed);     AdjustHJ(JID_RLEG_5,50,0.95* speed);
	}

	if(timer.GetTime()>=3&& timer.GetTime()<6)
	{
	AdjustHJ(JID_LLEG_3, 10,0.95* speed);      AdjustHJ(JID_RLEG_3,23,0.95* speed);
	AdjustHJ(JID_LLEG_4, -75,0.95* speed);     AdjustHJ(JID_RLEG_4,-60,0.95* speed);
	AdjustHJ(JID_LLEG_5, 55,0.95* speed);      AdjustHJ(JID_RLEG_5,35,0.95* speed);
	}

	if(timer.GetTime()>=6&& timer.GetTime()<9)
	{
	
	AdjustHJ(JID_LLEG_3, 20,0.95* speed);       AdjustHJ(JID_RLEG_3,30,0.95* speed);
	AdjustHJ(JID_LLEG_4, -58,0.95* speed);	    AdjustHJ(JID_RLEG_4,-85,0.95* speed);
	AdjustHJ(JID_LLEG_5, 50,0.95* speed);	    AdjustHJ(JID_RLEG_5, 53,0.95* speed);
	
	}

	if(timer.GetTime()>=9&& timer.GetTime()<12)
	{
	AdjustHJ(JID_LLEG_3, 23,0.95* speed);   AdjustHJ(JID_RLEG_3,10,0.95* speed);
	AdjustHJ(JID_LLEG_4, -60,0.95* speed);  AdjustHJ(JID_RLEG_4,-75,0.95* speed);
	AdjustHJ(JID_LLEG_5, 35,0.95* speed);   AdjustHJ(JID_RLEG_5,55,0.95* speed);
	
	
	}

   	if (timer.GetTime() >=12)
	{
		timer.ClearTimer();
		if(speed >= 0.1)
		{	speed = speed -0.08;
			if(speed < 0.08)
				return true;
			else return false;
		}
	} 
	else return false;
	
} 


bool ActHandle::WalkBackEx(int iWalkType, bool bClear)
{
	static double speed = 0.1;
	bool r;
	if (bClear)
	{
		speed = 0.1;
		return true;
	}

	if (iWalkType == 0) r = WalkBack(speed);
	else if (iWalkType == 1)  r = WalkBackLeft(speed);
	else if (iWalkType == -1)  r = WalkBackRight(speed);
	else if (iWalkType == 2) r = StopWalkBack(speed);
	return r;
}


//kick area 0.19
bool ActHandle::KickRight()
{
	wm.m_bIsKicking = true;
	if(!timer.IsTimerRun()) timer.SetTimer();

	if(timer.GetTime() < 20)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00,0.00,0.00,0.00,0.00,0.00,
				0.00,0.00,0.00,0.00,0.00,0.00,0.05);

	if(timer.GetTime() > 20 && timer.GetTime() < 45)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00,-8.32,8.28,-32.07,23.53,8.99,
				0.00,-8.86,8.45,-46.29,27.84,8.86,0.05);
	
	if(timer.GetTime() > 45 && timer.GetTime() < 70)
				 DoAction(-80,0,0,0,-80,0,0,-0,
				0.00, -10.23, -25.28, -12.07, 23.53, 10.99,
				0.00, -8.86,  -38.45, -74.26, 62.52, 8.86,    0.05);
	
	if(timer.GetTime() > 70 && timer.GetTime() < 90)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00, -10.23, -46.28, -52.07, 23.53,  10.99,
				0.00, -8.86,  80.00,  0.00,   -10.00, 8.86,    0.4);

	if(timer.GetTime() > 90 && timer.GetTime() < 110)
				DoAction(0,0,0,0,0,0,0,0,
				0.00,0.00,0.00,0.00,0.00,0.00,
				0.00,0.00,0.00,0.00,0.00,0.00,0.1);
	
	if(timer.GetTime() < 110) return false;
	timer.ClearTimer();
	wm.m_bIsKicking = false;
	return true;
}

//kick area 0.19
bool ActHandle::KickLeft()
{
	wm.m_bIsKicking = true;
	if(!timer.IsTimerRun()) timer.SetTimer();

	if(timer.GetTime() < 20)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00,0.00,0.00,0.00,0.00,0.00,
				0.00,0.00,0.00,0.00,0.00,0.00,0.05);

	if(timer.GetTime() > 20 && timer.GetTime() < 45)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00,8.86,8.45,-46.29,27.84,-8.86,
				0.00,8.32,8.28,-32.07,23.53,-8.99,0.05);
	
	if(timer.GetTime() > 45 && timer.GetTime() < 70)
				 DoAction(-80,0,0,0,-80,0,0,-0,
				0.00, 8.86,  -38.45, -74.26, 62.52, -8.86,
				0.00, 10.23, -25.28, -12.07, 23.53, -10.99,  0.05);
	
	if(timer.GetTime() > 70 && timer.GetTime() < 90)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00, 8.86,  80.00,  0.00,   -30.00, -8.86,
				0.00, 10.23, -46.28, -52.07, 23.53,  -10.99,  0.4);

	if(timer.GetTime() > 90 && timer.GetTime() < 110)
				DoAction(0,0,0,0,0,0,0,0,
				0.00,0.00,0.00,0.00,0.00,0.00,
				0.00,0.00,0.00,0.00,0.00,0.00,0.1);
	
	if(timer.GetTime() < 11000) return false;
	timer.ClearTimer();
	wm.m_bIsKicking = false;
	return true;
}

bool ActHandle::Step(int i)
{
	if(!timer.IsTimerRun()) timer.SetTimer();

	double speed = 0.3;
	double angle1, angle2, angle3, angle4;
	
	switch(i){
	case 0: angle1 = 26;
		angle2 = -64;
		angle3 = 38;
		angle4 = 0;
		break;
	
	case 6: angle1 = 34;
		angle2 = -56;
		angle3 = 22;
		angle4 = 0;
		break;
	
	case 3: angle1 = 30;
		angle2 = -60;
		angle3 = 30;
		angle4 = -5;
		break;	

	case 9: angle1 = 30;
		angle2 = -60;
		angle3 = 30;
		angle4 = 5;
		break;

	default:
		angle1 = 30;
		angle2 = -60;
		angle3 = 30;
		angle4 = 0;
		break;

	};

	if(timer.GetTime() < 3.5)
	{
		AdjustHJ( JID_LLEG_3, 40, speed);
		AdjustHJ( JID_LLEG_4, -80,speed);
		AdjustHJ( JID_LLEG_5, 40, speed);

		AdjustHJ(JID_RLEG_2, 0, speed);
		
	}

	if(timer.GetTime() > 3.5 && timer.GetTime() < 7)
	{
		AdjustHJ( JID_RLEG_3, angle1, speed);
		AdjustHJ( JID_RLEG_4, angle2, speed);
		AdjustHJ( JID_RLEG_5, angle3, speed);

		AdjustHJ( JID_LLEG_3, 30, speed);
		AdjustHJ( JID_LLEG_4, -60,speed);
		AdjustHJ( JID_LLEG_5, 30, speed);

		AdjustHJ(JID_LLEG_2, angle4, speed);
	}

	if(timer.GetTime() > 7 && timer.GetTime() < 10.5)
	{
		AdjustHJ( JID_RLEG_3, 40, speed);
		AdjustHJ( JID_RLEG_4, -80,speed);
		AdjustHJ( JID_RLEG_5, 40, speed);

		AdjustHJ( JID_LLEG_2, 0, speed);
	}

	if(timer.GetTime() > 10.5 && timer.GetTime() < 14)
	{
		
		AdjustHJ( JID_LLEG_3, angle1, speed);
		AdjustHJ( JID_LLEG_4, angle2,speed);
		AdjustHJ( JID_LLEG_5, angle3, speed);

		AdjustHJ( JID_RLEG_3, 30, speed);
		AdjustHJ( JID_RLEG_4, -60,speed);
		AdjustHJ( JID_RLEG_5, 30, speed);

		AdjustHJ( JID_RLEG_2, angle4, speed);
	}
	

	
	if(timer.GetTime() < 14) return false;
	timer.ClearTimer();
	return true;
}


bool ActHandle::StaticWalk()
{
	if(!timer.IsTimerRun()) timer.SetTimer();

	double speed = 0.3022;

	if(timer.GetTime() < 4)
	{
		AdjustHJ( JID_LLEG_3, 40, speed);
		AdjustHJ( JID_LLEG_4, -80,speed);
		AdjustHJ( JID_LLEG_5, 42, speed);

	}

	if(timer.GetTime() > 4 && timer.GetTime() < 8)
	{
		AdjustHJ( JID_LLEG_3, 30, speed);
		AdjustHJ( JID_LLEG_4, -60,speed);
		AdjustHJ( JID_LLEG_5, 32, speed);

	}

	if(timer.GetTime() > 8 && timer.GetTime() < 12)
	{
		AdjustHJ( JID_RLEG_3, 40, speed);
		AdjustHJ( JID_RLEG_4, -80,speed);
		AdjustHJ( JID_RLEG_5, 42, speed);

	}

	if(timer.GetTime() > 12 && timer.GetTime() < 16)
	{
		AdjustHJ( JID_RLEG_3, 30, speed);
		AdjustHJ( JID_RLEG_4, -60,speed);
		AdjustHJ( JID_RLEG_5, 32, speed);

	}

	if(timer.GetTime() < 16) return false;
	timer.ClearTimer();
	return true;
}

bool  ActHandle::StaticWalk(int iNum)
{
	static int i = iNum;
	cout<<i<<endl;
	if(StaticWalk()) i--;
	if(i <= 0)return true;
	else return false;
	
}

bool ActHandle::WalkSmall()
{
	static double speedL = 10;
	static double speedR = 10;
		if(!timer.IsTimerRun())  timer.SetTimer();

	AdjustHJ(JID_HEAD_1,0,0.37);
	AdjustHJ(JID_HEAD_2,0,0.37);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-125,0.37);      	AdjustHJ( JID_RARM_1,-125,0.37);
	AdjustHJ( JID_LARM_2, 0,0.37);	   	AdjustHJ( JID_RARM_2,0,0.37);
	AdjustHJ( JID_LARM_3,-90,0.37);         AdjustHJ( JID_RARM_3,90,0.37);
	AdjustHJ( JID_LARM_4,-75,0.37);		AdjustHJ( JID_RARM_4,75,0.37);// 手部的角度配置


	AdjustHJ(JID_LLEG_2, 0, 0.005* speedL);     AdjustHJ(JID_RLEG_2,0,0.005* speedR);
	
	AdjustHJ(JID_LLEG_6, 0,   0.005* speedL);  AdjustHJ(JID_RLEG_6, 0,0.005* speedR);//腿部的角度配置
	AdjustHJ(JID_LLEG_1, 0,  0.005 * speedL );   AdjustHJ(JID_RLEG_1, 0,0.005* speedR);

	if(timer.GetTime()>=0 && timer.GetTime()<3)
	{
		
	AdjustHJ(JID_LLEG_3, 30,  0.01* speedL );    AdjustHJ(JID_RLEG_3, 28,0.01* speedR);
	AdjustHJ(JID_LLEG_4, -90, 0.01* speedL);     AdjustHJ(JID_RLEG_4,-65,0.01* speedR);
	AdjustHJ(JID_LLEG_5, 55 ,0.01* speedL);      AdjustHJ(JID_RLEG_5, 40,0.01* speedR);
	
	
	}

	if(timer.GetTime()>=3&& timer.GetTime()<6)
	{
	
	AdjustHJ(JID_LLEG_3, 40,0.01* speedL);        AdjustHJ(JID_RLEG_3,  24,0.01* speedR);
	AdjustHJ(JID_LLEG_4, -70,0.01* speedL);       AdjustHJ(JID_RLEG_4, -70,0.01* speedR);
	AdjustHJ(JID_LLEG_5, 33,0.01* speedL);        AdjustHJ(JID_RLEG_5,  45,0.01* speedR);
	
	}

	if(timer.GetTime()>=6&& timer.GetTime()<9)
	{
	
	AdjustHJ(JID_LLEG_3, 28,0.01* speedL);     AdjustHJ(JID_RLEG_3,30,0.01* speedR);
	AdjustHJ(JID_LLEG_4, -65,0.01* speedL);	    AdjustHJ(JID_RLEG_4,-90,0.01* speedR);
	AdjustHJ(JID_LLEG_5, 40,0.01* speedL);	    AdjustHJ(JID_RLEG_5, 55,0.01* speedR);
	
	}

	if(timer.GetTime()>=9&& timer.GetTime()<12)
	{
		

	AdjustHJ(JID_LLEG_3, 24,0.01* speedL);   AdjustHJ(JID_RLEG_3,40,0.01* speedR);
	AdjustHJ(JID_LLEG_4, -70,0.01* speedL);  AdjustHJ(JID_RLEG_4,-70,0.01* speedR);
	AdjustHJ(JID_LLEG_5, 45,0.01* speedL);   AdjustHJ(JID_RLEG_5,33,0.01* speedR);
	
	}

	if (timer.GetTime() >=12)
	{
		if(speedL <20)
			speedL = speedL +10;
		//else speedL = 40;
		if(speedR < 20)
			speedR = speedR +10;
		//else speedR = 40;
		timer.ClearTimer();
		return true;
	}
	else return false;

} 

bool ActHandle::DoAction(double laj1, double laj2, double laj3, double laj4,
			 double raj1 ,double raj2, double raj3, double raj4,
			 double llj1, double llj2, double llj3, double llj4, double llj5, double llj6,
			 double rlj1, double rlj2, double rlj3, double rlj4, double rlj5, double rlj6,
				double speed
			)
			
{
	AdjustHJ(JID_LARM_1, laj1, speed);
	AdjustHJ(JID_RARM_1, raj1, speed);
	AdjustHJ(JID_LARM_2, laj2, speed);
	AdjustHJ(JID_RARM_2, raj2, speed);
	AdjustHJ(JID_LARM_3, laj3, speed);
	AdjustHJ(JID_RARM_3, raj3, speed);
	AdjustHJ(JID_LARM_4, laj4, speed);
	AdjustHJ(JID_RARM_4, raj4, speed);

	AdjustHJ(JID_LLEG_1, llj1, speed);
	AdjustHJ(JID_RLEG_1, rlj1,speed);
	AdjustHJ(JID_LLEG_2, llj2, speed);
	AdjustHJ(JID_RLEG_2, rlj2, speed);
	AdjustHJ(JID_LLEG_3, llj3, speed);
	AdjustHJ(JID_RLEG_3, rlj3, speed);
	AdjustHJ(JID_LLEG_4, llj4, speed);
	AdjustHJ(JID_RLEG_4, rlj4, speed);
	AdjustHJ(JID_LLEG_5, llj5, speed);
	AdjustHJ(JID_RLEG_5, rlj5, speed);
	AdjustHJ(JID_LLEG_6, llj6, speed);
	AdjustHJ(JID_RLEG_6, rlj6, speed);
}

void ActHandle::ClearAll()
{
	Vector o;
	Beam(o, 0, true);
	BeamAfterDelay(o, 0, 0, true);
	Walk(0, true);
	WalkBackEx(0, true);
	timer.ClearTimer();
	wm.m_bIsKicking = false;

}


bool ActHandle::KickSmallRight()
{
	wm.m_bIsKicking = true;
	if(!timer.IsTimerRun()) timer.SetTimer();

	if(timer.GetTime() < 25)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00,-8.32,8.28,-32.07,23.53,8.99,
				0.00,-8.86,8.45,-46.29,27.84,8.86,0.05);
	
	if(timer.GetTime() > 25 && timer.GetTime() < 50)
				 DoAction(-80,0,0,0,-80,0,0,-0,
				0.00,-8.23,-8.28,-22.07,23.53,8.99,
				0.00,-8.86,18.45,-84.26,42.52,8.86,0.075);
	
	if(timer.GetTime() > 50 && timer.GetTime() < 70)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00,-8.23,-15.28,-22.07,23.53,8.99,
				0.00,-8.86,40.00,0.00,-5.00,8.86,0.4);
	if(timer.GetTime() > 70 && timer.GetTime() < 90)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00,-8.23,-8.28,-22.07,23.53,8.99,
				0.00,-8.86,18.45,-84.26,42.52,8.86,0.2);
	if(timer.GetTime() < 90) return false;
	timer.ClearTimer();
	wm.m_bIsKicking = false;
	return true;
}


bool ActHandle::KickSmallLeft()
{
	wm.m_bIsKicking = true;
	if(!timer.IsTimerRun()) timer.SetTimer();

	if(timer.GetTime() < 25)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00,8.86,8.45,-46.29,27.84,-8.86,
				0.00,8.32,8.28,-32.07,23.53,-8.99,0.05);
	
	if(timer.GetTime() > 25 && timer.GetTime() < 50)
				 DoAction(-80,0,0,0,-80,0,0,-0,				
				0.00,8.86,18.45,-84.26,42.52,-8.86,
				0.00,8.23,-8.28,-22.07,23.53,-8.99,0.075);
	
	if(timer.GetTime() > 50 && timer.GetTime() < 70)
				DoAction(-80,0,0,0,-80,0,0,-0,
				0.00,8.86,40.00,0.00,-5.00,-8.86,
				0.00,8.23,-15.28,-22.07,23.53,-8.99,0.4);
	if(timer.GetTime() > 70 && timer.GetTime() < 90)
				DoAction(-80,0,0,0,-80,0,0,-0,				
				0.00,8.86,18.45,-84.26,42.52,-8.86,
				0.00,8.23,-8.28,-22.07,23.53,-8.99,0.2);
	
	if(timer.GetTime() < 90) return false;
	timer.ClearTimer();
	wm.m_bIsKicking = false;
	return true;
}


bool ActHandle::Move(int iType)//1 表示左移动 －1 表示右移动
{
	int iDirType = iType;
	if(!timer.IsTimerRun()) timer.SetTimer();
	if(iType == 1) cout<<"Move Left"<<endl;
	else cout<<"Move Right"<<endl;
	double speed = 0.2;

	
	AdjustHJ(JID_LLEG_1, 0, speed);	             AdjustHJ(JID_RLEG_1, 0, speed);

	if(timer.GetTime() >=0 && timer.GetTime() < 3)
	{
		if(iDirType == 1)
		{
			AdjustHJ( JID_LLEG_3,  35, speed);	
			AdjustHJ( JID_LLEG_4, -90,speed);	
			AdjustHJ( JID_LLEG_5, 55, speed);	
	
			AdjustHJ(JID_LLEG_2, 8, speed);	
		}
		else 
		{	
			AdjustHJ( JID_RLEG_3,  35, speed);	
			AdjustHJ( JID_RLEG_4, -90,speed);	
			AdjustHJ( JID_RLEG_5, 55, speed);	
	
			AdjustHJ(JID_RLEG_2, -8, speed);	

		}	
	}

	if(timer.GetTime() >=3 && timer.GetTime() < 6)
	{
		if(iDirType == 1)
		{
			AdjustHJ( JID_LLEG_3, 30, speed);	
			AdjustHJ( JID_LLEG_4, -73.5,speed);	
			AdjustHJ( JID_LLEG_5, 42, speed);	
			AdjustHJ(JID_RLEG_2, -8, speed);
		}
		else 
		{
			AdjustHJ( JID_RLEG_3, 30, speed);	
			AdjustHJ( JID_RLEG_4, -73.5,speed);	
			AdjustHJ( JID_RLEG_5, 42, speed);	
			AdjustHJ(JID_LLEG_2, 8, speed);


			
		}	
	}

	if(timer.GetTime() >=6 && timer.GetTime() < 9)
	{
		if(iDirType == 1)
		{
			AdjustHJ( JID_RLEG_3, 35, speed);
			AdjustHJ( JID_RLEG_4, -90, speed);
			AdjustHJ( JID_RLEG_5, 55, speed);
			AdjustHJ(JID_RLEG_2, 8, speed);
		}
		else 
		{
			AdjustHJ( JID_LLEG_3, 35, speed);
			AdjustHJ( JID_LLEG_4, -90, speed);
			AdjustHJ( JID_LLEG_5, 55, speed);
			AdjustHJ(JID_LLEG_2, -8, speed);

		
		}
		
	}

	if(timer.GetTime() >= 9 && timer.GetTime() < 12)
	{
		if(iDirType == 1)
		{
			AdjustHJ( JID_RLEG_3, 30, speed);
			AdjustHJ( JID_RLEG_4, -73.5, speed);
			AdjustHJ( JID_RLEG_5, 42, speed);
			AdjustHJ(JID_LLEG_2, -8, speed);
		}
		else 
		{
			AdjustHJ( JID_LLEG_3, 30, speed);
			AdjustHJ( JID_LLEG_4, -73.5, speed);
			AdjustHJ( JID_LLEG_5, 42, speed);
			AdjustHJ(JID_RLEG_2, 8, speed);

		}
	}

	if(timer.GetTime() < 12) return false;
	timer.ClearTimer();
	return true;
} 

 bool ActHandle ::FootFall()
{
	double speed = 0.25;
	
     if(!timer.IsTimerRun())  timer.SetTimer();
	AdjustHJ(JID_HEAD_1,0,0.07);
	AdjustHJ(JID_HEAD_2,0,0.07);// 头部的角度配置
	
	AdjustHJ( JID_LARM_1,-125,0.07);      	AdjustHJ( JID_RARM_1,-125,0.07);
	AdjustHJ( JID_LARM_2,0,0.07);	   	AdjustHJ( JID_RARM_2,0,0.07);
	AdjustHJ( JID_LARM_3,-90,0.07);         AdjustHJ( JID_RARM_3,90,0.07);
	AdjustHJ( JID_LARM_4,-75,0.07);		AdjustHJ( JID_RARM_4,75,0.07);// 手部的角度配置
	
	AdjustHJ(JID_LLEG_1,0,0.47);            AdjustHJ(JID_RLEG_1,0,0.47);
	AdjustHJ(JID_LLEG_2,0,0.47);           AdjustHJ(JID_RLEG_2,0,0.47);
	AdjustHJ(JID_LLEG_6,0,0.47);		AdjustHJ(JID_RLEG_6,0,0.47);//腿部的角度配置



     if(timer.GetTime()>=0&& timer.GetTime()<3)
     {
	AdjustHJ(JID_LLEG_3,45,speed); 
	AdjustHJ(JID_LLEG_4,-100,speed);
	AdjustHJ(JID_LLEG_5,50,speed);		
     }
	 
     if(timer.GetTime()>=3&& timer.GetTime()<6)
     {
	AdjustHJ(JID_LLEG_3,30,speed);
	AdjustHJ(JID_LLEG_4,-70,speed);	
	AdjustHJ(JID_LLEG_5,40,speed);	
     }
     if(timer.GetTime()>=6&& timer.GetTime()<9)
     {
	
 	AdjustHJ(JID_RLEG_3,45,speed);
  	AdjustHJ(JID_RLEG_4,-100,speed);
 	AdjustHJ(JID_RLEG_5,50,speed);
     }
     if(timer.GetTime()>=9&& timer.GetTime()<12)
     {
	
  	AdjustHJ(JID_RLEG_3,30,speed);		
	AdjustHJ(JID_RLEG_4,-70,speed);
	AdjustHJ(JID_RLEG_5,40,speed);

     }
     if (timer.GetTime() < 12) return false;
     timer.ClearTimer();
     return true;

}
 
bool ActHandle::WalkBackSmall() 
{
	if(!timer.IsTimerRun())  timer.SetTimer();
	static double speed = 0.1;
	
	AdjustHJ(JID_HEAD_1,0,0.37);
	AdjustHJ(JID_HEAD_2,0,0.37);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-105,0.37);      	AdjustHJ( JID_RARM_1,-105,0.37);
	AdjustHJ( JID_LARM_2, 0,0.37);	   	AdjustHJ( JID_RARM_2,0,0.37);
	AdjustHJ( JID_LARM_3,-90,0.37);         AdjustHJ( JID_RARM_3,90,0.37);
	AdjustHJ( JID_LARM_4,-45,0.37);		AdjustHJ( JID_RARM_4,45,0.37);// 手部的角度配置
	
	//AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	AdjustHJ(JID_LLEG_2, 0,  0.5* speed );    AdjustHJ(JID_RLEG_2,0,0.5* speed);
	AdjustHJ(JID_LLEG_6,2,   0.5* speed);	   AdjustHJ(JID_RLEG_6,2,0.5* speed);//腿部的角度配置



	if(timer.GetTime()>=0 && timer.GetTime()<3)
	{
	AdjustHJ(JID_LLEG_3, 35, 0.95* speed);     AdjustHJ(JID_RLEG_3,15,0.95* speed);
	AdjustHJ(JID_LLEG_4, -90, 0.95* speed);    AdjustHJ(JID_RLEG_4,-58,0.95* speed);
	AdjustHJ(JID_LLEG_5, 53, 0.95* speed);     AdjustHJ(JID_RLEG_5,43,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	}

	if(timer.GetTime()>=3&& timer.GetTime()<6)
	{
	
	AdjustHJ(JID_LLEG_3, 0,0.95* speed);      AdjustHJ(JID_RLEG_3,23,0.95* speed);
	AdjustHJ(JID_LLEG_4, -75,0.95* speed);     AdjustHJ(JID_RLEG_4,-60,0.95* speed);
	AdjustHJ(JID_LLEG_5, 63,0.95* speed);      AdjustHJ(JID_RLEG_5,35,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,-0,0.5* speed);
	}

	if(timer.GetTime()>=6&& timer.GetTime()<9)
	{
	
	AdjustHJ(JID_LLEG_3, 15,0.95* speed);       AdjustHJ(JID_RLEG_3,35,0.95* speed);
	AdjustHJ(JID_LLEG_4, -58,0.95* speed);	    AdjustHJ(JID_RLEG_4,-90,0.95* speed);
	AdjustHJ(JID_LLEG_5, 43,0.95* speed);	    AdjustHJ(JID_RLEG_5, 53,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,-0,0.5* speed);
	}

	if(timer.GetTime()>=9&& timer.GetTime()<12)
	{
	AdjustHJ(JID_LLEG_3, 23,0.95* speed);   AdjustHJ(JID_RLEG_3,0,0.95* speed);
	AdjustHJ(JID_LLEG_4, -60,0.95* speed);  AdjustHJ(JID_RLEG_4,-75,0.95* speed);
	AdjustHJ(JID_LLEG_5, 35,0.95* speed);   AdjustHJ(JID_RLEG_5,63,0.95* speed);
	
	AdjustHJ(JID_LLEG_1, 0,  0.5 * speed );   AdjustHJ(JID_RLEG_1,0,0.5* speed);
	
	}

   	if (timer.GetTime() >=12)
	{
		if(speed <0.2)
			speed = speed +0.1;
		else speed = 0.2;
		timer.ClearTimer();
		return true;
	} 
	else return false;
	
} 

bool ActHandle::Catch (Vector vCatchPos)
{

	if(!timer.IsTimerRun())  timer.SetTimer();


	if(timer.GetTime()>0&& timer.GetTime()<40)
    {
	 AdjustHJ(JID_HEAD_1,0,0.07);
	 AdjustHJ(JID_HEAD_2,0,0.07);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-125,0.1);      	AdjustHJ( JID_RARM_1,-125,0.1);
	AdjustHJ( JID_LARM_2,30,0.1);	   	AdjustHJ( JID_RARM_2,-30,0.1);
	AdjustHJ( JID_LARM_3,-90,0.1);         AdjustHJ( JID_RARM_3,90,0.1);
	AdjustHJ( JID_LARM_4,-45,0.1);		AdjustHJ( JID_RARM_4,45,0.1);// 手部的角度配置
	AdjustHJ(JID_LLEG_1,0,0.1);            AdjustHJ(JID_RLEG_1,0,0.1);
	AdjustHJ(JID_LLEG_2,0,0.1);           AdjustHJ(JID_RLEG_2,0,0.1);

	AdjustHJ(JID_LLEG_3,60,0.1);            AdjustHJ(JID_RLEG_3,60,0.1);
	AdjustHJ(JID_LLEG_4,-100,0.1);		AdjustHJ(JID_RLEG_4,-100,0.1);
	AdjustHJ(JID_LLEG_5,60,0.1);		AdjustHJ(JID_RLEG_5,60,0.1);

	AdjustHJ(JID_LLEG_6,0,0.1);		AdjustHJ(JID_RLEG_6,0,0.1);//腿部的角度配置
     }
    if(timer.GetTime()>40 && timer.GetTime()<50)
    {
	 AdjustHJ(JID_HEAD_1,0,0.07);
	 AdjustHJ(JID_HEAD_2,0,0.07);// 头部的角度配置

	AdjustHJ( JID_LARM_1,-125,0.1);      	AdjustHJ( JID_RARM_1,-125,0.1);
	AdjustHJ( JID_LARM_2,30,0.1);	   	AdjustHJ( JID_RARM_2,-30,0.1);
	AdjustHJ( JID_LARM_3,-90,0.1);         AdjustHJ( JID_RARM_3,90,0.1);
	AdjustHJ( JID_LARM_4,-45,0.1);		AdjustHJ( JID_RARM_4,45,0.1);// 手部的角度配置
	AdjustHJ(JID_LLEG_1,0,0.1);            AdjustHJ(JID_RLEG_1,0,0.1);
	AdjustHJ(JID_LLEG_2,0,0.1);           AdjustHJ(JID_RLEG_2,0,0.1);

	AdjustHJ(JID_LLEG_3,60,0.1);            AdjustHJ(JID_RLEG_3,60,0.1);
	AdjustHJ(JID_LLEG_4,-100,0.1);		AdjustHJ(JID_RLEG_4,-100,0.1);
	AdjustHJ(JID_LLEG_5,60,0.1);		AdjustHJ(JID_RLEG_5,60,0.1);

	AdjustHJ(JID_LLEG_6,0,0.1);		AdjustHJ(JID_RLEG_6,0,0.1);//腿部的角度配置
     }
	   if (timer.GetTime() < 40) return false;
//cout<<"Squat over Squat over Squat over Squat over Squat over Squat over "<<endl;
     timer.ClearTimer();
     return true;
} 

