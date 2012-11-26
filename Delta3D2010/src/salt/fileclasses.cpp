/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: fileclasses.cpp 76 2009-07-27 07:02:56Z hedayat $

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

#include "fileclasses.h"
#include <cstring>
#include <cstdlib>

#if HAVE_CONFIG_H
#include <sparkconfig.h>
#endif

#if USE_COREFOUNDATION
#if HAVE_COREFOUNDATION_COREFOUNDATION_H
#include <CoreFoundation/CoreFoundation.h>
#endif
#endif

namespace salt
{
/*static long fsize(FILE *f)
{
	long savepos, end;

	savepos = ftell(f);
	fseek(f, 0, SEEK_END);
	end = ftell(f);
	fseek(f, savepos, SEEK_SET);

	return end;
}*/
}

using namespace salt;

std::string
RFile::Sep()
{
#ifdef WIN32
    return "\\";
#else
    return "/";
#endif
}

std::string
RFile::BundlePath()
{
#if USE_COREFOUNDATION
#if HAVE_COREFOUNDATION_COREFOUNDATION_H
    char path[1024];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    assert(mainBundle);

    CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
    assert(mainBundleURL);

    CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
    assert(cfStringRef);

    CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);

    CFRelease(mainBundleURL);
    CFRelease(cfStringRef);

    return std::string(path) + Sep();
#endif
#else
    const char *envPrefix = getenv("SPARK_DIR");
    if (envPrefix)
        {
            return envPrefix + Sep() + "share" + Sep() + PACKAGE_NAME + Sep();
        }
# ifdef PREFIX
    return PREFIX + Sep() + "share" + Sep() + PACKAGE_NAME + Sep();
# else
    return "." + Sep();
# endif
#endif
}

//------------------------------------------------------------------------------------------------
// MemFile
//------------------------------------------------------------------------------------------------

MemFile::MemFile(const char *fn, const char *mode)
{
	if(fn==NULL)
	{
		mHandle		= NULL;
		mCharHandle	= NULL;
		mSize		= 0;
		mPosition	= 0;
	}
	else
	{
		Open(fn, mode);
	}
}

MemFile::MemFile(FILE *f)
{
  fseek(f,0,SEEK_END);
  mSize = ftell(f);
  rewind(f);

	mHandle		= new unsigned char[mSize];
	mCharHandle	= (unsigned char*)mHandle;
	mPosition	= 0;
	fread(mHandle,1,mSize,f);
}

MemFile::MemFile(RFile *f)
{
	mSize=f->Size();
	mHandle=new unsigned char[mSize];
	mCharHandle=(unsigned char*)mHandle;
	f->Read(mHandle,mSize);
	mPosition=0;
}

MemFile::~MemFile()
{
	if(mHandle!=NULL)
		Destroy();
}

bool MemFile::Open(const char *fn, const char *mode)
{
	if(fn==NULL)
		return false;
	else
	{
		StdFile* f = new StdFile(fn, mode);
		if(f->GetHandle())
		{
			mSize		= f->Size();
			mCharHandle	= new unsigned char[mSize];
			mHandle		= mCharHandle;
			mPosition	= 0;
			f->Read(mHandle, mSize);
			delete f;
			return true;
		}
		else
		{
			delete f;
			return false;
		}
	}
}

bool MemFile::Open(void *buffer, long s)
{
	mHandle		= buffer;
	mCharHandle	= (unsigned char*)mHandle;
	mSize		= s;
	mPosition	= 0;
	return true;
}

void MemFile::Close()
{
	Destroy();
}

void MemFile::Destroy()
{
	if(mHandle!=NULL)
	{
	  delete mCharHandle;
		mHandle		= NULL;
		mCharHandle	= NULL;
		mSize		= 0;
		mPosition	= 0;
	}
}

int MemFile::Eof()
{
	return (mPosition>=mSize);
}

long MemFile::Tell()
{
	return mPosition;
}

int MemFile::GetPos(long *pos)
{
	*pos=Tell();
	return 1;
}

