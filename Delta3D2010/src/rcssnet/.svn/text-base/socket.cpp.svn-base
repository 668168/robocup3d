/***************************************************************************
               socket.cpp  -  Base newtork socket class
                             -------------------
    begin                : 08-JAN-2003
    copyright            : (C) 2003 by The RoboCup Soccer Server
                           Maintenance Group.
    email                : sserver-admin@lists.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU LGPL as published by the Free Software  *
 *   Foundation; either version 2 of the License, or (at your option) any  *
 *   later version.                                                        *
 *                                                                         *
 ***************************************************************************/

#include "socket.hpp"

#if HAVE_CONFIG_H
#include <sparkconfig.h>
#endif

#include <sys/types.h>

//#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
//#endif
//#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
//#endif
//#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
//#endif
//#ifdef HAVE_UNISTD_H
#include <unistd.h>
//#endif
#include <fcntl.h>
#include <cerrno>
//#if defined (HAVE_POLL_H)
#include <poll.h>
//#endif

#ifndef __socklen_t_defined
typedef int socklen_t;
#endif

#ifdef HAVE_WINSOCK2_H
#include "Winsock2.h"
#endif

#include "handler.hpp"
#include "tcpsocket.hpp"

#include <iostream>

namespace rcss
{
    namespace net
    {


#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(CYGWIN)
                const Socket::SocketDesc Socket::INVALIDSOCKET = INVALID_SOCKET;
#else
                const Socket::SocketDesc Socket::INVALIDSOCKET = -1;
#endif


        void
        Socket::closeFD( SocketDesc* s )
        {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
            ::closesocket( *s );
#else
            ::close( *s );
#endif
            delete s;
        }

        Socket::Socket()
                        : m_handler( &Handler::instance() )
        {}

        Socket::Socket( SocketDesc s )
                        : m_handler( &Handler::instance() )
        {
            m_handle = boost::shared_ptr< SocketDesc >( new SocketDesc( s ),
                                                        Socket::closeFD );
        }


        Socket::~Socket()
        { close(); }

        bool
        Socket::open()
        {
            SocketDesc s;
            if( !doOpen( s ) )
                return false;

            m_handle = boost::shared_ptr< SocketDesc >( new SocketDesc( s ),
                                                        Socket::closeFD );
#if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)
            int err = setCloseOnExec();
            if( err < 0 )
            {
                err = errno;
                close();
                return false;
            }
#endif
            return true;
        }

        bool
        Socket::bind( const Addr& addr )
        {
            if( isOpen() )
            {
                int err = ::bind( getFD(),
                                  (struct sockaddr *)&( addr.getAddr() ),
                                  sizeof( addr.getAddr() ) );
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                if( err == SOCKET_ERROR )
                    return false;
#else
                if( err < 0 )
                    return false;
#endif
                return true;
            }
            return false;
        }

        Addr
        Socket::getName() const
        {
            if( isOpen() )
            {
                Addr::AddrType name;
                socklen_t from_len = sizeof( name );
                int err = ::getsockname( getFD(),
                                         (struct sockaddr *)&name,
                                         &from_len );
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(CYGWIN)
                if( err == SOCKET_ERROR )
                {
                    err = WSAGetLastError();
                    return Addr();
                }
#else
                if( err < 0 )
                    return Addr();
#endif
                return Addr( name );
            }
            else
                return Addr();
        }

        bool
        Socket::connect( const Addr& addr )
        {
            if( isOpen() )
            {
                int err = ::connect( getFD(),
                                     (const struct sockaddr *)&( addr.getAddr() ),
                                     sizeof( addr.getAddr() ) );
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(CYGWIN)
                if( err == SOCKET_ERROR )
                    return false;
#else
                if( err < 0 )
                    return false;
#endif

                return true;
            }
            else
                return false;
        }

        Addr
        Socket::getPeer() const
        {
            if( isOpen() )
            {
                Addr::AddrType name;
                socklen_t from_len = sizeof( name );
                int err = ::getpeername( getFD(),
                                         (struct sockaddr *)&name,
                                         &from_len );
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(CYGWIN)
                if( err == SOCKET_ERROR )
                {
                    return Addr();
                }
#else
                if( err < 0 )
                    return Addr();
#endif
                return Addr( name );
            }
            else
                return Addr();
        }

