#include "worldmodel.ih"


void WorldModel::update()
{
  //std::cout << "wm.update" << std::endl;
  d_comm.update(); // @@First beam is performed in this line.
  
  rf<Predicate> pred = d_comm.getPred();

  _debugLevel4("PREDICATE: " << *pred);
//  std::cout << "PREDICATE: " << *pred << std::endl;

  double time = d_info[iNow].getX();
  if (pred)
    intergrate(pred);
  
  initDebugMessage();

  if (time != d_info[iNow].getX())
  {
    updateJoints();
    updateVision();
    updatePosture();

    // convert to world coordinate
    convertToWorldCoord();
    estimateInvisibleObject();
//    estimateInvisibleObjectFromUnit();

    // calculate Nao Position in the field coordinate
    //updateNaoFRef();

    //calculate distances between players and the ball, and between players
    updateDistances();

    // set attacker state ( main attaker or sub attacker )
    if(getPlayerType(d_unum) == Types::ATTACKER)
      updateAttackerState();

//  if(d_neckDirUpdate)
    updateNeckDir();
  }

//  std::cout << "update finished!" << std::endl;

}
