#ifndef _Logger_HH_INCLUDED_
#define	_Logger_HH_INCLUDED_

#include <string>
#include <fstream>
#include <cstdarg>

namespace bats
{
  class Logger
  {
    static Logger *s_ptr;
    static bool s_disabled;
    std::ofstream d_logstream;
    std::string d_filename;

  public:
    /**\brief The type of log record

       The type can be used to allow a parser to be triggered
       to parse the information in the log record and do special things.

    */
    enum Type
      {
	None, ///<No special parsing possible, flat string
	Event, ///<An event: one of "Log start", "Log end" (may include game states and generals in the future).
	Ident	///<An source identified message: Ident">"Information
      };
		
    /** Fully disable the logger
	A valid instance will still be given, but it log anything.
    */
    static void disable(bool set = true)
    {
      s_disabled = set;
    }

    /**\brief Destroy the logger
       This removes the Logger instance, effectively destoying the singleton.
       It also resets the enabled bit.
    */
    static void destroy()
    {
      if(s_ptr)
	{
	  s_ptr->log("Log end", Event);
	  s_ptr->flush();
	  delete s_ptr;
	}
      s_ptr = 0;
      s_disabled = false;
    }
		
    /** Initialize the logger system
	Initialize the logger with the given filename
	\param filename The filename to write the logs to
    */
    static void initialize(std::string const &filename = "default.log");
				
    /** Get an instance of the logger singleton
	This function will always successeed
	\return An instance to the Logger class
    */
    static Logger &getInstance()
    {
      if(s_ptr)
	return *s_ptr;
      initialize();
      return *s_ptr;
    }
		
    /** Log the given information

	\param information The information to log.
	\param type	The type of log information. This should be used if the actual information line conforms to a special format, so the log visualizer should interpret it.
    */
    void log(std::string const &information, Type type = None);
		
    /**Typed formatted log function
     *
     * This function works just like fprint (it simply calls it
     * ) and may be used to place formatted strings in the logs
     * . The first argument must be the type of log.
     * \param type The type of log entry
     * \param format The format string (first part of printf)
     * \param ... The arguments (second part of printf)
     */
    void tflog(Type type, char const* format, ...)
    {
      static char text[1024];
      va_list vl;
      va_start(vl, format);
      vsnprintf(&text[0], sizeof(text), format, vl);
      va_end(vl);
      log(&text[0], type);
    }
		
    /**Formatted log function
     *
     * This function works just like fprint (it simply calls it
     * ) and may be used to place formatted strings in the logs
     * .
     * \param format The format string (first part of printf)
     * \param ... The arguments (second part of printf)
     */
    void flog(char const* format, ...)
    {
      static char text[1024];
      va_list vl;
      va_start(vl, format);
      vsnprintf(&text[0], sizeof(text), format, vl);
      va_end(vl);
      log(&text[0]);
    }

    /**\brief Flush the log stream
     */
    void flush()
    {
      d_logstream.flush();
    }

    /** Return the current time as a asctime timestring
		
	This is only public so everybody can see what time the logger thinks it is.
    */
    static std::string time();
		
  private:
    Logger(std::string const &filename);
  };
}//Namespace

/*
#ifndef BATS_NO_LOGGER
#  define _log(info) bats::Logger::getInstance().log(info)
#  define _flog(info, ...) bats::Logger::getInstance().flog(info, __VA_ARGS__)
#  define _typedFlog(type, info, ...) bats::Logger::getInstance().tflog(bats::Logger::type, info, __VA_ARGS__)
#  define _typedLog(info, type) bats::Logger::getInstance().log(info, bats::Logger::type)
#else
*/
#  define _log(info) 
#  define _flog(info, ...) 
#  define _typedFlog(type, info, ...) 
#  define _typedLog(info, type) 
//#endif

#endif
