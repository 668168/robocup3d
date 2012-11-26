#include "socketcomm.ih"

void SocketComm::send()
{
  _debugLevel4("The Big Send");
  
  _debugLevel4("Queue size: " << d_oMessageQueue.size());
  
  string message;// = "";
  
  while (!d_oMessageQueue.empty())
  {
    message += d_oMessageQueue.front()->toString();
    d_oMessageQueue.pop();
  }

  _debugLevel4(message);
  if (!message.empty())// != "")
  {
  	_debugLevel4(message);
    sendMessage(message);
  }
}
