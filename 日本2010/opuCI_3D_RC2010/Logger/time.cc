
#include "logger.ih"

std::string Logger::time()
{
  time_t current = ::time(0);
  if(current < 0)
    return "Non Non 00 00:00:00:00 0000";
  std::string time = asctime(localtime(&current));
  return time.substr(0, time.size() -1);
}
