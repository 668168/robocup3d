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

/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: commserver.h,v 1.1.1.1 2006/01/04 06:06:21 xy Exp $

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
#ifndef COMMSERVER_H
#define COMMSERVER_H

#include <string>
#include "ReadBuffFD.h"
#include "Singleton.h"

class CommServer : public Singleton<CommServer>
{
public:
    CommServer();
    virtual ~CommServer();

    bool GetInput();
    void PutOutput(const char* out);
    void PutOutput(const std::string& str) { PutOutput(str.c_str()); }

    const char* GetMsg() const { return mBuffer; }
	unsigned int getMsgSize() const { return mBufferSize;}

protected:
    bool SelectInput();

protected:
    // the input file descriptor
    const int mReadFd;

    // the output file descriptor
    const int mWriteFd;

    // the receive buffer
    char* mBuffer;
    unsigned int mBufferSize;

private:
    spades::ReadBuffFD rdfd;
};

#define COMM CommServer::GetSingletonPtr()

#endif // COMMSERVER_H
