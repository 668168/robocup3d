#include "parser.ih"

#include <stack>

#define IDXPT(x) "(" << x/(256*4) << "/" << (x/256)%4 << ")"

rf<Predicate> Parser::parse(unsigned char const *data, unsigned len)
{
  // Lexer iteration.
  unsigned char const *lexSrc = data;
  unsigned char const *lexI = lexSrc;

  // Lexer state table pointers.
  ParseEntry
    *pCurrentState  = s_unifiedTable + *lexI;

  // Lexer token
  char const *lexToken = reinterpret_cast<char const *>(lexSrc);
  unsigned lexTokenLength = 1;

  // The stack.
  std::stack< rf<Predicate> > stck;

  // Initial stack value.
  stck.push(new Predicate(Predicate::type_list));

  while (true) {

    //    cerr << "IN: '" << *lexI << "'." << endl;

    switch (pCurrentState->action) {

    case Shift:
      // Increase the token data length.
      ++lexTokenLength;
      // Change state.
      pCurrentState = reinterpret_cast<ParseEntry*>(pCurrentState->value) + *(++lexI);
      continue;

    case ShiftNull:
      pCurrentState = reinterpret_cast<ParseEntry*>(pCurrentState->value) + *(++lexI);
      lexToken = reinterpret_cast<char const *>(lexI);
      lexTokenLength = 0;
      continue;

    case PushPred:
      // Change parser state.
      pCurrentState = reinterpret_cast<ParseEntry*>(pCurrentState->value) + *(++lexI);

      // Push new predicate.
      stck.push(stck.top()->push(new Predicate(string(lexToken,lexTokenLength),Predicate::type_node)));

      // Update the lexer tokens.
      lexToken = reinterpret_cast<char const *>(lexI);
      lexTokenLength = 0;
      continue;

    case AddToPred:
      // Change parser state.
      pCurrentState = reinterpret_cast<ParseEntry*>(pCurrentState->value) + *(++lexI);

      // Append predicate.
      stck.top()->push(new Predicate(string(lexToken,lexTokenLength),Predicate::type_leaf));

      lexToken = reinterpret_cast<char const *>(lexI);
      lexTokenLength = 0;
      continue;

    case ClosePred:
      // Change parser state.
      pCurrentState = reinterpret_cast<ParseEntry*>(pCurrentState->value) + *(++lexI);

      stck.pop();

      if (stck.empty())
	throw std::runtime_error("parse error, to many right parentises");

      // Update the lexer tokens.
      lexToken = reinterpret_cast<char const *>(lexI);
      lexTokenLength = 0;
      continue;

    case ClosePredEnd:
      stck.pop();

      if (stck.empty())
	throw std::runtime_error("parse error, to many right parentises");
      break;

    case End:
      return stck.top();

    case Error:
    case Warning:
      cerr << "Error: " << reinterpret_cast<unsigned long>(pCurrentState->value) << "." << endl;
      throw std::runtime_error("unknown parser or lexer error");


      /*
    case ERBeforeL:
      throw std::runtime_error("parse error, expected '(' or END_OF_LINE got ')'");

    case EEmptyPred:
      throw std::runtime_error("parse error, empty predicate");

    case ELonelyID:
      throw std::runtime_error("parse error, got an ID outside a predicate");

    case EPremEnd:
      throw std::runtime_error("parse error, premature end of line");
      */      
    };

    break;
  }

  //if (pred->getParent() != result)
  //    throw std::runtime_error("parse error, not enough right parentises");

  return stck.top();
}
