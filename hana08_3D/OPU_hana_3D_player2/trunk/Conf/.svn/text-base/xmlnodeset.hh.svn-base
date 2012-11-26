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















#ifndef __INC_BATS_XMLNODESET_HH_
#define __INC_BATS_XMLNODESET_HH_

#include <libxml/xpathInternals.h>

#include <cassert>

#include <string>

namespace bats {

  /**
   *  A set of xml nodes.
   */
  class XMLNodeSet {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    struct Data {
      unsigned ref;
      xmlXPathObjectPtr xpathObj;
    };

#endif // DOXYGEN_SHOULD_SKIP_THIS

    Data *data;

    void destroy()
    {
      if (data && !--(data->ref)) {
	xmlXPathFreeObject(data->xpathObj);
	delete data;
      }
    }

    void copy(XMLNodeSet const &other)
    {
      data = other.data;
      data->ref++;
    }

  public:

    /**
     *  A xml nodes set iterator.
     */
    struct Iterator {
      xmlNodePtr *d_ptr;

      void copy(Iterator const &other)
      {
	d_ptr = other.d_ptr;

      }

      void destroy()
      {
      }

      Iterator(Iterator const &other)
      {
	copy(other);
      }

      Iterator(xmlNodePtr *ptr)
	: d_ptr(ptr) {}

      ~Iterator()
      {
	destroy();
      }
      
      Iterator &operator=(Iterator const &other)
      {
	if (this != &other) {
	  destroy();
	  copy(other);
	}
	return *this;
      }

      bool operator==(Iterator const &other) const
      {
	return d_ptr == other.d_ptr;
      }

      bool operator!=(Iterator const &other) const
      {
	return d_ptr != other.d_ptr;
      }

      XMLNode operator*()
      {
	return XMLNode(*d_ptr);
      }

      Iterator operator-(int value)
      {
	return Iterator(d_ptr - value);
      }

      Iterator operator+(int value)
      {
	return Iterator(d_ptr + value);
      }

      /**
       *  Increments the iterator>
       */
      void operator++()
      {
	d_ptr++;
      }

      /**
       *  Increments the iterator>
       */
      void operator++(int)
      {
	++d_ptr;
      }
    operator bool() const { return d_ptr; }

    };

    typedef Iterator iterator;

    XMLNodeSet()
      : data(0)
    {      
    }

    XMLNodeSet(XMLNodeSet const &other) { copy(other); }

    XMLNodeSet(xmlXPathObjectPtr node)
    {
      assert(node);

      if (node) {
	data = new Data;
	data->ref = 1;
	data->xpathObj = node;
      } else
	data = 0;
    }

    ~XMLNodeSet() { destroy(); }

    XMLNodeSet &operator=(XMLNodeSet const &other)
    {
      if (this != &other) {
	destroy();
	copy(other);
      }
      return *this;
    }

    /**
     *  @returns false when the node is NULL.
     */
    operator bool() const { return data; }

    /**
     *  @returns the number of nodes in the set.
     */
    unsigned size() const
    {
      assert(data->xpathObj->nodesetval);
      return (data?data->xpathObj->nodesetval->nodeNr:0);
    }

    /**
     *  @returns true when the set is empty.
     */
    bool empty() const
    {
//      assert(data->xpathObj->nodesetval);

      return !data || !data->xpathObj->nodesetval || data->xpathObj->nodesetval->nodeNr == 0;
    }

    /**
     *  Works the same way as stl iterators.
     */
    iterator begin() const
    {
      return (data && data->xpathObj && data->xpathObj->nodesetval?Iterator(data->xpathObj->nodesetval->nodeTab):Iterator(0));
    }

    /**
     *  Works the same way as stl iterators.
     */
    iterator end() const
    {
      return (data?Iterator(data->xpathObj->nodesetval->nodeTab + data->xpathObj->nodesetval->nodeNr):Iterator(0));
    }

    /**
     *  @returns the first element in the set.
     */
    XMLNode front() const
    {
      XMLNodeSet::Iterator f = begin();
      assert(f);
      return *f;
    }

    /**
     *  @returns the last element in the set.
     */
    XMLNode back() const
    {
      return *(end()-1);
    }


  };

};

#endif // __INC_BATS_XMLNODESET_HH_
