//==============================================================================
#ifndef TLITERALTOKEN_H
#define TLITERALTOKEN_H
//==============================================================================
#include "token.h"
//==============================================================================
typedef struct tagWordToken {
      TTokenCode        code;
      QString           word;
} WordToken;
//------------------------------------------------------------------------------
class TLiteralToken : public TToken {
   private:
      static   WordToken   parseToken[];
               TTokenCode  find();
   public:
                           TLiteralToken(TTextOutBuffer* pOut)
                             : TToken(pOut, ccLetter)
                           {
                              _code = tcIdentifier;
                           }
      virtual  QString&    get(TTextInBuffer& in);
      virtual  void        print(void) const;
};
//==============================================================================
#endif // TLITERALTOKEN_H
//==============================================================================
