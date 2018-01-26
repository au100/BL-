//==============================================================================
#include "specialtoken.h"
//==============================================================================
QString& TSpecialToken::get(TTextInBuffer& in)
{
   QChar ch = initParse(in);
   if(charCode(ch) == ccSpecial)
   {
      _parse += ch;
      switch(ch.toLatin1())
      {
      case '.' : _code = tcDot;         return _parse;
      case ',' : _code = tcPeriod;      return _parse;
      case '\'': _code = tcSingleQuote; return _parse;

      case '[' : _code = tcStartArray;  return _parse;
      case ']' : _code = tcEndArray;    return _parse;
      case '{' : _code = tcStartBlock;  return _parse;
      case '}' : _code = tcEndBlock;    return _parse;
      case '(' : _code = tcStartParam;  return _parse;
      case ')' : _code = tcEndParam;    return _parse;

      case '?' : _code = tcQuestion;    return _parse;
      case ':' : _code = tcChoice;      return _parse;
      case '~' : _code = tcDelete;      return _parse;
      case '$' : _code = tcDollar;      return _parse;
      case '#' : _code = tcBar;         return _parse;
      case '\\': _code = tcBackSlash;   return _parse;

      case ';' : _code = tcEndOperator; return _parse;
      }

      QChar cc = in.getChar();
      switch(ch.toLatin1())
      {
         case '+' :
                 if(cc == '+') { _code = tcDoublePlus;      _parse += cc; }
            else if(cc == '=') { _code = tcPlusEqual;       _parse += cc; }
            else               { _code = tcPlus;       in.putBackChar(); }
            break;

         case '-' :
                 if(cc == '-') { _code = tcDoubleMinus;     _parse += cc; }
            else if(cc == '=') { _code = tcMinusEqual;      _parse += cc; }
            else               { _code = tcMinus;      in.putBackChar(); }
            break;

         case '*' :
                 if(cc == '=') { _code = tcMulEqual;        _parse += cc; }
            else if(cc == '/') { _code = tcCommentEnd;      _parse += cc; }
            else               { _code = tcMul;        in.putBackChar(); }
            break;

         case '/' :
                 if(cc == '=') { _code = tcDevideEqual;     _parse += cc; }
            else if(cc == '/') { _code = tcCommentLine;     _parse += cc;
                                 this->skipLine(in);                    }
            else if(cc == '*') { _code = tcCommentStart;    _parse += cc; }
            else               { _code = tcDevide;     in.putBackChar(); }
            break;

         case '%' :
            if(cc == '=')      { _code = tcModEqual;        _parse += cc; }
            else               { _code = tcMod;        in.putBackChar(); }
            break;

         case '=' :
            if(cc == '=')      { _code = tcEqu;             _parse += cc; }
            else               { _code = tcLiken;      in.putBackChar(); }
            break;

         case '&' :
                 if(cc == '=') { _code = tcAndEqual;        _parse += cc; }
            else if(cc == '&') { _code = tcAnd;             _parse += cc; }
            else               { _code = tcBitAnd;     in.putBackChar(); }
            break;

         case '|' :
                 if(cc == '=') { _code = tcOrEqual;         _parse += cc; }
            else if(cc == '|') { _code = tcOr;              _parse += cc; }
            else               { _code = tcBitOr;      in.putBackChar(); }
            break;

         case '^' :
                 if(cc == '=') { _code = tcXorEqual;        _parse += cc; }
            else if(cc == '^') { _code = tcXor;             _parse += cc; }
            else               { _code = tcBitXor;     in.putBackChar(); };
            break;

         case '!' :
            if(cc == '=')      { _code = tcNeq;             _parse += cc; }
            else               { _code = tcNot;        in.putBackChar(); }
            break;

         case '<' :
                 if(cc == '=') { _code = tcLeq;             _parse += cc; }
            else if(cc == '<') {
                 _parse += cc;
                 cc = in.getChar();
                 if(cc == '=') { _code = tcShiftLeftEqual;  _parse += cc; }
                 else          { _code = tcShiftLeft;  in.putBackChar(); }
                 }
            else               { _code = tcLs;         in.putBackChar(); }
            break;

         case '>' :
                 if(cc == '=') { _code = tcGeq;             _parse += cc; }
            else if(cc == '>') {
                 _parse += cc;
                 cc = in.getChar();
                 if(cc == '=') { _code = tcShiftRightEqual; _parse += cc; }
               else            { _code = tcShiftRight; in.putBackChar(); }
            }
            else               { _code = tcGt;         in.putBackChar(); }
            break;


         default  :
            in.putBackChar();
            _code = tcError;
            // Set Error TODO
            break;

      }
   }
   return _parse;
}
//------------------------------------------------------------------------------
void TSpecialToken::print(void) const
{
   QString tst;
   switch(code())
   {
      case tcDoublePlus:      tst = "Doubleplus        "; break;
      case tcPlusEqual:       tst = "PlusEqual         "; break;
      case tcPlus:            tst = "Plus              "; break;
      case tcDoubleMinus:     tst = "DoubleMinus       "; break;
      case tcMinusEqual:      tst = "MinusEqual        "; break;
      case tcMinus:           tst = "Minus             "; break;
      case tcMulEqual:        tst = "MulEqual          "; break;
      case tcMul:             tst = "Mul               "; break;
      case tcDevideEqual:     tst = "DevideEqual       "; break;
      case tcDevide:          tst = "Devide            "; break;
      case tcModEqual:        tst = "ModEqual          "; break;
      case tcMod:             tst = "Mod               "; break;
      case tcEqu:             tst = "Equ               "; break;
      case tcLiken:           tst = "Liken             "; break;
      case tcAndEqual:        tst = "AndEqual          "; break;
      case tcAnd:             tst = "And               "; break;
      case tcBitAnd:          tst = "BitAnd            "; break;
      case tcOrEqual:         tst = "OrEqual           "; break;
      case tcOr:              tst = "Or                "; break;
      case tcBitOr:           tst = "BitOr             "; break;
      case tcXorEqual:        tst = "XorEqual          "; break;
      case tcXor:             tst = "Xor               "; break;
      case tcBitXor:          tst = "BitXor            "; break;
      case tcNeq:             tst = "Neq               "; break;
      case tcNot:             tst = "Not               "; break;
      case tcLeq:             tst = "Leq               "; break;
      case tcShiftLeftEqual:  tst = "ShiftLeftEqual    "; break;
      case tcShiftLeft:       tst = "ShiftLeft         "; break;
      case tcLs:              tst = "Ls                "; break;
      case tcGeq:             tst = "Geq               "; break;
      case tcShiftRightEqual: tst = "ShiftRightEqual   "; break;
      case tcShiftRight:      tst = "ShiftRight        "; break;
      case tcGt:              tst = "Gt                "; break;
      case tcDot:             tst = "Dot               "; break;
      case tcPeriod:          tst = "Period            "; break;
      case tcSingleQuote:     tst = "SingleQuote       "; break;
      case tcStartArray:      tst = "StartArray        "; break;
      case tcEndArray:        tst = "EndArray          "; break;
      case tcStartBlock:      tst = "StartBlock        "; break;
      case tcEndBlock:        tst = "EndBlock          "; break;
      case tcStartParam:      tst = "StartParam        "; break;
      case tcEndParam:        tst = "EndParam          "; break;
      case tcQuestion:        tst = "Question          "; break;
      case tcChoice:          tst = "Choice            "; break;
      case tcDelete:          tst = "Delete            "; break;
      case tcDollar:          tst = "Dollar            "; break;
      case tcBar:             tst = "Bar               "; break;
      case tcBackSlash:       tst = "BackSlash         "; break;
      case tcEndOperator:     tst = "EndOperator       "; break;
      case tcError:           tst = "ErrorCode         "; break;
      case tcCommentLine:     tst = "CommentLine       "; break;
      default:                tst = "UnknownOperator   "; break;
   }

   _out.putLine("\t>> Special: " + tst + "\t" + _parse);
}
//==============================================================================
