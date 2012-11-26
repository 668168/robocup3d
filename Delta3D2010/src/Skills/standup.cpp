
#include "standup.h"

StandUp::StandUp() : Ffcount ( 46 ),Bcount ( 46 ),Fcount ( 66 ),
                     controlCycle ( WorldModel::instance().getCurrentCycle() ),
                     counter ( -40 ),brakenFrontflag(false)
{
	flag  = false;
	flag1 = false;
	flag2 = false;
	flag3 = false;
	flag4 = true ;
	flag5 = true;
        flagstandup = false;
	standupFinished = false;
	var1 = 10;
	var2 = 10;
	temp = 0;
	t     = 0;
	rep = 300;
}
 
StandUp& StandUp::instance()
{
	static StandUp sStandUp;
	return sStandUp;
}

StandUp::~StandUp()
{
}



std::string StandUp::fastFrontStart ( int cycle )
{
	standupFinished = false;
	
	AngularMotor* eff = & AngularMotor::instance();
	eff->clear();

	if ( controlCycle!=cycle )
	{
		counter++;
		rep--;
	}
	controlCycle=cycle;
	if ((rep >= 0 )/*&&( EndFrontStandUpCycle != rep)*/)	
	{//recognizeFrontSt[abs(rep)%30][0] = sqrt((WorldModel::instance().getGyr().x*WorldModel::instance().getGyr().x)  + (WorldModel::instance().getGyr().y*WorldModel::instance().getGyr().y) + (WorldModel::instance().getGyr().z* WorldModel::instance().getGyr().z) );
	//WorldModel::instance().setFellDown(false);
         //FallDownRecognition::instance().forceStop = true; 
	   //cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << recognizeFrontSt[abs(rep)%30][0] << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	// return "";  
	recognizeFrontSt[abs(counter)%30][0] =  sqrt(WorldModel::instance().getFRP(FID_LF).f_x*WorldModel::instance().getFRP(FID_LF).f_x + WorldModel::instance().getFRP(FID_LF).f_y*WorldModel::instance().getFRP(FID_LF).f_y + WorldModel::instance().getFRP(FID_LF).f_z*WorldModel::instance().getFRP(FID_LF).f_z );
	recognizeFrontSt[abs(counter)%30][1] =  sqrt(WorldModel::instance().getFRP(FID_RF).f_x*WorldModel::instance().getFRP(FID_RF).f_x + WorldModel::instance().getFRP(FID_RF).f_y*WorldModel::instance().getFRP(FID_RF).f_y + WorldModel::instance().getFRP(FID_RF).f_z*WorldModel::instance().getFRP(FID_RF).f_z );
	}
	if( rep==0)
	{
	  for(int l = 0; l<2 ; l++)
	    for(int h = 0 ; h<30 ; h++)
	    { temp = temp + recognizeFrontSt[h][l];
	    
	    }

	
	    temp = temp/30; //average
	    
	    for(int h = 0 ; h<30 ; h++) 
	    {
	     recognizeFrontSt[h][2] = abs(recognizeFrontSt[h][0]-temp);
	     recognizeFrontSt[h][3] = abs(recognizeFrontSt[h][1]-temp);
	     
	    }
 	    var1 = 0;
 	    var2 = 0;
	     for(int l = 0; l<2 ; l++)
	     for(int h = 0 ; h<30 ; h++)
	      {var1 = var1 +  recognizeFrontSt[h][l];
	       var2 = var2 + recognizeFrontSt[h][l];
	      }
	     var2 = var2/30;
	     
// 	     cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << var2 << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	        
	//if (var2 >300)
	if (var1 == 0 && var2 ==0 )
	{ //FallDownRecognition::instance().endStartCycle = cycle;
               brakenFrontflag = true;
	       
	       counter=-40;
	       //rep = 30;
	       var1 = 10;
	       var2 = 10;
	       temp = 0;
	       t     = 0;
	       rep = 300;
	       flag  = false;
	       flag1 = false;
	       flag2 = false;
	       flag3 = false;
	       flag4 = true ;
	       Fcount = 66; }
	 }
	
	EndFrontStandUpCycle = rep;
	
	string ss= "";
        bool f = false;
//         cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl<<abs(rep-EndFrontStandUpCycle)<<endl<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
	if(compare(1,JID_HEAD_1)&&compare(2,JID_HEAD_2)&&compare(3,JID_LARM_1)&&compare(4,JID_LARM_2)&&compare(5,JID_LARM_3)&&compare(6,JID_LARM_4)&&compare(7,JID_LLEG_1)&&compare(8,JID_LLEG_2)&&compare(9,JID_LLEG_3)&&compare(10,JID_LLEG_4)&&compare(11,JID_LLEG_5)&&compare(12,JID_LLEG_6)&&compare(13,JID_RARM_1)&&compare(14,JID_RARM_2)&&compare(15,JID_RARM_3)&&compare(16,JID_RARM_4)&&compare(17,JID_RLEG_1)&&compare(18,JID_RLEG_2)&&compare(19,JID_RLEG_3)&&compare(20,JID_RLEG_4)&&compare(21,JID_RLEG_5)&&compare(0,JID_RLEG_6)) 
                ss = Skill::instance().standUp ("Front",f ,t,rep);
	else 
		t--;
	update(1,JID_HEAD_1);
	update(2,JID_HEAD_2);
	update(3,JID_LARM_1);
	update(4,JID_LARM_2);
	update(5,JID_LARM_3);
	update(6,JID_LARM_4);
	update(7,JID_LLEG_1);
	update(8,JID_LLEG_2);
	update(9,JID_LLEG_3);
	update(10,JID_LLEG_4);
	update(11,JID_LLEG_5);
	update(12,JID_LLEG_6);
	update(13,JID_RARM_1);
	update(14,JID_RARM_2);
	update(15,JID_RARM_3);
	update(16,JID_RARM_4);
	update(17,JID_RLEG_1);
	update(18,JID_RLEG_2);
	update(19,JID_RLEG_3);
	update(20,JID_RLEG_4);
	update(21,JID_RLEG_5);
	update(0,JID_RLEG_6);
//         cout << "========================================"<<endl<<ss<<endl<<"==================================";
	if (ss!="")
	   return ss;//eff->str();
        else if (counter > 0){
		standupFinished = true;
		FallDownRecognition::instance().flag=0;
		brakenFrontflag = false;
		FallDownRecognition::instance().forceStop= false;
		counter = -40;
		flag  = false;
		flag1 = false;
		flag2 = false;
		flag3 = false;
		flag4 = true ;
		Ffcount = 46;
		rep =100;
		t = 0;
              }
          eff->allJointsOff();
          return eff->str();
}



