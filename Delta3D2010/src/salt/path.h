/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: path.h 56 2009-03-17 18:03:47Z hedayat $

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

   Path

   HISTORY:
                13.06.2002 MK
                        - initial version
                31.08.2002 MK
                        - moved to salt
*/
#ifndef SALT_PATH_H
#define SALT_PATH_H

#ifdef HAVE_CONFIG_H
# undef EXTERN
# undef HAVE_VPRINTF
# undef PACKAGE
# undef PACKAGE_BUGREPORT
# undef PACKAGE_NAME
# undef PACKAGE_STRING
# undef PACKAGE_TARNAME
# undef PACKAGE_VERSION
# undef PREFIX
# undef VERSION
#include <sparkconfig.h>
#endif

#include "salt_defines.h"
#include <string>
#include <list>

namespace salt
{

/** This class serves as a helper for path strings within the object
  *     hierarchy. It is capable of cleaning paths and separating a path
  *     into path components.
  */
class SALT_API Path
{
    //
    // types
    //
public:
    typedef std::list<std::string>      TStringList;

    //
    // functions
    //
public:

    /** constructs a path object from a string, using the Set
     * method
     */
    Path(const std::string &path = "");

    /** Sets the managed path expression. The path gets tokenized
     *  and can be read element by element using Back(), Front(),
     *  PopBack() and PopFront()
     */
    void Set(const std::string &path);

    /** returns true if the managed path expression denotes an
     * absoulute path, i.e. has a leading slash
     */
    bool IsAbsolute() const;

    /** returns the first path component */
    const std::string& Front() const;

    /** returns and removes the first path component */
    void PopFront();

    /** returns the last path component */
    const std::string& Back() const;

    /** returns and removes the last path component */
    void PopBack();

    /** returns true, if no path components remain, i.e. all path
     * components are popped
     */
    bool IsEmpty() const;

    /** returns a cleaned path expression, removing superfluous
     * separators
     */
    std::string GetCleanPath(const std::string &sep = "/") const;

private:
    Path(const Path &obj);
    Path& operator=(const Path &obj);

    /** tokenizes the path components */
    void Tokenize(const std::string &path);

    //
    // members
    //
public:
protected:
    /** the list of tokenized path components */
    TStringList mPathComponents;

    /** indicates an absolute path expression */
    bool                mIsAbsolute;
private:
};

} //namespace salt

#endif //SALT_PATH_H
