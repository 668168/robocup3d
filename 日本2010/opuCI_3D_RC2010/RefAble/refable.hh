#ifndef __INC_BATS_REFABLE_HH_
#define __INC_BATS_REFABLE_HH_

namespace bats {


  /**
   *  RefAble is a necessary baseclass for all objects
   *  that can be referenced using the rf<> system.
   */
  class RefAble {

    // This can be mutable, because it doesn't change
    // the meaning of the object when its value changes.
    mutable unsigned d_refCount;

    RefAble(RefAble const &); // NI
    RefAble operator=(RefAble const &); // NI

  public:

    RefAble() : d_refCount(0) {}

    /**
     *  This increments the reference count.
     */
    inline void grab() const
    {
      // The lock operand ensures that the memory is
      // only accessed by one thread at the same time.
      /* This is not portable..
      asm volatile (
	   "lock incl %0\n\t"
	   : "=m" (d_refCount)
	     //	   : "m" (x)
	     //		  : "memory"
	   );
      */
      ++d_refCount;
    }

    /**
     *  This decrements the reference count.
     *
     *  @returns true when the reference count is zero.
     */
    inline bool release() const
    {
      bool res = false;

      // The lock operand ensures that the memory is
      // only accessed by one thread at the same time.

      // We don't need a lock like thing with setz, because it
      // uses the result flags of decl! Isn't that cool?
      // I think we need to do it like this because of the above
      // reason. Otherwise we might return d_refCount.

      /* This is not portable...
      asm volatile (
	   "lock decl %0\n\t"
	   "setz %1\n\t"
	   : "=m" (d_refCount),
	     "=m" (res)
	     //	   : "m" (x)
	     //		  : "memory"
	   );
      */

      res = !--d_refCount;

      return res;
    }


  };


};

#endif // __INC_BATS_REFABLE_HH_
