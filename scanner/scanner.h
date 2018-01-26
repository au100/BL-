//==============================================================================
#ifndef TSCANNER_H
#define TSCANNER_H
//==============================================================================
#include "../tokens/token.h"
#include "../tokens/literaltoken.h"
#include "../tokens/numbertoken.h"
#include "../tokens/stringtoken.h"
#include "../tokens/specialtoken.h"
#include "../streams/buffer.h"
#include <QList>
//==============================================================================
class TScanner
{
   protected:
      QList<TToken*>          _token;
      TTextInBuffer*          _in;
      TTextOutBuffer*         _out;
   public:
                              TScanner(TTextInBuffer*  pIn,
                                       TTextOutBuffer* pOut);
      virtual                ~TScanner();
              TTextInBuffer&  textInput()
                              {
                                 return *_in;
                              }
              TTextOutBuffer& textOutput()
                              {
                                 return *_out;
                              }
      virtual TToken*         get(void) = 0;
              TToken*         getToken(TCharCode code = ccError);
   private:
              TToken*         appendToList(TToken* tkn);
};
//==============================================================================
class TTextScanner : public TScanner
{
   private:
      QChar                   skipSpace();
   public:
                              TTextScanner(TTextInBuffer*  pIn,
                                           TTextOutBuffer* pOut);
      virtual  TToken*        get();
};
//==============================================================================
class TokenFactory
{
   public:
      static TToken*          Factory(TCharCode code,
                                      TTextOutBuffer* out)
      {
         switch(code)
         {
            case ccQuote:     return new TStringToken(out);
            case ccDigit:     return new TNumberToken(out);
            case ccLetter:    return new TLiteralToken(out);
            case ccSpecial:   return new TSpecialToken(out);
            case ccEndOfFile: return new TEndOfFileToken(out);
            default:          return new TErrorToken(out);
         }
      }
};
//==============================================================================
#endif // TSCANNER_H
//==============================================================================
