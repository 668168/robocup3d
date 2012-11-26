#ifndef TIMER_H
#define TIMER_H

/**
	@author HeFei University of Technology,China <baodunqiao@sina.com>
*/
class Timer
{
public:
    Timer();
    ~Timer();

public :
	
	void SetTimer ( long lTime = 0);
	void ClearTimer ();
	void CheckTimer ();
	long GetTime ();	
	bool IsTimerRun ();
    void Pause();
    void Start();
	

private:
	long count;
	bool flag;
};

#endif