std::string StandUp::backStart ( int cycle )
{
	standupFinished = false;
	AngularMotor* eff = & AngularMotor::instance();
	eff->clear();

	if ( controlCycle!=cycle )
	{
		counter++;
	}
	controlCycle=cycle;

	if ( counter <=-36 )
	{
		eff->allJointsOff();
		return eff->str();
	}


//start of home
	if ( counter <= 10 )
	{
		setInitialStandUpBack();
// 		std::cout<<std::endl<<std::endl<< "sdfgbfsg"<<eff->str() <<std::endl<<std::endl;
		return eff->str();
	}
//end of home

	else if ( counter>START_SITTING_DOWN && counter<=END_SITTING_DOWN )
	{
		eff->moveArm ( left_side, -2.2,0 ,0 ,0 );
		eff->moveLeg ( left_side, 0, 0, 3, 0, 0, 0 );
		eff->moveArm ( right_side, -2.2,0 ,0 ,0 );
		eff->moveLeg ( right_side, 0, 0, 3, 0, 0, 0 );
		return eff->str();
	}
	else if ( counter>START_OPEN_LEG && counter<=END_OPEN_LEG )
	{
		eff->moveArm ( left_side, 0, 2 ,0 ,0 );
		eff->moveLeg ( left_side, -7, 0, 5, -3, -2, 0 );//--> please Note : lle3+lle4+lle5=0
		eff->moveArm ( right_side, 0, -2 ,0 ,0 );
		eff->moveLeg ( right_side, -7, 0, 5, -3, -2, 0 );//--> please Note : rle3+lle4+rle5=0
		return eff->str();
	}
	else if ( counter>START_CROSS_STAND_UP && counter<=END_CROSS_STAND_UP )
	{
		eff->moveLeg ( left_side, 6, 2, -5, 3, 2.3, -2 );//--> please Note : lle3+lle4+lle5=0
		eff->moveLeg ( right_side, 6, -2, -5, 3, 2.3, 2 );//--> please Note : rle3+lle4+rle5=0
		return eff->str();
	}
	else if ( WorldModel::i().getHJoint ( JID_LLEG_2 ).angle>=START_CONTROL_MOTOR &&
	          WorldModel::i().getHJoint ( JID_RLEG_2 ).angle<=END_CONTROL_MOTOR &&
	          counter>START_FULL_STAND_UP &&
	          counter <=END_FULL_STAND_UP )
	{
		eff->moveArm(left_side, 1, -1 ,0 ,0 );
    		eff->moveLeg(left_side, 0, -1, 0, 0, 0, 0.5);
    		eff->moveArm(right_side, 1, +1 ,0 ,0 );
    		eff->moveLeg(right_side, 0, 1, 0, 0, 0, -0.5); 
    		return eff->str();
	}
	if (counter >= END_FULL_STAND_UP )
	{
		standupFinished = true;
		FallDownRecognition::instance().forceStop = false;
		counter = -40;
		flag  = false;
		flag1 = false;
		flag2 = false;
		flag3 = false;
		flag4 = true ;
		Fcount = 46;
		brakenFrontflag = true;
	}

	eff->allJointsOff();
	return eff->str();
}

