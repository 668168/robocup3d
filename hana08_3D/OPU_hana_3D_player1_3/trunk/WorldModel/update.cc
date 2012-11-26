#include "worldmodel.ih"


void WorldModel::update()
{
//  std::cout << "wm.update" << std::endl;
  d_comm.update();	// @@First beam is performed in this line.
  
  rf<Predicate> pred = d_comm.getPred();

  _debugLevel4("PREDICATE: " << *pred);
//  std::cout << "PREDICATE: " << *pred << std::endl;

  double time = d_info[iNow].getX();
  if (pred)
    intergrate(pred);
  
  if (time != d_info[iNow].getX())
  {
    updateJoints();
    updateVision();
    updatePosture();
  }
 
}
