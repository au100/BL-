//==============================================================================
#include "stringtoken.h"
//==============================================================================
bool getHexCode(TTextInBuffer& in, QChar& c)
{
   bool ret = false;
   char ch = in.getChar().toLatin1();
   c = 0;
   if(ch >= '0' && ch <= '9')
   {
      ch -= '0';
      ret = true;
   }
   else if(ch >= 'a' && ch <= 'z')
   {
      ch = ch -'a' + 10;
      ret = true;
   }
   else if(ch >= 'A' && ch <= 'Z')
   {
      ch = ch - 'A' + 10;
      ret = true;
   }
   if(ret == true)
      c = ch;
   return ret;
}
//------------------------------------------------------------------------------
QString& TStringToken::get(TTextInBuffer& in)
{
   bool endString = false;
<<<<<<< HEAD
   QChar ch       = initParse(in);
=======
   QChar      ch = initParse(in);
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
   while(endString == false)
   {
      if(charCode(ch) == ccQuote)
      {
         ch = in.getChar();
         TCharCode cc = charCode(ch);
         while(cc != ccQuote)
         {
            //------------------------------------------------------------------
            // Special token to get special characters
            // '\r', '\n', '\t' ...
            //------------------------------------------------------------------
            if(ch == '\\')
            {
               ch = in.getChar();
                    if(ch == 'n' ) ch = '\n'; // Перевод строки
               else if(ch == 'r' ) ch = '\r'; // Возврат каретки
               else if(ch == 't' ) ch = '\t'; // Табуляция
               else if(ch == 'v' ) ch = '\v'; // Веритикальная табуляция
               else if(ch == '\\') ch = '\\'; // Обратный слеш
               else if(ch == 'a' ) ch = '\a'; // Сигнал бипера
               else if(ch == 'f' ) ch = '\f'; // Разрыв страницы
               else if(ch == '0' ) ch = 0;    // Нулевой символ в строке
               else if(ch == '\"') ch = '\"'; // Кавычки
               else if(ch == 'x' )            // 16 значение char в формате x0A
               {
                  QChar c;
                  if(getHexCode(in, c) == true)
                  {
                     ch = (c.toLatin1() << 4) & 0xF0;
                     if(getHexCode(in, c) == true)
                        ch = (ch.toLatin1() | c.toLatin1());
                     // else set Error Char Hex format in string TODO (line, pos)
                  }
                  // else set error Char Hex format in string TODO (line, pos)
               }
            }
            _parse += ch;
            ch = in.getChar();
            cc = charCode(ch);
         }
         TCharCode c;
         c = charCode(in.getChar());
         while(c == ccSpace)
            c = charCode(in.getChar());
         if(c != ccQuote)
         {
            in.putBackChar();
            endString = true;
         }
      }
      else
      {
         endString = true;
         // set error in string String not started with quote (line)
      }
   }
   return _parse;
}
//------------------------------------------------------------------------------
void TStringToken::print(void) const
{
   _out.putLine("\t>> String:  " + _parse);
}
//==============================================================================
