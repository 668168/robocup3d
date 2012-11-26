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



#include "Skill.h"
#include "Logger.h"
#include "Formation.h"


/*****************************************************************/
/************************** SKILL ********************************/
/*****************************************************************/

Skill::Skill()
{
	
}

Skill::~Skill()
{

}

Vector3f Skill::getPowerForVel( Vector3f driveForce, Vector3f myVel[3], const Vector3f &endVel )
{
	//endVel = NormalizeVel(endVel);
	
	Vector3f ek = endVel - myVel[0];
	Vector3f ek_1 = endVel - myVel[1];
	Vector3f ek_2 = endVel - myVel[2];
	
	Vector3f drivePower;
	drivePower[0] = velPID( ek[0],ek_1[0],ek_2[0] );
	drivePower[1] = velPID( ek[1],ek_1[1],ek_2[1] );
	drivePower[2] = 0;

	//drivePower = normalizeDriveForce( drivePower );//-* no need -- only for test
	
	drivePower = drivePower + driveForce;
	drivePower[2] = 0;

	return normalizeDriveForce( drivePower );
}

const float posPID_thr = 1.9;//1.62;//1.8;

Vector3f Skill::getPowerForVel( const Vector3f &endVel ) const
{
	Vector3f driveForce = WM->getMyDriveForce();
	Vector3f myVel[3];
	myVel[0] = WM->getMyGlobalVel(0);
	myVel[1] = WM->getMyGlobalVel(1);
	myVel[2] = WM->getMyGlobalVel(2);
	
	return getPowerForVel( driveForce, myVel, endVel);
}

float Skill::velPID( float ek, float ek_1, float ek_2 )
{
	const float Kp = 12;//62;
		  float Ki = 10;//100;
	const float Kd = 10;//*5;
	const float A  = 0.4;
	const float B  = 0.1;

	if ( abs(ek) <= B)
		Ki *= 1;
	else
		Ki *= ( A - abs(ek) + B )/A;
	
	float Uk;
	if ( abs(ek) > A )
		Uk = algorithmP( Kp, ek);//P
		//Uk = algorithmPD( Kp, Kd, ek, ek_1, ek_2);//PD
	else
		Uk = algorithmPID( Kp, Ki, Kd, ek, ek_1, ek_2 );//PID

	return Uk;
}

Vector3f Skill::gotoNStop( Vector3f driveForce, Vector3f myVel[3], Vector3f myPos[3], Vector3f endPos )
{	
	Vector3f ek = endPos - myPos[0];
	Vector3f ek_1 = endPos - myPos[1];
	Vector3f ek_2 = endPos - myPos[2];
	
	Vector3f drivePower,driveSpeed;
	if ( ek.Length() < posPID_thr )
	{
		driveSpeed[0] = posPID( ek[0],ek_1[0],ek_2[0]) + (myVel[0])[0];
		driveSpeed[1] = posPID( ek[1],ek_1[1],ek_2[1]) + (myVel[0])[1];
		LOG( 12,"driveSpeed: %f, %f",driveSpeed.x(),driveSpeed.y());
	}
	else
	{
		driveSpeed = setVector3fLength( ek, 10);
		LOG( 12,"full speed!");
	}
	driveSpeed[2] = 0;
	
	drivePower = getPowerForVel( driveForce, myVel, driveSpeed );
	drivePower.z() = 0;
	
	return normalizeDriveForce(drivePower);
}

Action Skill::gotoNStop( const Vector3f &endPos ) const
{
	Vector3f driveForce = WM->getMyDriveForce();
	Vector3f myPos[3], myVel[3];
	myPos[0] = WM->getMyGlobalPos(0);//WM->getMyGlobalPos(0*20);//-* need more test
	myPos[1] = WM->getMyGlobalPos(1);//WM->getMyGlobalPos(1*20);
	myPos[2] = WM->getMyGlobalPos(2);//WM->getMyGlobalPos(2*20);
	myVel[0] = WM->getMyGlobalVel(0);//WM->getMyGlobalVel(0*20);
	myVel[1] = WM->getMyGlobalVel(1);//WM->getMyGlobalVel(1*20);
	myVel[2] = WM->getMyGlobalVel(2);//WM->getMyGlobalVel(2*20);

	Action act;
	Vector3f power = gotoNStop( driveForce, myVel, myPos, endPos );
	act.setDriveForce( power );
	act.setTime( WM->getRealTime() );
	return act;
}

Vector3f Skill::gotoWithMinSpeed( Vector3f driveForce, Vector3f myVel[3], Vector3f myPos[3], Vector3f endPos, float minSpeed )
{
	Vector3f ek = endPos - myPos[0];
	ek.z() = 0;
	Vector3f ek_1 = endPos - myPos[1];
	Vector3f ek_2 = endPos - myPos[2];
	
	Vector3f drivePower,driveSpeed;
	if ( ek.Length() < posPID_thr )
	{
		driveSpeed[0] = posPID( ek[0],ek_1[0],ek_2[0]) + (myVel[0])[0];
		driveSpeed[1] = posPID( ek[1],ek_1[1],ek_2[1]) + (myVel[0])[1];
	}
	else
	{
		driveSpeed = setVector3fLength( ek, 10);
	}
	driveSpeed[2] = 0;
	
	//-* differnt with gotoNStop
	if ( driveSpeed.Length() < minSpeed )
		driveSpeed = setVector3fLength( ek,minSpeed );
	LOG( 12,"driveSpeed: %f, %f, :",driveSpeed.x(),driveSpeed.y());
	//float max_agent_speed = 10;
	//if ( ek.Length()>1.5 ) driveSpeed = setVector3fLength(driveSpeed,max_agent_speed);
	
	drivePower = getPowerForVel( driveForce, myVel, driveSpeed );
	
	return normalizeDriveForce(drivePower);
	
}

Action Skill::gotoWithMinSpeed( Vector3f endPos, float minSpeed )
{
	Vector3f driveForce = WM->getMyDriveForce();
	Vector3f myPos[3], myVel[3];
	myPos[0] = WM->getMyGlobalPos(0);//WM->getMyGlobalPos(0*20);//-* need more test
	myPos[1] = WM->getMyGlobalPos(1);//WM->getMyGlobalPos(1*20);
	myPos[2] = WM->getMyGlobalPos(2);//WM->getMyGlobalPos(2*20);
	myVel[0] = WM->getMyGlobalVel(0);//WM->getMyGlobalVel(0*20);
	myVel[1] = WM->getMyGlobalVel(1);//WM->getMyGlobalVel(1*20);
	myVel[2] = WM->getMyGlobalVel(2);//WM->getMyGlobalVel(2*20);

	Action act;
	Vector3f power = gotoWithMinSpeed( driveForce, myVel, myPos, endPos, minSpeed );
	act.setDriveForce( power );
	act.setTime( WM->getRealTime() );
	return act;
}

