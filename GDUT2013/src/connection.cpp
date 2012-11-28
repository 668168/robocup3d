/***************************************************************************
 *   Copyright (C) 2007 by Alex   *
 *   root@linux   *
 *                                                                         *
           *
 ***************************************************************************/
#include "connection.h"
#include <errno.h>

Connection::Connection()
{
	sHostIP = "127.0.0.1";
	socket_fd = -1;
	iPlayerPort = 3100;
	memset(mBuffer, '\0', sizeof(mBuffer));
}


bool Connection::Connect ()
{

	int iConnectResult=-1;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		cout<<"socket(): socket failed()"<<endl;
		return false;
	}

	server_addr.sin_addr.s_addr = inet_addr (sHostIP);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons (iPlayerPort);
	iConnectResult = connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in));
	if (iConnectResult < 0)
	{
		cout<<"connection failed"<<endl;
		return false;
	}
	
	return true;
}


bool Connection::SendMsg (const char* msg)
{
	memset(mBuffer, '\0', sizeof(mBuffer));
	strcpy(mBuffer + sizeof(long), msg);
	unsigned int len = strlen(msg);
	unsigned int netlen = htonl(len);
	memcpy(mBuffer, &netlen, sizeof(netlen));
	unsigned int iLeftLen = sizeof(long) + len;
	unsigned int iSendLen = 0;
	 int iSendResult = -1;
	while (iLeftLen > 0)
	{
		iSendResult = send(socket_fd ,mBuffer+iSendLen ,iLeftLen , 0  );
		if (iSendResult <= 0)
		{
			cout<<"sendMessage failed"<<endl;
			return false;
		}
		iSendLen += iSendResult;
		iLeftLen -= iSendLen;
	}
	return true;
}


bool Connection::SendMsg (const std::string& msg)
{
       return  SendMsg(msg.c_str());
}


bool Connection::ReceiveMsg ()
{
	unsigned int bytesRead = 0;
	int readResult = -1;
	// get the msg 's length
	memset(mBuffer, '\0', sizeof(mBuffer));
	unsigned int iLen = sizeof(unsigned int);
	while(bytesRead < iLen)
	{
		if (!SelectInput())
		{
			return false;
		}
		readResult = read(socket_fd, mBuffer + bytesRead, iLen - bytesRead);
        	if(readResult <= 0)
		{
			cout <<" ReadCError! "<<endl;
			return false;
			//}
				continue;
		}        // by this way ,it can not exit normally when the server shutdown first.
		bytesRead += readResult;
	}
	 // msg is prefixed with it's total length
	unsigned int iMsgLen = ntohl(*(unsigned int*)mBuffer);
	if(iLen + iMsgLen > sizeof(mBuffer)) 
	{
		cout << "too long message; aborting" << endl;
		return false;
	}
	unsigned int msgRead = bytesRead - iLen;
	char *offset = mBuffer + bytesRead;
	readResult = -1;
	int readLen = 0;
	while (msgRead < iMsgLen)
	{
		if (!SelectInput())
		{
			return false;
		}
        	readLen = sizeof(mBuffer) - msgRead;
        	if(readLen > iMsgLen - msgRead)
            		readLen = iMsgLen - msgRead;
		readResult = read(socket_fd, offset, readLen);
		if(readResult < 0)
        	{
			cout <<" ReadError! "<<endl;
			return false;
		}
        	msgRead += readResult;
        	offset += readResult;
	}
	(*offset) = '\0';
	return true;
}


bool Connection::ReceiveMsg(string &sMsg)
{
	bool r = ReceiveMsg();
	if (r)
	{
		sMsg = string(mBuffer + sizeof(unsigned int));
	}
	return r;
}


char* Connection::GetMsg ()
{
	return mBuffer + sizeof(unsigned int);
}


bool Connection::SelectInput ()
{
	fd_set readfds;
	struct timeval tv = {10,0};
	FD_ZERO(&readfds);
	FD_SET(socket_fd,&readfds);
    
	while(1) 
	{
		switch(select(socket_fd+1,&readfds, 0, 0, &tv)) {
		case 1:
			return true;
		case 0:
			cout << "(SelectInput) select failed " << strerror(errno) << endl;
			return false;
		default:
			if(errno == EINTR)  
                		continue;
           		 cout << "(SelectInput) select failed " << strerror(errno) << endl;
            		return false;
        }
    }
}

void Connection::SetHostIP (const char* HostIP)
{
	sHostIP = HostIP;
}


void Connection::SetHostPort(int HostPort)
{
	iPlayerPort = HostPort;
}


const char* Connection::GetHostIP () 
{
	return sHostIP;
}

int  Connection::GetHostPort ()
{
	return iPlayerPort;
}

bool Connection::CloseConnection ()
{
	cout << "closed connection to " << string(sHostIP) << ":" << iPlayerPort << "\n";
	return close (socket_fd);
}

Connection::~Connection()
{
	CloseConnection();
}
