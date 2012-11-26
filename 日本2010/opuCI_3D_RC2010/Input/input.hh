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










#ifndef __INCLUDED_INPUT_HH__
#define __INCLUDED_INPUT_HH__

#include <string>
#include <cstdio>
#include <sys/select.h>

namespace bats
{
class Input
{
		int fid;
		fd_set rfds;
		std::string d_buf;
		static Input *s_instance;
		
		Input()
		{
			fid = 0;
		}
	public:

		bool open()
		{
			return feof(stdin) == 0;	//use fdopen
		}
		std::string line()
		{
			std::string::size_type i = d_buf.find('\n');
			if(std::string::npos == i)
				return "";
			
			std::string l = d_buf.substr(0, i);
			d_buf.erase(0, i+1);
			return l;
		}
		void readUp()
		{
			char buf[256];
			size_t s = read(fid, &buf, 255);
			buf[s] = '\0';
			d_buf += buf;
		}
		void collect()
		{
			struct timeval tv;
			int retval;
			//Select, read
			FD_ZERO(&rfds);
      FD_SET(fid, &rfds);

      /* Wait up to five seconds. */
      tv.tv_sec = 0;
      tv.tv_usec = 0;

      retval = select(1, &rfds, NULL, NULL, &tv);
      /* Don’t rely on the value of tv now! */

      if (retval == -1)
          perror("select()");
      else if (retval)
          readUp();
//          /* FD_ISSET(0, &rfds) will be true. */
//      else
//          printf("No data within five seconds.\n");
//      return 0;
		}
		
		static Input &getInstance()
		{
			if(s_instance)
				return *s_instance;
			s_instance = new Input();
			return *s_instance;
		}
		bool lineReady()
		{
			return d_buf.rfind('\n') != std::string::npos;
		}
};
} //namespace
#endif
