/*
 *  Little Green BATS (2008), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	November 1, 2008
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
 *		Foundation; either version 3 of the License, or (at 
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

#ifndef __INC_MVDS_SOCKETADDRESS_H_
#define __INC_MVDS_SOCKETADDRESS_H_

#ifndef __SYSINC_SYS_TYPES_H_
#define __SYSINC_SYS_TYPES_H_
#include <sys/types.h>
#endif

#ifndef __SYSINC_SYS_SOCKET_H_
#define __SYSINC_SYS_SOCKET_H_
#include <sys/socket.h>
#endif

#ifndef __SYSINC_NETINET_IN_H_
#define __SYSINC_NETINET_IN_H_
#include <netinet/in.h>
#endif


#ifndef __SYSINC_CERRNO
#define __SYSINC_CERRNO
#include <cerrno>
#endif

#ifndef __SYSINC_STRING
#define __SYSINC_STRING
#include <string>
#endif

namespace mvds {

  /**
   *  A C++ wrapper for socketaddress
   * \todo Document
   */  
  class SocketAddress {

    friend std::ostream &operator<<(std::ostream &, const SocketAddress &);

    union sock {
      struct sockaddr s;
      struct sockaddr_in i;
    };

    sock sock_address;

    void NSLookup(std::string const &_host_name);

    void copy(SocketAddress const &_other);
    void destroy();

  public:

    SocketAddress();

    SocketAddress(SocketAddress const &_other);

    SocketAddress(int _family, int _port, in_addr_t addr = INADDR_ANY);

    SocketAddress(int _port, in_addr_t = INADDR_ANY);

    SocketAddress(int _family, int _port, std::string const &_host_name);

    SocketAddress(int _port, std::string const &_host_name);

    SocketAddress &operator=(SocketAddress const &_other);

    ~SocketAddress();

    int getFamily() const
    {
      return sock_address.i.sin_family;
    }

    int getPort() const
    {
      return ntohs(sock_address.i.sin_port);
    }

    operator sockaddr*()
    {
      return &(sock_address.s);
    }

    operator sockaddr_in*()
    {
      return &(sock_address.i);
    }

    unsigned getLength() const
    {
      return sizeof(sock_address);
    }

  };


};

#endif //  __INC_MVDS_SOCKETADDRESS_H_
