#include "ast.ih"

/**
 * \TODO: This can be optimized a very lot!!
 */
rf<AST::Node> AST::Node::select(Path const &select) const
{
  vector<rf<AST::Node> > search_space;

  Path p = select;

  if (p.path.empty())
    return 0;

  if (p.path.front() == "/") {
    // Search in all predicates with value path[0] which are in
    // the top level of the tree.
    p.path.pop_front();
    if (p.path.empty())
      return (d_nodes.empty()?rf<AST::Node>(0):d_nodes.front());
    else
      findAll(search_space,p.path.front());
  } else // Search in all predicates with value path[0].
    findAllDeep(search_space,p.path.front());

  p.path.pop_front();

  for (vector<rf<AST::Node> >::iterator i = search_space.begin();
       i != search_space.end(); ++i)
    if (p.path.empty())
      return *i;
    else
      return (*i)->select(p);

  return 0;
}
