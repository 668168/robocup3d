
#include "logger.ih"

void Logger::initialize(std::string const &filename)
{
  if(s_ptr && filename == s_ptr->d_filename)
    {
      s_ptr->log("Log continue in same file", Event);
      return;
    }
  
  destroy();
  s_ptr = new Logger(filename);
  s_ptr->log("Log start: " + filename, Event);

}
