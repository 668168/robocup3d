/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * $Id: Logger.cpp,v 1.1.1.1 2006/09/15 02:03:05 Administrator Exp $
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

 
 #include "Logger.h"
 #ifdef Solaris
 #include <varargs.h> //-*  needed for va_list and va_start under Solaris
#else
 #include <stdarg.h>
#endif


#include "WorldModel.h"


using namespace std;
using namespace salt;


extern string teamName;

/*****************************************************************************/
/**************************** LOGGER *****************************************/
/*****************************************************************************/
#ifdef ENABLE_LOG
Logger::Logger( ostream& o, int iMin, int iMax ):
mOS(&o),_timeLogged(0)
{
	addLogRange( iMin, iMax );
}

bool Logger::addLogLevel( int iLevel )
{
  _setLogLevels.insert( iLevel );
  return true;
}

bool Logger::addLogRange( int iMin, int iMax )
{
  bool bReturn = true;
  for( int i = iMin ; i <= iMax;  i++ )
    bReturn &= addLogLevel( i );
  return bReturn;
}

bool Logger::log( int iLevel, string str )
{
  if( isInLogLevel( iLevel ) )
  {
	printTree(iLevel);
	*mOS << str << '\n';
    return true;
  }

  return false;
}

bool Logger::log( int iLevel, char *str, ... )
{
  if( isInLogLevel( iLevel ) )
  {
    va_list ap;
#ifdef Solaris
    va_start( ap );
#else
    va_start( ap, str );
#endif
    if( vsnprintf( _buf, MAX_LOG_LINE-1, str, ap ) == -1 )
      assert(! "Logger::log, buffer is too small!\n");
    va_end(ap);
    
	printTree(iLevel);
	*mOS << _buf << '\n'; 
    return true;
  }

  return false;
}

bool Logger::isInLogLevel( int iLevel )
{
  return _setLogLevels.find( iLevel ) != _setLogLevels.end() ;
}

char* Logger::repeatChar( char c, int n )
{
  const static int MAX_REP = 100;
  static char out[MAX_REP+1];
  if( n > MAX_REP )
    n = MAX_REP;
  for( int i = 0; i < n; i++ )
    out[i] = c;
  out[n] = '\0';
  return out;
}

void Logger::logTable()
{
	*mOS<<"# ( GameTime SimTime )"<<endl;
}

void Logger::printTree( int iLevel )
{
	if ( iLevel != 0 )
	{
		Time currentTime = WM->getRealTime();
		if ( _timeLogged < currentTime )
		{// need log time
			_timeLogged = currentTime;
			*mOS <<"# ( "
			<< WM->getGameTime() << " " 
			<< currentTime
			<< " )\n";
		}
    	int num = _functions.size();
		*mOS << "# " << iLevel << ' ' << num << ' ';
		if ( num > 0 )
		{
			*mOS << '[' << _functions.back() << "] ";
		}
	}
}

int Logger::normalizeLogLevel( int iLevel )
{
	return clamp(iLevel,MIN_LOG_LEVEL,MAX_LOG_LEVEL);
}

void Logger::flush()
{
	mOS->flush();
}

void Logger::functionBegin(const string &name)
{
	_functions.push_back(name);
}

void Logger::functionEnd()
{
	_functions.pop_back();
}
#endif

void Logger::logErr( string str )
{
	cerr << str << endl;
}

void Logger::logErr( char *str, ... )
{
	va_list ap;
#ifdef Solaris
    va_start( ap );
#else
    va_start( ap, str );
#endif
    if( vsnprintf( _buf, MAX_LOG_LINE-1, str, ap ) == -1 )
      assert( !"Logger::log, buffer is too small!\n");
    va_end(ap);

	cerr << _buf << endl; 
}


#ifdef ENABLE_LOG
LogFlag::LogFlag(const char* name1,const char* name2)
{
	char name[256];
	sprintf(name,"%s::%s",name1,name2);
	Logger::GetSingletonPtr()->functionBegin(name);
}
#endif

/*****************************************************************************/
/**************************** FILE LOGGER ************************************/
/*****************************************************************************/
#ifdef ENABLE_LOG
FileLogger::FileLogger():
_filePtr(NULL),
_enabled(false)
{}

FileLogger::FileLogger( const char* logname )
{
	openFile( logname );
}

FileLogger::~FileLogger()
{
	if ( _filePtr != NULL )
		fclose(_filePtr);
	_filePtr = NULL;
	_enabled = false;
}

bool FileLogger::openFile(const char* logname, const char* teamname, unsigned int id)
{
	if ( _filePtr != NULL )
		fclose(_filePtr);
	_filePtr = NULL;
	_enabled = false;
	sprintf(_fileName, "logs/%s-%s-%d.log", logname, teamname, id);
	_filePtr = fopen(_fileName, "w");
	if(!_filePtr)
	{
		LOGERR("Cannot open file %s for writing!\n", _fileName);
	}
	else
	{
    	LOG( 1, "FileLogger opend: %s\n", _fileName);
    	_enabled = true;
	}
	return _enabled;
}

bool FileLogger::openFile( const char* logname )
{
	return openFile( logname, teamName.c_str(), WM->getMyNum());
}

