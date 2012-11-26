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

#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <iostream>
#include "../rcssnet/tcpsocket.hpp"
#include "../rcssnet/exception.hpp"


class Connection 
{
public:
    Connection();
    ~Connection();
    static Connection& instance();
    static const Connection& i(){ return instance();}
    bool init();

    void done();

    bool getMessage(std::string& msg);

    bool sendMessage(const std::string& msg);

    bool selectInput();

    void setServer(std::string host) { mHost = host; }

    void setPort(int port) { mPort = port; }
private:
    rcss::net::TCPSocket    mSocket;

    std::string             mHost;

    int                     mPort;
};

#endif // CONNECTION_H
