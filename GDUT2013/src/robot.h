#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>
using namespace std;

class Robot{
public:
	Robot();
	~Robot();
	bool Create();
	bool Init();
	bool Run();
	bool Say(string msg);
	bool LogFile(char cFileName[], char cMsg[]);

	bool m_bInit;
	bool AnalyseServFile (string sFileName,string sTargetFileName);
	bool LogTrainFile (string sTargetFileName,int TranType);


};

#endif
