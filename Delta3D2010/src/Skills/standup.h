#ifndef STANDUP_H
#define STANDUP_H
#include <string>
#include <iostream>
#include "../Connection/Connection.h"
#include "../Effectors/AngularMotor.h"
#include "../Effectors/Effectors.h"
#include <boost/lexical_cast.hpp>
#include "../Skills/Walk.h"
#include "../WorldModel/FallDownRecognition.h"
#include "TwoElements.h"
#include "../Skills/SuperStandUp.h"
#include "../Behavior/BhvDribble.h"

using namespace std;

class  StandUp{
public:
    StandUp();

    ~StandUp();
    
    static StandUp& instance();
    
    static const StandUp& i(){return instance();}

	std::string backStart(int cycle);

	std::string frontStart(int cycle);

	void addvalue();

	void stop();

	bool canStop();

	void test();

	bool isStandUpFinished();
	
	bool standupFinished;
	
	std::string fastFrontStart ( int cycle );
	
	bool setInitialStandUpFront();
	
	bool setInitialStandUpFastFront();
	
	void fastFrontAddValue();
	
	bool  setInitialStandUpBack();
	
	void backAddValue();
	
	void frontAddValue();
	
	int brakenFrontflag;
	
	float   next[22];
	
	float   prvious[22];
	
	TwoElements   Temp[22];
	
	bool    compare(int i ,EJointID EJID);
	
	bool    update(int i ,EJointID EJID);
	
	int     rep;
	
	double    recognizeFrontSt[30][0];
	
	float    temp,var1,var2;



private:
//Uncyncoronization flags
	bool flag;
	bool flag1;
	bool flag2;
	bool flag3;
	bool flag4;
	bool flag5;
//Back Stand Up temprory varibles
        float Baddllj1;
        float Baddllj2;
        float Baddllj3;
        float Baddllj4;
        float Baddllj5;
        float Baddllj6;
        float Baddrlj1;
        float Baddrlj2;
        float Baddrlj3;
        float Baddrlj4;
        float Baddrlj5;
        float Baddrlj6;
        float Baddlaj1;
        float Baddlaj2;
        float Baddlaj3;
        float Baddlaj4;
        float Baddraj1;
        float Baddraj2;
        float Baddraj3;
        float Baddraj4;
	float BaddHj1;
	float BaddHj2;
//Fast Front Stand Up temprory varibles
        float Ffaddllj1;
	float Ffaddllj2;
	float Ffaddllj3;
	float Ffaddllj4;
	float Ffaddllj5;
	float Ffaddllj6;
	float Ffaddrlj1;
	float Ffaddrlj2;
	float Ffaddrlj3;
	float Ffaddrlj4;
	float Ffaddrlj5;
	float Ffaddrlj6;
	float Ffaddlaj1;
	float Ffaddlaj2;
	float Ffaddlaj3;
	float Ffaddlaj4;
	float Ffaddraj1;
	float Ffaddraj2;
	float Ffaddraj3;
	float Ffaddraj4;
	float FfaddHj1;
	float FfaddHj2;
//Front Stand Up temprory varibles
        float Faddllj1;
	float Faddllj2;
	float Faddllj3;
	float Faddllj4;
	float Faddllj5;
	float Faddllj6;
	float Faddrlj1;
	float Faddrlj2;
	float Faddrlj3;
	float Faddrlj4;
	float Faddrlj5;
	float Faddrlj6;
	float Faddlaj1;
	float Faddlaj2;
	float Faddlaj3;
	float Faddlaj4;
	float Faddraj1;
	float Faddraj2;
	float Faddraj3;
	float Faddraj4;
	float FaddHj1;
	float FaddHj2;
//time validation varibles
	int Bcount;
	int Ffcount;
	int Fcount;
	int controlCycle;
	int counter;
	//Skill *ACS;
	double t;
	bool flagstandup;
	int  EndFrontStandUpCycle;
};

#endif
