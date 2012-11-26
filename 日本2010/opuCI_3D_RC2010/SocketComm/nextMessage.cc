#include "socketcomm.ih"

rf<Predicate> SocketComm::nextMessage()
{
  if (!hasNextMessage())
    return 0;

  rf<Predicate> msg = d_iMessageQueue.front();
  d_iMessageQueue.pop();
  return msg;
}
