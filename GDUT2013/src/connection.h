/***************************************************************************
 *   Copyright (C) 2007 by Alex   *
 *   root@linux   *
 *                                                                         *
            *
 ***************************************************************************/
#ifndef CONNECTION_H
#define CONNECTION_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>


using namespace std;

/**
@author Alex
*/
class Connection{
public:
	Connection();
	~Connection();
	bool Connect ();
	bool SendMsg (const char* msg);
	bool SendMsg (const string& msg);
	bool ReceiveMsg ();
	bool ReceiveMsg (string &sMsg);
	char* GetMsg ();
	bool SelectInput ();
	void SetHostIP(const char* HostIP);
	void SetHostPort(int HostPort);
	bool CloseConnection ();
	const char* GetHostIP ();
	int GetHostPort ();
private:
	char mBuffer [16 * 1024];
	int socket_fd;
	sockaddr_in  server_addr;   // in <netinet/in.h>
	const char* sHostIP;
    	int iPlayerPort;
};

#endif