int MemFile::Seek(long offset, int origin)
{
	switch(origin){
		case SEEK_SET:
			return (mPosition=offset);
			break;
		case SEEK_END:
			return (mPosition=mSize-1-offset);
			break;
		default:
			return (mPosition+=offset);
			break;
	}
}

void MemFile::Rewind()
{
	mPosition=0;
}

long MemFile::Size()
{
	return mSize;
}

char* MemFile::Gets(char* buffer, int n)
{
	int i		= 0;
	bool done	= false;

	if(Eof()) return NULL;

	while(!done)
	{
		buffer[i]=mCharHandle[mPosition];
		mPosition++;
		i++;
		if((i==n)||(buffer[i-1]=='\n')||(Eof())) done=true;
	}
	buffer[i]=0;
	return buffer;
}

int MemFile::Getc()
{
	mPosition++;
	if((mPosition-1)>=mSize)
		return EOF;
	else
		return (int)(mCharHandle[(mPosition-1)]);
}

size_t MemFile::Read(void *buffer, size_t size, size_t count)
{
	long oldPos = mPosition;

	mPosition += static_cast<long>(size*count);
	if(mPosition >= mSize)
	{
		memcpy(buffer, &mCharHandle[oldPos], (mSize-oldPos));
		return (mSize-oldPos);
	}
	else
	{
		memcpy(buffer, &mCharHandle[oldPos], size*count);
		return (count);
	}
}

//------------------------------------------------------------------------------------------------
// StdFile
//------------------------------------------------------------------------------------------------

StdFile::StdFile(FILE* h)
{
	//Make sure object is free
	Destroy();
	//Assign new mHandle
	mHandle=h;
}

StdFile::StdFile(const char* fn,const char* mode)
{
	mHandle=NULL;
	//open file
	Open(fn,mode);
}

StdFile::~StdFile()
{
	//Free up memory
	Destroy();
}

void StdFile::Destroy()
{
	//Close file
	Close();
}

void StdFile::Close()
{
	//Close file
	if(mHandle!=NULL)
		fclose((FILE*)mHandle);

	mHandle = NULL;
}

bool StdFile::Open(const char* fileName,const char* mode)
{
	//Open fn with mode mode
	if(fileName==NULL)
		return false;
	else
	{
		mHandle=fopen(fileName, mode);
		if(mHandle==NULL)
			return false;
		else
			return true;
	}
}

int StdFile::Eof()
{
	return feof((FILE*)mHandle);
}

long StdFile::Tell()
{
	return ftell((FILE*)mHandle);
}

long StdFile::Size()
{
  long pos = ftell((FILE*)mHandle);
  fseek((FILE*)mHandle,0,SEEK_END);
  long size = ftell((FILE*)mHandle);
  fseek((FILE*)mHandle,pos,SEEK_SET);
  return size;
}

int StdFile::GetPos(long* /*pos*/)
{
  return ftell((FILE*)mHandle);
}

void StdFile::Rewind()
{
	rewind((FILE*)mHandle);
}

char* StdFile::Gets(char* buffer, int n)
{
	return fgets(buffer, n, (FILE*)mHandle);
}

int StdFile::Getc()
{
	return fgetc((FILE*)mHandle);
}

int StdFile::Puts(const char*s)
{
	return fputs(s, (FILE*)mHandle);
}

int StdFile::Putc(int c)
{
	return fputc(c, (FILE*)mHandle);
}

int StdFile::Seek(long offset, int origin)
{
	return fseek((FILE*)mHandle, offset, origin);
}

size_t StdFile::Read(void *buffer,size_t mSize,size_t count)
{
	return fread(buffer, mSize, count, (FILE*)mHandle);
}

size_t StdFile::Write(void *buffer,size_t mSize,size_t count)
{
	return fwrite(buffer, mSize, count, (FILE*)mHandle);
}

void* StdFile::GetHandle()
{
	return (void*) mHandle;
}
