/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * $Id: Logger.h,v 1.1.1.1 2006/09/15 02:03:05 Administrator Exp $
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

 
#ifndef _LOGGER_H
#define _LOGGER_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include <iostream>   //-*  needed for ostream (logging to output stream)
#include <fstream>    //-*  needed for fstream (logging to file)
#include <string>     //-*  needed for string
#include <iomanip>    //-*  needed for setw
#include <set>        //-*  needed for set
#include <vector>
#include <ctime>      //-*  needed for log year month day time
#include <sys/time.h> //-*  needed for timeval
#include <sstream>
#include "Geometry.h"
#include "Singleton.h"
#include "LogData.h"

using namespace std;

/** define some color */
const Vector3f colorRed(1,0,0);
const Vector3f colorGreen(0,1,0);
const Vector3f colorBlue(0,0,1);
const Vector3f colorWhite(1,1,1);
const Vector3f colorBlack(0,0,0);
const Vector3f colorPink(1.0f, 0.5f, 0.5f);


class WorldModel;
/*****************************************************************************/
/**************************** LOGGER *****************************************/
/*****************************************************************************/
class Logger : public Singleton <Logger>
{
private:
	char     _buf[MAX_LOG_LINE];    //-*  buffer needed by different methods  
#ifdef ENABLE_LOG
	set<int> _setLogLevels;         //-*  set that contains all log levels     
	ostream* mOS;                   //-*  output stream to print messages to   
	Time	_timeLogged;	//-* indicate the current info have print

	vector<string>	_functions;
#endif

public:	
#ifdef ENABLE_LOG
	Logger( ostream& os=cout, int iMinLogLevel=0, int iMaxLogLevel = 0);
	
	bool	addLogLevel( int iLevel);
	bool	addLogRange( int iMin, int iMax);

	bool	log( int iLevel , string str );
	bool	log( int iLevel , char *str, ... );
	void	logTable();
	void	flush();
	void	functionBegin(const string &name);
	void	functionEnd();
#else
	~Logger(){};
#endif

	void	logErr( string str );
	void	logErr( char *str, ... );
	
#ifdef ENABLE_LOG
protected:
	int		normalizeLogLevel( int iLevel );
	void	printTree( int iLevel );
	bool	isInLogLevel( int iLevel );
	char*	repeatChar( char c, int n );
#endif
};
/*****************************************************************************/
/**************************** LOG FLAG ***************************************/
/*****************************************************************************/
#ifdef ENABLE_LOG
class LogFlag
{
public:
	LogFlag(const char* name1,const char* name2);
	~LogFlag(){ Logger::GetSingletonPtr()->functionEnd(); }
};
#endif

#ifdef ENABLE_LOG
#define LOGPTR	Logger::GetSingletonPtr()
#define LOG 	Logger::GetSingletonPtr()->log
#define ADDLOG	Logger::GetSingletonPtr()->addLogLevel
#define LOGTABLE Logger::GetSingletonPtr()->logTable()
#define WRITELOG Logger::GetSingletonPtr()->flush()
#define LOGBEGIN LogFlag logFlagInstance(__FILE__,__FUNCTION__)
#else
#define LOGPTR
#define LOG(...)
#define ADDLOG(...)
#define LOGTABLE
#define WRITELOG
#define LOGBEGIN
#endif
#define LOGERR	Logger::GetSingletonPtr()->logErr("ERROR in File:  %s  Line:  %d ",__FILE__,__LINE__);Logger::GetSingletonPtr()->logErr

/*****************************************************************************/
/**************************** FILE LOGGER ************************************/
/*****************************************************************************/
#ifdef ENABLE_LOG
class FileLogger
{
protected:
    FILE* _filePtr;
    char _fileName[100];
	bool _enabled;


public:
	FileLogger();
	FileLogger( const char* logname );
	~FileLogger();

	bool	openFile( const char* logname );
	void	log( const string& log_str );
	void	log( const char* log_msg, ... );
	void	enable() { _enabled = true; }
	void	disable() { _enabled = false; }
	void	flush() { if ( _filePtr != NULL ) fflush(_filePtr); }
	
protected:
	bool	openFile( const char* logname, const char* teamname, unsigned int id );

};
#endif

/*****************************************************************************/
/**************************** LOGGER *****************************************/
/*****************************************************************************/
#ifdef ENABLE_GL_LOG
class GraphicLogger : public Singleton <GraphicLogger>
{
private:
	set<string>  _setLogLevels;       // set that contains all log levels     
	ostream&     _OS;                 // output stream to print messages to   
	LogLevel     _data;               // the log data

public:
	GraphicLogger( ostream& os=cout );
	
	~GraphicLogger(){};
	
	void	addLogLevel( const string& level );

	int     getLevelIndex(const string& strLevel)const;

	void    logSphere(const string& level, const Vector3f& pos, float r);
	void    logSphere(const string& level, const Vector3f& pos, float r, const Vector3f& rgb);
	
	void    logRectangle(const string& level, const Vector3f& pos, float szX, float szY);
	void    logRectangle(const string& level, const Vector3f& pos, float szX, float szY, const Vector3f& rotation);
	void    logRectangle(const string& level, const Vector3f& pos, float szX, float szY, const Vector3f& rotation, const Vector3f& rgb);
	
	void    logCircle(const string& level, const Vector3f& pos, float r);
	void    logCircle(const string& level, const Vector3f& pos, float r, const Vector3f& rotation);
	void    logCircle(const string& level, const Vector3f& pos, float r, const Vector3f& rotation, const Vector3f& rgb);		
	
	void    logLine(const string& level, const Vector3f& x0, const Vector3f& x1);
	void    logLine(const string& level, const Vector3f& x0, const Vector3f& x1, const Vector3f& rgb);		

	void    logText(const string& level, const Vector3f& pos, const string& str);
	void    logText(const string& level, const Vector3f& pos, const char *str, ...);
	void    logText(const string& level, const Vector3f& pos, const Vector3f& rgb, const string& str);
	void    logText(const string& level, const Vector3f& pos, const Vector3f& rgb, const char *str, ... );
		
	void    logPrint(const string& level, const string& str);
	void    logPrint(const string& level, const char *str, ... );
	void    logPrint(const string& level, const Vector3f& rgb, const string& str );
	void    logPrint(const string& level, const Vector3f& rgb, const char *str, ... );
	
	void	flush();

	void    registerLevel();

protected:
	//void	printTree( int iLevel );
	bool	isInLogLevel( const string& level );

};

#define GL_ADD_LEVEL GraphicLogger::GetSingletonPtr()->addLogLevel
#define GL_REGISTER GraphicLogger::GetSingletonPtr()->registerLevel();
#define GL_SPHERE GraphicLogger::GetSingletonPtr()->logSphere
#define GL_RECT GraphicLogger::GetSingletonPtr()->logRectangle
#define GL_CIRCLE GraphicLogger::GetSingletonPtr()->logCircle
#define GL_LINE GraphicLogger::GetSingletonPtr()->logLine
#define GL_TEXT GraphicLogger::GetSingletonPtr()->logText
#define GL_PRINT GraphicLogger::GetSingletonPtr()->logPrint
#define GL_FLUSH GraphicLogger::GetSingletonPtr()->flush()
#else
#define GL_ADD_LEVEL(...)
#define GL_REGISTER
#define GL_SPHERE(...)
#define GL_RECT(...)
#define GL_CIRCLE(...)
#define GL_LINE(...)
#define GL_TEXT(...)
#define GL_PRINT(...)
#define GL_FLUSH
#endif

#endif /* _LOGGER_H */
