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








#ifndef __INC_BATS_BATSEXCEPTION_HH_
#define __INC_BATS_BATSEXCEPTION_HH_

#include <stdexcept>
#include <sstream>

namespace bats {

  /** Our Very Own Exception
   *
   *  This is used for the exeption trace generated at some of the Behavior classes.
   */
  class BatsException : public std::exception {

    std::stringstream d_messages;

    void copy(BatsException const &other)
    {
//       d_messages = other.d_messages;
    }

    void destroy()
    {
    }

    BatsException(BatsException const &); // NI
    BatsException &operator=(BatsException const &); // NI

  public:

    BatsException(std::string const msg)
    {
      d_messages << msg << std::endl;
    }

    BatsException(std::string const &filename, unsigned line, std::string const msg)
    {
      d_messages << filename << ":" << line << ": " << msg << std::endl;
    }

/*    
    BatsException(BatsException const &other)
    {
      copy(other);
    }

    BatsException &operator=(BatsException const &other)
    {
      if (this != &other) {
	destroy();
	copy(other);
      }
      return *this;
    }
*/    

    std::stringstream &messages() { return d_messages; }

    virtual char const *what() const throw () { return d_messages.str().c_str(); }

    virtual ~BatsException() throw () { destroy(); }

  };


};

#define BATS_CATCH_FRAME(e) e->messages() << __FILE__ << ":" << __LINE__ << std::endl; throw e


#endif // __INC_BATS_BATSEXCEPTION_HH_
