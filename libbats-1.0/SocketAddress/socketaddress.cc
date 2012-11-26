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


#include <netdb.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <iostream>
#include <cstring>

#include "socketaddress.hh"

namespace mvds {

  void SocketAddress::NSLookup(std::string const &_host_name)
  {

    struct hostent *h = gethostbyname(_host_name.c_str());

    if (!h)
      throw std::runtime_error(hstrerror(h_errno));

	memcpy(&(sock_address.i.sin_addr),*(h->h_addr_list),sizeof(struct in_addr));

  }

  void SocketAddress::copy(SocketAddress const &_other)
  {
    memcpy(&sock_address,&(_other.sock_address),sizeof(sock_address));
  }

  void SocketAddress::destroy()
  {
  }

  SocketAddress::SocketAddress()
  {
    sock_address.i.sin_family = AF_INET;
    sock_address.i.sin_port = 0;
  }

  SocketAddress::SocketAddress(SocketAddress const &_other)
  {
    copy(_other);
  }

  SocketAddress::SocketAddress(int _family, int _port, in_addr_t addr)
  {
    sock_address.i.sin_family = _family;
    sock_address.i.sin_port = htons(_port);
    sock_address.i.sin_addr.s_addr = addr;
  }

  SocketAddress::SocketAddress(int _port, in_addr_t addr)
  {
    sock_address.i.sin_family = AF_INET;
    sock_address.i.sin_port = htons(_port);
    sock_address.i.sin_addr.s_addr = addr;
  }

  SocketAddress::SocketAddress(int _family, int _port, std::string const &_host_name)
  {
    sock_address.i.sin_family = _family;
    sock_address.i.sin_port = htons(_port);

    NSLookup(_host_name);
  }

  SocketAddress::SocketAddress(int _port, std::string const &_host_name)
  {
    sock_address.i.sin_family = AF_INET;
    sock_address.i.sin_port = htons(_port);

    NSLookup(_host_name);
  }

  SocketAddress &SocketAddress::operator=(SocketAddress const &_other)
  {
    if (this != &_other) {
      destroy();
      copy(_other);
    }
    return *this;
  }

  SocketAddress::~SocketAddress()
  {
    destroy();
  }

  std::ostream &operator<<(std::ostream &_os, const SocketAddress &_sa)
  {

    _os
      << inet_ntoa(_sa.sock_address.i.sin_addr);
    _os
      << ":" << ntohs(_sa.sock_address.i.sin_port);
 
    return _os;
   
  }

};

