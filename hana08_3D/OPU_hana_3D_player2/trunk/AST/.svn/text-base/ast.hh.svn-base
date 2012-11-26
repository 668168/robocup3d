/*
 *  Little Green BATS (2007), AI department, University of Groningen
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
 *  Date: 	July 27, 2007
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








/*
 *  Abstract Syntax Tree
 *
 *
 */

#ifndef __INC_BATS_AST_HH_
#define __INC_BATS_AST_HH_

#include <vector>
#include "rf.hh"
#include "path.hh"
#include "refable.hh"
#include "vector3.hh"

namespace bats {

  
  /**
   *  An Abstract Syntax Tree.
   */
  class AST {

  public:

    /**
     *  Inherit from this node to create specific tree nodes.
     */
    class Node : public RefAble {

      //Node(Node const &); // NI
      //Node &operator=(Node const &); //

    public:

      typedef std::vector< rf<Node> > NodeVector;

      typedef NodeVector::const_iterator const_iterator;
      typedef NodeVector::iterator iterator;

    protected:

      unsigned d_type;
      NodeVector d_nodes;
      
    public:

      /**
       *  @param type is the node type, zero means NONO or ERROR.
       */
      Node(unsigned type = 0)
        : d_type(type) {}

      virtual ~Node() {}

      /**
       *  @returns the type.
       */
      unsigned getType() const { return d_type; }

      /**
       *  @returns a const vector of children.
       */
      NodeVector const &getChildren() const { return d_nodes; }

      /**
       *  @returns the number of children.
       */
      unsigned size() const { return d_nodes.size(); }

      /**
       *  @returns the iterators.
       */
      iterator begin() { return d_nodes.begin(); }
      iterator end() { return d_nodes.end(); }

      const_iterator begin() const { return d_nodes.begin(); }
      const_iterator end() const { return d_nodes.end(); }

      /**
       *  @returns false if it has no type.
       */
      virtual bool isOk() const { return d_type; }

      /**
       *  @returns false if and only if type is zero.
       */
      operator bool() const { return isOk(); }

      /**
       *  @returns the child at index.
       */
      rf<Node> getChild(unsigned index)
      {
        assert(index < d_nodes.size());
        return d_nodes[index];
      }
      
      /**
       *  @returns the child at index.
       */
      rf<Node> const getChild(unsigned index) const
      {
        assert(index < d_nodes.size());
        return d_nodes[index];
      }

      /**
       *  @returns true if this is not a leaf node.
       */
      bool hasChildren()
      {
        return d_nodes.size() > 0;
      }

      rf<Node> operator[](unsigned index) { return getChild(index); }

      /**
       *  Adds a child node to this node.
       */
      rf<Node> addChild(rf<Node> child) { d_nodes.push_back(child); return child; }

      /**
       *  @returns true if this is a leaf node (has no children).
       */
      bool isLeaf() const { return d_nodes.empty(); }

      /* --- Tree Search Interface --- */

      /**
       *  Used to match strings with nodes. Needs to be implemented
       *  for the find* methods to work.
       */
      virtual bool match(std::string const &query) const { return false; }

      /**
       *  Finds the first node witch matches query and returns it.
       *
       *  In most cases query will be the name or value of the node. The
       *  match() method is used to match the query to a node.
       */
      rf<Node> find(std::string const &query) const;

      /**
       *  Finds all nodes witch match query and appends them to res.
       *  @returns the number of matches.
       */
      unsigned findAll(std::vector<rf<Node> > &res, std::string const &query) const;
      
      /**
       *  Finds the first node in the entire tree witch matches query and returns it.
       *
       *  Warning: If there is a loop in the tree, this function will
       *           never exit! (So we need loop detection)
       *
       */
      rf<Node> findDeep(std::string const &query) const;

			Vector3D getVector(std::string const &name) const;
			
      /**
       *  Finds all nodes in the entire tree witch match query and appends them to res.
       *
       *  Warning: If there is a loop in the tree, this function will
       *           never exit! (So we need loop detection)
       *
       *  @returns the number of hits.
       */
      unsigned findAllDeep(std::vector<rf<Node> > &res, std::string const &query) const;

      /* --- Path System Interface --- */

      /**
       *  Finds all the predicates that comply with the specified select string
       *  and pushes them into res.
       *  @return ths number of hits.
       */
      unsigned selectAll(std::vector<rf<Node> > &res, Path const &select) const;

      /**
       *  @returns the first predicate that complies with select.
       */
      rf<Node> select(Path const &select) const;


      /* --- Tree Matching System --- */
      


    };

  };

};


#endif // __INC_BATS_AST_HH_
