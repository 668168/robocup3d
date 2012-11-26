#include "timer.h"
#include <iostream>

using namespace std;

Timer::Timer()
{
	count = 0;
	flag = false;
}

void Timer::SetTimer  ( long lTime )
{
	count = lTime;
	flag = true;
	//cout<<"set time!"<<endl;
}

long Timer::GetTime ()
{
	//cout<<count<<endl;
	return count;
}

bool Timer::IsTimerRun ()
{
	return flag;
}

void Timer::CheckTimer ()
{
	if (flag) count++;
	//cout<<count<<endl;
}

void Timer::ClearTimer ()
{
	flag = false;
	count = 0;
}

Timer::~Timer()
{
}




/*!
    \fn Timer::Pause()
 */
void Timer::Pause()
{
    /// @todo implement me
	flag = false;
}


/*!
    \fn Timer::Start()
 */
void Timer::Start()
{
    /// @todo implement me
	flag = true;
}
