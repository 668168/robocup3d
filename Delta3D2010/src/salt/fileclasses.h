/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: fileclasses.h 56 2009-03-17 18:03:47Z hedayat $

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

/* this file defines two interfaces- RFile and WFile, that are used to
 * implement classes providing unified file semantics employing
 * different means. Two classes implementing these interfaces are
 * included: Memfile and StdFile.
 * Derived file classes providing access to .zip, .rar and other
 * archives have been implemented as plugins to the fileserver of the
 * zeitgeist library.
 */
#ifndef SALT_FILECLASSES_H
#define SALT_FILECLASSES_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include "salt_defines.h"

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

namespace salt
{

/** RFile defines an interface and some basic support functions for
  * classes providing read only file services
  */
class SALT_API RFile
{
public:
    virtual ~RFile() {};

    /** The separator for path names (depends on the platform)
     * @return path separator
     */
    static std::string Sep();
    /** A (platform specific) "bundle path", i.e. a hint where files of the package might be found.
     * @return the bundle path name with a trailing path separator
     */
    static std::string BundlePath();

    // a bunch of pure virtual functions which a file must implement

    /** opens the file fn in the specified mode. The implementation of
     *     the namespace and mode semantics ist up to derived classes
     */
    virtual bool    Open(const char* fn=NULL, const char* mode="rb") = 0;

    /** closes a previously opened file */
    virtual void    Close() = 0;

    /** releases any occupied ressources used by the file. The
     *     semantic is up to the derived classes
     */
    virtual void    Destroy() = 0;

    /** returns a non zero value if the file pointer is at the end of
     *     the file
     */
    virtual int             Eof() = 0;

    /** returns the current file pointer position */
    virtual long    Tell() = 0;

    /** copies the current file pointer position to pos and returns
     *     true on success
     */
    virtual int             GetPos(long *pos) = 0;

    /** sets the file pointer for the file. The new position, measured
     * in bytes, is obtained by adding offset bytes to the position
     * specified by origin.  If origin is set to SEEK_SET, SEEK_CUR, or
     * SEEK_END, the offset is relative to the start of the file, the
     * current position indicator, or end-of-file, respectively.
     */
    virtual int             Seek(long offset, int origin) = 0;

    /** sets the file pointer to the beginning of the file */
    virtual void    Rewind() = 0;

    /** return the size of the file */
    virtual long    Size() = 0;

    /** reads in at most one less than n characters from the file and
     * stores them into buffer. A '\0' is stored after the last character in
     * the buffer.
     */
    virtual char*   Gets(char*buffer,int n) = 0;

    /** reads the next character from the file returns it as an int r
     * EOF on end of file or error.
     */
    virtual int             Getc() = 0;

    /** returns a handle identifying the file. The semantics of this
     * handle depends on the subclass, implementing this method
     */
    virtual void*   GetHandle() = 0;

    /** reads reads count elements of data, each size bytes long,
     * storing them in the specified buffer
     */
    virtual size_t  Read(void *buffer,size_t size,size_t count) = 0;

    /** reads count bytes of data, storing them in the specified buffer */
    virtual size_t  Read(void *buffer,size_t bytes) = 0;

    /** reads a 2 byte int from the file in Intel ordering */
    int Igetw()
    {
        int b1, b2;

        if ((b1 = Getc()) != EOF)
            if ((b2 = Getc()) != EOF)
                return ((b2 << 8) | b1);
        return EOF;
    }

    /** reads a 4 byte int from the file in Intel ordering */
    long Igetl()
    {
        int b1, b2, b3, b4;

        if ((b1 = Getc()) != EOF)
            if ((b2 = Getc()) != EOF)
                if ((b3 = Getc()) != EOF)
                    if ((b4 = Getc()) != EOF)
                        return (((long)b4<<24) | ((long)b3<<16) | ((long)b2<<8) | (long)b1);
        return EOF;
    }

    /** reads a 2 byte int from the file in Motorola ordering */
    int Mgetw()
    {
        int b1, b2;

        if ((b1 = Getc()) != EOF)
            if ((b2 = Getc()) != EOF)
                return ((b1 << 8) | b2);
        return EOF;
    }

    /** reads a 4 byte int from the file in Motorola ordering */
    long Mgetl()
    {
        int b1, b2, b3, b4;

        if ((b1 = Getc()) != EOF)
            if ((b2 = Getc()) != EOF)
                if ((b3 = Getc()) != EOF)
                    if ((b4 = Getc()) != EOF)
                        return (((long)b1<<24) | ((long)b2<<16) | ((long)b3<<8) | (long)b4);
        return EOF;
    }
};

/** Memfile implements the RFile interface using an inmemory
 *     buffer. On open() a file is completely read into the buffer and
 *     from there on served from memory.
 */
class SALT_API MemFile : public RFile
{
public:
    MemFile(const char*fn=NULL, const char*mode="rb");
    MemFile(FILE*f);
    MemFile(RFile *f);
    ~MemFile();

