#include "humanoidagent.ih"

void HumanoidAgent::run()
{

	// Startup agent
	startUp();
	
	
	// Get our worldmodel
	WorldModel& wm = WorldModel::getInstance();


	// Get first message	
	wm.update();
	unsigned i(0);
	
	
	while(wm.getNumMsgReceived() < 5 && ++i < 200) /// \todo Tweak to a minimum possible number of messages before sending init is ok.
		wm.update();

	
	//Send init
	d_comm.init(d_unum, d_teamName);


	// Beam to an initial position
//	d_comm.beam(new Vector3D(-5, 0, 0));
/*
	int num;
	std::cin >> num;
	std::cout << num << std::endl;
*/
	//Wait for unum
	while(wm.getNumMsgReceived() < 10 && wm.getUnum() == 0)//Failsafe max messages
		wm.update();
		
	
	//Init behavior system
	init();
	
	double distInit[2];
	double distFinal[2];
	double width;
	bool first = true;

	while(true)
	{
		_debugLevel4("----------------------- New think cycle ------------------------");
		
//		std::cout << "OK 1" << std::endl;		
		wm.update();	// @@First beam is performed in this line.
//		std::cout << "OK 2" << std::endl;
	
		// Get the polar coordinate from agent's initial position
		if(wm.getPlayMode() != wm.BEFORE_KICKOFF && first){
			distInit[0] = wm.get(WorldModel::iVisionFlag1L).getX();
			distInit[1] = wm.get(WorldModel::iVisionFlag2L).getX();
			width = (wm.getObjectPosition(Types::FLAG1L).getMu() - wm.getObjectPosition(Types::FLAG2L).getMu()).length();
			first = false;
		}

		think();
//		std::cout << "OK 3" << std::endl;		
/*		// Print ball position relative to the agent
		std::cout << "(" << wm.getObjectPosition(Types::BALL).getMu().getX() << ", " 
				<< wm.getObjectPosition(Types::BALL).getMu().getY() << ", " 
				<< wm.getObjectPosition(Types::BALL).getMu().getZ() << ")  " 
				<< "(" << wm.getObjectVector(Types::BALL).getMu().getX() << ", " 
				<< wm.getObjectVector(Types::BALL).getMu().getY() << ", " 
				<< wm.getObjectVector(Types::BALL).getMu().getZ() << ")" << std::endl;
*/

		if( d_exitTime != 0.0 && wm.getGameTime() > d_exitTime ){
			distFinal[0] = wm.get(WorldModel::iVisionFlag1L).getX();
			distFinal[1] = wm.get(WorldModel::iVisionFlag2L).getX();
			break;
		}
	}
	
//	std::cout << "Init: (" << init.getX() << ", " << init.getY() << ", " << init.getZ() << ")" << std::endl;
//	std::cout << "Final: (" << final.getX() << ", " << final.getY() << ", " << final.getZ() << ")" << std::endl;
//	std::cout << "Final: (" << wm.getObjectPosition(Types::FLAG1US).getMu().getX() << ", " 
//			<< wm.getObjectPosition(Types::FLAG1US).getMu().getY() << ", " 
//			<< wm.getObjectPosition(Types::FLAG1US).getMu().getZ() << ")" << std::endl;
	
//	std::cout << distInit[0] << " & " << distInit[1] << std::endl;
//	std::cout << distFinal[0] << " & " << distFinal[1] << std::endl;
//	std::cout << width << std::endl;
	double y[2];
	y[0] = calcYCoordinate(distInit[0], distInit[1], width);
	y[1] = calcYCoordinate(distFinal[0], distFinal[1], width);
//	std::cout << y[1] << ", " << y[0] << std::endl;	
//	std::cout << calcXCoordinate(distFinal[0], y[1]) << ", " << calcXCoordinate(distInit[0], y[0]) << std::endl;
	
	// Output the distance that the agent has walked 
	std::cout << sqrt( pow(calcXCoordinate(distFinal[0], y[1]) - calcXCoordinate(distInit[0], y[0]), 2) 
				+ pow(calcYCoordinate(distFinal[0], distFinal[1], width) - calcYCoordinate(distInit[0], distInit[1], width), 2) ) << std::endl;
	
}
