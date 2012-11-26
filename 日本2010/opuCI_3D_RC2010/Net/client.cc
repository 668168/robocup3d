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





#ifndef __INC_MVDS_CLIENT_H_
#include "client.hh"
#endif


namespace mvds {

  const int Client::default_timeout = 10;

  void Client::check_select()
  {
    assert(socket);
    assert(state != cs_error && state != cs_offline);

    fd_set read_set, write_set, except_set;

    TimeVal tv(default_timeout,0);

    int max_descr = socket, res;

    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
    FD_ZERO(&except_set);

    //std::cerr << "Adding client socket" << static_cast<int>(socket) << " to the list." << std::endl;

    FD_SET(socket,&read_set);

    max_descr = static_cast<int>(socket) + 1;

    res = select(max_descr,&read_set,&write_set,&except_set,tv);

    if (res == -1)
      throw std::runtime_error(std::string() + "select():" + strerror(errno));
    else if (res) {
      //std::cout << "Action!" << std::endl;

      if (FD_ISSET(socket,&except_set))
	ready_to_read_oob();

      if (FD_ISSET(socket,&read_set))
	state = (ready_to_read()?cs_write:state);

      // might be a hack..
      if (state == cs_write || FD_ISSET(socket,&write_set))
	state = (ready_to_write()?cs_read:state);
      
    } else
      std::cout << "timeout!" << std::endl;
  }

  Client::Client(SocketAddress const &_sockAddr)
    : socket(PF_INET,SOCK_STREAM,0)
  {
    socket_address = _sockAddr;

    state = cs_offline;
  }

  Client::~Client()
  {
    shutdown();
  }

  void Client::connect()
  {
    std::cerr << "Connecting to: " << socket_address << std::endl;

    socket.connect(socket_address);

    if (socket) {
      state = cs_connected;
      initConnection();
    } else
      state = cs_error;

  }

  void Client::connect(SocketAddress const &_sockAddr)
  {
    socket_address = _sockAddr;

    connect();
  }

  void Client::shutdown()
  {
    socket.close();

    state = cs_offline;
  }

  bool Client::run()
  {
    running = true;

    while (running && state != cs_error) {
      update();
    }

    std::cerr << "Stopped running, state = " << state << std::endl;

    return state != cs_error;
  }

  void Client::stop()
  {
    running = false;
  }

  void Client::update()
  {
    check_select();
  }

};
