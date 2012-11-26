/*
 *  Little Green BATS (2007), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	July 27, 2007
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */





#ifndef __INC_MVDS_TIMEVAL_H_
#define __INC_MVDS_TIMEVAL_H_

#ifndef __SYSINC_SYS_TIME_H_
#define __SYSINC_SYS_TIME_H_
#include <sys/time.h>
#endif

#ifndef __SYSINC_TIME_H_
#define __SYSINC_TIME_H_
#include <time.h>
#endif

#ifndef __SYSINC_IOSTREAM
#define __SYSINC_IOSTREAM
#include <iostream>
#endif

namespace mvds {

  /**
   *  Timeval encapsulation
   *
   *  (see: man gettimeofday).
   */
  class TimeVal {

    friend std::ostream &operator<<(std::ostream &, const TimeVal &);

    struct timeval tv;

    void copy(TimeVal const &_other)
      {
	tv.tv_sec = _other.tv.tv_sec;
	tv.tv_usec = _other.tv.tv_usec;
      }

    void destroy()
      {
      }

  public:

    /**
     *  @returns the current time.
     */
    static TimeVal getTimeOfDay();

    /**
     *  Initializes to zero.
     */
    TimeVal()
      {
	tv.tv_sec = 0;
	tv.tv_usec = 0;
      }

    TimeVal(TimeVal const &other)
      {
	copy(other);
      }

    /**
     *  Initializes to sec seconds and usec microseconds.
     *
     */
    TimeVal(time_t sec, suseconds_t usec)
      {
	tv.tv_sec  = sec;
	tv.tv_usec = usec;
      }

    TimeVal(struct timeval const &_tv)
      {
	tv.tv_sec  = _tv.tv_sec;
	tv.tv_usec = _tv.tv_usec;
      }

    ~TimeVal()
      {
	destroy();
      }

    TimeVal &operator=(TimeVal const &_other)
      {
	if (this != &_other) {
	  destroy();
	  copy(_other);
	}
	return *this;
      }

    operator struct timeval &()
      {
	return tv;
      }

    operator struct timeval *()
      {
	return &tv;
      }

    bool operator==(TimeVal const &_other) const
      {
	return ((tv.tv_sec == _other.tv.tv_sec) &&
		(tv.tv_usec == _other.tv.tv_usec));
      }

    bool operator!=(TimeVal const &_other) const
      {
	return ((tv.tv_sec != _other.tv.tv_sec) ||
		(tv.tv_usec != _other.tv.tv_usec));
      }

    bool operator>(TimeVal const &_other) const
      {
	return ((tv.tv_sec > _other.tv.tv_sec) ||
		((tv.tv_sec == _other.tv.tv_sec) &&
		 (tv.tv_usec > _other.tv.tv_usec)));
      }

    bool operator<(TimeVal const &_other) const
      {
	return ((tv.tv_sec < _other.tv.tv_sec) ||
		((tv.tv_sec == _other.tv.tv_sec) &&
		 (tv.tv_usec < _other.tv.tv_usec)));
      }

    bool operator>=(TimeVal const &_other) const
      {
	return ((tv.tv_sec >= _other.tv.tv_sec) ||
		((tv.tv_sec == _other.tv.tv_sec) &&
		 (tv.tv_usec >= _other.tv.tv_usec)));
      }

    bool operator<=(TimeVal const &_other) const
      {
	return ((tv.tv_sec <= _other.tv.tv_sec) ||
		((tv.tv_sec == _other.tv.tv_sec) &&
		 (tv.tv_usec <= _other.tv.tv_usec)));
      }

    TimeVal operator+(TimeVal const &_other) const
      {
	return TimeVal((tv.tv_sec + _other.tv.tv_sec) + ((tv.tv_usec + _other.tv.tv_usec) / 1000000),
		       (tv.tv_usec + _other.tv.tv_usec) % 1000000);
      }

    TimeVal operator-(TimeVal const &_other) const
      {
	struct timeval res;

	res.tv_sec = (tv.tv_sec - _other.tv.tv_sec);

	if (tv.tv_usec < _other.tv.tv_usec) {
	  res.tv_sec -= (1 + (_other.tv.tv_usec - tv.tv_usec) / 1000000);
	  res.tv_usec = (1000000 - ((_other.tv.tv_usec - tv.tv_usec) % 1000000));
	} else
	  res.tv_usec = (tv.tv_usec - _other.tv.tv_usec);

	return TimeVal(res);
      }

    /**
     *  @returns a float of the time in seconds.
     */
    float getRealSeconds() const
    {
      return tv.tv_sec + tv.tv_usec / 1000000.0;
    }

  };

  std::ostream &operator<<(std::ostream &_os, const TimeVal &_tv);

};

#endif //  __INC_MVDS_TIMEVAL_H_
