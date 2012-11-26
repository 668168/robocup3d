/*
 *  Little Green BATS (2008), AI department, University of Groningen
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
 *  Date: 	November 1, 2008
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

#ifndef __INC_BATS_PATH_HH_
#define __INC_BATS_PATH_HH_

#include <string>
#include <list>

namespace bats {

  class AST;

  /**
   *  This is used for the Path expressions used by predicate. They are
   *  similar to XPath expressions but with less functionality.
   *  (@see Predicate).
   *
   *  Expressions:
   *  - "/"          gives the root element.
   *  - "/X/Y"       gives all Y elements of all X elements in the root.
   *  - "X/Y"        gives all Y elements of all X elements anywhere in the tree.
   */
  class Path {

    //    friend class AST::Node;
    friend class XMLNode;

  public: // temporary hack..
    
    std::list<std::string> path;

  private:

    void init(std::string const& _path);
    
    void copy(Path const &_other)
    {
      path = _other.path;
    }

    void destroy()
    {
    }

  public:

    Path(Path const &_other)
    {
      copy(_other);
    }

    Path(char const* _path);
    
    Path(std::string const &_path);

    Path &operator=(Path const &_other)
    {
      if (this != &_other) {
        destroy();
        copy(_other);
      }
      return *this;
    }

  };
}

#endif // __INC_BATS_PATH_HH_