        void
        Socket::close()
        {
            m_handle.reset();
        }

        int
        Socket::setCloseOnExec( bool on )
        {
            if( isOpen() )
            {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                errno = EPERM;
                return -1;
#else
                return fcntl( getFD(), F_SETFD,
                              ( on ? FD_CLOEXEC : ~FD_CLOEXEC ) );
#endif
            }
            else
            {
                errno = EPERM;
                return -1;
            }
        }

        int
        Socket::setNonBlocking( bool on )
        {
            if( isOpen() )
            {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                u_long tmp = on;
                return ioctlsocket( getFD(), FIONBIO, &tmp );
#else
                int flags = fcntl( getFD(), F_GETFL, 0 );
                if( flags == -1 )
                    return flags;

                if( on )
                    return fcntl( getFD(), F_SETFL,
                                  O_NONBLOCK | flags );
                else
                    return fcntl( getFD(), F_SETFL,
                                  ~O_NONBLOCK & flags );
#endif
            }
            else
            {
                errno = EPERM;
                return -1;
            }
        }

        int
        Socket::setAsync( bool on )
        {
#ifdef O_ASYNC
            if( isOpen() )
            {
                int flags = fcntl( getFD(), F_GETFL, 0 );

                if ( on )
                    return fcntl ( getFD(), F_SETFL,
                                   O_ASYNC | flags );
                else
                    return fcntl ( getFD(), F_SETFL,
                                   ~O_ASYNC & flags );
            }
#endif
            errno = EPERM;
            return -1;

        }

        int
        Socket::setBroadcast( bool on )
        {
#ifdef SO_BROADCAST
            if( isOpen() )
            {
                int ison = on;
                return setsockopt( getFD(), SOL_SOCKET,
                                   SO_BROADCAST,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                   (const char*)&ison,
#else
                                   (void*)&ison,
#endif
                                   sizeof( int ) );
            }
#endif
            errno = EPERM;
            return -1;
        }

        int
        Socket::setReuseAddr( bool on )
        {
            if( isOpen() )
            {
                int doreuse = on;
                return setsockopt( getFD(), SOL_SOCKET,
                                   SO_REUSEADDR,
                                   (const char*)&doreuse,
                                   sizeof( int ) );
            }
            errno = EPERM;
            return -1;
        }

        Socket::SocketDesc
        Socket::getFD() const
        { return ( isOpen() ? *(m_handle.get()) : Socket::INVALIDSOCKET ); }

        bool
        Socket::isOpen() const
        { return m_handle.get() != NULL; }

        bool
        Socket::isConnected() const
        {
            return getPeer() != Addr();
        }

        Addr
        Socket::getDest() const
        { return getPeer(); }

        int
        Socket::send( const char* msg,
                      size_t len,
                      const Addr& dest,
                      int flags,
                      CheckingType check )
        {
            if( check == DONT_CHECK )
            {
                return ::sendto( getFD(), msg,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                                (int)len,
#else
                                                                len,
#endif
                                                                flags,
                                 (struct sockaddr *)&( dest.getAddr() ),
                                 sizeof( dest.getAddr() ) );
            }
            else
            {
                for(;;)
                {
                    int sent = ::sendto( getFD(), msg,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                                                 (int)len,
#else
                                                                                 len,
#endif
                                                                                 flags,
                                         (struct sockaddr *)&( dest.getAddr() ),
                                         sizeof( dest.getAddr() ) );
                    if( sent != -1
                        || ( errno != EINTR
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                     && errno != WSAEWOULDBLOCK
#else
                                                     && errno != EWOULDBLOCK
#endif
                                                        ) )
                        return sent;
                }
            }
        }

