/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * Additionally,this program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ****************************************************************************************/

/* -*- Mode: c++ -*- */

/*
 *Copyright:

 Copyright (C) 2002, 2003 Patrick Riley
 Copyright (C) 2001 Patrick Riley and Emil Talpes

 This file came from the SPADES simulation system.

 The SPADES simulation system is free software; you can
 redistribute it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software
 Foundation; either version 2 of the License, or (at your option)
 any later version.

 The SPADES simulation system is distributed in the hope that it
 will be useful, but WITHOUT ANY WARRANTY; without even the implied
 warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with the SPADES simulation system; if not, write to
 the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 *EndCopyright:
*/

/* this read buffer a file descriptor, notably allowing a read until a particular demlimeter */

#ifndef READ_BUFF_FD_H_
#define READ_BUFF_FD_H_

#include <iostream>

namespace spades
{

  class ReadBuffFD 
  {
  public:
    ReadBuffFD(int new_fd = -1);
    ~ReadBuffFD();

    void forgetFD();
    int getFD() const { return fd; }
    //Note this will close the current one!
    void setNewFD(int new_fd);

    bool close();
  
    /* return
       > 0: number of bytes read
       0  : not enough available right now
       -1 : fd is now invalid (errno will be set)	
       Note that the delimiter is on the buf */
    int readline(char* buf, int maxlen, char delim);

    /* return
       1:  data available
       0  : not enough available right now
       -1 : fd is now invalid (errno will be set) */
    int isFixedLengthDataAvailable(int len);
  
    /* return
       len: succesfully read
       0  : not enough available right now
       -1 : fd is now invalid (errno will be set) */
    int readFixedLength(char* buf, int len);

    /* the first sizeof(int) bytes (in net byte order) say how long this
       "message" is. The buffer may be reallocated to fill this. The four byte length
       is *not* put into buf 
       return
       >0 : amt successfully read
       0: not enough data avilable
       -1: fd is invalid, errno wil be set */
    int readLengthPrefixed(char** pbuf, unsigned int* plen);

    friend std::ostream& operator<<(std::ostream& o, const ReadBuffFD& f)
    { o << "ReadBuffFD(fd="<<f.fd<<")"; return o; }

    int getReadBufferLen() const { return read_buffer_len; }

    bool addToReadBuffer(const char* b, int l);
	
  private:
    void reallocReadBuffer(int new_len);
    
    int fd;

    /* the read_buffer can be resized on a fixed length read */
    char* read_buffer;
    int read_buffer_len;
    int read_buffer_size; //the currently allocated length
  
    static const int s_default_read_buffer_size;
  
  };

} //spades namespace


#endif