std::string StandUp::frontStart ( int cycle )
{
	//start
	standupFinished = false;
	AngularMotor* eff = & AngularMotor::instance();
	eff->clear();
	if ( controlCycle!=cycle )
	{
		counter++;
	}
	controlCycle=cycle;
	if ( counter <=-36 )
	{
		eff->allJointsOff();
		return eff->str();
	}

	else if ( counter<0 )
	{
		setInitialStandUpFront();
// 		cout<< endl << "init :  " << counter; 
		return eff->str();
	}



//start of home
	else if ( counter>=10 && counter<20 )
	{
// 		cout << "front" << endl;
		eff->printAngles();
		frontAddValue();
		eff->moveArm ( right_side, Faddraj1, Faddraj2, Faddraj3, Faddraj4 );
		eff->moveArm ( left_side, Faddlaj1, Faddlaj2, Faddlaj3, Faddlaj4 );
		return eff->str();
	}

	else if ( counter <= 30 )
	{
		frontAddValue();
		eff->moveLeg ( right_side, Faddrlj1, Faddrlj2, Faddrlj3, Faddrlj4, Faddrlj5, Faddrlj6 );
		eff->moveLeg ( left_side, Faddllj1, Faddllj2, Faddllj3, Faddllj4, Faddllj5, Faddllj6 );
		return eff->str();
	}


	else if ( WorldModel::instance().getHJoint ( JID_RARM_1 ).angle <= UPPING_RIGHTLEG_ARM1  && WorldModel::instance().getHJoint ( JID_LARM_1 ).angle<= UPPING_LEFTLEG_ARM1 && ( counter>UPPING_LEG_CYCLE ) && ( flag3==false ) )
	{
	        if (abs(WorldModel::instance().getGyr().x) < 4.0 && counter > UPPING_LEG_CYCLE+20)
	        { FallDownRecognition::instance().endStartCycle = cycle;
		  brakenFrontflag = true;
		  counter=-40;
		  flag  = false;
		  flag1 = false;
		  flag2 = false;
		  flag3 = false;
		  flag4 = true ;
		  Fcount = 66; 
		}else{
// 		cout << "front" << endl;
// 		eff->printAngles();
		eff->moveLeg ( left_side, 0,0 , 0, 0, -2, 0 );
		eff->moveLeg ( right_side, 0,0, 0, 0, -2,0 );
		eff->moveArm ( left_side, 1.5, 0, 0, 0 );
		eff->moveArm ( right_side, 1.5, 0, 0, 0 );
		return eff->str();}

	}

	else if ( WorldModel::instance().getHJoint ( JID_RLEG_3 ).angle <= BENDING_LEG3  && WorldModel::instance().getHJoint ( JID_LARM_3 ).angle <= BENDING_ARM3 && ( counter>BENDING_CYCLE ) && ( flag1==false ) )
	{
		eff->moveLeg ( left_side, -1, 0, 4.5, 0, 2, -0.5 );
		eff->moveLeg ( right_side, -1, 0, 4.5, 0, 2, 0.5 );
		return eff->str();
	}

	else if ( WorldModel::instance().getHJoint ( JID_RLEG_3 ).angle >= STANDINGUP_RIGHTLEG3  && WorldModel::instance().getHJoint ( JID_LLEG_3 ).angle >= STANDINGUP_LEFTLEG3 && ( counter>STANGINGUP_CYCLE ) && ( flag==false ) )
	{
		flag1=true;
		flag2=true;
		flag3=true;
		eff->moveLeg ( left_side, 0.2,0 , -1.5, 0, 0.01, 0.1 );
		eff->moveLeg ( right_side, 0.2,0, -1.5, 0, 0.01,-0.1 );
		return eff->str();
	}
	else if ( counter >= 150 )
	{
		standupFinished = true;
		
		FallDownRecognition::instance().endStartCycle = cycle;
		counter=-40;
		flag  = false;
		flag1 = false;
		flag2 = false;
		flag3 = false;
		flag4 = true ;
		Fcount = 66; 
	}
	eff->allJointsOff();
	return eff->str();
	//end

}

