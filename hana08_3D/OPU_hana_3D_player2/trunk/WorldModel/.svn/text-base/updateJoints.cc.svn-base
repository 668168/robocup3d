#include "worldmodel.ih"

//#define DEBUGLEVEL 4
//#include "debug.hh"

void WorldModel::updateJoints()
{
  for (unsigned i = 0; i < Types::NJOINTS; ++i)
  {
    unsigned id = i + iHeadJoint1;
    _debugLevel4("Joint " << i << ": " << d_info[id]);
//    std::cout << "WorldModel::updateJoints  joint " << i << ": " 
//	      << d_info[id] << std::endl; 
    
    d_jointAngles[i].init(d_info[id].getX() / 180.0 * M_PI, 0.01);
    d_jointRates[i].init(d_info[id].getY() / 180.0 * M_PI, 0.01);
  }
}
