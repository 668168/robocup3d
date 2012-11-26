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

#ifndef __INC_BATS_PARSER_HH_
#define __INC_BATS_PARSER_HH_

#include "../Parser/parser.hh"

#include <iostream>
#include "../BatsException/batsexception.hh"

namespace bats {

  /**\brief Reentrant Communication Parser
   * 
   *  A reentrant version of The Parser (tm)...
   *
   *  It is a little bit slower compared to Parser, but is still really fast.
   *
   *  The parser is used to parse the communication messages (the lisp like language)
   *  to a Predicate (tree like structure @see Predicate).
   *
   *  Because the normal Parser is broken at the moment, this is the only parser available.
   *
   *  For an example implementation see SocketComm/receive.cc.
   *
   */
  class PortableParser {
    static Parser::ParseEntry s_initializerState[256];

    // Lexer state table pointers.
    Parser::ParseEntry *d_pCurrentState;

    // The stack (there are faster stacks than this one..).
    std::stack< rf<Predicate> > d_stck;

    std::string d_tokenStr;

    bool d_done;

    //    std::stringstream d_err;

    PortableParser(Parser const &); // NI
    PortableParser &operator=(Parser const &); // NI

  public:

    PortableParser() { reset(); }

    /**
     *  Resets the portable parser. This always needs to be done
     *  before beginning to parse something.
     */
    void reset()
    {
      d_done = false;
      d_pCurrentState = s_initializerState;
      d_stck = std::stack< rf<Predicate> >();
      d_stck.push(new Predicate(Predicate::type_list));
    }

    /**
     *  Inputs a single character to the parser.
     *  @returns true when we have finished parsing a line.
     */
    inline bool parse(unsigned char chr)
    {
      d_pCurrentState = reinterpret_cast<Parser::ParseEntry*>(d_pCurrentState->value) + chr;

      switch (d_pCurrentState->action) {

      case Parser::Shift:
        d_tokenStr += chr;
        return false;

      case Parser::ShiftNull:
        d_tokenStr.clear();
        return false;

      case Parser::PushPred:
        d_stck.push(d_stck.top()->push(new Predicate(d_tokenStr,Predicate::type_node)));
        d_tokenStr.clear();
        return false;

      case Parser::AddToPred:
        d_stck.top()->push(new Predicate(d_tokenStr,Predicate::type_leaf));
        d_tokenStr.clear();
        return false;

      case Parser::ClosePred:
        d_stck.pop();
        if (d_stck.empty())
          throw new BatsException("parse error, to many right parentises");
        d_tokenStr.clear();
        return false;

      case Parser::ClosePredEnd:
        d_stck.pop();
      case Parser::End:
        if (d_stck.empty())
          throw new BatsException("parse error, to many right parentises");
        else if (d_stck.size() > 1) {
          std::cerr << "Stacksize: " << d_stck.size() << std::endl;
          std::cerr << "StackTrace:" << std::endl;
          for (unsigned i = d_stck.size(); i; --i) {
            std::cerr << "(" << i << ") " << d_stck.top() << " {" << *d_stck.top() << "}." << std::endl;
            d_stck.pop();
          }
          throw new BatsException("parse error, predicate is not closed");
        }
        d_done = true;
        return true;

      case Parser::Error:
        std::cerr << "Error: " << reinterpret_cast<unsigned long>(d_pCurrentState->value) << " with char code: " << static_cast<unsigned>(chr) << "." << std::endl;
        throw new BatsException(std::string()+"unknown parser or lexer error (current char: '"+static_cast<char>(chr)+"')");

      case Parser::Warning:
        std::cerr << "Warning: " << (d_pCurrentState->value-Parser::s_unifiedTable)/256 << " with char code: " << static_cast<unsigned>(chr) << "." << std::endl;
        throw new BatsException(std::string()+"parler warning (current char: '"+static_cast<char>(chr)+"')");
        //        return false;


      };

      d_done = true;
      return true;
    }


    /**
     *  Parses up to len bytes from buf.
     *
     *  @returns the number of parsed bytes.
     *  @throws BatsException*
     */
    inline unsigned parse(unsigned char const *buf, unsigned len)
    {
      unsigned char const *i;

      try {

        for (i = buf; i < buf + len; ++i) {
          if (!*i) {
            std::cerr << "There is a zero here on column " << (i-buf) << " (len = " << len << ")" << std::endl;
            throw new BatsException("Found a zero in the parser buffer (this usually means that something went wrong with the agent<->server communication).");
          }
          if (parse(*i))
            return i-buf;
        }

      } catch (BatsException* e) {
        std::stringstream ss;
        ss << "parser error, " << e->what() << " at character #" << (i-buf) << " with context: (len=" << len << ") "
           << std::string(reinterpret_cast<char const *>(buf),len) << std::endl;


        //        ss.write(reinterpret_cast<char const*>(buf),len);
        
        throw new BatsException(ss.str());
      }

      return len;
    }

    /**
     *  Parses a complete line and returns the predicate.
     *
     *  @returns the parsed predicate.
     */
    inline rf<Predicate> parseLine(std::string const &data)
    {
      unsigned count = 0;
      while (count < data.length()) {
        count += parse(reinterpret_cast<unsigned char const *>(data.c_str())+count,data.length()-count+1);
      }
      return d_stck.top();
    }

    /**
     *  @returns true when we have parsed a exactly one predicate
     *           no more and no less.
     */
    inline bool endOfPred() const
    {
      return (d_stck.size() == 1);
    }

    /**
     *  @returns true if a complete line had been parsed.
     */
    inline bool done() const
    {
      return d_done;
    }
    
    /**
     *  @returns the parsed predicate.
     */
    rf<Predicate> getPredicate() const
    {
      return d_stck.top();
    }

  };

};

#endif // __INC_RBATS_PARSER_HH_
