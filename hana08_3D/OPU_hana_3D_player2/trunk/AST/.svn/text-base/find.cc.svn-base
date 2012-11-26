#include "ast.ih"

rf<AST::Node> AST::Node::find(string const &query) const
{
  for (NodeVector::const_iterator i = d_nodes.begin();
       i != d_nodes.end(); ++i)
    if ((*i)->match(query))
      return *i;

  // return 0 if there are no matches.
  return 0;
}