        int
        Socket::send( const char* msg,
                      size_t len,
                      int flags,
                      CheckingType check )
        {
            if( check == DONT_CHECK )
            {
                return ::send( getFD(), msg,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                           (int)len,
#else
                                                           len,
#endif
                                                           flags );
            }
            else
            {
                int s, sent;
                for(sent = 0; sent<len; )
                {
                    s = ::send( getFD(), msg+sent,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                (int)(len-sent),
#else
                                len-sent,
#endif
                                flags );
                    if( s == -1
                          && ( errno != EINTR
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                     && errno != WSAEWOULDBLOCK
#else
                                                     && errno != EWOULDBLOCK
#endif
                            ) ){
                        return s;
                    }

                    if ( s > 0 )
                        sent+=s;
                }
                return sent;
            }
        }

        int
        Socket::recv( char* msg,
                      size_t len,
                      Addr& from,
                      int flags,
                      CheckingType check )
        {
            if( check == DONT_CHECK )
            {
                Addr::AddrType addr;
                socklen_t from_len = sizeof( addr );
                int rval = ::recvfrom( getFD(), msg,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                                           (int)len,
#else
                                                                           len,
#endif
                                                                           flags,
                                       (struct sockaddr *)&addr, &from_len );
                from = Addr( addr );
                return rval;
            }
            else
            {
                for(;;)
                {
                    Addr::AddrType addr;
                    socklen_t from_len = sizeof( addr );
                    int received = ::recvfrom( getFD(), msg,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                                                  (int)len,
#else
                                                                                   len,
#endif
                                                                                   flags,
                                               (struct sockaddr *)&addr,
                                               &from_len );
                    from = Addr( addr );
                    if( received != -1
                        || errno != EINTR )
                        return received;
                }
            }
        }

        int
        Socket::recv( char* msg,
                      size_t len,
                      int flags,
                      CheckingType check )
        {
            if( check == DONT_CHECK )
                return ::recv( getFD(), msg,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                      (int)len,
#else
                                                          len,
#endif
                                                          flags );
            else
            {
                for(;;)
                {
                    int received = ::recv( getFD(), msg,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                                               (int)len,
#else
                                                                               len,
#endif
                                                                               flags );
                    if( received != -1
                        || errno != EINTR )
                        return received;
                }
            }
        }

        bool
        Socket::listen( int backlog )
        {
            return ::listen( getFD(), backlog ) == 0;
        }

        bool
        Socket::accept( Socket& sock )
        {
            SocketDesc fd = ::accept( getFD(), NULL, 0 );
            if( fd == INVALIDSOCKET )
                return false;
            sock = TCPSocket( fd );
            return true;
        }
        
        Socket* Socket::accept(Addr& addr)
        {
            socklen_t len = sizeof(struct sockaddr);
            SocketDesc fd = ::accept( getFD(), 
                                      (struct sockaddr *)&( addr.getAddr() ),
                                      &len
                                      );

            if (fd == INVALIDSOCKET )
                {
                    return 0;
                }

            return new TCPSocket(fd);
        }

        int
        Socket::recv( int timeout,
                      char* msg,
                      size_t len,
                      Addr& from,
                      int flags )
        {
#if defined (HAVE_POLL_H)
            pollfd fd = { getFD(), POLLIN | POLLPRI, 0 };
            int res = poll( &fd, 1, timeout );
            if( res == 0 )
            {
                errno = EAGAIN;
                return -1;
            }
            else if( res == 1 )
            {
                return recv( msg,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                         (int)len,
#else
                                                         len,
#endif
                                                         from, flags );
            }
            else
            {
                return res;
            }
#else
            errno = EPERM;
            return -1;
#endif
        }

        int
        Socket::recv( int timeout,
                      char* msg,
                      size_t len,
                      int flags )
        {
#if defined (HAVE_POLL_H)
            pollfd fd = { getFD(), POLLIN | POLLPRI, 0 };
            int res = poll( &fd, 1, timeout );
            if( res == 0 )
            {
                errno = EAGAIN;
                return -1;
            }
            else if( res == 1 )
            {
                return recv( msg,
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
                                                         (int)len,
#else
                                                         len,
#endif
                                                         flags );
            }
            else
            {
                return res;
            }
#else
            errno = EPERM;
            return -1;
#endif
        }
    }
}
