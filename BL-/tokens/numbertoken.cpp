//==============================================================================
#include "numbertoken.h"
//==============================================================================
QChar TNumberToken::accumulateHexValue(TTextInBuffer& in)
{
   QChar      ch = in.getChar();
   while((charCode(ch) == ccDigit) ||
         (ch >= 'a' && ch <= 'f')  ||
         (ch >= 'A' && ch <= 'F'))
   {
      _parse += ch;
      ch = in.getChar();
   }
   return ch;
}
//------------------------------------------------------------------------------
QChar TNumberToken::accumulateDecimalValue(TTextInBuffer& in)
{
   QChar      ch = in.getChar();
   while(charCode(ch) == ccDigit)
   {
      _parse += ch;
      ch = in.getChar();
   }
   return ch;
}
//------------------------------------------------------------------------------
// avaliable formats:
// (+/-) supprted in SpecialToken (if they are before number)
//    1.  [0-9] - simple integer
//    2.  0x[0-9 a/A-f/F] integer in hex
//    3.  [0-9][.][0-9] real number
//    4.  [0-9][.][0-9][e/E][+/-][0-9] - real number with exponent
//------------------------------------------------------------------------------
QString& TNumberToken::get(TTextInBuffer& in)
{
   bool  hex      = false;
   bool  real     = false;
   bool  exp      = false;
   bool  expReal  = false;
   bool  bWhile   = true;

   // minus(-), plus(+) inversion (~) and not(!) are supported in SpecialToken

   TCharCode  cc;
   _parse = "";

   QChar ch = accumulateDecimalValue(in);

   do {
      cc = charCode(ch);
      switch(cc)
      {
         case ccLetter:
            // -----------------------------------------------------------------
            // Hex value
            // -----------------------------------------------------------------
            if(ch == 'x' || ch == 'X')
            {
               if(hex == false)
               {
                  if(_parse.length() == 1 && _parse[0] == '0')
                  {
                     hex = true;
                     _parse += ch;
                     ch = accumulateHexValue(in);
                     break;
                  }
                  bWhile = false;
                  break;
               }
            }
            // -----------------------------------------------------------------
            // Real value with exponent
            // -----------------------------------------------------------------
            else if(ch == 'e' || ch == 'E')
            {
               if(hex == false && exp == false)
               {
                  exp = true;
                  _parse += ch;
                  ch = in.getChar();
                  if(ch == '-' || ch == '+')
                     _parse += ch;
                  else
                     in.putBackChar();
                  ch = accumulateDecimalValue(in);
                  break;
               }
            }
            bWhile = false;
            break;

         case ccSpecial:
            // -----------------------------------------------------------------
            // Real value
            // -----------------------------------------------------------------
            if(ch == '.')
            {
               if(real == false)
               {
                  real = true;
                  _parse += ch;
                  ch = accumulateDecimalValue(in);
                  break;
               }
               // --------------------------------------------------------------
               // exponent
               // --------------------------------------------------------------
               else if(exp == true && expReal == false)
               {
                  expReal = true;
                  _parse += ch;
                  ch = accumulateDecimalValue(in);
                  break;
               }
            }

         default:
            in.putBackChar();
            bWhile = false;
            break;
      }

   } while(bWhile);
   // make Token Value, TokenType
   // TODO: convert to number with special format defined before
   return _parse;
}
//------------------------------------------------------------------------------
void TNumberToken::print(void) const
{
   _out.putLine("\t>> Number:  " + _parse);
}
//==============================================================================