void FileLogger::log(const char* log_msg, ... )
{
  if(_enabled)
  {
      va_list ap;
      va_start(ap, log_msg );
      vfprintf(_filePtr, log_msg, ap);
  }
}

void FileLogger::log( const string& log_str )
{
	log( log_str.c_str() );
}
#endif


#ifdef ENABLE_GL_LOG
GraphicLogger graphic_logger;

GraphicLogger::GraphicLogger( ostream& o ):
_OS(o)
{
}

void GraphicLogger::addLogLevel( const string& level )
{
	_setLogLevels.insert( level );
}

void GraphicLogger::logSphere(const string& level, const Vector3f& pos, float r)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogShpere(pos, r));
	}
}

void GraphicLogger::logSphere(const string& level, const Vector3f& pos, float r, const Vector3f& rgb)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogShpere(pos, r, rgb));
	}
}

int GraphicLogger::getLevelIndex(const string& strLevel)const
{
	set<string>::const_iterator iterFind= _setLogLevels.find(strLevel);
	if ( iterFind == _setLogLevels.end() ) return -1;// no this level!!
	int index = 0;
	for( set<string>::const_iterator iter = _setLogLevels.begin();
		iter != iterFind; ++iter )
	{
		index++;
	}
	return index;
}

void GraphicLogger::flush()
{
	_OS<<"(L "<<WM->getGameTime()<<' '<<_data<<")\n";
	_OS.flush();
	_data.clear();
}

void GraphicLogger::registerLevel()
{
	_OS<<"(LogRegister "<<WM->getMyTeamName()<<' '<<WM->getMyNum();
	
	for( set<string>::const_iterator iter = _setLogLevels.begin();
		iter != _setLogLevels.end(); ++iter )
	{
		_OS<<' '<<*iter;
	}
	_OS<<")\n";
	_OS.flush();
}

void GraphicLogger::logRectangle(const string& level, const Vector3f& pos, float szX, float szY)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogRectangle(pos, szX, szY));
	}
}

void GraphicLogger::logRectangle(const string& level, const Vector3f& pos, float szX, float szY, const Vector3f& rotation)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogRectangle(pos, szX, szY, rotation));
	}
}

void GraphicLogger::logRectangle(const string& level, const Vector3f& pos, float szX, float szY, const Vector3f& rotation, const Vector3f& rgb)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogRectangle(pos, szX, szY, rotation, rgb));
	}
}

void GraphicLogger::logCircle(const string& level, const Vector3f& pos, float r)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogCircle(pos, r));
	}
}

void GraphicLogger::logCircle(const string& level, const Vector3f& pos, float r, const Vector3f& rotation)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogCircle(pos, r, rotation));
	}
}

void GraphicLogger::logCircle(const string& level, const Vector3f& pos, float r, const Vector3f& rotation, const Vector3f& rgb)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogCircle(pos, r, rotation, rgb));
	}
}

void GraphicLogger::logLine(const string& level, const Vector3f& x0, const Vector3f& x1)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogLine(x0, x1));
	}
}

void GraphicLogger::logLine(const string& level, const Vector3f& x0, const Vector3f& x1, const Vector3f& rgb)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogLine(x0, x1,rgb));
	}
}

void GraphicLogger::logText(const string& level, const Vector3f& pos, const string& str)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogText(pos, str));
	}
}

void GraphicLogger::logText(const string& level, const Vector3f& pos, const char *str, ... )
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		static char buffer[MAX_LOG_LINE];
		va_list ap;
    	va_start(ap, str );
    	vsprintf(buffer, str, ap);
		va_end(ap);
		_data[index].add(new LogText(pos, buffer));
	}
}

void GraphicLogger::logText(const string& level, const Vector3f& pos, const Vector3f& rgb, const string& str)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogText(pos, str, rgb));
	}
}

void GraphicLogger::logText(const string& level, const Vector3f& pos, const Vector3f& rgb, const char *str, ... )
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		static char buffer[MAX_LOG_LINE];
		va_list ap;
    	va_start(ap, str );
    	vsprintf(buffer, str, ap);
		va_end(ap);
		_data[index].add(new LogText(pos, buffer, rgb));
	}
}

void GraphicLogger::logPrint(const string& level, const string& str)
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogPrint(str));
	}
}

void GraphicLogger::logPrint(const string& level, const Vector3f& rgb, const string& str )
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		_data[index].add(new LogPrint(str,rgb));
	}
}

void GraphicLogger::logPrint(const string& level, const char *str, ... )
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		static char buffer[MAX_LOG_LINE];
		va_list ap;
    	va_start(ap, str );
    	vsprintf(buffer, str, ap);
		va_end(ap);
		_data[index].add(new LogPrint(buffer));
	}
}

void GraphicLogger::logPrint(const string& level, const Vector3f& rgb, const char *str, ... )
{
	int index = getLevelIndex(level);
	if ( index >=0 )
	{
		static char buffer[MAX_LOG_LINE];
		va_list ap;
    	va_start(ap, str );
    	vsprintf(buffer, str, ap);
		va_end(ap);
		_data[index].add(new LogPrint(buffer,rgb));
	}
}

#endif
