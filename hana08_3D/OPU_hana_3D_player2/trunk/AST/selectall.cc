#include "ast.ih"

unsigned AST::Node::selectAll(vector<rf<AST::Node> > &res, Path const &select) const
{
  vector<rf<AST::Node> > search_space;

  Path p = select;

  if (p.path.empty())
    return 0;

  if (p.path.front() == "/") {
    // Search in all predicates with value path[0] which are in
    // the top level of the tree.
    p.path.pop_front();
    if (p.path.empty()) {
      res.insert(res.end(),d_nodes.begin(),d_nodes.end());
      return d_nodes.size();
    } else
      findAll(search_space,p.path.front());
  } else {
    // Search in all predicates with value path[0].
    findAllDeep(search_space,p.path.front());
  }

  p.path.pop_front();

  unsigned cnt = 0;

  for (vector<rf<AST::Node> >::iterator i = search_space.begin();
       i != search_space.end(); ++i) {
    if (p.path.empty()) {
      res.push_back(*i);
      ++cnt;
    } else
      cnt += (*i)->selectAll(res,p);
  }

  return cnt;
}
