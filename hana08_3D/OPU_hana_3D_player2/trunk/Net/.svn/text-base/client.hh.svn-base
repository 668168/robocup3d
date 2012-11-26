/*
 *  Little Green BATS (2007), AI department, University of Groningen
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
 *  Date: 	July 27, 2007
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




#ifndef __INC_MVDS_CLIENT_HH_
#define __INC_MVDS_CLIENT_HH_

#ifndef __INC_MVDS_SOCKET_HH_
#include "socket.hh"
#endif

#ifndef __INC_MVDS_TIMEVAL_HH_
#include "timeval.hh"
#endif

#ifndef __SYSINC_LIST
#define __SYSINC_LIST
#include <list>
#endif

namespace mvds {

  /**
   *  The TCP Network Client
   *
   *  This does automatic socket io select and such..
   */
  class Client {

  public:

    enum ConnectionState {
      cs_offline,
      cs_connected,
      cs_read,
      cs_write,
      cs_error,
    };

    ConnectionState state;

    TimeVal last_time;

  protected:

    Socket socket;

  private:

    static const int default_timeout;

    SocketAddress socket_address;

    bool running;

    void check_select();

    Client(Client const &_); // NI
    Client &operator=(Client const &_); //NI

  public:

    Client(SocketAddress const &_sockAddr);

    virtual ~Client();

    void connect(SocketAddress const &_sockAddr);

    void connect();

    void shutdown();

    Socket &getSocket() { return socket; }

    SocketAddress &getSocketAddress() { return socket_address; }

    bool ok() const { return state != cs_error; }

    bool connected() const { return (state == cs_connected || state == cs_read || state == cs_write); }

    virtual bool run();
    virtual void update();
    virtual void stop();

    virtual void initConnection() = 0;
    virtual bool ready_to_read() = 0;
    virtual bool ready_to_write() = 0;
    virtual bool ready_to_read_oob() = 0;

  };


};

#endif //  __INC_MVDS_CLIENT_HH_
