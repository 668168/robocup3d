#include "humanoidagent.ih"

void HumanoidAgent::connectToDebugger()
{
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons( d_debuggerPort );
  addr.sin_addr.s_addr = inet_addr( d_debuggerHost.c_str() );
//  addr.sin_port = htons( 8492 );
//  addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
  d_sock = socket(AF_INET, SOCK_STREAM, 0);

  if(connect(d_sock, (struct sockaddr *)&addr, sizeof(addr))<0){
    std::cerr << "connection failed!!" << std::endl;
    return;
  }
  else
    std::cerr << "connection =>" << std::endl;

}