float Skill::posPID( float ek, float ek_1, float ek_2)
{
	const float Kp = 5.5;//4;//8;//5;//10;//15;//*3;//4;//km=5;
		  float Ki = 0.47;//0.48;//0.45;//0.5;//0.4;//2.0;//1.0;//*0.4;//0.35;//0.3;//0.4;//0.6;//0.8;//1;//2;//3;//*0.574;//0.287*2;
	const float Kd = 1.0;//0.5;//2;//1.0;//3;//2;//1.5;//1.0;//0.8;//1.0;//1.1;//1.2;//1.5;//2;//1;//*0.5233;//0.785/1.5;	
	const float A  = posPID_thr;//1.5;
	const float B  = 0.1;

	if ( abs(ek) <= B)
		Ki *= 1;
	else
		Ki *= ( A - abs(ek) + B )/A;
	
	float Uk;
	if ( abs(ek) > A )
		Uk = algorithmP( Kp, ek);//P
	else 
		Uk = algorithmPID( Kp, Ki, Kd, ek, ek_1, ek_2 );//PID
	
	return Uk;
}

Action Skill::runStrategicPos() const
{
	return runStrategicPos( WM->getBallGlobalPos());
}

Action Skill::runStrategicPos( const Vector3f &posBall) const
{
	int num = WM->getMyNum();
	Vector3f posStrategic = FM->getStrategicPosition( num, posBall );
	return gotoNStop( posStrategic );	
}

//-* the old intercept, which is good in defence
Action Skill::interceptBall0( Vector3f goal )
{
	Vector3f posIntercept = WM->getInterceptPos( goal );
	posIntercept = projectInterceptPos( posIntercept );
	Vector3f velEnd(0,0,0);
	return runTo( posIntercept, velEnd );
}

Action Skill::interceptBall( Vector3f goal, const bool isKicking)  const
{
	//-* const
	//-- const of close intercept
	const float dist_close_intercept = 1.87;//1.33;//1.87;//1.0f;
	const AngDeg ang_close_intercept = 20.42;//18.83;//20.42;//22.5f;
	const AngDeg velAng_close_intercept = 5.62;//18.95;//5.62;//45.0f;
	const float ball_stop_vel = 1.02;//1.14;//1.02;//1.5f;
	//-- const of my end vel
	const float my_min_end_speed = 0.52;//0.19;//0.52;//0.35f;
	
	Vector3f posInterceptBall = WM->getInterceptBallPos();
	Vector3f posKick = WM->getInterceptPos( goal );
	bool isClostIntercept = false;
	// close intercept
	if ( (WM->getMyGlobalPos()-WM->getBallGlobalPos()).Length() < dist_close_intercept//1.0f 
		&& isThreePointOneLine(WM->getMyGlobalPos(),WM->getBallGlobalPos(),goal,ang_close_intercept)//22.5)//15)
		&& abs(getClipAng(WM->getBallGlobalVel(),WM->getMyGlobalPos()-goal)) < velAng_close_intercept//45
		&& WM->isBallStop(ball_stop_vel)//(1.5f)//(1.0f)//(0.5f)
		)
	{
		isClostIntercept = true;
		posInterceptBall = WM->getBallGlobalPos();
		posKick = posInterceptBall + (goal-posInterceptBall).Normalized()*kick_pos_dist;
	}
	
	AngDeg dribbleAng = getVector3fHorizontalAng(goal-posInterceptBall);
	Vector3f newPos = projectDribblePos(WM->getMyGlobalPos(),
											posInterceptBall,
											dribbleAng);
	LOG( 14,"posInterceptBall: %f, %f, %f",posInterceptBall.x(),posInterceptBall.y(),posInterceptBall.z());
	LOG( 14,"newPos: %f, %f %f",newPos.x(),newPos.y(),newPos.z());

	// for dribble test
	// kick_margin/sim_cycle_time
	float minSpeed = my_min_end_speed;//0.35;
	float speedK = cosDeg(getClipAng(WM->getMyGlobalPos(),newPos,goal));
	minSpeed *= speedK;
	Vector3f velEnd(0,0,0);
	velEnd = goal - posKick;
	velEnd = setVector3fLength( velEnd, minSpeed);
	Action driveAction = runTo( newPos, velEnd );
	
	//-* 2005-11-12
	// very close to the ball, need turn around ball
	/*if ( (WM->getMyGlobalPos()-WM->getBallGlobalPos()).Length() < dist2ball_turn_around//0.35f 
		&& (WM->getMyGlobalPos()-posKick).Length() < dist2kickPos_turn_around//0.35f
		)
	{
		AngDeg angErr = getClipAng(goal-WM->getBallGlobalPos(),WM->getBallGlobalPos()-WM->getMyGlobalPos());
		bool turnClockWise = ( angErr < 0 );
		driveAction = turnAroundPos(WM->getBallGlobalPos(),radious_turn_around,turnClockWise);
	}
	*/
	//-* 2005-11-13
	// ready to kick, dash to the ball
	if ( (  isKicking || shoudIKick(goal))
		&& isClostIntercept )
	{
		driveAction = dashToBall();
	}
	
	return driveAction;
}

Vector3f Skill::projectInterceptPos( Vector3f posIntercept ) const
{
	//-* geometry algorithm-------------------------
	const float block_dist = 0.4;//0.4;//0.33;
	Vector3f posMe = WM->getMyGlobalPos();
	Vector3f posBall = WM->getBallGlobalPos();
	//-* just now, consider 2D only;
	posMe[2] = posBall[2] = posIntercept[2] = 0;
	
	//-* may block the ball
	float distIntercept = ( posIntercept-posMe).Length();
	//LOG( 12,"posBall: %f,%f,%f \tvelBall: %f,%f,%f",posBall[0],posBall[1],posBall[2],WM->getBallGlobalVel()[0],WM->getBallGlobalVel()[1],WM->getBallGlobalVel()[2]);
	//LOG( 12,"distIntercept:%f",distIntercept);
	//LOG( 12,"distToBall:%f",(posBall-posMe).Length() );
	//float const ball_vel_thr = 1.0;
	if ( isThreePointOneLine( posMe, posBall, posIntercept, 90 )
		&& ( distIntercept - (posBall-posMe).Length() > WM->getBallRadius()*2 ) 
		)
	{
		//LOG( 12,"may block");
		float dist = getDistToLine( posBall, posMe, posIntercept );
		//LOG( 12,"dist:%f",dist);
		if ( fabs(dist) < block_dist )//-* block
		{
			//LOG( 12,"block!!!!");
			AngDeg direction = getVector3fHorizontalAng( posIntercept - posMe );
			//LOG( 12,"direction:%f",direction);
			direction += sign( dist ) * Rad2Deg( block_dist / distIntercept );
			//LOG( 12,"new direction:%f",direction);
			direction = normalizeAngle( direction );
			//LOG( 12,"new direction:%f",direction);
			VisionSense pol;
			pol.distance = distIntercept;
			pol.theta = direction;
			pol.phi = 0;
			posIntercept = posMe + getPosRelativeFromVision( pol );
		}
	}
	
	posIntercept.z() = WM->getMyRadius();
	//LOG( 12,"new distIntercept:%f", (posMe-posIntercept).Length());
	//LOG( 12,"new dist:%f",getDistToLine(posBall,posMe,posIntercept));
	return posIntercept;
}

Action Skill::runTo( const Vector3f &endPos, const Vector3f &endVel ) const
{
	Action act;
	act.setTime( WM->getRealTime() );
	act.setDriveForce( runTo( WM->getMyGlobalPos(), WM->getMyGlobalVel(), endPos, endVel) );
	return act;
}

