// -*-c++-*-

/***************************************************************************
                          addr.cpp  - A network address class
                             -------------------
    begin                : 07-JAN-2003
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

#include "addr.hpp"

#if HAVE_CONFIG_H
#include <sparkconfig.h>
#endif

//#ifdef HAVE_NETDB_H
#include <netdb.h>
//#endif

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

#ifdef HAVE_WINSOCK2_H
#include "Winsock2.h"
#endif

#include "handler.hpp"
#include "exception.hpp"
#include <iostream>
#include <cstring>
#include <errno.h>

namespace rcss
{
    namespace net
    {
        const Addr::HostType Addr::BROADCAST = INADDR_BROADCAST;
        const Addr::HostType Addr::ANY = INADDR_ANY;

        class AddrImpl
        {
	private:
	    void
	    setAddr( Addr::PortType port, Addr::HostType host )
		{
		    memset( (char *)&m_addr, 0, sizeof( m_addr ) ) ;
		    m_addr.sin_family = AF_INET ;
		    m_addr.sin_addr.s_addr = host;
		    m_addr.sin_port = port;
		}


            bool
            setPortRaw( Addr::PortType port )
            {
                m_addr.sin_port = port;
                return true;
            }

            bool
            setHostRaw( Addr::HostType host )
            {
                m_addr.sin_addr.s_addr = host;
                return true;
            }
         public:
            AddrImpl( const Addr::AddrType& addr )
				: m_handler( Handler::instance() ),
				  m_addr( addr )
            {}

			AddrImpl( Addr::PortType port, Addr::HostType host )
				: m_handler( Handler::instance() )
            {
                setAddr( htons( port ), htonl( host ) );
            }

            AddrImpl( Addr::PortType port, const std::string& host )
                : m_handler( Handler::instance() ), m_host_name( host )
            {
                struct hostent* host_ent
                    = (struct hostent*)gethostbyname( host.c_str() );
                if( host_ent == NULL )
                    throw HostNotFound( h_errno );

                memset( (char *)&m_addr, 0, sizeof( m_addr ) ) ;
                m_addr.sin_family = AF_INET ;
                m_addr.sin_addr.s_addr
                    = ((struct in_addr *)host_ent->h_addr_list[0])->s_addr;
                m_addr.sin_port = htons( port );
            }


            bool
            setPort( Addr::PortType port )
		{
		    m_port_name = std::string();
		    return setPortRaw( htons( port ) );
		}

            bool
            setPort( const std::string& port,
                     const std::string& proto = "" )
            {
				if( port.empty() )
				{
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(CYGWIN)
					errno = WSAHOST_NOT_FOUND;
#else
					errno = HOST_NOT_FOUND;
#endif
                    return false;
				}
                struct servent* serv_ent
                    = (struct servent*)getservbyname( port.c_str(),
													  ( proto.empty()
													    ? NULL
														: proto.c_str() ) );
                if( serv_ent == NULL )
				{
                    return false;
				}
                m_port_name = port;
				return setPortRaw( serv_ent->s_port );
            }

            bool
            setHost( Addr::HostType host )
            {
                m_host_name = std::string();
                return setHostRaw( htonl( host ) );
            }

            bool
            setHost( const std::string& host )
            {
				if( host.empty() )
				{
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(CYGWIN)
					errno = WSAHOST_NOT_FOUND;
#else
				    errno = HOST_NOT_FOUND;
#endif
				    return false;
				}
                struct hostent* host_ent
                    = (struct hostent*)gethostbyname( host.c_str() );
                if( host_ent == NULL )
				{
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(CYGWIN)
					return false;
#else
					return false;
#endif
				}
                m_host_name = host;
				return setHostRaw( ((struct in_addr *)host_ent->h_addr_list[0])->s_addr );
            }


            const Addr::AddrType&
            getAddr() const
            { return m_addr; }

            Addr::PortType
            getPort() const
            { return ntohs( m_addr.sin_port );  }

            Addr::HostType
            getHost() const
            { return htonl( m_addr.sin_addr.s_addr ); }

            std::string
            getHostStr() const
            {
                if( m_host_name.empty() )
                {
                    m_host_name = inet_ntoa( m_addr.sin_addr );
                }
                return m_host_name;
            }

            std::string
		    getPortStr( const std::string& proto = "" ) const
            {
                if( m_port_name.empty() )
                {
					struct servent* serv_ent = getservbyport( m_addr.sin_port,
															  ( proto.empty()
															    ? NULL
																: proto.c_str() ) );
	                if( serv_ent == NULL )
					{
                        return m_port_name;
					}
					m_port_name = serv_ent->s_name;
                }
                return m_port_name;
            }
		private:
			Handler& m_handler;
			Addr::AddrType m_addr;
            mutable std::string m_host_name;
            mutable std::string m_port_name;
            Addr::Error m_error;
            int m_errno;
        };

        Addr::Addr( PortType port, HostType host )
            : m_impl( new AddrImpl( port, host ) )
        {}

        Addr::Addr( const AddrType& addr )
            : m_impl( new AddrImpl( addr ) )
        {}

        bool
        Addr::setPort( PortType port )
        {
            return m_impl->setPort( port );
        }

        bool
        Addr::setPort( const std::string& port,
                       const std::string& proto )
        {
            return m_impl->setPort( port, proto );
        }

        bool
        Addr::setHost( HostType host )
        {
             return m_impl->setHost( host );
        }

        bool
        Addr::setHost( const std::string& host )
        {
             return m_impl->setHost( host );
        }

        Addr::Addr( PortType port, const std::string& host )
            : m_impl( new AddrImpl( port, host ) )
        {}


        const Addr::AddrType&
        Addr::getAddr() const
        { return m_impl->getAddr(); }

        Addr::PortType
        Addr::getPort() const
        { return m_impl->getPort(); }

        Addr::HostType
        Addr::getHost() const
        { return m_impl->getHost(); }

        std::string
        Addr::getHostStr() const
        { return m_impl->getHostStr(); }

        std::string
		Addr::getPortStr( const std::string& proto ) const
        { return m_impl->getPortStr( proto ); }

        bool
        operator==( const Addr& a,
                    const Addr& b )
        {
            return ( a.getAddr().sin_port == b.getAddr().sin_port
                     && ( a.getAddr().sin_addr.s_addr
                          == b.getAddr().sin_addr.s_addr ) );
        }

        bool
        operator!=( const Addr& a,
                    const Addr& b )
		{
			return !(a == b);
		}

        bool
        operator < ( const Addr& a,
                    const Addr& b )
        {
          const Addr::HostType host_a = a.getHost();
          const Addr::HostType host_b = b.getHost();

          if (host_a != host_b)
          {
            return host_a < host_b;
          }

          return a.getPort() < b.getPort();
        }

        std::ostream&
        operator<<( std::ostream& o, const rcss::net::Addr& addr )
        { return o << '(' << addr.getPort() << ':' << addr.getHostStr() << ')'; }

    }
}