void StandUp::backAddValue()
{
        BaddHj1=(0 - WorldModel::instance().getHJoint(JID_HEAD_1).angle)/Bcount;
        BaddHj2=(0 - WorldModel::instance().getHJoint(JID_HEAD_2).angle)/Bcount;
        Baddllj1=(0-WorldModel::instance().getHJoint(JID_LLEG_1).angle)/Bcount;
        Baddllj2=(0-WorldModel::instance().getHJoint(JID_LLEG_2).angle)/Bcount;
        Baddllj3=(3.75-WorldModel::instance().getHJoint(JID_LLEG_3).angle)/Bcount;
        Baddllj4=(0-WorldModel::instance().getHJoint(JID_LLEG_4).angle)/Bcount;
        Baddllj5=(-5.74-WorldModel::instance().getHJoint(JID_LLEG_5).angle)/Bcount;
        Baddllj6=(0-WorldModel::instance().getHJoint(JID_LLEG_6).angle)/Bcount;
        Baddrlj1=(0-WorldModel::instance().getHJoint(JID_RLEG_1).angle)/Bcount;
        Baddrlj2=(0-WorldModel::instance().getHJoint(JID_RLEG_2).angle)/Bcount;
        Baddrlj3=(3.75-WorldModel::instance().getHJoint(JID_RLEG_3).angle)/Bcount;
        Baddrlj4=(0-WorldModel::instance().getHJoint(JID_RLEG_4).angle)/Bcount;
        Baddrlj5=(-5.74-WorldModel::instance().getHJoint(JID_RLEG_5).angle)/Bcount;
        Baddrlj6=(0-WorldModel::instance().getHJoint(JID_RLEG_6).angle)/Bcount;
        Baddlaj1=(-96.0-WorldModel::instance().getHJoint(JID_LARM_1).angle)/Bcount;
        Baddlaj2=(0-WorldModel::instance().getHJoint(JID_LARM_2).angle)/Bcount;
        Baddlaj3=(0-WorldModel::instance().getHJoint(JID_LARM_3).angle)/Bcount;
        Baddlaj4=(0-WorldModel::instance().getHJoint(JID_LARM_4).angle)/Bcount;
        Baddraj1=(-96.0-WorldModel::instance().getHJoint(JID_RARM_1).angle)/Bcount;
        Baddraj2=(0-WorldModel::instance().getHJoint(JID_RARM_2).angle)/Bcount;
        Baddraj3=(0-WorldModel::instance().getHJoint(JID_RARM_3).angle)/Bcount;
        Baddraj4=(0-WorldModel::instance().getHJoint(JID_RARM_4).angle)/Bcount;
        Bcount--;
	if (Bcount<1)
		Bcount = 46;
}