Vector3f Skill::runTo( const Vector3f &beginPos, const Vector3f &beginVel, const Vector3f &endPos, const Vector3f &endVel) const
{
	//const float minPowerOneAxes = 0.1;//meaning 10% of maxPower
	const float maxPower = max_drive_force;
	Vector3f direction = endPos - beginPos;
	if ( direction.Length() < 0.005 ) return Vector3f(0,0,0);
	Vector3f power = direction.Normalized();
	power.x() = abs( power.x());//max( minPowerOneAxes, abs( power.x()));
	power.y() = abs( power.y());//max( minPowerOneAxes, abs( power.y()));
	power.x() *= getRunPower( beginPos.x(),beginVel.x(),endPos.x(),endVel.x(),maxPower);
	power.y() *= getRunPower( beginPos.y(),beginVel.y(),endPos.y(),endVel.y(),maxPower);
	power.z() = 0;
	return power;
}

float Skill::getRunPower( const float &x0, const float &v0, const float &xf, const float &vf, const float &maxPower) const
{
	const float u = 62;
	const float m = 30;
	//-* float t1 = ((xf-x0)*u +(vf-v0)*m)*0.5/maxPower;
	//-- float f = t1/sim_cycle_time*maxPower;
	//-- make it simple @2005-11-20-by-XuYuan
	float f = ((xf-x0)*u +(vf-v0)*m)*0.5/sim_cycle_time;
	if ( abs(f) < maxPower )
	{
		f = ( 2/(1+exp(-2.5*f/maxPower))-1 )*maxPower;//2//5//3
		//f = ( 0.5/( 1+( exp( -abs(f) ) ) ) )*maxPower*sign(f);
	}
	
	return setMaxNMin(f,maxPower,-maxPower);
}

//2005-10-25
float Skill::changeSpeed( const float &v0, const float &v1, const float &maxF, float &d, Time &t)
{
	//- const
	const float v_gap = 0.5;//0.3;
	const float m=30;
	const float u=maxF/( real_agent_max_speed + 0.01);//62;

	float f=0;
	t=0;
	d=0;
	if ( abs( v1-v0 ) < v_gap )
	{
    	f = u*v1;
    	t= sim_cycle_time;
    	d= v1*sim_cycle_time;
	}
	else
	{
    	if ( v1 > v0 )
        	f = maxF;
    	else
        	f = -maxF;

    	t = m/u*log((u*v0-f)/(u*v1-f));
    	//d = m/u*(v0-f/m)*(1-exp(-u/m*t))+f/u*t;
		d = m/u*(v0-f/u)*(1-exp(-u/m*t))+f/u*t;
	}
	//LOG( 13,"cd: v0=%f, v1=%f, f=%f",v0,v1,f);
	//LOG( 13,"cs: t=%f ,(u*v0-f)/(u*v1-f)=%f",t,(u*v0-f)/(u*v1-f));
	return f;
}

float Skill::driveTo( const float &x0, const float &v0, const float &xf, const float &vf, const float &maxF, Time &t)
{
	//- const
	const float maxSpeed = real_agent_max_speed*maxF/max_drive_force;
	const float v_gap = 0.1;
	//const float x_gap = 0.1;//0.05;

	//- init
	float f=0;
	float d=0;
	t=0;
	float dist = abs(xf-x0);
	float f_brake,f_dash;
	if ( vf*(xf-x0)<0 ) //-- not the same direction
	{
		float tBack = 0.0f;
		changeSpeed(0.0f,vf,maxF,d,tBack);
		float new_xf = xf - d;
		f = driveTo(x0,v0,new_xf,0.0f,maxF,t);
		t += tBack;
	}
	else //-- the same direction
	{
		f_brake = changeSpeed(v0,vf,maxF,d,t);
		if ( abs(d) >= dist )//--brake
    		f = f_brake;
		else//-- fish dash, then brake
		{
			float vm;
			float d1=0;
			float d2=0;
			Time t1=0;
			Time t2=0;
			if ( dist > 2 )
        		vm = sign(xf-x0)*maxSpeed;
    		else
			{
        		float vr = sign(xf-x0)*(maxSpeed+v_gap);
        		float vl = 0;
        		while ( abs( vl-vr ) > v_gap )
				{
            		vm = ( vl + vr )*0.5;
            		f_dash = changeSpeed(v0,vm,maxF,d1,t1);
            		f_brake = changeSpeed(vm,vf,maxF,d2,t2);
            		if ( abs( d1+d2 ) > dist )
                		vr = vm;
            		else
                		vl = vm;
				}
			}
    		f_dash = changeSpeed(v0,vm,maxF,d1,t1);
    		f_brake = changeSpeed(vm,vf,maxF,d2,t2);
    		float tm = ( dist - abs(d1+d2) )/abs(vm);
    		t = t1+tm+t2;
    		f= f_dash;
		}
	}
	
	return setMaxNMin(f,maxF,-maxF);
}

Vector3f Skill::driveTo( const Vector3f &beginPos, const Vector3f &beginVel, const Vector3f &endPos, const Vector3f &endVel,Time &time)
{
	const float maxPower = max_drive_force;
	Vector3f direction = endPos - beginPos;
	//if ( direction.Length() < 0.05 ) return Vector3f(0,0,0);
	Vector3f power = direction.Normalized();
	float fx = abs( power.x())*maxPower;
	float fy = abs( power.y())*maxPower;
	
	Time tx=0,ty=0;
	power.x() = driveTo( beginPos.x(),beginVel.x(),endPos.x(),endVel.x(),fx,tx);
	power.y() = driveTo( beginPos.y(),beginVel.y(),endPos.y(),endVel.y(),fy,ty);
	power.z() = 0;
	time = max(tx,ty);
	//LOG( 13,"tx=%f, ty=%f, drive_t = %f",tx,ty,time);
	return power;
}

Action Skill::driveTo( const Vector3f &endPos, const Vector3f &endVel, Time &time) const
{
	Action act;
	act.setTime( WM->getRealTime() );
	act.setDriveForce( driveTo( WM->getMyGlobalPos(), WM->getMyGlobalVel(), endPos, endVel, time) );
	return act;
}

