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

#ifndef __INC_MVDS_SOCKET_H_
#define __INC_MVDS_SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include "../SocketAddress/socketaddress.hh"


#include <cassert>

#ifndef __SYSINC_IOSTREAM
#include <iostream>
#define __SYSINC_IOSTREAM
#endif

/** \brief Originally Mart's code.
 *  
 */
namespace mvds {

  /**
   *  A C++ wrapper for a socket.
   *  \todo Document
   */
  class Socket {

    int socket_handle;

    unsigned *refcnt;

    void copy(Socket const &_other)
    {
      socket_handle = _other.socket_handle;
      refcnt = _other.refcnt;
      ++*refcnt;
    }

    void destroy()
    {
      if (!(--(*refcnt)))
      {
        if (socket_handle != -1)
        {
          ::shutdown(socket_handle, SHUT_RDWR);
          ::close(socket_handle);
        }
        delete refcnt;
      }

    }

  public:

    Socket(Socket const &_other)
    {
      copy(_other);
    }

    Socket()
    : socket_handle(-1), refcnt(new unsigned)
    {
      (*refcnt) = 1;
    }

    Socket(int _socket_handle)
    : socket_handle(_socket_handle), refcnt(new unsigned)
    {
      (*refcnt) = 1;
    }

    Socket(int _domain, int _type, int _protocol);

    Socket &operator=(Socket const &_other)
    {
      if (this != &_other)
      {
        destroy();
        copy(_other);
      }
      return *this;
    }

    bool operator==(Socket const &_other) const
      { return (socket_handle == _other.socket_handle); }

    bool operator!=(Socket const &_other) const
      { return (socket_handle != _other.socket_handle); }

    bool operator>(Socket const &_other) const
      { return (socket_handle > _other.socket_handle); }

    bool operator<(Socket const &_other) const
      { return (socket_handle < _other.socket_handle); }

    bool operator>=(Socket const &_other) const
      { return (socket_handle >= _other.socket_handle); }

    bool operator<=(Socket const &_other) const
      { return (socket_handle <= _other.socket_handle); }

    operator bool() const
    {
      return (socket_handle != -1);
    }

    ~Socket()
    {
      destroy();
    }

    void setsockopt(int _optname, int _value)
    {
      assert(socket_handle);
      if (::setsockopt(socket_handle,SOL_SOCKET,_optname,&_value,sizeof(int)) == -1)
        throw std::runtime_error(strerror(errno));
    }

    void setsockopt(int _optname, bool _value)
    {
      setsockopt(_optname,_value);
    }

    operator int const()
    {
      return socket_handle;
    }

    void connect(SocketAddress &_server_address)
    {
      assert(socket_handle);
      if (::connect(socket_handle,_server_address,_server_address.getLength()) == -1)
        throw std::runtime_error(strerror(errno));
    }

    void bind(SocketAddress &_my_address)
    {
      assert(socket_handle);
      if (::bind(socket_handle,_my_address,_my_address.getLength()) == -1)
        throw std::runtime_error(strerror(errno));
    }

    void listen(int _backlog)
    {
      assert(socket_handle);
      if (::listen(socket_handle,_backlog) == -1)
        throw std::runtime_error(strerror(errno));
    }

    Socket accept(SocketAddress &_address)
    {
      assert(socket_handle);
      socklen_t len = _address.getLength();
      int sock = ::accept(socket_handle,_address,&len);
      if (sock == -1)
        throw std::runtime_error(strerror(errno));
      return sock;
    }

    void close()
    {
      ::close(socket_handle);
      socket_handle = -1;
    }

    void shutdown(int how)
    {
      assert(socket_handle);
      ::shutdown(socket_handle, how);
    }

    void shutdownRead()
    {
      shutdown(SHUT_RD);
    }
    
    void shutdownWrite()
    {
      shutdown(SHUT_WR);
    }

    unsigned read(char *_buf, unsigned _size)
      {
        assert(socket_handle);
        int res = ::read(socket_handle,_buf,_size);
        if (res == -1) {
	  if (errno != EAGAIN)
    	    throw std::runtime_error(strerror(errno));
	  res = 0;
	}
        return static_cast<unsigned>(res);
      }

    unsigned readExactly(char *_buf, unsigned _size)
    {
      unsigned total;
      for (total = 0;
           total < _size;
           total += read(_buf + total,_size-total));
      return total;
    }

    unsigned write(char const *_buf, unsigned _size)
    {
      assert(socket_handle);
      int res = ::write(socket_handle,_buf,_size);
      if (res == -1 && errno != EAGAIN)
        throw std::runtime_error(strerror(errno));
      return static_cast<unsigned>(res);
    }

    unsigned writeExactly(char const *_buf, unsigned _size)
    {
      unsigned total;
      for (total = 0;
           total < _size;
           total += write(_buf + total,_size-total));
      return total;
    }


    int fcntl(int cmd)
    {
      return ::fcntl(socket_handle,cmd);
    }

    int fcntl(int cmd, long arg)
    {
      return ::fcntl(socket_handle,cmd,arg);
    }

    int fcntl(int cmd, struct flock *lock)
    {
      return ::fcntl(socket_handle,cmd,lock);
    }

    int setBlocking(bool blocking)
    {
      int flags = fcntl(F_GETFL);

      if (blocking && !(flags & O_NONBLOCK))
	return fcntl(F_SETFL,flags & ~O_NONBLOCK);
      else
	return fcntl(F_SETFL,flags | O_NONBLOCK);
    }

    bool getBlocking()
    {
      int flags = fcntl(F_GETFL);
      return !(flags & O_NONBLOCK);
    }

  };


};

#endif //  __INC_MVDS_SOCKET_H_
