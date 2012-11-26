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

 This file is part of the SPADES simulation system.

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

#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include "ReadBuffFD.h"


using namespace spades;

/**********************************************************************************/

const int
spades::ReadBuffFD::s_default_read_buffer_size = 1024;

/**********************************************************************************/

spades::ReadBuffFD::ReadBuffFD(int new_fd)
  : fd(-1)
{
  read_buffer = new char[s_default_read_buffer_size];
  read_buffer_size = s_default_read_buffer_size;
  read_buffer_len = 0;

  setNewFD(new_fd);
}


spades::ReadBuffFD::~ReadBuffFD()
{
  close();
  delete [] read_buffer;
}

void
spades::ReadBuffFD::forgetFD()
{
  //actlog(100, SLC->network()) << "ReadBuffFD: forgetting fd " << fd << ende;
  fd = -1;
}

void
spades::ReadBuffFD::setNewFD(int new_fd)
{
  close();

  fd = new_fd;

  if (fd != -1)
    {
      if (fcntl (fd, F_SETFL, O_NONBLOCK) != 0)
		  ;
	//errorlog << *this << ": Error on fcntl " << errno << ": " << strerror(errno) << ende;
    }
}


bool
spades::ReadBuffFD::close()
{
  if (fd == -1)
    return true;
  
  bool ret = true;
  
  if (::close (fd) != 0)
    {
      //warninglog(10) << *this << ": Error on close " << errno << ": " << strerror(errno) << ende;
      ret = false;
    }

  fd = -1;
  
  return ret;
}


/* return
   > 0: number of bytes read
   0  : not enough available right now
   -1 : fd is now invalid (errno will be set)
   Note that the delimiter is on the buf
   if we reach the max len on the buffer, the buffer is filled */
int
spades::ReadBuffFD::readline(char* buf, int maxlen, char delim)
{
  //warninglog(10) << "You are now using ReadBuffFD::readline; this function has been modified and not tested as it was not used at the time of modification" << ende;
  
  for (;;)
    {
      /* check to see if we have enough data */
      char* rb = read_buffer;
      for (int i=0; i<read_buffer_len; i++)
	{
	  if (*rb == delim || i+1 == maxlen)
	    {
	      //actlog(220, SLC->network()) << *this << ": satisfying from read buffer " << i << ende;
	      memcpy(buf, read_buffer, i+1);
	      if (i+1 != read_buffer_len)
		memmove(read_buffer, rb+1, read_buffer_len - i - 1);
	      read_buffer_len = read_buffer_len - i - 1;
	      return i+1;
	    }
	  rb++;
	}

      /* there was not enough data in the read buffer, so let's try to get some more */
      /* rb points to the location right after the last valid byte in the buffer */
      int res = ::read(fd, rb, read_buffer_size - read_buffer_len);
      if (res < 0)
	{
	  /* error case */
	  if (errno == EAGAIN)
	    {
	      /* no more data available */
	      //actlog(220, SLC->network()) << *this << ": no more data " << read_buffer_len << ende;
	      return 0;
	    }
	  else if (errno == EINTR)
	    {
	      /* Note that we really could keep trying in this case. However,
		 I want to avoid looping on a single socket. A select call on this
		 socket will still return immediately, so it shouldn't slow us down
		 (much). Plus I don't think we get interrupted all that often */
	      //actlog(200, SLC->network()) << *this << ": interrupted system call, returning" << ende;
	      return 0;
	    }
	  else
	    {
	      //errorlog << *this << ": error on read "
		  //     << errno << ": " << strerror(errno) << ende;
	      if (read_buffer_len)
		{
		  /* let's copy whatever data we have */
		  int len = read_buffer_len;
		  memcpy(buf, read_buffer, len);
		  read_buffer_len = 0;
		  return len;
		}
	      return -1;
	    }
	}
      else if (res == 0)
	{
	  /* we got an eof! */
	  //actlog(220, SLC->network()) << *this << ": EOF with " << read_buffer_len << ende;
	  if (read_buffer_len)
	    {
	      /* let's copy whatever data we have */
	      int len = read_buffer_len;
	      memcpy(buf, read_buffer, len);
	      read_buffer_len = 0;
	      return len;
	    }
	  errno = EBADF;
	  return -1;
	}
  
      /* res is > 0 */
      //actlog(220, SLC->network()) << *this << ": read " << res << ende;
      read_buffer_len += res;
      
    }
  
}