//2005-10-30-by-XuYuan
//-* this function use a geometry alogrithm to project a run position
//-- when the agent trying to dribble
Vector3f Skill::projectDribblePos( const Vector3f &posPlayer, const Vector3f &posBall,  const AngDeg &ang ) const
{
	//-* const
	//const float max_project_dist = 2;
	//const AngDeg ang_error_thr = 10;
	
	const float max_dist_2_ball = 0.5;//1.0;//0.5;//1.0;//0.981179;//1.0;
	const float cut_point_dist_to_ball = 0.3;//0.292476;//0.5;
	const float cut_circle_radius = 0.5;//0.507844;//0.5;
	
	
	Vector3f posI;
	Vector3f L1 = posBall - posPlayer;
	L1.z() = 0;
	AngDeg angL1 = getVector3fHorizontalAng(L1);
	AngDeg k = normalizeAngle(angL1-ang);
	float dL1 = L1.Length();
	float dL2 = 0;

	if ( isAngInInterval( k,-70, 70 ) )
	{
		LOG( 14,"projectDribblePos:zhong chui xian");
		dL2 = dL1*0.5/cosDeg(k);
		if ( dL2>max_dist_2_ball)
		{
			dL2 = max_dist_2_ball;
		}
		else
		{
			dL2 = kick_pos_dist;
		}
		//dL2 = (1-exp(-dL2))*max_dist_2_ball;
		//dL2 = max(dL2,kick_pos_dist);
		posI = posBall - getPosRelativeFromVision(VisionSense(dL2,ang,0.0f));
	}
	else
	{
		LOG( 14,"projectDribblePos:qie ru yuan");
		Vector3f posC = posBall - getPosRelativeFromVision(VisionSense(cut_point_dist_to_ball,ang,0.0f));
		AngDeg angOC = ang - sign(k)*90;
		Vector3f posO = posC + getPosRelativeFromVision(VisionSense(cut_circle_radius,angOC,0.0f));
		if ( abs( posC.x()-posPlayer.x() ) < EPSILON )
		{
			LOG( 14,"projectDribblePos:chui zhi");
			posI.y() = ( posPlayer.y()+posC.y())*0.5;
			posI.x() = posO.x()-sign(ang)*sqrt(pow2(cut_circle_radius)-pow2(posI.y()-posO.y()));
		}
		else
		{
			LOG( 14,"projectDribblePos:not chui zhi");
			float kL1 = ( posPlayer.y()-posC.y())/(posPlayer.x()-posC.x());
			float a = pow2(kL1)+1;
			float b = 2*kL1*posO.x()-2;
			float c = pow2(posO.x())+pow2(posO.y())-pow2(cut_circle_radius);
			float delta = pow2(b)-4*a*c;
			LOG( 14,"k=%f, a=%f, b=%f, c=%f, delta:",kL1,a,b,c,delta);
			if ( delta >= 0 )
			{
				posI.y() = (-b-sign(k)*sqrt(delta))/a*0.5;
				posI.x() = -kL1*posI.y();
			}
			else//-- no root
			{
				posI = (posC+posO)*0.5;
			}
		}
		//-new add @2005-11-05
		//- inorder to smooth the point
		if ( isAngInInterval( k,70, 110 ) || isAngInInterval( k,-110, -70 ) )
		{
			Vector3f posImax = posBall - getPosRelativeFromVision(VisionSense(max_dist_2_ball,ang,0.0f));
			posI = ( posImax + posI )*0.5;
		}
	}
	posI.z() = WM->getMyRadius();
	return posI;
}

//2005-11-01-by-XuYuan
/*! this function generate an action which makes the agent to kick the ball
	1. run to the kick position
	2. should I kick?
	*TODO*
	the maxErrAng should depend on the suitation and opponent model
*/
Actions Skill::kickTo( const Vector3f &goal ,const float kickForce,const AngDeg kickAng, const AngDeg maxAngErr) const
{
	Actions kickToAction;
	
	Time kickTime = WM->getRealTime();
	bool isKicking = shoudIKick(goal,maxAngErr);
	if ( isKicking )
	{
		Action kickAction;
		kickAction.setTime(kickTime);
		kickAction.setKick(kickAng,kickForce);
		for ( Step i=0; i<step_num_per_cycle; i+=2 )
		{
			kickAction.setTime( kickTime+i );
			kickToAction += kickAction;
		}
	}
	/*else
	{
		Vector3f posBall=WM->getBallGlobalPos();
		Vector3f posAttack=posBall-goal;
		posAttack=goal+posAttack*1.009;
		Action driveAction=interceptBall(posAttack,1);
		
	}*/

	Action driveAction = interceptBall(goal,isKicking);
	kickToAction += driveAction;
	
	return kickToAction;
}

bool Skill::shoudIKick( const Vector3f &goal, const AngDeg maxAngErr ) const
{
	//-* const
	//const AngDeg max_ang_err = 12;//6;
	
	Vector3f posMe = WM->getMyGlobalPos();
	Vector3f posBall = WM->getBallGlobalPos();
	//-* if the ball is just above my head, the angle error is too big
	//-* so, i should not kick at this time
	if ( (pow2(posBall.x()-posMe.x())+pow2(posBall.y()+posMe.y())) < 0.03 )
	{
		return false;
	}
	
	return isThreePointOneLine(posMe,posBall,goal,maxAngErr);
}

/*! calculate the needed kick force by a physical formulate
	f=u*v=m*a=m*v'  --> v(t) = C*exp(-u*t/m)
	d = Sigma[v(t)]=-m/u*(vf-v1) --> v1 = u*d/m + vf
	k*F*t = m*(v1-v0) --> F = m*(u*d/m+vf-v0)/k/t = (u*d+m*(vf-v0))/k/t
	\param kick dist
	\param the speed of ball before kick
	\param the speed of ball when it reach the dist,meaning end speed
	\return the kick force
*/
float Skill::calGroundKickForce( const float &dist, const float &v0, const float &vf ) const
{
	return ( ground_friction_factor*dist + WM->getBallMass()*(vf-v0))/kick_effect_time/kick_force_factor;
}

/*! compute a good approximation of need power
	see RoboLog
	\param kick distance
	\return kick force
*/
float Skill::calGroundKickForce( const float &dist) const
{

	float f = (0.02518+sqrt(0.00063-0.0137*(0.41129-dist)))/(0.00685);
	return setMaxNMin(f,max_kick_force,0.0f);
}

/*! dribble -- only test version
	kick when can kick, so keep controling the ball
	allow the kick ang is not point to the goal, only try to keep kicking
	\param goal position
	\return actions of kick and drive
*/
Actions Skill::dribble( const Vector3f &goal ) const
{
//	if(!WM->isSpaceAhead(goal))
//	{
//		return kickTo(Vector3f(45,45,0));
//	}
    if ( isThreePointOneLine( WM->getMyGlobalPos(),WM->getInterceptBallPos(),goal,15 ) )
	{
	return fastDribble(goal);
	}
	//else
	//{
	//-* drive action

//	Action driveAction = interceptBall(goal);
//	driveAction.setTime(WM->getRealTime());
//	driveAction.setActionType(ACT_DRIVE);
//	kickToAction += driveAction;
	else
	{
		Actions kickToAction;
/*		Num oppNum = WM->getClosestOppNum2Ball();
		Vector3f posOpp = WM->getOpponentGlobalPos(oppNum);
		Vector3f velOpp = WM->getOpponentGlobalVel(oppNum);
		Vector3f posBall = WM->getBallGlobalPos();
		Vector3f velBall = WM->getBallGlobalVel();
		float opp2Ball = pow2(posOpp[0] - posBall[0]) + pow2(posOpp[1] - posBall[1]);
		if(opp2Ball < 2.5 && posOpp[0] < posBall[0] && false)
		{
			Vector3f posTemp = (posBall - posOpp).Normalized();
			posTemp += posBall;
			kickToAction += interceptBall(posTemp);
		}
		else		
*/		kickToAction += interceptBall(goal);
	//-* kick action
		if(WM->getBallGlobalVel().x() < 0.5f)//getBallRelativePos().x()<1)//
		{
//		cout<<WM->getGameTime()<<vel<<endl;
			Action kickAction;
			kickAction.setTime(WM->getRealTime());
			kickAction.setKick(0,14.0f);
			kickToAction += kickAction;
		}

//	kickAction.setKick(20,15);//20);

	
		return kickToAction;
	}
}

