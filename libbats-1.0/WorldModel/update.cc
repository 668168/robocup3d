
#include "worldmodel.ih"


void WorldModel::update()
{
  if (d_time != SCochlea::getInstance().getInfo(Cochlea::iNow)[0])
  {
	//double diff = SCochlea::getInstance().getInfo(Cochlea::iNow)[0] - d_time;

	//	if (diff > 0.021)
	//	  cerr << "Difference: " << diff << endl;

    ++d_numMsgReceived;
    updateGameState();
    updateVision();
  }
}
