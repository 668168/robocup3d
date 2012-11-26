// -*-c++-*-

/***************************************************************************
                 socketstreambuf.hpp  -  A socket stream buffer
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


#ifndef RCSS_NET_SOCKETSTREAMBUF_HPP
#define RCSS_NET_SOCKETSTREAMBUF_HPP

//g++ 2.95.6 doesn't have the streambuf header, so iostream is used instead
//#include <streambuf>
#include<iostream>
#include <cstdio>

#include "socket.hpp"

namespace rcss
{
    namespace net
    {
        class SocketStreamBuf
            : public std::streambuf
        {
        public:
            typedef int int_type;
            typedef char char_type;

            enum ConnType { CONN_ON_READ, NO_CONN };
        public:
            SocketStreamBuf( Socket& socket,
                             const Addr& dest,
                             ConnType conn = CONN_ON_READ,
                             std::streamsize bufsize = 8192 )
                : m_socket( socket ),
                  m_end_point( dest ),
                  m_bufsize( bufsize ),
                  m_inbuf( NULL ),
                  m_outbuf( NULL ),
                  m_remained( 0 ),
                  m_connect( conn )
            {}


            SocketStreamBuf( Socket& socket,
                             ConnType conn = NO_CONN,
                             std::streamsize bufsize = 8192 )
                : m_socket( socket ),
                  m_bufsize( bufsize ),
                  m_inbuf( NULL ),
                  m_outbuf( NULL ),
                  m_remained( 0 ),
                  m_connect( conn )
            {}

	    virtual
            ~SocketStreamBuf()
            {
                overflow();
                delete [] m_inbuf;
                delete [] m_outbuf;
            }

            void
            setEndPoint( const Addr& addr )
            { m_end_point = addr; }

            void
            setConnectType( ConnType conn )
            { m_connect = conn; }


        protected:
	    virtual
            bool
            writeData()
            {
                unsigned long size = (unsigned long)((pptr () - m_outbuf) * sizeof(char_type));
                if( size == 0 )
                    return true;

                if( m_socket.isConnected() )
                    return m_socket.send( m_outbuf, size ) > 0;
                else
                    return m_socket.send( m_outbuf, size, m_end_point ) > 0;
            }

	    virtual
            int_type
            overflow( int_type c = EOF )
            {
                // this method is supposed to flush the put area of the buffer
                // to the I/O device

                // if the buffer was not already allocated nor set by user,
                // do it just now
                if( pptr() == NULL )
                {
                    m_outbuf = new char_type[m_bufsize];
                }
                else
                {
                    if( !writeData() )
                    {
                        return EOF;
                    }
                }
                setp( m_outbuf, m_outbuf + m_bufsize );
                if( c != EOF )
                    sputc( c );
                return 0;
            }

	    virtual
            int
            sync()
            {
                if( pptr() != NULL )
                {
                    // just flush the put area
                    if( !writeData() )
                    {
                        return EOF;
                    }
                    setp( m_outbuf, m_outbuf + m_bufsize );
                }
                return 0;
            }

	    virtual
        int_type
	    underflow()
            {

                // this method is supposed to read some bytes from the I/O device

                // if the buffer was not already allocated nor set by user,
                // do it just now
                if( gptr() == NULL )
                {
                    m_inbuf = new char_type[m_bufsize];
                }

                if( m_remained != 0 )
                    m_inbuf[0] = m_remained_char;

                int readn = m_bufsize * sizeof( char_type ) - m_remained;
                if( m_socket.isConnected() )
                    readn = m_socket.recv( m_inbuf + m_remained,
                                           readn );
                else
                {
                    Addr addr;
                    readn = m_socket.recv( m_inbuf + m_remained,
                                           readn,
                                           addr );
                    if( m_connect == CONN_ON_READ && readn > 0 )
                        m_socket.connect( addr );
                }

                if( readn < 0 || ( readn == 1 && (m_inbuf + m_remained)[ 0 ] == -1 ) )
                {
                    (m_inbuf + m_remained)[ 0 ] = -1;
                    return EOF;
                }
                int totalbytes = readn + m_remained;
                setg( m_inbuf, m_inbuf,
                      m_inbuf + totalbytes / sizeof(char_type) );

                m_remained = totalbytes % sizeof( char_type );
                if( m_remained != 0 )
                    m_remained_char = m_inbuf[totalbytes / sizeof(char_type)];

                return sgetc();
            }

        private:

            // not used
            SocketStreamBuf( const SocketStreamBuf& );

            // not used
            SocketStreamBuf&
            operator=( const SocketStreamBuf& );

            Socket& m_socket;
            Addr m_end_point;
            std::streamsize m_bufsize;
            char_type* m_inbuf;
            char_type* m_outbuf;
            int m_remained;
            char_type m_remained_char;
            ConnType m_connect;
        };
    }
}

#endif