/*! turn around a position
	\param the center position of the cycle 
	\param the radious of the cycle
	\param the trun direction
	\return the drive action
*/
Action Skill::turnAroundPos( const Vector3f &pos, const float &radious, bool clockWise ) const
{
	const AngDeg turnAng = 33.63;//20.0f;//20.0f;//10.0f;
	const float turnSpeed = 3.03;//6;
	
	Vector3f relPos = WM->getMyGlobalPos() - pos;
	AngDeg ang2Pos = getVector3fHorizontalAng(relPos);
	AngDeg incAngle = (clockWise? -turnAng:turnAng);
	AngDeg newAng = normalizeAngle( ang2Pos+incAngle);
	AngDeg newNewAng = normalizeAngle( newAng+incAngle);
	Vector3f newPos,newNewPos;
	newPos = pol2xyz(VisionSense(radious,newAng,0.0f)) + pos;
	newNewPos = pol2xyz(VisionSense(radious,newNewAng,0.0f)) + pos;
	Vector3f vel = newNewPos - newPos;
	vel.z() = 0;
	vel.Normalized();
	vel*=turnSpeed;
	LOG( 15,"turnforce: %f",runTo(newPos,vel).getDriveForce().Length());
	return runTo(newPos,vel);
}

/*! direct pass to teammate
	only kick to teammate's position
	\param teammate's num
	\return pass actions
*/
Actions Skill::directPass( Num num )
{
	//if (WM->getMyFreedom()<3)
	//{
	//	return fastPass(num);
	//}
	//return pass(num);
	
	Vector3f posTeammate = WM->getTeammateGlobalPos(num);
	Vector3f posBall = WM->getBallGlobalPos();
	Vector3f attack = WM->getOppGoalCenter() - posTeammate;
	attack.Normalize();
	attack*=(0.1*(posBall-posTeammate).Length());
	attack+=posTeammate;
	float kickForce = calGroundKickForce((attack-posBall).Length());
	
	return kickTo((WM->getOppGoalCenter()+posTeammate)/2,kickForce,0,15);

}

/*! dash to the direction by max drive power
	it is needed when try kick and direct dash
	\param dash aim pos
	\return drive power
*/
Action Skill::dashTo( const Vector3f &pos)const
{
	AngDeg dashDir = getVector3fHorizontalAng(pos-WM->getMyGlobalPos());
	Vector3f endVel = pol2xyz(Polar(real_agent_max_speed,dashDir,0.0f));
	return runTo( pos,endVel);
}

/*! no predicat, just dash to the ball's current position
	\return drive action
*/
Action	Skill::dashToBall() const
{
	return dashTo(WM->getBallGlobalPos());
}

/*! this skill enable the agent kick the ball between two goals
	this is useful in shoot
	\param two goals
	\return actions of drive and kick
*/
Actions Skill::kickBetween( const  Vector3f &goalLeft, const Vector3f &goalRight, const float kickForce, const AngDeg kickAng) const
{
	Actions kickToAction;
	//-* kick action
	Time kickTime = WM->getRealTime();
	bool isKicking = false;
	if ( shoudIKick(goalLeft,goalRight) )
	{
		LOG( 17,"kicking!!!!!");
		Action kickAction;
		kickAction.setTime(kickTime);
		kickAction.setKick(kickAng,kickForce);
		for ( Step i=0; i<step_num_per_cycle; i+=step_num_per_kick )
		{
			kickAction.setTime( kickTime+i );
			kickToAction += kickAction;
		}
		isKicking = true;
	}
	
	//-* drive action
	LOG( 17,"driveAction");
	Vector3f posInterceptBall = WM->getInterceptBallPos();
	const AngDeg angLeft = normalizeAngle(getVector3fHorizontalAng(goalLeft-posInterceptBall));
	const AngDeg angRight = normalizeAngle(getVector3fHorizontalAng(goalRight-posInterceptBall));
	const AngDeg angBisector = getBisectorTwoAngles(angLeft,angRight);
	Vector3f goal = pol2xyz(VisionSense(10.0f,angBisector,0))+posInterceptBall;
	Action driveAction = interceptBall(goal,isKicking);	
	kickToAction += driveAction;

	return kickToAction;
}

bool Skill::shoudIKick( const Vector3f &goalLeft, const Vector3f &goalRight) const
{
	LOG( 17,"shoudIKick");
	
	Vector3f posBall = WM->getBallGlobalPos();
	Vector3f posMe = WM->getMyGlobalPos();
	//-* if the ball is just above my head, the angle error is too big
	//-* so, i should not kick at this time
	if ( (pow2(posBall.x()-posMe.x())+pow2(posBall.y()+posMe.y())) < 0.03 )
	{
		return false;
	}
	
	if ( (goalLeft-posBall).Length() > max_kick_distance
		&& (goalRight-posBall).Length() > max_kick_distance
		)//-* too far away
	{
		return shoudIKick(0.5f*(goalLeft+goalRight));//(shoudIKick(goalLeft)||shoudIKick(goalRight));
	}
	else
	{
		AngDeg angLeft = getVector3fHorizontalAng(goalLeft-posBall);
		AngDeg angRight = getVector3fHorizontalAng(goalRight-posBall);
		AngDeg angHeading = getVector3fHorizontalAng(posBall-posMe);
		
		AngDeg angClip = normalizeAngle(angLeft-angRight );
		if ( angClip < 0 )
		{
			swap(angLeft,angRight);
		}
		
		return isAngInInterval(angHeading,angRight,angLeft);
	}
}

Action Skill::interceptClearBall() const
{
	const float interceptFreeChange = 0;//-1.3;//gene1[5];//0
	const float interceptFree = -1.0f;//-0.55f;//gene1[6];//-0.5f
	if ( ( WM->getMyFreedomChange() > interceptFreeChange)
		|| WM->getMyFreedom() > interceptFree
		)
	{	
		LOG( 18,"my freedom = %f; [%d]",WM->getMyFreedom(),WM->getMyFreeState());
		Vector3f posIntercept = WM->getInterceptPos( WM->getOppGoalCenter() );		
		posIntercept = projectInterceptPos( posIntercept );
		Vector3f velEnd(0,0,0);
		posIntercept = setInterceptPosBeforeGoal(posIntercept);
		return runTo( posIntercept, velEnd );
	}
	else
	{
		Vector3f posIntercept = WM->getInterceptBallPos( );
		posIntercept = setInterceptPosBeforeGoal(posIntercept);
		return dashTo(posIntercept);
	}
}
/*! if the intercept position is after goal, it is no useful,
	so try intercept the ball before goal
	\param the old intercept position
	\return the new intercept position
*/
Vector3f Skill::setInterceptPosBeforeGoal(const Vector3f &posIntercept) const
{
	if ( posIntercept.x() > WM->getOurBaseLine() )
		return posIntercept;
	
	AngDeg angShoot = getVector3fHorizontalAng(posIntercept-WM->getBallGlobalPos());
	Vector3f newPos(0,0,0);
	newPos.x() = WM->getOurBaseLine();
	newPos.y() = WM->getBallGlobalPos().y() - tanDeg(angShoot)*(WM->getBallGlobalPos().x()-newPos.x());
	if ( abs(newPos.y()) > half_goal_width + 0.2 )
		return posIntercept;
	
	return newPos;
}

