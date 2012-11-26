/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: rect.h 56 2009-03-17 18:03:47Z hedayat $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifndef SALT_RECT_H
#define SALT_RECT_H

#include "salt_defines.h"

namespace salt
{

/** this class provides rectangle in two dimensional space */
class SALT_API Rect
{
public:
    /** constucts undefined Rect for performance reasons */
    f_inline                Rect()                                                                                                  { }
    /** copy constructs a Rect from inOther */
    f_inline                Rect(const Rect &inOther)                                                               : mLeft(inOther.Left()), mTop(inOther.Top()), mRight(inOther.Right()), mBottom(inOther.Bottom()) { }

    /** constructs a Rect from the coordinates inLeft, inTop, inRight and inBottom */
    f_inline                Rect(int inLeft, int inTop, int inRight, int inBottom)  : mLeft(inLeft), mTop(inTop), mRight(inRight), mBottom(inBottom) { }

    /** sets up a Rect from the coordinates inLeft, inTop, inRight and inBottom */
    f_inline void   Set(int inLeft, int inTop, int inRight, int inBottom)   { mLeft=inLeft; mTop=inTop;                     mRight=inRight;                                                 mBottom=inBottom; }

    // member access
    /** returns the left boundary of the rectangle */
    f_inline int    Left() const                    { return mLeft; }

    /** return the right boundary of the rectangle */
    f_inline int    Right() const                   { return mRight; }

    /** return the top boundary of the rectangle */
    f_inline int    Top() const                     { return mTop; }

    /** return the bottom boundary of the rectangle */
    f_inline int    Bottom() const                  { return mBottom; }

    /** calculates the width of the rectangle */
    f_inline int    Width() const                   { return mRight-mLeft; }

    /** calculates the height of the rectangle */
    f_inline int    Height() const                  { return mBottom-mTop; }

    /// Actions
    /** normalizes the rectangle coordinates, i.e. assures that right>left and top>bottom. */
    f_inline void   Normalize()                                                                             { if (mRight < mLeft) gSwap(mLeft, mRight); if (mBottom < mTop) gSwap(mTop, mBottom); }

    /** widens the rectangle about inDelta */
    f_inline void   Widen(int inDelta)                                                              { mLeft-=inDelta; mTop-=inDelta; mRight+=inDelta; mBottom+=inDelta;     }

    /** widens the rectangle horizontally about inDeltaWidth and
     * vertically about inDeltaHeight
     */
    f_inline void   Widen(int inDeltaWidth, int inDeltaHeight)              { mRight+=inDeltaWidth; mBottom+=inDeltaHeight; }

    /** widens the rectangles left boundary about inDeltaleft, the right
     * boundary about inDeltaRigt, the top boundary about inDeltaTop
     * and the bottom boundary about inDeltaBottom
     */
    f_inline void   Widen(int inDeltaLeft, int inDeltaTop, int inDeltaRight, int inDeltaBottom)     { mLeft-=inDeltaLeft; mTop-=inDeltaTop; mRight+=inDeltaRight; mBottom+=inDeltaBottom;           }

    /** shrinks the rectangle about inDelta */
    f_inline void   Shrink(int inDelta)                                                             { mLeft+=inDelta;       mTop+=inDelta;  mRight-=inDelta; mBottom-=inDelta;      }

    /** shrinks the rectangle horizontally about inDeltaWidth and
     * vertically about inDeltaHeight
     */
    f_inline void   Shrink(int inDeltaWidth, int inDeltaHeight)             { mRight-=inDeltaWidth; mBottom-=inDeltaHeight; }

    /** shrinks the rectangles left boundary about inDeltaleft, the right
     * boundary about inDeltaRigt, the top boundary about inDeltaTop
     * and the bottom boundary about inDeltaBottom
     */
    f_inline void   Shrink(int inDeltaLeft, int inDeltaTop, int inDeltaRight, int inDeltaBottom) { mLeft+=inDeltaLeft; mTop+=inDeltaTop; mRight-=inDeltaRight; mBottom-=inDeltaBottom;              }

    /** moves the rectangle horizontally inDeltaX and vertically inDeltaY */
    f_inline void   Offset(int inDeltaX, int inDeltaY)                              { mLeft+=inDeltaX;      mTop+=inDeltaY; mRight+=inDeltaX;       mBottom+=inDeltaY; }

    /** returns true if this rectangle intersects with the rectangle b */
    f_inline bool   Intersects(const Rect &b) const                                 { return !(mLeft > b.mRight || mRight < b.mLeft || mTop > b.mBottom || mBottom < b.mTop); }

    // assignment

    /** sets up the rectangle from inOther */
    f_inline Rect&          operator=(const Rect &inOther)                                                          { mLeft=inOther.Left(); mTop=inOther.Top();     mRight=inOther.Right(); mBottom=inOther.Bottom(); return *this; }

    // comparison

    /** returns true if inRhs is equal to this rectangle */
    f_inline bool           operator==(const Rect &inRHS) const                                                     { return (mLeft==inRHS.Left()) && (mTop==inRHS.Top()) && (mRight==inRHS.Right()) && (mBottom==inRHS.Bottom()); }

    /** returns true if inRhs differs from this rectangle */
    f_inline bool           operator!=(const Rect &inRHS) const                                                     { return (mLeft!=inRHS.Left()) || (mTop!=inRHS.Top()) || (mRight!=inRHS.Right()) || (mBottom!=inRHS.Bottom()); }

private:
    /** the left boundary */
    int mLeft;

    /** the top boundary */
    int mTop;

    /** the right boundary */
    int mRight;

    /** the bottom boundary */
    int mBottom;
};

} //namespace salt

#endif //SALT_RECT_H
