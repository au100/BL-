//==============================================================================
#ifndef TSPECIALTOKEN_H
#define TSPECIALTOKEN_H
//==============================================================================
#include "token.h"
//==============================================================================
class TSpecialToken : public TToken
{
   public:
                           TSpecialToken(TTextOutBuffer* pOut)
                             : TToken(pOut, ccSpecial)
                           {
                              _code = tcSpecial;
                           }
      virtual  QString&    get(TTextInBuffer& in);
      virtual  void        print(void) const;
};
//==============================================================================
#endif // TSPECIALTOKEN_H
//==============================================================================
