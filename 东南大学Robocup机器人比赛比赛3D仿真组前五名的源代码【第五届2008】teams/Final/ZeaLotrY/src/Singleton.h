/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * Additionally,this program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ****************************************************************************************/

 
#ifndef _SINGLETON_H
#define _SINGLETON_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include <cassert>

#define NO_ASSERT

#ifndef NO_ASSERT
#define ASSERT assert
#else
#define ASSERT(x);
#endif

template <typename T> class Singleton
{
	static T* ms_Singleton;

public:
	Singleton( void )
	{
		assert( !ms_Singleton );
		int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
		ms_Singleton = (T*)((int)this + offset );
	}
	~Singleton( void )
	{
		ASSERT( ms_Singleton );
		ms_Singleton = 0;
	}
	static T& GetSingleton( void )
	{
		ASSERT( ms_Singleton );
		return ( *ms_Singleton );
	}
	static T* GetSingletonPtr( void )
	{
		ASSERT( ms_Singleton );
		return ( ms_Singleton );
	}
};

template <typename T> T* Singleton <T>::ms_Singleton = 0;

#ifdef NO_ASSERT
#undef NO_ASSERT
#undef ASSERT
#endif

#endif /* _SINGLETON_H */
