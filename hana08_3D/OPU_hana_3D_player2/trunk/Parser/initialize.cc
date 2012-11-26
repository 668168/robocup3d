#include "parser.ih"

#define PTIDX(x,y) s_unifiedTable+(x*4 + y)*256
#define PTINT(x) reinterpret_cast<ParseEntry*>(x)

void Parser::initialize()
{

  static ParseEntry ptLP[16] =
    {
      /* 0  0  0 */ {ShiftNull,PTIDX(1,0)},
      /* 1     1 */ {ShiftNull,PTIDX(1,1)},
      /* 2     2 */ {ShiftNull,PTIDX(1,2)},
      /* 3     3 */ {ShiftNull,PTIDX(1,3)},

      /* 4  1  0 */ {PushPred,PTIDX(1,1)},
      /* 5     1 */ {PushPred,PTIDX(1,1)},
      /* 6     2 */ {PushPred,PTIDX(1,1)},
      /* 7     3 */ {PushPred,PTIDX(1,1)},

      /* 8  2  0 */ {Error,PTINT(1)},
      /* 9     1 */ {Error,PTINT(2)},
      /* 10    2 */ {ClosePred,PTIDX(1,3)},
      /* 11    3 */ {ClosePred,PTIDX(1,3)},

      /* 12 3  0 */ {Error,PTINT(3)},
      /* 13    1 */ {PushPred,PTIDX(1,2)},
      /* 14    2 */ {AddToPred,PTIDX(1,2)},
      /* 15    3 */ {AddToPred,PTIDX(1,2)},
    };

  static ParseEntry ptRP[16] =
    {
      /* 0  0  0 */ {ShiftNull,PTIDX(2,0)},
      /* 1     1 */ {ShiftNull,PTIDX(2,1)},
      /* 2     2 */ {ShiftNull,PTIDX(2,2)},
      /* 3     3 */ {ShiftNull,PTIDX(3,3)},

      /* 4  1  0 */ {PushPred,PTIDX(2,1)},
      /* 5     1 */ {PushPred,PTIDX(2,1)},
      /* 6     2 */ {PushPred,PTIDX(2,1)},
      /* 7     3 */ {PushPred,PTIDX(2,1)},

      /* 8  2  0 */ {Error,PTINT(4)},
      /* 9     1 */ {Error,PTINT(5)},
      /* 10    2 */ {ClosePred,PTIDX(2,3)},
      /* 11    3 */ {ClosePred,PTIDX(2,3)},

      /* 12 3  0 */ {Error,PTINT(6)},
      /* 13    1 */ {PushPred,PTIDX(2,2)},
      /* 14    2 */ {AddToPred,PTIDX(2,2)},
      /* 15    3 */ {AddToPred,PTIDX(2,2)},
    };

  static ParseEntry ptWS[16] =
    {
      /* 0  0  0 */ {ShiftNull,PTIDX(0,0)},
      /* 1     1 */ {ShiftNull,PTIDX(0,1)},
      /* 2     2 */ {ShiftNull,PTIDX(0,2)},
      /* 3     3 */ {ShiftNull,PTIDX(0,3)},

      /* 4  1  0 */ {PushPred,PTIDX(0,1)},
      /* 5     1 */ {PushPred,PTIDX(0,1)},
      /* 6     2 */ {PushPred,PTIDX(0,1)},
      /* 7     3 */ {PushPred,PTIDX(0,1)},

      /* 8  2  0 */ {Error,PTINT(7)},
      /* 9     1 */ {Error,PTINT(8)},
      /* 10    2 */ {ClosePred,PTIDX(0,3)},
      /* 11    3 */ {ClosePred,PTIDX(0,3)},

      /* 12 3  0 */ {Error,PTINT(9)},
      /* 13    1 */ {PushPred,PTIDX(0,2)},
      /* 14    2 */ {AddToPred,PTIDX(0,2)},
      /* 15    3 */ {AddToPred,PTIDX(0,2)},
    };

  static ParseEntry ptSTAR[16] =
    {
      /* 0  0  0 */ {Shift,PTIDX(3,0)},
      /* 1     1 */ {Shift,PTIDX(3,1)},
      /* 2     2 */ {Shift,PTIDX(3,2)},
      /* 3     3 */ {Shift,PTIDX(3,3)},

      /* 4  1  0 */ {Shift,PTIDX(3,1)},
      /* 5     1 */ {Shift,PTIDX(3,1)},
      /* 6     2 */ {Shift,PTIDX(3,1)},
      /* 7     3 */ {Shift,PTIDX(3,1)},

      /* 8  2  0 */ {Error,PTINT(10)},
      /* 9     1 */ {Error,PTINT(11)},
      /* 10    2 */ {Error,PTINT(23)},
      /* 11    3 */ {Error,PTINT(24)},

      /* 12 3  0 */ {Shift,PTIDX(3,0)},
      /* 13    1 */ {Shift,PTIDX(3,1)},
      /* 14    2 */ {Shift,PTIDX(3,2)},
      /* 15    3 */ {Shift,PTIDX(3,3)}
    };

  static ParseEntry ptNEWLINE[16] =
    {
      /* 0  0  0 */ {End,},
      /* 1     1 */ {Error,PTINT(13)},
      /* 2     2 */ {Error,PTINT(14)},
      /* 3     3 */ {Error,PTINT(15)},

      /* 4  1  0 */ {Error,PTINT(16)},
      /* 5     1 */ {Error,PTINT(17)},
      /* 6     2 */ {Error,PTINT(18)},
      /* 7     3 */ {Warning,PTIDX(1,3)},

      /* 8  2  0 */ {Error,PTINT(20)},
      /* 9     1 */ {Error,PTINT(21)},
      /* 10    2 */ {ClosePredEnd,0},
      /* 11    3 */ {ClosePredEnd,0},

      /* 12 3  0 */ {Error,PTINT(22)},
      /* 13    1 */ {Warning,PTIDX(3,1)},
      /* 14    2 */ {Warning,PTIDX(3,2)},
      /* 15    3 */ {Error,PTINT(27)}
    };

  // Initialize to zero.
  memset(s_unifiedTable,0,4*4*256*sizeof(ParseEntry));

  for (unsigned i = 0; i < 16; ++i) {

    for (unsigned j = 0; j < 256; ++j)
      s_unifiedTable[i*256+j] = ptSTAR[i];

    s_unifiedTable[i*256+'('] = ptLP[i];
    s_unifiedTable[i*256+')'] = ptRP[i];
    s_unifiedTable[i*256+' '] = ptWS[i];
    s_unifiedTable[i*256+'\t'] = ptWS[i];
    s_unifiedTable[i*256+'\n'] = ptNEWLINE[i];
    s_unifiedTable[i*256+'\0'] = ptNEWLINE[i];

  }

}
