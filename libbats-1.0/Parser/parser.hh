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

#ifndef __INC_RCP_PARSER_HH_
#define __INC_RCP_PARSER_HH_

#include <string>
#include <stack>
#include "../Predicate/predicate.hh"

namespace bats {

  /**\brief Communication parser
   * 
   *  The parser...
   *
   *  The parser is used to parse the communication messages (the lisp like language)
   *  to a Predicate (tree like structure @see Predicate).
   *
   *  Doesn't currently work. Use the PortableParser.
   *
   */
  class Parser {

    friend class PortableParser;

    Parser(Parser const &); // NI
    Parser &operator=(Parser const &); // NI

    /// The token type.
    struct Token {

      enum Type {
        none = 0,    ///< Not a token.
        error = 1,   ///< Error token.
        lparent = 2, ///< '('
        rparent = 3, ///< ')'
        ws = 4,      ///< White space
        id = 5,      ///< Everything that is not a ' ','(' or ')' (or: identifier).
        end_of_line = 6 ///< The end of the line.
      };

      Type type;
      std::string value;
      
    };

    enum Action {
      Error,
      Shift,
      ShiftNull,
      PushPred,
      AddToPred,
      ClosePred,
      ClosePredEnd,
      Warning,
      End,
      //      ERBeforeL,
      //      EEmptyPred,
      //      ELonelyID,
      //      EPremEnd,
    };

    /**
     *  Entry of the Parse table
     */
    struct ParseEntry {
      Action action;
      ParseEntry *value;
    };

    // The unified lexer/parser table.
    static ParseEntry s_unifiedTable[];

  public:

    static unsigned long long s_counters[6];

    static void initialize();

    Parser();

    /**
     *  Parses data into a Predicate.
     *  @returns the parsed message.
     *  @throws runtime_error
     */
    rf<Predicate> parse(unsigned char const *data, unsigned len);
    rf<Predicate> parse(std::string const &msg)
    { return parse(reinterpret_cast<unsigned char const*>(msg.c_str()),msg.length()); }


    /**
     *  Generates a lisp like expression of
     *  the message, which can be send to the
     *  simulation server.
     */
    std::string generate(rf<Predicate> const &_pred);

  };

};

#endif // __INC_RBATS_PARSER_HH_
