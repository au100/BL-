//==============================================================================
#include "token.h"
//==============================================================================
TCharCode* TToken::_charCodeMap = Q_NULLPTR;
//------------------------------------------------------------------------------
TToken::TToken(TTextOutBuffer* pOut,
               TCharCode token)
      : _tokenType(token)
      , _code(tcDummy)
      , _type(ttDummy)
      , _out(*pOut)
{
   _value.pInt64 = 0;
   initCharCodeMap();
}
//------------------------------------------------------------------------------
void TToken::initCharCodeMap()
{
   if(_charCodeMap == Q_NULLPTR)
   {
      _charCodeMap = new TCharCode[sizeof(TCharCode) * 128];
      for(int i =  0;  i <= 127; i++) _charCodeMap[i]= ccError;
      for(int i = 'a'; i <= 'z'; i++) _charCodeMap[i]= ccLetter;
      for(int i = 'A'; i <= 'Z'; i++) _charCodeMap[i]= ccLetter;
      for(int i = '0'; i <= '9'; i++) _charCodeMap[i]= ccDigit;

      _charCodeMap[ '_' ] = ccLetter;

      _charCodeMap[ '+' ] = _charCodeMap[ '-' ] =
      _charCodeMap[ '*' ] = _charCodeMap[ '/' ] =
      _charCodeMap[ '=' ] = _charCodeMap[ '^' ] =
      _charCodeMap[ '.' ] = _charCodeMap[ ',' ] =
      _charCodeMap[ '<' ] = _charCodeMap[ '>' ] =
      _charCodeMap[ '(' ] = _charCodeMap[ ')' ] =
      _charCodeMap[ '[' ] = _charCodeMap[ ']' ] =
      _charCodeMap[ '{' ] = _charCodeMap[ '}' ] =
      _charCodeMap[ ':' ] = _charCodeMap[ ';' ] =
      _charCodeMap[ '\''] = _charCodeMap[ '!' ] =
      _charCodeMap[ '~' ] = _charCodeMap[ '%' ] =
      _charCodeMap[ '&' ] = _charCodeMap[ '$' ] =
      _charCodeMap[ '|' ] = _charCodeMap[ '\\'] =
      _charCodeMap[ '?' ] = _charCodeMap[ '#' ] = ccSpecial;

      _charCodeMap[ ' ' ] = _charCodeMap[ '\t'] =
      _charCodeMap[ '\n'] = _charCodeMap[ '\r'] = ccSpace;

      _charCodeMap[ '\"']                      = ccQuote;
   }
}
//------------------------------------------------------------------------------
QChar TToken::initParse(TTextInBuffer& in)
{
   _parse = "";
   return in.getChar();
}
//------------------------------------------------------------------------------
TCharCode TToken::checkEnd(TTextInBuffer& in)
{
   int len = in.line().length();
   int pos = in.pos();
   if(pos < len)
      return ccOk;
   else if(in.atEnd() == true)
      return ccEndOfFile;
   else
      return ccError;
}
//------------------------------------------------------------------------------
void TToken::skipLine(TTextInBuffer& in)
{
   in.getLine();
}
//------------------------------------------------------------------------------
void TToken::skipWord(TTextInBuffer& in)
{
   TCharCode cc;
   do
      cc = charCode(in.getChar());
   while(cc == ccLetter || cc == ccDigit);
   in.putBackChar();
}
//------------------------------------------------------------------------------
TCharCode TToken::charCode(QChar ch, TTextInBuffer* in)
{
   if(_charCodeMap == Q_NULLPTR)
      initCharCodeMap();
   ushort u = ch.unicode();
   if(u > 0 && u <= 127)
      return _charCodeMap[u];
   if(in != Q_NULLPTR && u == 0)
     return checkEnd(*in);
   else
    return ccError;
}
//==============================================================================
QString& TEndOfFileToken::get(TTextInBuffer& in)
{
   QChar      ch = initParse(in);
   if(charCode(ch, &in) == ccEndOfFile)
      _parse += '\n';
   else
   {
      // set Error
   }
   return _parse;
}
//------------------------------------------------------------------------------
void TEndOfFileToken::print(void) const
{
   _out.putLine("End of file");
}
//==============================================================================
QString& TErrorToken::get(TTextInBuffer& in)
{
   _parse = QString::number(in.lineNo());
//   initParse(in);
   // set Error
   return _parse;
}
//------------------------------------------------------------------------------
void TErrorToken::print(void) const
{
   _out.putLine("\t>> Error in line " + _parse);
}
//==============================================================================

