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

#ifndef _BATS_SINGLETON_HH_
#define _BATS_SINGLETON_HH_

#include <stdexcept>

namespace bats
{
  /**
   * A template to turn any class into a Singleton. To use it on your class:
   * - Define your class's constructor and assignment operator as private
   * - Your class must have a default constructor
   * - Make the singleton a friend of your class.
   * - If your class needs parameters, overload the Params class, define a constructor accepting a Singleton::Params* and use Singleton<T>::initialize<I>(Params*)
   *
   * Example:
   *   \code
       class MyClass
       {
         friend class Singleton<MyClass>;
         ...
       private:
         MyClass();
         MyClass& operator=(MyClass const& other); // Not Implemented
         ...
       };
       \endcode
   */
  template <typename T>
  class Singleton
  {
  public:
    class Params
    {
      public:
        virtual ~Params() {}
    };
    
    /** Initialize the singleton with a new instance of the given type.
    */
    static void initialize()
    {
      if (s_instance)
        delete s_instance;
      s_instance = new T();
    }

    /** Initialize the singleton with a new instance of the given type with parameters
      * @params parameters to be passed to the classes construction
    */
    static void initialize(Params* params)
    {
      if (s_instance)
        delete s_instance;
      s_instance = new T(params);
    }
    
    /** Initialize the singleton with a new instance of the given derived class type.
      * With this method, it is possible to create different derived class type from
      * same abstract singleton type.
    */
    template <typename I>
    static void initialize()
    {
      if(s_instance)
        delete s_instance;
      s_instance = new I();      
    }
    
    /** Initialize the singleton with a new instance of the given type with parameters
      * With this method, it is possible to create different derived class type from
      * same abstract singleton type.
      * @params parameters to be passed to the classes construction

    */
    template <typename I>
    static void initialize(Params *params)
    {
      if(s_instance)
        delete s_instance;
        
      s_instance = new I(params);
    }

    static bool initialized()
    {
      return s_instance? true : false;
    }
    
    /**
     * Get a reference to the only instance of class \a T
     */
    static T& getInstance() {
      if(s_instance == 0)
        throw std::runtime_error("A Singleton must be initialized before use. Call initialize first.");
        
      return *s_instance;
    }
  private:
    static T* s_instance;
    Singleton();
    ~Singleton();
    Singleton(Singleton const&);
    Singleton& operator=(Singleton const&);
  };
  
  template <typename T>
  T* Singleton<T>::s_instance = 0;
}

#endif
