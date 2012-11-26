// -*-c++-*-

/***************************************************************************
                          addr.hpp  - A network address class
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

#ifndef RCSS_NET_ADDR_HPP
#define RCSS_NET_ADDR_HPP

struct sockaddr_in;

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include "rcssnet3D_defines.h"

namespace rcss
{
    namespace net
    {
        class AddrImpl;
        
        class RCSSNET3D_API Addr
        {
        public:
            typedef boost::uint16_t PortType;
            typedef boost::uint32_t HostType;
            typedef struct sockaddr_in AddrType;

            enum Error { eADDR_OK, eSERV_NOT_FOUND, eHOST_NOT_FOUND };

            static const HostType BROADCAST;
            static const HostType ANY;
            
            Addr( PortType port = 0, HostType host = Addr::ANY );
            Addr( PortType port, const std::string& host );
            Addr( const AddrType& addr );
            
			bool setPort( PortType port = 0 );
			bool setPort( const std::string& port, 
                          const std::string& proto = "" );

            bool setHost( HostType host = Addr::ANY );
            bool setHost( const std::string& host );
           
            const AddrType&
            getAddr() const;
            
            PortType
            getPort() const;
            
            HostType
            getHost() const;
            
            std::string
            getHostStr() const;

			std::string
			getPortStr( const std::string& proto = "" ) const;
			
		private:
            boost::shared_ptr< AddrImpl > m_impl;
        };
        
		RCSSNET3D_API bool 
        operator ==( const Addr& a,
                    const Addr& b );
        
		RCSSNET3D_API bool 
        operator !=( const Addr& a,
                    const Addr& b );

        RCSSNET3D_API bool 
        operator < ( const Addr& a,
                    const Addr& b );
					
		RCSSNET3D_API std::ostream&
        operator<<( std::ostream& o, const Addr& addr );
    }
}

#endif

