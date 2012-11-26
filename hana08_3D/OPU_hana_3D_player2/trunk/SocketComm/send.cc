#include "socketcomm.ih"

void SocketComm::send()
{

  string message;// = "";
 
  while (!d_oMessageQueue.empty())
  {
    message += d_oMessageQueue.front()->toString();

    d_oMessageQueue.pop();
  }

//  std::cout << "send() message: " << message << std::endl;
  _debugLevel4(message);
  if (!message.empty())// != "")
  {
  	_debugLevel4(message);
    sendMessage(message);
  }
}
