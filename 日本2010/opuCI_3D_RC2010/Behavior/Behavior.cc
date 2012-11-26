#include "behavior.ih"

Behavior::Behavior(std::string const &name, std::string const &id)
  : d_name(name),
    d_id(id),
    d_tree(0),
    d_curStep(-1),
    d_action(0),
    d_commit(false),
    d_committed(false),
    d_childrenCommitted(false),
    d_lastUpdate(0)
{
}

Behavior::Behavior(std::string const &name, std::string const &id, std::string const &playerClass)
  :
  d_name(name),
  d_id(id),
  d_curStep(-1),
  d_playerClass(playerClass),
  d_action(0),
  d_commit(false),
  d_committed(false),
  d_childrenCommitted(false),
  d_lastUpdate(0)
{

}
