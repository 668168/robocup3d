#include "wait.ih"

Wait::Wait(string const &id, string const &playerClass)
  : Behavior("Wait", id, playerClass)
{
  d_tree = 0;
}