void StandUp::frontAddValue()
{
        FaddHj1 = (0 - WorldModel::instance().getHJoint(JID_HEAD_1).angle)/Fcount;
        FaddHj2 = (0 - WorldModel::instance().getHJoint(JID_HEAD_2).angle)/Fcount;
	Faddllj1 = ( 0-WorldModel::instance().getHJoint ( JID_LLEG_1 ).angle ) /Fcount;
	Faddllj2 = ( 0-WorldModel::instance().getHJoint ( JID_LLEG_2 ).angle ) /Fcount;
	Faddllj3 = ( 0-WorldModel::instance().getHJoint ( JID_LLEG_3 ).angle ) /Fcount;
	Faddllj4 = ( 0-WorldModel::instance().getHJoint ( JID_LLEG_4 ).angle ) /Fcount;
	Faddllj5 = ( 50.09-WorldModel::instance().getHJoint ( JID_LLEG_5 ).angle ) /Fcount;
	Faddllj6 = ( 0-WorldModel::instance().getHJoint ( JID_LLEG_6 ).angle ) /Fcount;
	Faddrlj1 = ( 0-WorldModel::instance().getHJoint ( JID_RLEG_1 ).angle ) /Fcount;
	Faddrlj2 = ( 0-WorldModel::instance().getHJoint ( JID_RLEG_2 ).angle ) /Fcount;
	Faddrlj3 = ( 0-WorldModel::instance().getHJoint ( JID_RLEG_3 ).angle ) /Fcount;
	Faddrlj4 = ( 0-WorldModel::instance().getHJoint ( JID_RLEG_4 ).angle ) /Fcount;
	Faddrlj5 = ( 50.10-WorldModel::instance().getHJoint ( JID_RLEG_5 ).angle ) /Fcount;
	Faddrlj6 = ( 0-WorldModel::instance().getHJoint ( JID_RLEG_6 ).angle ) /Fcount;
	Faddlaj1 = ( -77.86-WorldModel::instance().getHJoint ( JID_LARM_1 ).angle ) /Fcount;
	Faddlaj2 = ( 0-WorldModel::instance().getHJoint ( JID_LARM_2 ).angle ) /Ffcount;
	Faddlaj3 = ( 0-WorldModel::instance().getHJoint ( JID_LARM_3 ).angle ) /Fcount;
	Faddlaj4 = ( 0-WorldModel::instance().getHJoint ( JID_LARM_4 ).angle ) /Fcount;
	Faddraj1 = ( -77.86-WorldModel::instance().getHJoint ( JID_RARM_1 ).angle ) /Fcount;
	Faddraj2 = ( 0-WorldModel::instance().getHJoint ( JID_RARM_2 ).angle ) /Fcount;
	Faddraj3 = ( 0-WorldModel::instance().getHJoint ( JID_RARM_3 ).angle ) /Fcount;
	Faddraj4 = ( 0-WorldModel::instance().getHJoint ( JID_RARM_4 ).angle ) /Fcount;
	Fcount--;

}


void StandUp::fastFrontAddValue()
{
        FfaddHj1=(0 - WorldModel::instance().getHJoint(JID_HEAD_1).angle)/Ffcount;
        FfaddHj2=(0 - WorldModel::instance().getHJoint(JID_HEAD_2).angle)/Ffcount;
        Ffaddllj1=(0-WorldModel::instance().getHJoint(JID_LLEG_1).angle)/Ffcount;
        Ffaddllj2=(0-WorldModel::instance().getHJoint(JID_LLEG_2).angle)/Ffcount;
        Ffaddllj3=(3.75-WorldModel::instance().getHJoint(JID_LLEG_3).angle)/Ffcount;
        Ffaddllj4=(0-WorldModel::instance().getHJoint(JID_LLEG_4).angle)/Ffcount;
        Ffaddllj5=(-5.74-WorldModel::instance().getHJoint(JID_LLEG_5).angle)/Ffcount;
        Ffaddllj6=(0-WorldModel::instance().getHJoint(JID_LLEG_6).angle)/Ffcount;
        Ffaddrlj1=(0-WorldModel::instance().getHJoint(JID_RLEG_1).angle)/Ffcount;
        Ffaddrlj2=(0-WorldModel::instance().getHJoint(JID_RLEG_2).angle)/Ffcount;
        Ffaddrlj3=(3.75-WorldModel::instance().getHJoint(JID_RLEG_3).angle)/Ffcount;
        Ffaddrlj4=(0-WorldModel::instance().getHJoint(JID_RLEG_4).angle)/Ffcount;
        Ffaddrlj5=(-5.74-WorldModel::instance().getHJoint(JID_RLEG_5).angle)/Ffcount;
        Ffaddrlj6=(0-WorldModel::instance().getHJoint(JID_RLEG_6).angle)/Ffcount;
        Ffaddlaj1=(-90.0-WorldModel::instance().getHJoint(JID_LARM_1).angle)/Ffcount;
        Ffaddlaj2=(0-WorldModel::instance().getHJoint(JID_LARM_2).angle)/Ffcount;
        Ffaddlaj3=(0-WorldModel::instance().getHJoint(JID_LARM_3).angle)/Ffcount;
        Ffaddlaj4=(0-WorldModel::instance().getHJoint(JID_LARM_4).angle)/Ffcount;
        Ffaddraj1=(-90.0-WorldModel::instance().getHJoint(JID_RARM_1).angle)/Ffcount;
        Ffaddraj2=(0-WorldModel::instance().getHJoint(JID_RARM_2).angle)/Ffcount;
        Ffaddraj3=(0-WorldModel::instance().getHJoint(JID_RARM_3).angle)/Ffcount;
        Ffaddraj4=(0-WorldModel::instance().getHJoint(JID_RARM_4).angle)/Ffcount;
        Ffcount--;
	if (Ffcount<1)
		Ffcount = 46;
}

