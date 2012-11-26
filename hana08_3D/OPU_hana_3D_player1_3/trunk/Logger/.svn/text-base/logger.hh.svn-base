/*
 *  Little Green BATS (2007), AI department, University of Groningen
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
 *  Date: 	July 27, 2007
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




#ifndef _Logger_HH_INCLUDED_
#define	_Logger_HH_INCLUDED_

#include <string>
#include <fstream>
#include <cstdarg>

namespace bats
{
/** \brief Logging singleton
 *
	For convenience, four macro's have been defined:
		_log(text)
		_typedLog(text, typename)
		_flog(fprint_format_string, fprint arguments...)
		_typedFlog(typename, fprint_format_string, fprint arguments....)

	Or use: Logger::getInstance() etc..
	
	Initialization is fully default if not specified, resulting in the file default.log to be used.
	
	Log line example:
	<pre>
		Tue Dec 13 14:06:30 2005 (1): Log start
	</pre>
	Which has the following abstract:
		asctime (type): information

	Types are used to allow the information to contain a specific format which
	can then be parsed again (for instance a period described by start-end:info)
	
	Types are:
	- None 0: information is a flat string, default
	- Event 1: Special event, information is one of "Log start", "Log end"...
	- Ident 2: Log with a source ident. The message can be split using the first ">". An example could be "Behavior::StayInField> activated"

	The logger MUST BE DESTROYED in the end to flush the buffers and close the file
	The logger will truncate any precious information.	
	
	See src/test/logger.cc for an example of use and generation of a testlog.log file.
	
	\author A. Bram Neijt <bneijt@gmail.com>
	\todo Disabling the logger, still touches the file it uses.
*/
class Logger
{
		static Logger *s_ptr;
		static bool s_disabled;
		std::ofstream	d_logstream;
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
#ifndef BATS_NO_LOGGER
#  define _log(info) bats::Logger::getInstance().log(info)
#  define _flog(info, ...) bats::Logger::getInstance().flog(info, __VA_ARGS__)
#  define _typedFlog(type, info, ...) bats::Logger::getInstance().tflog(bats::Logger::type, info, __VA_ARGS__)
#  define _typedLog(info, type) bats::Logger::getInstance().log(info, bats::Logger::type)
#else
#  define _log(info) 
#  define _flog(info, ...) 
#  define _typedFlog(type, info, ...) 
#  define _typedLog(info, type) 
#endif

#endif