int
spades::ReadBuffFD::isFixedLengthDataAvailable(int len)
{
  if (len == 0)
    return 1;
  
  /* check whether the read_buffer is large enough to handle this request
     if not, reallocate the array */
  if (read_buffer_size < len)
    {
      reallocReadBuffer(len);
    }

  for (;;)
    {
      /* See if we have enough data to satisfy request */
      if (read_buffer_len >= len)
	{
	  return 1;
	}

      /* there was not enough data in the read buffer, so let's try to get some more */
      int res = ::read(fd, read_buffer + read_buffer_len, read_buffer_size - read_buffer_len);
      if (res < 0)
	{
	  /* error case */
	  if (errno == EAGAIN)
	    {
	      /* no more data available */
	      //actlog(210, SLC->network()) << "ReadBuffFD::isFixedLengthDataAvailable: only "
			//		  << read_buffer_len << " available, < " << len << ende;
	      return 0;
	    }
	  else
	    {
	      //errorlog << *this << "::readFixedLength: error on read "
		  //     << errno << ": " << strerror(errno) << ende;
	      return -1;
	    }
	}
      else if (res == 0)
	{
	  /* we got an eof! */
	  //actlog(150, SLC->network()) << *this << ": EOF with " << read_buffer_len
		//		      << " of " << len << " desired" << ende;
	  errno = EBADF;
	  return -1;
	}
  
      /* res is > 0 */
      read_buffer_len += res;
      
    }	
  
  
}


/* return
   1  : succesfully read
   0  : not enough available right now
   -1 : fd is now invalid (errno will be set)
   Note that this could cause a realloc of read_buffer 	*/
int
spades::ReadBuffFD::readFixedLength(char* buf, int len)
{
  if (len == 0)
    return 1;

  int res = isFixedLengthDataAvailable(len);

  if (res == 1)
    {
      memcpy(buf, read_buffer, len);
      memmove(read_buffer, read_buffer+len, read_buffer_len - len);
      read_buffer_len -= len;
      return len;
    }

  //res is 0 or -1
  return res;

  
}


/* the first sizeof(int) bytes (in net byte order) say how long this
   "message" is. The buffer may be reallocated to fill this. The four byte length
   is *not* put into buf 
   return
   >0 : amt successfully read
   0: not enough data avilable
   -1: fd is invalid, errno wil be set */
int
spades::ReadBuffFD::readLengthPrefixed(char** pbuf, unsigned int* plen)
{
  unsigned int mess_len;
  int res;
  
  res = isFixedLengthDataAvailable(sizeof(int));
  if (res != 1)
    return res;

  //get the message length
  memcpy(&mess_len, read_buffer, sizeof(int));
  mess_len = ntohl(mess_len);

  //make sure the target buffer is big enough
  if (*pbuf == NULL || mess_len > *plen)
    {
      //use a doubling sort of scheme so that we don't waste too much time reallocing
      int new_len = (*plen*2 >= mess_len) ? *plen*2 : mess_len;
      //actlog(200, SLC->network()) << "readLengthPrefixed: requiring realloc of " << new_len
		//		  << ": " << mess_len << " > " << *plen << ende;
      delete [] (*pbuf);
      *pbuf = new char[new_len];
      *plen = new_len;
    }
  
  //try and get the data
  res = isFixedLengthDataAvailable(mess_len+sizeof(int));
  if (res != 1)
    return res;

  //we have to copy, skipping the sizeof(int) bytes at the beginning
  memcpy(*pbuf, read_buffer+sizeof(int), mess_len);
  memmove(read_buffer, read_buffer+sizeof(int)+mess_len, read_buffer_len - (sizeof(int) + mess_len));
  read_buffer_len -= sizeof(int) + mess_len;

  return mess_len;
}

bool
spades::ReadBuffFD::addToReadBuffer(const char* b, int l)
{
  if ( b == NULL || l <= 0 )
    return false;

  if (read_buffer_len + l > read_buffer_size)
    reallocReadBuffer(read_buffer_len + l);

  memcpy(read_buffer + read_buffer_len, b, l);
  read_buffer_len += l;
  return true;

}

void
spades::ReadBuffFD::reallocReadBuffer(int new_len)
{
#ifdef SANITY_CHECKING
  if (new_len > 1 << 16)
    errorlog << "ReadBuffFD::reallocReadBuffer: new_len seems really big: " << new_len << ende;
#endif	
  char* old_read_buffer = read_buffer;
  read_buffer = new char[new_len];
  memcpy(read_buffer, old_read_buffer, read_buffer_len);
  read_buffer_size = new_len;
  delete [] old_read_buffer;
}
