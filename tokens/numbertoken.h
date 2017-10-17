//==============================================================================
#ifndef TNUMBERTOKEN_H
#define TNUMBERTOKEN_H
//==============================================================================
#include "token.h"
//==============================================================================
class TNumberToken : public TToken
{
   public:
                           TNumberToken(TTextOutBuffer* pOut)
                             : TToken(pOut, ccDigit)
                           {
                              _code = tcNumber;
                           }
      virtual  QString&    get(TTextInBuffer& in);
      virtual  void        print(void) const;
   private:
      QChar                accumulateDecimalValue(TTextInBuffer& in);
      QChar                accumulateHexValue(TTextInBuffer& in);
};

//==============================================================================
#endif // TNUMBERTOKEN_H
//==============================================================================
