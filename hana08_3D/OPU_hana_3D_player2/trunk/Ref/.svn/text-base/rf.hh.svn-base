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















#ifndef __INC_BATS_RF_HH_
#define __INC_BATS_RF_HH_

#include "assert.hh"

namespace bats {

  /**
   *  The automated reference wrapper template.
   *
   *  This encapsulates an object pointer and uses reference counting
   *  to handle appropriate deallocation. The encapsulated object
   *  needs to implement the RefAble interface or at least have a
   *  compatible grab() and release() method (@see RefAble).
   *
   */
  template <class T>
  class rf {
    
    T *d_obj;

    void copy(rf<T> const &other)
    {
      d_obj = other.d_obj;

      if (d_obj)
        d_obj->grab();
    }

    template <class S>
    void copy2(rf<S> const &other)
    {
      d_obj = other.getPtr();

      if (d_obj)
        d_obj->grab();
    }

    void destroy()
    {
      if (d_obj && d_obj->release())
        delete d_obj;

      d_obj = 0;
    }

  public:

    rf(rf<T> const &other) { copy(other); }

    template <class S>
    rf(rf<S> const &other) { copy2(other); }

    ~rf() { destroy(); }

    /**
     */
    rf(T *obj) : d_obj(obj)
    { if (d_obj) d_obj->grab(); }

    rf() : d_obj(0) {}

    rf<T> &operator=(rf<T> const &other)
    {
      if (this != &other) {
        destroy();
        copy(other);
      }
      return *this;
    }

    /**
     *  @returns true if the two rf<T> objects hold the same pointer.
     */
    bool operator==(rf<T> const &other) const
    {
      return (d_obj == other.d_obj);
    }

    /**
     *  Compares pointer values.
     */
    bool operator<(rf<T> const &other) const
    {
      return (d_obj < other.d_obj);
    }

    /**
     *  Dereferences the pointer and compares the objects using their
     *  == operator.
     */
    bool equals(rf<T> const &other) const
    {
      assert(d_obj && other.d_obj);

      return (*d_obj == *other.d_obj);
    }

    /**
     *  Dereferences the pointer and compares the objects using their
     *  < operator.
     */
    bool smaller(rf<T> const &other) const
    {
      assert(d_obj && other.d_obj);

      return (*d_obj < *other.d_obj);
    }

    /**
     *  @returns false if the reference is NULL (pointer value is zero).
     */
    operator bool() const { return d_obj; }

    T *operator->()
    {
      assert(d_obj);
      return d_obj;
    }

    /**
     *  So you can use rf<X>->bla() to access X.bla().
     */
    T const *operator->() const
    {
      assert(d_obj);
      return d_obj;
    }

    /**
     *  @returns a c++ reference to the object (dangerous, you must always first check if
     *           it is allocated).
     */
    T &operator*()
    {
      assert(d_obj);
      return *d_obj;
    }

    /**
     *  @returns a const c++ reference to the object (dangerous, you must always first check if
     *           it is allocated).
     */
    T const &operator*() const
    {
      assert(d_obj);
      return *d_obj;
    }

    /**
     *  @returns the pointer of the encapsulated object.
     */
    T *getPtr() const { return d_obj; }

    /**
     *  Proxy for the [] operator.
     */
    template <class U, class K>
    U operator[](K index)
    {
      return (*d_obj)[index];
    }

  };

  /**
   *  Casts one rf<> reference to another rf<> reference.
   */
/*  template <typename To, typename From>
  rf<To> rf_cast(rf<From> &from)
  {
    return rf<To>(reinterpret_cast<To*>(&*from));
  }*/

  /**
   *  Casts one rf<> reference to another rf<> reference.
   */
  template <typename To, typename From>
  rf<To> rf_cast(rf<From> from)
  {
    return rf<To>(reinterpret_cast<To*>(from.getPtr()));
  }

 /**
   *  Casts one rf<> reference to another rf<> reference.
   */
  template <typename To, typename From>
  rf<To> rf_static_cast(rf<From> &from)
  {
    return rf<To>(static_cast<To*>(&*from));
  }

 /**
   *  Casts one rf<> reference to another rf<> reference.
   */
  template <typename To, typename From>
  rf<To> rf_dynamic_cast(rf<From> &from)
  {
    return rf<To>(dynamic_cast<To*>(&*from));
  }

};

#endif // __INC_BATS_RF_HH_
