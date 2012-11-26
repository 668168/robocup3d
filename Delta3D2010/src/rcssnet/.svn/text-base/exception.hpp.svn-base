// -*-c++-*-

/***************************************************************************
               exception.hpp  -  Network associated excpetions
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

#ifndef RCSS_NET_EXCPETION_HPP
#define RCSS_NET_EXCEPTION_HPP

#include <exception>
#include "rcssnet3D_defines.h"

namespace rcss
{
    namespace net
    {
        class RCSSNET3D_API HostNotFound
            : public std::exception
        {
        public:
            HostNotFound( int err ) throw();

            const char*
            what() const throw();

            int
            err() const throw();
        private:
            int m_err;
        };

        class RCSSNET3D_API OpenErr
            : public std::exception
        {
        public:
            OpenErr( int err ) throw();

            const char*
            what() const throw();

            int
            err() const throw();
        private:
            int m_err;
        };

        class RCSSNET3D_API BindErr
            : public std::exception
        {
        public:
            BindErr( int err ) throw();

            const char*
            what() const throw();

            int
            err() const throw();
        private:
            int m_err;
        };

        class RCSSNET3D_API ListenErr
            : public std::exception
        {
        public:
            ListenErr( int err ) throw();

            const char*
            what() const throw();

            int
            err() const throw();
        private:
            int m_err;
        };

        class RCSSNET3D_API AcceptErr
            : public std::exception
        {
        public:
            AcceptErr( int err ) throw();

            const char*
            what() const throw();

            int
            err() const throw();
        private:
            int m_err;
        };

        class RCSSNET3D_API GetNameErr
            : public std::exception
        {
        public:
            GetNameErr( int err ) throw();

            const char*
            what() const throw();

            int
            err() const throw();
        private:
            int m_err;
        };

        class RCSSNET3D_API ConnectErr
            : public std::exception
        {
        public:
            ConnectErr( int err ) throw();

            const char*
            what() const throw();

            int
            err() const throw();
        private:
            int m_err;
        };
    }
}

#endif
