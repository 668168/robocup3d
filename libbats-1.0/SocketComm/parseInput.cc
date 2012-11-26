#include "socketcomm.ih"

void SocketComm::parseInput(bool p)
{
  if (!p)
    d_socket.shutdownRead();
    
  d_parseInput = p;
}

