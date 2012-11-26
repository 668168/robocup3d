/*
 *  Little Green BATS (2006)
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *  Date: 	September 14, 2006
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
 *		Foundation; either version 2 of the License, or (at 
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


#include "socket.hh"

namespace mvds {

  Socket::Socket(int _domain, int _type, int _protocol)
  : refcnt(new unsigned)
  {
    (*refcnt) = 1;

    // This is very, very scary, but it doesn't work without it!!??
    socket_handle = ::socket(_domain,_type,_protocol);
    socket_handle = ::socket(_domain,_type,_protocol);

    if (socket_handle == -1)
      throw std::runtime_error("error creating the socket");
//    std::cerr << "Socket: " << socket_handle << std::endl;
  }


};