Actions Skill::clearBall(Num num ) const
{
	Actions clearAction;

	Vector3f posBall = WM->getBallGlobalPos();
	
	Time kickTime = WM->getRealTime();
	if ( canIClear() )
	{
		//-* calculate clear force,can't let the ball out
		float clearForce = max_kick_force;
		float clearDist = WM->getOppBaseLine()-posBall.x();
		if ( 0 == num )
		{
			if ( clearDist < max_kick_distance && (!shoudIKick(WM->getOppGoalLeft(),WM->getOppGoalRight())) )
			{
				clearDist = clearDist/cosDeg(WM->getMyKickHorizontalAng());
				clearForce = clearDist/max_kick_distance*max_kick_force;
			}
		}
		else
		{
			num = selectPass(num);
			clearDist = (WM->getBallGlobalPos()-WM->getTeammateGlobalPos(num)).Length();
			clearForce = calGroundKickForce(clearDist);
		}
		
		//in dangerous area,clear using full force!
		Rectangle danagerArea(WM->getOurBaseLine(),half_penalty_width,WM->getOurBaseLine()+15.0f,-half_penalty_width);
		if ( danagerArea[posBall] ) clearForce = max_kick_force;
		
		Action kickAction;
		kickAction.setTime(kickTime);
		kickAction.setKick(calClearAngle(),100);
		for ( Step i=0; i<step_num_per_cycle; i+=step_num_per_kick )
		{
			kickAction.setTime( kickTime + i );
			clearAction += kickAction;
		}
	}
	Action catchAction;
	catchAction.setTime(WM->getRealTime());
	catchAction.setCatch();
	clearAction += catchAction;
	
	Action driveAction = interceptClearBall();
	clearAction += driveAction;
	

	return clearAction;
}

Actions Skill::goalieClearBall(Num num ) const
{
	Actions clearAction;

	Vector3f posBall = WM->getBallGlobalPos();
	
	Time kickTime = WM->getRealTime();
	if ( canIClear() )
	{
		//-* calculate clear force,can't let the ball out
		float clearForce = 100;
		float clearDist = WM->getOppBaseLine()-posBall.x();
		/*if ( 0 == num )
		{
			if ( clearDist < max_kick_distance && (!shoudIKick(WM->getOppGoalLeft(),WM->getOppGoalRight())) )
			{
				clearDist = clearDist/cosDeg(WM->getMyKickHorizontalAng());
				clearForce = clearDist/max_kick_distance*max_kick_force;
			}
		}
		else*/
		//{
			clearDist = (WM->getBallGlobalPos()-WM->getTeammateGlobalPos(4)).Length();
			clearForce = max_kick_force;
		//}
		
		//in dangerous area,clear using full force!
		Rectangle danagerArea(WM->getOurBaseLine(),half_penalty_width,WM->getOurBaseLine()+15.0f,-half_penalty_width);
		if ( danagerArea[posBall] ) clearForce = max_kick_force;
		
		Action kickAction;
		kickAction.setTime(kickTime);
		kickAction.setKick(calClearAngle(),clearForce);
		for ( Step i=0; i<step_num_per_cycle; i+=step_num_per_kick )
		{
			kickAction.setTime( kickTime + i );
			clearAction += kickAction;
		}
	}
	Action catchAction;
	catchAction.setTime(WM->getRealTime());
	catchAction.setCatch();
	clearAction += catchAction;
	
	Action driveAction = interceptClearBall();
	clearAction += driveAction;
	

	return clearAction;
}

//for test;
Actions Skill::catchBall()
{
	Action catchAction;
	Time catchTime=WM->getRealTime();
	catchAction.setTime(catchTime);
	catchAction.setCatch();
	for (Step i=0;i<step_num_per_cycle;i+=step_num_per_kick)
	{
		catchAction.setTime(catchTime+i);
		catchAction+=catchAction;		
	}
	Action driveAction = SKILL->dashTo(WM->getInterceptBallPos());
	catchAction += driveAction;
	
	return catchAction;
}
/*! calculate which angle should clear, 
	suitations consider:
	1. if clear back, angle should large
	2. if opponent hold in the clear way, angle should enough large to over him
	3. else choose a small angle to clear far away
*/
AngDeg	Skill::calClearAngle() const
{
	AngDeg clearAng = 0;
	Vector3f posOpp = WM->getOpponentGlobalPos(WM->getClosestOppNum2Ball());
	if ( isThreePointOneLine(WM->getMyGlobalPos(),
							WM->getBallGlobalPos(),
							posOpp,
							5.0f )
		)
	{
		clearAng += 30.0f;
	}
	
	const AngDeg angK = 10.0f;//0.21f;//gene1[0];//10.0f;
	float posOppDist = (posOpp-WM->getBallGlobalPos()).Length();
	if ( posOppDist < 5
		&& isThreePointOneLine(WM->getMyGlobalPos(),
								WM->getBallGlobalPos(),
								posOpp,
								60.0f )
		)
	{
		clearAng += (5-posOppDist)*angK;
	}
	
	float dist2OurGoal = ( WM->getBallGlobalPos() - WM->getOurGoalCenter() ).Length();
	if ( dist2OurGoal < max_kick_distance 
		&& isKickDirectionDanagerous()
		)
	{
		clearAng = max_kick_angle;
	}
	float dist2OppGoal = ( WM->getBallGlobalPos()-WM->getOppGoalCenter()).Length();
	if ( dist2OppGoal > 20 && dist2OppGoal < 30 )
	{
		clearAng = max_kick_angle;
	}
	//AngDeg clearAng = -WM->getBallGlobalPos().x()/WM->getFieldLength()*100;
	
	AngDeg minClearAng = 20.0f;//min_kick_angle;//20.0f;
	if ( (WM->getBallGlobalPos()-WM->getOppGoalCenter()).Length()<20 )
		minClearAng = 10;//0
	clearAng = setMaxNMin(clearAng,max_kick_angle,minClearAng);
	return clearAng;
}

/*! this function return whether the ball will be kick to our own goal
	\return the current kick direction is in our own goal?
*/
bool Skill::isKickDirectionDanagerous() const
{
	Vector3f posBias(0.0, 1.0, 0.0);
	return shoudIKick(WM->getOurGoalRight()-posBias,WM->getOurGoalLeft()+posBias);
}

