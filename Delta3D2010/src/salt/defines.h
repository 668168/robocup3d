/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: defines.h 56 2009-03-17 18:03:47Z hedayat $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/* this file contains defines that are ugly but necessary, to
 * disable compiler warnings or work around differences between
 * supported compilers
 */

#ifndef SALT_DEFINES_H
#define SALT_DEFINES_H

#ifdef HAVE_CONFIG_H
#include <sparkconfig.h>
#endif

#include <cassert>

#if             defined(_MSC_VER)
        // here we turn of a couple of pesky warnings VC emmits
        #pragma warning (disable : 4786)  // truncation of debug information
        #pragma warning (disable : 4251)  // don't complain about missing dll interfaces
#endif

// some compiler-specific defines
#if             defined(_MSC_VER)
        // shared library export/import stuff
        #define SHARED_LIB_EXPORT       __declspec(dllexport)
        #define SHARED_LIB_IMPORT       __declspec(dllimport)
        // other symbols
        #define f_inline                        __forceinline
        // hide the attribute definitions from MSVC
        #define  __attribute__(x)  /*NOTHING*/
#elif   defined(__GNUC__)
        #define SHARED_LIB_EXPORT
        #define SHARED_LIB_IMPORT
        #define f_inline                        inline
#endif

// this macro only exports the class in a header, if the shared library version is compiled
#ifdef SHARED_LIB_COMPILE
        #define API_EXPORT  SHARED_LIB_EXPORT
        #define API_IMPORT  SHARED_LIB_IMPORT
#else
        #define API_EXPORT
        #define API_IMPORT
#endif

#define Assert(expression, desc)        assert(expression && desc)

#endif //SALT_DEFINES_H