bool  StandUp::setInitialStandUpFront(){
	AngularMotor::instance().clear();
	frontAddValue();
	AngularMotor::instance().moveHead(FaddHj1,FaddHj1);
	AngularMotor::instance().moveArm(right_side, Faddraj1, Faddraj2, Faddraj3, Faddraj4);
	AngularMotor::instance().moveLeg(right_side, Faddrlj1, Faddrlj2, Faddrlj3, Faddrlj4, Faddrlj5, Faddrlj6);
	AngularMotor::instance().moveArm(left_side, Faddlaj1, Faddlaj2, Faddlaj3, Faddlaj4);
	AngularMotor::instance().moveLeg(left_side, Faddllj1, Faddllj2, Faddllj3, Faddllj4, Faddllj5, Faddllj6);
	return true;
}



bool  StandUp::setInitialStandUpFastFront(){
	AngularMotor::instance().clear();
	fastFrontAddValue();
	AngularMotor::instance().moveHead(FfaddHj1,FfaddHj1);
	AngularMotor::instance().moveArm(right_side, Ffaddraj1, Ffaddraj2, Ffaddraj3, Ffaddraj4);
	AngularMotor::instance().moveLeg(right_side, Ffaddrlj1, Ffaddrlj2, Ffaddrlj3, Ffaddrlj4, Ffaddrlj5, Ffaddrlj6);
	AngularMotor::instance().moveArm(left_side, Ffaddlaj1, Ffaddlaj2, Ffaddlaj3, Ffaddlaj4);
	AngularMotor::instance().moveLeg(left_side, Ffaddllj1, Ffaddllj2, Ffaddllj3, Ffaddllj4, Ffaddllj5, Ffaddllj6);
	return true;
}
 
bool  StandUp::setInitialStandUpBack(){
	AngularMotor::instance().clear();
	backAddValue();
	AngularMotor::instance().moveHead(BaddHj1,BaddHj1);
	AngularMotor::instance().moveArm(right_side, 2*Baddraj1, 2*Baddraj2, 2*Baddraj3, 2*Baddraj4);
	AngularMotor::instance().moveLeg(right_side, 2*Baddrlj1, 2*Baddrlj2, 2*Baddrlj3, 2*Baddrlj4, 2*Baddrlj5, 2*Baddrlj6);
	AngularMotor::instance().moveArm(left_side, 2*Baddlaj1, 2*Baddlaj2, 2*Baddlaj3, 2*Baddlaj4);
	AngularMotor::instance().moveLeg(left_side, 2*Baddllj1, 2*Baddllj2, 2*Baddllj3, 2*Baddllj4, 2*Baddllj5, 2*Baddllj6);
	return true;
}


bool  StandUp::isStandUpFinished(){
return standupFinished;
}

bool  StandUp::compare(int i,EJointID EJID){
if( (Temp[i].Befor() - WorldModel::instance().getHJoint(EJID).angle) > -10000 && (Temp[i].Befor() - WorldModel::instance().getHJoint(EJID).angle) < 10000 )
        return true;
else 
        return false;
}

bool  StandUp::update(int i,EJointID EJID){
Temp[i].Add(WorldModel::instance().getHJoint(EJID).angle);
return true;
}