/*! this function return false in some suitation:
	(the ball will be cleared to our own goal!)
	1. too near the our goal
	2. not too close, but the lofted ball will fall on ground just near the goal
	3. if I am free, I have enough time to turn and kick to opp's goal
	\return can clear the ball in current suitation
*/
bool Skill::canIClear() const
{
	Vector3f posBall = WM->getBallGlobalPos();
	//-* I am free :)
	const Rectangle rectCenter(WM->getOurBaseLine(),15,WM->getOurBaseLine()+20,-15);
	AngDeg attackDir = getVector3fHorizontalAng(WM->getOppGoalCenter()-posBall );
	const float freeBias = 3;//gene1[2];//0.3f
	if ( ( WM->getMyFreedom() > cosDeg(WM->getMyKickHorizontalAng()-attackDir)*10.0f+freeBias)
		|| ( WM->getMyFreedom()>4 && abs(WM->getMyKickHorizontalAng()) > 45 )
		//|| ( (WM->getMyGlobalPos().x()+0.1)>WM->getBallGlobalPos().x() && FM->getMyType() > PT_MIDFIELDER_SWEEPER )
		|| ( WM->getBallGlobalPos().x()<(WM->getOurBaseLine()+20) && abs(WM->getMyGlobalPos().y())>(abs(WM->getBallGlobalPos().y())+0.2) && !rectCenter[posBall])
		)
	{
		return false;
	}
	//-* the kick direction is danagerous?
	if ( !isKickDirectionDanagerous() )
		return true;
	//-* is the ball just in front of the goal?
	const Rectangle rectGoalFront(WM->getOurBaseLine(),half_goal_width,WM->getOurBaseLine()+0.5f,-half_goal_width);
	if ( rectGoalFront[posBall] && FM->getMyType() != PT_GOALKEEPER )
		return false;
	
	//-* will the lofted ball fall into our goal?
	const float bigRange = 20.0f;//11.0f;
	const float smallRange = 9.0f;//3.0f;
	const Rectangle rectGoalBig(WM->getOurBaseLine(),half_goal_width+bigRange,WM->getOurBaseLine()+bigRange,-half_goal_width-bigRange);
	const Rectangle rectGoalSmall(WM->getOurBaseLine(),half_goal_width+smallRange,WM->getOurBaseLine()+bigRange,-half_goal_width-smallRange);
	if ( rectGoalBig[posBall] && !rectGoalSmall[posBall] )
		return false;
	
	return true;
}

/*! this is function define how the goalie defend the goal
	1. if the ball is not in shootBox, run strategic pos
	2. if opp is near the ball and ready to shoot, run to the def-shoot point
	3. if the ball is fast and heading to goal, run to the def-shoot point
	4. default is run to the biesection's position
	\return defend goal's actions
*/
Actions Skill::defendGoal() const
{
	const float closeShootBoxL = 5;//gene1[3];//5
	const float closeShootBoxW = half_goal_width+1.5f;
	Rectangle closeShootBox(WM->getOurBaseLine(),closeShootBoxW,WM->getOurBaseLine()+closeShootBoxL,-closeShootBoxW);
	if ( ( closeShootBox[WM->getInterceptBallPos()] || closeShootBox[WM->getBallGlobalPos()] )
			&& ( !WM->isInDefencePos(2) && !WM->isInDefencePos(3) && !WM->isInDefencePos(4) )
		)
	{
		LOG( 19,"too near the goal, trying clear it");
		return clearBall();
	}
	
	Actions defendGoalActions;
	
	Vector3f posMe = WM->getMyGlobalPos();
	Vector3f ourGoal = WM->getOurGoalCenter();
	Vector3f ourGoalLeft = WM->getOurGoalLeft();
	Vector3f ourGoalRight = WM->getOurGoalRight();
	Vector3f posBall = WM->getBallGlobalPos();
	Vector3f velBall = WM->getBallGlobalVel();
	//float speedBall = velBall.Length();
	//AngDeg angBall = getVector3fHorizontalAng(velBall);
	AngDeg angBall = getVector3fHorizontalAng(WM->getInterceptBallPos()-posBall);
	unsigned int oppNum = WM->getClosestOppNum2Ball();
	Vector3f posOpp = WM->getOpponentGlobalPos(oppNum);
	float opp2Ball = ( posOpp - posBall ).Length();
	
	AngDeg angBias = 5;
	AngDeg angLeft = getVector3fHorizontalAng( ourGoalLeft - posBall )-angBias;
	AngDeg angRight = getVector3fHorizontalAng( ourGoalRight - posBall )+angBias;
	Vector3f shoot = posBall - posOpp;
	AngDeg angShoot = getVector3fHorizontalAng(shoot);

	float distShoot = min((ourGoalLeft - posBall).Length(),(ourGoalRight - posBall).Length());
	//distShoot -= 0.5;
	Vector3f posDef;
	//-*catch action
	Action catchAction;
	Time kickTime=WM->getRealTime();
	for ( Step i=0; i<step_num_per_cycle; i+=1)//step_num_per_kick )
		{
			catchAction.setTime( kickTime+i );
			defendGoalActions += catchAction;
		}
	defendGoalActions +=catchAction;
	//-* kick action
	/*if ( canIClear())
	//{
		Action kickAction;
		kickTime = WM->getRealTime();
		kickAction.setKick(max_kick_angle,100);
		for ( Step i=0; i<step_num_per_cycle; i+=1)//step_num_per_kick )
		{
			kickAction.setTime( kickTime+i );
			defendGoalActions += kickAction;
		}
	//}*/

	//-* drive action
	Action driveAction;
	Rectangle shootBox(WM->getOurBaseLine(),penalty_width,WM->getOurBaseLine()+penalty_length+10,-penalty_width);
	if ( shootBox[posBall])
	{
		const float shootDistOpp = 0.5;//gene1[4];//1
		if ( opp2Ball < shootDistOpp && WM->isBallStop()//speedBall < 1 
			&& isAngInInterval(angShoot,angLeft,angRight)
			)
		{
			LOG( 19,"opp is ready for shooting");
			posDef = pol2xyz(Polar(distShoot,angShoot,0.0f)) + posBall;
		}
		else if ( isAngInInterval(angBall,angLeft,angRight)
				)
		{
			LOG( 19,"opp has shooted");
			LOG( 19,"ball's direction angle: %f",angBall);
			LOG( 19,"posMe: %f, %f, %f",posMe.x(),posMe.y(),posMe.z());
			posDef = pol2xyz(Polar(distShoot,angBall,0.0f)) + posBall;
		}
		else
		{
			LOG( 19,"prepare for defneding goal");
			AngDeg angHalf = getBisectorTwoAngles(angLeft,angRight);
			posDef = pol2xyz(Polar(distShoot,angHalf,0.0f)) + posBall;
		}
		posDef.z() = WM->getMyRadius();
		posDef = setInterceptPosBeforeGoal(posDef);	
		LOG( 19,"posBall:(%f, %f, %f)",posBall.x(),posBall.y(),posBall.z());
		LOG( 19,"posDef:(%f, %f, %f)",posDef.x(),posDef.y(),posDef.z());
		driveAction = runTo(posDef,Vector3f(0,0,0));
		//driveAction = dashTo(posDef);
	}	
	else
	{
		
		driveAction = runStrategicPos();
	}
	
	
	defendGoalActions += driveAction;
	
	return defendGoalActions;
}

/*!
	pass skill using calGroundPassForce
\param teammateNum the teammate's num
\return pass actions (include drive and skill)
*/
Actions Skill::pass( Num teammateNum ) const
{
	Vector3f posTeammate = WM->getTeammateGlobalPos(teammateNum);
	Vector3f posBall = WM->getBallGlobalPos();
	Vector3f posBias = WM->getOppGoalCenter() - posTeammate;
	posBias.Normalize();
	posBias*=(0.05*(posBall-posTeammate).Length());
	Vector3f posAttack = posTeammate+posBias;
	//float kickForce = calGroundKickForce((attack-posBall).Length());
	float passDist = (posAttack-posBall).Length();
	float kickForce = calGroundKickForce(passDist);
	AngDeg kickAng = calPassAng(passDist);
	AngDeg dir = abs(WM->getMyKickHorizontalAng());
	if ( dir > 100 )
	{//back pass
		kickForce *= (1+0.3*cosDeg(dir))*0.8*0.8;
	}
	else
	{
		kickForce /=cosDeg(kickAng);
		kickForce*=0.8;
	}
	Vector3f posOppGoal = WM->getOppGoalCenter();
	AngDeg angCanKick = abs(getClipAng(posBall,posOppGoal,posTeammate));
	if ( angCanKick > 15 && angCanKick < 30 )
	{
		return kickBetween(posOppGoal,posTeammate,kickForce,kickAng);
	}
	else
	{
		return kickTo(posAttack,kickForce,kickAng,15);
	}
	//return kickTo(posAttack,kickForce,kickAng,15);
	return kickBetween(posAttack+posBias,posTeammate,kickForce);
}

