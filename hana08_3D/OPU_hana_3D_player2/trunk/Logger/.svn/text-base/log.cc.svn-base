
#include "logger.ih"

void Logger::log(std::string const &information, Type type)
{
	if(!s_disabled)
  {
    _debugLevel4("Logging: " << information);
    d_logstream << time()
		<< " (" << type << "): "
		<< information << std::endl; //"\n";
  }
}
