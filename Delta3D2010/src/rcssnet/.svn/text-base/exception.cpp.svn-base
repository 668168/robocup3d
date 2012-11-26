// -*-c++-*-

/***************************************************************************
               exception.cpp  -  Network associated excpetions
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

#if HAVE_CONFIG_H
#include <sparkconfig.h>
#endif

#include "exception.hpp"
#include <cstring>

#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <netinet/in.h>
#endif

#ifdef HAVE_ARPA_NAMESER_H
#include <arpa/nameser.h>
#endif

#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif

#ifdef HAVE_RESOLV_H
#include <resolv.h>
#endif




namespace rcss
{
    namespace net
    {
        HostNotFound::HostNotFound( int err ) throw()
            : m_err( err )
        {}

        const char*
        HostNotFound::what() const throw()
        {
#if defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
        return "Network error";
#else
            return std::strerror( m_err );
#endif
        }

        int
        HostNotFound::err() const throw()
        { return m_err; }

        OpenErr::OpenErr( int err ) throw()
            : m_err( err )
        {}

        const char*
        OpenErr::what() const throw()
        { return std::strerror( m_err ); }

        int
        OpenErr::err() const throw()
        { return m_err; }

        BindErr::BindErr( int err ) throw()
            : m_err( err )
        {}

        const char*
        BindErr::what() const throw()
        { return strerror( m_err ); }

        int
        BindErr::err() const throw()
        { return m_err; }

        ListenErr::ListenErr( int err ) throw()
            : m_err( err )
        {}

        const char*
        ListenErr::what() const throw()
        { return strerror( m_err ); }

        int
        ListenErr::err() const throw()
        { return m_err; }


        AcceptErr::AcceptErr( int err ) throw()
            : m_err( err )
        {}

        const char*
        AcceptErr::what() const throw()
        { return strerror( m_err ); }

        int
        AcceptErr::err() const throw()
        { return m_err; }


        GetNameErr::GetNameErr( int err ) throw()
            : m_err( err )
        {}

        const char*
        GetNameErr::what() const throw()
        { return strerror( m_err ); }

        int
        GetNameErr::err() const throw()
        { return m_err; }

        ConnectErr::ConnectErr( int err ) throw()
            : m_err( err )
        {}

        const char*
        ConnectErr::what() const throw()
        { return strerror( m_err ); }

        int
        ConnectErr::err() const throw()
        { return m_err; }
    }
}