/*!
	the idea is want the player can pass as fast as possible
	1.find the fastPass teammate, who do not need long adjusting time
	2.pass to fastPass teammate
\return the pass actions
*/
Actions Skill::fastPass(Num num)const
{
	float myFreedom = WM->getMyFreedom();
	if ( ( myFreedom<3)//0 )//|| (myFreedom<2&&WM->getMyFreedomChange()<0) )
		//&& ( !WM->isSpaceAhead(1,1) )
		)
	{
		return oneTouch( num );
	}
	if ( myFreedom<5 )
	{
		num = selectPass( num );
	}
	return pass(num);
}

Actions Skill::oneTouch(Num num)const
{
	//num = selectPass(num);
//	return safePass(num);
	
	Vector3f aim = WM->getTeammateGlobalPos(num);
	Vector3f posBall = WM->getBallGlobalPos();
	float kickDist = (aim-posBall).Length();
	float force = calGroundKickForce(kickDist);
	AngDeg kickAng = calPassAng(kickDist);
	AngDeg dir = abs(WM->getMyKickHorizontalAng());
	if ( dir > 100 )
	{//back pass
		force *= (1+0.5*cosDeg(dir))*0.8;
	}
	else
	{
		force /=cosDeg(kickAng);
	}
	return kickTo(aim,force,kickAng,500);
}

Num Skill::selectPass( Num num)const
{
	float kickDir = WM->getMyKickHorizontalAng();
	float minErr = 60;
	float minDist = 25;
	Vector3f posBall = WM->getBallGlobalPos();
	for ( Num i=1; i<=5; i++)
	{
		Vector3f posTeammate = WM->getTeammateGlobalPos(i);
		Polar pol = xyz2pol(posTeammate - posBall);
		if (  FM->getPlayerType(i) >= PT_MIDFIELDER_SWEEPER 
			//&& WM->calOurFreedom(i) > 0
			//&& posTeammate.x() > posBall.x() - 9
			&& pol.distance < minDist
			&& pol.distance > 1
			&& abs(normalizeAngle(pol.theta-kickDir)) < minErr
			)
		{
			num = i;
			minErr = setMaxNMin(abs(normalizeAngle(pol.theta-kickDir)),minErr,30.0f);
			minDist = pol.distance;
		}
	}
	return num;
}


Actions Skill::fastDribble(const Vector3f &goal) const
{
	Actions act;
	Action drive;
	Action kick;
	Time actTime = WM->getRealTime();
	Vector3f posBall = WM->getBallGlobalPos();
	Vector3f posMe = WM->getMyGlobalPos();
	Vector3f velBall = WM->getBallGlobalVel();
	Vector3f velMe = WM->getMyGlobalVel();
	Vector3f posIntercept = WM->getInterceptPos(goal);



	kick.setKick(0,15.0f);
	for ( int i = 0; i < 20; i ++ )
	{
		kick.setTime( actTime + i );
		act += kick;
	}
	Vector3f direction = posIntercept - posMe;
	direction = direction.Normalized() * max_drive_force;
	drive.setDriveForce(direction);
	drive.setTime( actTime );


	act += drive;
	
	return act;
}

AngDeg	Skill::calPassAng(const float passDist)const
{
	AngDeg passAng = 0;
	
	float kickDir = WM->getMyKickHorizontalAng();
	float minErr = 45;
	float maxDist = min(10.0f,passDist);
	Vector3f posBall = WM->getBallGlobalPos();
	Num num = 0;
	float oppDist=maxDist;
	for ( Num i=1; i<=opponents_num; i++)
	{
		Vector3f posOpp = WM->getOpponentGlobalPos(i);
		Polar pol = xyz2pol(posOpp - posBall);
		if ( pol.distance < maxDist
			&& abs(normalizeAngle(pol.theta-kickDir)) < minErr
			)
		{
			num = i;
			oppDist = pol.distance;
			minErr = abs(normalizeAngle(pol.theta-kickDir));
		}
	}
	if ( 0==num )
	{
		passAng = 0;
	}
	else
	{
		passAng = 30*cosDeg(minErr);
		if ( oppDist < 5 ) passAng+=5;
		if ( oppDist < 3 ) passAng+=5;
		if ( oppDist < 1 ) passAng+=10;
	}
	
	passAng = setMaxNMin(passAng,max_kick_angle,min_kick_angle);
	return passAng;
}

/*! this action gurarantee our teammate will snatch the ball first.
	that means, the ball should NOT pass to opponent
	But, it may cost time
\param teammateNum inspirer teammate's num, may not pass to him
*/
Actions Skill::safePass( Num teammateNum ) const
{
	Vector3f pos3Teammate = WM->getTeammateGlobalPos(teammateNum);
	if ( WM->getBallRelativePos().Length() > 2 )
	{
		return kickTo(pos3Teammate,1.0,0,60);
	}
	
	Vector2f posTeammate = projection(pos3Teammate);
	Vector2f posOpp = projection(WM->getOpponentGlobalPos(WM->getClosestOppNum2Pos(pos3Teammate)));

	Vector2f posBall = projection(WM->getBallGlobalPos());
	AngDeg kickDir = WM->getMyKickHorizontalAng();
	Line2f kickLine = Line2f::makeLineFromPositionAndAngle(posBall,kickDir);
	Vector2f maxKickEnd = posBall + projection(pol2xyz(Polar(max_kick_distance,kickDir,0.0f)));
	Vector2f pos2Aim = maxKickEnd;
	
	Vector2f posProjection = kickLine.getPointOnLineClosestTo(posTeammate);
	Vector2f delta = projection(pol2xyz(Polar(1.0f,kickDir,0.0f)));
	Vector2f posBias1 = posProjection;
	Vector2f posBias2 = posProjection;

	while( kickLine.isInBetween(posBias1,posBall,maxKickEnd)
		|| 	kickLine.isInBetween(posBias2,posBall,maxKickEnd) )
	{
		if ( (posBias1-posTeammate).Length() < (posBias1-posOpp).Length() )
		{
			pos2Aim = posBias1;
			break;
		}
		else if ( (posBias2-posTeammate).Length() < (posBias2-posOpp).Length() )
		{
			pos2Aim = posBias2;
			break;
		}
		else
		{
			posBias1 += delta;
			posBias2 -= delta;
		}
	}

	float kickDist = (pos2Aim-posBall).Length();
	float force = calGroundKickForce(kickDist);
	AngDeg kickAng = calPassAng(kickDist);

	return kickTo(pos3Teammate,force,kickAng,500);
}
