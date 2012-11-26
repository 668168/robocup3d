// -*-c++-*-

/***************************************************************************
                          handler.cpp  - handles network startup
                             -------------------
    begin                : 14-AUG-2003
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

#include "handler.hpp"

namespace rcss
{
	namespace net
	{
		Handler&
		Handler::instance()
		{
			static Handler rval;
			return rval;
		}

		Handler::Handler()
            : m_valid( true )
		{
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(CYGWIN)
			WORD wVersionRequested;
			int err;
 
			wVersionRequested = MAKEWORD( 2, 2 );
 			err = WSAStartup( wVersionRequested, &m_WSAData );
			if ( err != 0 )
			{
                m_valid = false;
                return;
			}
 			if ( LOBYTE( m_WSAData.wVersion ) != 2 ||
				 HIBYTE( m_WSAData.wVersion ) != 2 )
			{
				WSACleanup();
				m_valid = false;
                return;
			}
#endif
		}

		Handler::~Handler()
		{
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(CYGWIN)
			WSACleanup();
#endif
		}
	}
}
