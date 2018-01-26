//==============================================================================
#ifndef TSTRINGTOKEN_H
#define TSTRINGTOKEN_H
//==============================================================================
#include "token.h"
//==============================================================================
class TStringToken : public TToken
{
   public:
                           TStringToken(TTextOutBuffer* pOut)
                             : TToken(pOut, ccQuote)
                           {
                              _code = tcString;
                           }
      virtual  QString&    get(TTextInBuffer& in);
      virtual  void        print(void) const;
};
//==============================================================================
#endif // TSTRINGTOKEN_H
//==============================================================================
