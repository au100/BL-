//==============================================================================
#include "scanner.h"
//==============================================================================
TScanner::TScanner(TTextInBuffer*  pIn,
                   TTextOutBuffer* pOut)
        : _in(pIn)
        , _out(pOut)
{
   // TODO
   //   if(pIn == Q_NULLPTR)
   //      make FatalError
   //   if(pOut == Q_NULLPTR)
   //      make FatalError
}
//------------------------------------------------------------------------------
TScanner::~TScanner()
{
   for(QList<TToken*>::const_iterator ci = _token.cbegin();
       ci != _token.cend();
       ++ci)
      delete *ci;
}
//------------------------------------------------------------------------------
TToken* TScanner::appendToList(TToken* tkn)
{
   _token.append(tkn);
   return tkn;
}
//------------------------------------------------------------------------------
TToken* TScanner::getToken(TCharCode code)
{
   for(QList<TToken*>::const_iterator ci = _token.cbegin();
       ci != _token.cend();
       ++ci)
   {
      if((*ci)->token() == code)
         return *ci;
   }

   return TokenFactory::Factory(code, _out);
}
//==============================================================================
TTextScanner::TTextScanner(TTextInBuffer*  pIn,
                           TTextOutBuffer* pOut)
            : TScanner(pIn, pOut)
{
}
//------------------------------------------------------------------------------
QChar TTextScanner::skipSpace()
{
   QChar ch;
   do ch = _in->getChar();
   while(TToken::charCode(ch) == ccSpace);
   return ch;
}
//------------------------------------------------------------------------------
TToken* TTextScanner::get()
{
   QChar ch = skipSpace();
   TToken* token = getToken(TToken::charCode(ch, _in));
   _in->putBackChar();
   token->get(*_in);
   return token;
}
//==============================================================================

