#include "socketcomm.ih"

void SocketComm::beam(Vector3D const& pos)
{
//  std::cout << "beam() in SocketComm start!!" << std::endl;
  send(makeBeamMessage(pos));
}

rf<Predicate> SocketComm::makeBeamMessage(Vector3D const& pos)
{
  rf<Predicate> beamPred = new Predicate("beam");
  beamPred->pushLeafs(pos);
//  beamPred->pushLeafs(Vector3D(-10, 0, 0));
  _debugLevel4(*beamPred);
//  std::cout << "*beamPred: " << *beamPred << std::endl;
  return beamPred;
}

