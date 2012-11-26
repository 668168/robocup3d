/*
 *  Little Green BATS (2006)
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *  Date: 	September 14, 2006
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 2 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */





#ifndef __SYSINC_SYS_TIME_H_
#define __SYSINC_SYS_TIME_H_
#include <sys/time.h>
#endif

#ifndef __SYSINC_SYS_TYPES_H_
#define __SYSINC_SYS_TYPES_H_
#include <sys/types.h>
#endif

#ifndef __SYSINC_UNISTD_H_
#define __SYSINC_UNISTD_H_
#include <unistd.h>
#endif

#ifndef __SYSINC_IOSTREAM
#define __SYSINC_IOSTREAM
#include <iostream>
#endif

#include "server.hh"

namespace mvds {

  const int Server::default_backlog = 5;

  const int Server::default_timeout = 10;

  void Server::check_select()
  {
    fd_set read_set, write_set, except_set;

    TimeVal tv(default_timeout,0);

    int max_descr = socket, res;

    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
    FD_ZERO(&except_set);

    //      std::cerr << "Adding server socket" << static_cast<int>(socket) << " to the list." << std::endl;

    FD_SET(socket,&read_set);

    SocketList::iterator si = connections.begin();
    while (si != connections.end()) {

      if (-1 == (*si).socket) {
        delete_connection(*si);
        si = connections.erase(si);
        continue;
      }

      //      std::cerr << "Adding socket" << static_cast<int>((*si).socket) << " to the list." << std::endl;

      if ((*si).state == cs_read) {
        FD_SET((*si).socket,&read_set);
        //std::cerr << "Selecting READ!" << std::endl;
      } else if ((*si).state == cs_write)
        FD_SET((*si).socket,&write_set);

      FD_SET((*si).socket,&except_set);

      if (static_cast<int>((*si).socket) > max_descr)
        max_descr = static_cast<int>((*si).socket);

      si++;

    }

    max_descr++;

    res = select(max_descr,&read_set,&write_set,&except_set,tv);

    if (res == -1)
      throw std::runtime_error(std::string() + "select():" + strerror(errno));
    else if (res) {
      //std::cout << "Action! " << res << std::endl;

      for (SocketList::iterator i = connections.begin();
           i != connections.end(); i++) {

        if (FD_ISSET((*i).socket,&except_set)) {
          ready_to_read_oob(*i);
          continue;
        }

        if (FD_ISSET((*i).socket,&read_set)) {
          if (ready_to_read(*i))
            (*i).state = cs_write;
          continue;
        }

        if (FD_ISSET((*i).socket,&write_set)) {
          if (ready_to_write(*i))
            (*i).state = cs_read;
          continue;
        }

      }

      if (FD_ISSET(socket,&read_set)) {

        SocketInfo si;
        si.socket = socket.accept(si.address);
        si.state = cs_accepting;
        //std::cerr << "Accepting, socket handle = " << static_cast<int>(si.socket) << std::endl;
        connections.push_back(si);

        if (!accept_connection(connections.back())) {
          connections.pop_back();
          si.socket.close();
        }

        if (connections.back().state == cs_accepting)
          connections.back().state = cs_read;
      }

    } else
    {}
      //std::cout << "timeout!" << std::endl;
    
  }

  Server::Server(unsigned _port)
    : socket_address(_port), socket(PF_INET,SOCK_STREAM,0)
  {

    // Bind the socket to a port.
    socket.bind(socket_address);

  }

  void Server::finish()
  {
    while (!connections.empty()) {
      delete_connection(connections.back());
      connections.pop_back();
    }
  }

  Server::~Server()
  {
    std::cerr << "#Socket: Server Destructed!" << std::endl;
    socket.close();
  }

  void Server::listen()
  {
    socket.listen(default_backlog);

    running = true;

    while (running)
      check_select();
  }

  void Server::stop()
  {
    running = false;
  }

};
