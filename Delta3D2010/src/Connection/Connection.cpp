/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <errno.h>
#ifndef WIN32
#include <netinet/in.h>
#endif

#include "Connection.h"
#include <cstring>

using namespace rcss::net;
using namespace std;

Connection::Connection()
{
    mHost = "127.0.0.1";
    mPort = 3100;
}

Connection::~Connection()
{
}
Connection& Connection::instance()
{
    static Connection sConnection;
    return sConnection;
}
bool Connection::init()
{
    std::cout << "connecting to TCP " << mHost << ":" << mPort << "\n";
    try
    {
        Addr local(INADDR_ANY,INADDR_ANY);
        mSocket.bind(local);
	std::cout << "mSocket.bind(local): " << mSocket.bind(local)  << "  Local: " << local << "\n";
	
    }

    catch (BindErr error)
    {
        cerr << "failed to bind socket with '"
            << error.what() << "'" << std::endl;

        mSocket.close();
        return false;
    }

    try
    {
        Addr server(mPort,mHost);
        mSocket.connect(server);
	std::cout << "mSocket.connect(server): " << mSocket.connect(server)  << "  server: " << server << "\n";
    }

    catch (ConnectErr error)
    {
        cerr << "connection failed with: '"
            << error.what() << "'" << std::endl;
        mSocket.close();
        return false;
    }
    return true;
}

void Connection::done()
{
    mSocket.close();
    std::cout << "closed connection to " << mHost << ":" << mPort << "\n";
	//exit(0);
}

bool Connection::selectInput()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(mSocket.getFD(), &readfds);

#ifdef WIN32
    int maxFd = 0;
#else
    int maxFd = mSocket.getFD()+1;
#endif
    return select(maxFd,&readfds, 0, 0, 0) > 0;
}

bool Connection::sendMessage(const string& msg)
{
    if (msg.empty())
    {
        return false;
    }

    // prefix the message with it's payload length
    unsigned int len = static_cast<unsigned int>(htonl(msg.size()));
    mSocket.send((const char*)&len, sizeof(unsigned int));
    int rval = mSocket.send(msg.data(), msg.size());

    if (rval < 0)
    {
        cerr
            << "(sendMessage) ERROR: "
            << " send returned error '"
            << strerror(errno) << "' " << std::endl;
        return false;
    }
    return true;
}

bool Connection::getMessage(string& msg)
{
    static char buffer[16 * 1024];

    unsigned int bytesRead = 0;
    while(bytesRead < sizeof(unsigned int))
    {
        selectInput();

        int readResult = mSocket.recv(buffer + bytesRead, sizeof(unsigned int) - bytesRead);
        if(readResult <= 0)
        {
		done();
		return false;
            cerr 
                << "(getMessage) ERROR: "
                << " read returned error '"
                << strerror(errno) << "' " << std::endl;
            //continue;
	    //break;
	    
            
        }
        bytesRead += readResult;
    }

    // msg is prefixed with it's total length
    unsigned int msgLen = ntohl(*(unsigned int*)buffer);
    // cerr << "GM 6 / " << msgLen << " (bytesRead " << bytesRead << ")\n";
    if(sizeof(unsigned int) + msgLen > sizeof(buffer)) {
        cerr << "too long message; aborting" << std::endl;
        abort();
    }

    // read remaining message segments
    unsigned int msgRead = bytesRead - sizeof(unsigned int);

    char *offset = buffer + bytesRead;

    while (msgRead < msgLen)
    {
        if (! selectInput())
        {
            return false;
        }

        int readLen = sizeof(buffer) - msgRead;
        if(readLen > (msgLen) - (msgRead))
            readLen = msgLen - msgRead;

        int readResult = mSocket.recv(offset, readLen);
        if (readResult <= 0)
        {
            cerr 
                << "(getMessage) ERROR: "
                << " read returned errors '"
                << strerror(errno) << "' " << std::endl;
    
            // continue;
            return false;
        }
        msgRead += readResult;
        offset += readResult;
    }

    // zero terminate received data
    (*offset) = 0;

    msg = string(buffer+sizeof(unsigned int));

    return true;
}