
#include "logger.ih"

Logger::Logger(std::string const &filename)
	:	
	d_filename(filename)
{
	if(!s_disabled)
  {
    _debugLevel2("starting log " << filename);
		d_logstream.open(filename.c_str(), std::ios::trunc);
  }
}
