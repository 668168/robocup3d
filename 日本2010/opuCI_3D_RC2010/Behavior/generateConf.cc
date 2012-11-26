#include "behavior.ih"

void Behavior::generateConf(ostream& out)
{
  unsigned index = 0;
  generateConf(out, d_tree, index);
}

void Behavior::generateConf(ostream& out, rf<AST::Node> node, unsigned& index)
{
  unsigned subIndex = 0;
  if (!node)
  {
    out << "<behavior type=\"" << ident() << "\" id=\"\">\n";
    out << "</behavior><!-- " << ident() << " -->\n";
    return;
  }
      
  switch (node->getType())
  {
    case sequenceType:
      out << "<behavior type=\"" << ident() << "\" id=\"\">\n";
      for (NodeVector::iterator iter = node->begin(); iter != node->end(); ++iter)
        generateConf(out, *iter, index);
      out << "</behavior><!-- " << ident() << " -->\n";
    break;
    
    case andType:
      for (NodeVector::iterator iter = node->begin(); iter != node->end(); ++iter)
      {
        out << "\t<slot index=\"" << index << "-" << subIndex << "\">\n";
        out << "\t\t<behavior refid=\"\"/>\n";
        out << "\t</slot>\n";
        ++subIndex;
      }
      ++index;
    break;
    
    default:
    break;
  }
}