    bool    Open(const char* fn=NULL, const char* mode="rb");
    bool    Open(void*buffer, long s);
    void    Close();
    void    Destroy();

    int             Eof();
    long    Tell();
    int             GetPos(long *pos);
    int             Seek(long offset, int origin);
    void    Rewind();
    long    Size();

    char*   Gets(char*buffer,int n);
    int             Getc();

    void*   GetHandle()     {       return mHandle; }

    size_t  Read(void *buffer,size_t size,size_t count);
    size_t  Read(void *buffer,size_t count) {       return Read(buffer, 1,count);   }
private:

    /** the file handle */
    void*                   mHandle;

    /** a pointer to the buffer holding the file */
    unsigned char*  mCharHandle;

    /** the size of the file in bytes */
    long                    mSize;

    /** the current file pointer position */
    long                    mPosition;
};

/** WFile extends the RFile interface with methods for writing to a
 * file and related support funtions
 */
class SALT_API WFile : public RFile
{
public:
    virtual ~WFile() {};

    /** writes a string without the trailing '\0' */
    virtual int     Puts(const char*s) = 0;

    /** writes a single character */
    virtual int     Putc(int c) = 0;

    /** writes a 2 byte int in Intel ordering */
    int Iputw(int w)
    {
        int b1, b2;

        b1 = (w & 0xFF00) >> 8;
        b2 = w & 0x00FF;

        if (Putc(b2)==b2)
            if (Putc(b1)==b1)
                return w;
        return EOF;
    }

    /** writes count elements of data from buffer, each size bytes long */
    virtual size_t  Write(void *buffer,size_t size,size_t count) = 0;

    /** writes count bytes of data from buffer */
    virtual size_t  Write(void *buffer,size_t count) = 0;

    /** writes a 4 byte int in Intel ordering */
    long Iputl(long l)
    {
        int b1, b2, b3, b4;

        b1 = (int)((l & 0xFF000000L) >> 24);
        b2 = (int)((l & 0x00FF0000L) >> 16);
        b3 = (int)((l & 0x0000FF00L) >> 8);
        b4 = (int)l & 0x00FF;

        if (Putc(b4)==b4)
            if (Putc(b3)==b3)
                if (Putc(b2)==b2)
                    if (Putc(b1)==b1)
                        return l;
        return EOF;
    }

    /** writes a 2 byte int in Motorola ordering */
    int Mputw(int w)
    {
        int b1, b2;

        b1 = (w & 0xFF00) >> 8;
        b2 = w & 0x00FF;

        if (Putc(b1)==b1)
            if (Putc(b2)==b2)
                return w;
        return EOF;
    }

    /** writes a 4 byte in in Motorola ordering */
    long Mputl(long l)
    {
        int b1, b2, b3, b4;

        b1 = (int)((l & 0xFF000000L) >> 24);
        b2 = (int)((l & 0x00FF0000L) >> 16);
        b3 = (int)((l & 0x0000FF00L) >> 8);
        b4 = (int)l & 0x00FF;

        if (Putc(b1)==b1)
            if (Putc(b2)==b2)
                if (Putc(b3)==b3)
                    if (Putc(b4)==b4)
                        return l;
        return EOF;
    }
};

/** StdFile implements the WFile interface using the standard file system */
class SALT_API StdFile : public WFile
{
public:
    StdFile(FILE*f);
    StdFile(const char* fn = NULL, const char* mode = "rb");
    virtual ~StdFile();

    bool    Open(const char*fn=NULL, const char* mode="rb");
    void    Close();
    void    Destroy();

    int             Eof();
    long    Tell();
    int             GetPos(long *pos);
    int             Seek(long offset, int origin);
    void    Rewind();
    long    Size();

    char*   Gets(char*buffer,int n);
    int             Getc();

    int             Puts(const char*s);
    int             Putc(int c);

    size_t  Read(void *buffer,size_t size,size_t count);
    size_t  Read(void *buffer,size_t count) {       return Read(buffer,1,count);    }

    size_t  Write(void *buffer,size_t size,size_t count);
    size_t  Write(void *buffer,size_t count)        {       return Write(buffer,1,count);   }

    void*   GetHandle();

protected:
    /** the standard file handle */
    FILE    *mHandle;
};

} //namespace salt

#endif //FILECLASSES_H__
