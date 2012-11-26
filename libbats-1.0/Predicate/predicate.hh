/*
 *  Little Green BATS (2008), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	November 1, 2008
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef __INC_BATS_PREDICATE_HH_
#define __INC_BATS_PREDICATE_HH_

#include <string>
#include <vector>
#include <set>
#include <list>
#include <clocale>
#include <cassert>
#include <sstream>
#include <cstdlib>

#include "../AST/ast.hh"
#include "../Path/path.hh"


namespace bats {

  class Predicate;
  /**
   *  The Predicate class...
   *
   *  Isues:
   *  - Should a predicate be strongly typed?
   *  
   *   Predicate is a tree structure which is outputted by the parser and
   *   can be used by the parser to generate the list like language that
   *   is used for communication with the soccer server.
   *
   *   The lisp like language looks like this: (foo (bar 10) (node leaf)).
   *   This is then parsed in a tree looking like this:
   *
   *   <ul>
   *     <li>foo
   *       <ul>
   *         <li>bar
   *          <ul>
   *           <li>"10"</li>
   *          </ul>
   *         </li>
   *         <li>node
   *          <ul>
   *           <li>"leaf"</li>
   *          </ul>
   *         </li>
   *       </ul>
   *     </li>
   *   </ul>
   *
   *   In short: [[foo [bar 10] [node leaf]]] (I use different brackets to
   *   specify the differense between the input lisp like language and the
   *   tree that is generated).
   *   If you look closely you will see that the tree has an extra root node.
   *   The reason for this is that there can be more then one predicate per
   *   parsed line; thus the root node acts as a list op predicates (and
   *   actually has the type <i>type_list</i>).
   *
   *   There are three types of nodes in a Predicate tree: type_node, type_list
   *   and type_leaf @see Type.
   *
   *   <b>type_node</b>
   *   <br>
   *   This is a very straight forward tree node in the sense that it has a value (its
   *   name) and one or more children (e.g. [node0 [node1 leaf]], here node1
   *   is a child of node0 (and leaf is a child of node1, but more on that
   *   later).
   *
   *   <b>type_leaf</b>
   *   <br>
   *   This is a leaf node. It has no children and only a value. This value
   *   is always stored as a string, but can represent a string, an int and a
   *   double value. Which can be gotten via the getStr(), getInt() or
   *   getDouble() methods, or by using the type conversion operators
   *   (e.g. Predicate p("100",type_leaf); int v = p; // -> v = 100;).
   *
   *   <b>type_list</b>
   *   <br>
   *   A list is a node without a value. The main use for it is to be able
   *   to parse more then one predicate per line without changing the
   *   apparent structure of the predicate (although it is internally different).
   *   The line "(bla bla)(bar foo)" will be represented by the tree
   *   [[bla bla][bar foo]] (pay attention to the extra '['s surrounding the
   *   predicates).
   *   List type nodes will also be treated differently by the select() and
   *   selectAll() methods.
   */
  class Predicate : public AST::Node {
    friend std::ostream &operator<<(std::ostream &, Predicate const &);

    // (so the parser can iterate trought the arguments).
    friend class Parser;

  public:

    /**
     *  The predicate node types.
     */
    enum Type {
      type_node = 1,
      type_leaf = 2,
      type_list = 3,
    };

    static bool pred_comp(rf<Predicate> p, std::string const &val)
    {
      return p->getStr() < val;
    }

  private:

    std::string d_value;

    void copy(Predicate const &_other);
    void destroy();
    
    static unsigned s_predCount;   

  public:

    /**
     *  Creates a predicate with value and type.
     *
     *  @param value specifies the value of the Predicate.
     *  @param type specifies the type of the Predicate @see Type.
     */
    Predicate(std::string const &value, Type type = type_node)
      : Node(type), d_value(value) { ++s_predCount; }

    /**
     *  @param type specifies the type of the Predicate.
     *  @see Type
     */
    Predicate(Type type)
      : Node(type) { ++s_predCount; }

    //    Predicate(Predicate const &other) { copy(other); }

    ~Predicate() { destroy(); }

    /*
    Predicate &operator=(Predicate const &other)
    {
      if (this != &other) {
        destroy();
        copy(other);
      }
      return *this;
    }
    */

    /**
     *  Sets the predicate value.
     */
    void setValue(std::string const &value)
    {
      d_value = value;
    }

    /**
     *  Pushes a Predicate to the back of the children list.
     *
     *  Note: no circular predicates should be created
     *        (because they won't be destroyed automaticaly).
     */
    rf<Predicate> push(rf<Predicate> msg)
    {
      return rf_cast<Predicate>(addChild(rf_cast<AST::Node>(msg)));
    }

    /**
     *  Pushes a leaf type Predicate with value str.
     */
    void pushLeaf(std::string const &str)
    {
      push(new Predicate(str,type_leaf));
    }

    /**
     *  Pushes a leaf type predicate with value val.
     */
    void pushLeaf(unsigned val)
    {
      std::ostringstream s;
      s << val;
      push(new Predicate(s.str(),type_leaf));
    }

    /**
     *  Pushes a leaf type predicate with value val.
     */
    void pushLeaf(double val)
    {
      std::ostringstream s;
      s << val;
      push(new Predicate(s.str(),type_leaf));
    }
    
    /**
     *  Pushes a leaf type predicate with values ( vec.x, vec.y, vec.z).
     */
    void pushLeafs(Vector3D const& vec)
    {
      pushLeaf(vec.getX());
      pushLeaf(vec.getY());
      pushLeaf(vec.getZ());
    }

    /**
     *  Gets the child with index idx.
     */
    rf<Predicate> get(unsigned idx) { return rf_cast<Predicate>(getChild(idx)); }
    rf<Predicate> const get(unsigned idx) const { return rf_cast<Predicate>(getChild(idx)); }
    rf<Predicate> const operator[](unsigned idx) { return rf_cast<Predicate>(getChild(idx)); }

    /**
     *  The STL iterators. These return iterators to the children
     *  container.
     */
    //    iterator begin() const { return children.begin(); }
    //    iterator end() const { return children.end(); }

    /**
     *  @returns true if the predicate node is a node (has a
     *           meaningful value).
     */
    bool isNode() const { return d_type == type_node; }

    /**
     *  @returns true if the predicate node is a leaf (has no
     *           children).
     */
    bool isLeaf() const { return d_type == type_leaf; }

    /**
     *  @returns true if the predicate node is a list (has no
     *           value).
     */
    bool isList() const { return d_type == type_list; }


    /**
     *  @returns true when the predicate has no value and no children.
     */
    bool isEmpty() const { return (d_value.empty() && isLeaf()); }

    /**
     *  @returns fals when the predicate has no value.
     */
    virtual bool isOk() const { return !d_value.empty(); }

    /**
     *  @returns the string value of argument name.
     */
    std::string getStr() const { return d_value; }

    /**
     *  @returns the int value of argument name.
     */
    int getInt() const { return std::atoi(d_value.c_str()); }

    /**
     *  @returns the double value of argument name.
     */
    double getDouble() const
    {
      std::setlocale(LC_NUMERIC, "C"); // this is a fix.
      return std::atof(d_value.c_str());
    }

    /**
     *  Conversion operators.
     */
    operator std::string() const { return getStr(); }
    operator int() const { return getInt(); }
    operator float() const { return getDouble(); }
    operator double() const { return getDouble(); }

    bool operator<(Predicate const &other) const { return d_value < other.d_value; }
    bool operator==(Predicate const &other) const { return d_value == other.d_value; }

    /**
     *  Used to match strings with nodes. Needs to be implemented
     *  for the find* methods to work.
     */
    virtual bool match(std::string const &query) const { return query == d_value; }

    /**
     *  @returns a lisp like string of the Predicate without the
     *           parentices of the list nodes.
     */
    std::ostream &generate(std::ostream &os) const;

    std::string toString();
  };

  /**
   *  Predicate stream insertion operator.
   */
  std::ostream &operator<<(std::ostream &os, Predicate const &pred);
  
};

#endif // __INC_BATS_PREDICATE_HH_
