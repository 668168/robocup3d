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

#include "commserver.h"
#include <netinet/in.h>
#include "Settings.h"
#include "Logger.h"

using namespace std;
#ifdef ENABLE_LOG
extern FileLogger msgLog;
#endif

CommServer::CommServer()
    : mReadFd(3), mWriteFd(4), rdfd(mReadFd)
{
    mBufferSize = default_read_buffer_size;
    mBuffer = new char[mBufferSize];
}

CommServer::~CommServer()
{
    delete [] mBuffer;
}

bool
CommServer::SelectInput()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(mReadFd,&readfds);

    return select(mReadFd+1,&readfds, 0, 0, 0) > 0;
}

void
CommServer::PutOutput(const char* out)
{
    strcpy(mBuffer + sizeof(unsigned int), out);
    unsigned int len = strlen(out);
    unsigned int netlen = htonl(len);
    memcpy(mBuffer,&netlen,sizeof(netlen));
    write(mWriteFd, mBuffer, len + sizeof(netlen));
#ifdef ENABLE_LOG
	msgLog.log(out);
	msgLog.log("\n");
#endif
}

bool
CommServer::GetInput()
{
    for (int count = 0; count < 100; count++)
        {
            
            int res = rdfd.readLengthPrefixed(&mBuffer, &mBufferSize);
            if (res < 0)
                {
                    //GetLog()->Debug() << "CommServer::GetInput: readLeangthPrefixed returned -1\n";
                    return false;
                }
            else if (res > 0)
                {
                    // successful read
                    if (static_cast<unsigned int>(res) == mBufferSize)
                        {
                            //GetLog()->Debug() << "CommServer::GetInput: read exactly buffer size! can't null term\n";
                            return false;
                        }
                    mBuffer[res] = 0;
                    return true;
                }

            // if we are here, res == 0, which means not enough input

            // this blocks until more input
            if (! SelectInput())
                {
                    //GetLog()->Debug() << "CommServer::GetInput select returned false\n";
                    return false;
                }
        }

    //GetLog()->Debug() << "CommServer::GetInput: fell out of for loop\n";
    return false;
}
