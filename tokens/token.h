//==============================================================================
#ifndef TTOKEN_H
#define TTOKEN_H
//==============================================================================
#include "../streams/buffer.h"
#include "../log/log.h"
#include "../errors/errors.h"
#include "../scanner/misc.h"
//==============================================================================
class TToken
{
   public:
                           TToken(TTextOutBuffer* pOut,
                                  TCharCode token = ccError);
      virtual             ~TToken() {}

   protected:
      TCharCode            _tokenType;
      TTokenCode           _code;
      TTokenType           _type;
      TTokenValue          _value;
      QString              _parse;
      static TCharCode*    _charCodeMap;
      TTextOutBuffer&      _out;
      QChar                initParse(TTextInBuffer& in);
      static TCharCode     checkEnd(TTextInBuffer& in);

   public:
      TTokenCode           code() const
                           {
                              return _code;
                           }
      TTokenType           type() const
                           {
                              return _type;
                           }
      TTokenValue          value() const
                           {
                              return _value;
                           }
      TCharCode            token()
                           {
                              return _tokenType;
                           }

      void                 skipWord(TTextInBuffer&  in);
      void                 skipLine(TTextInBuffer&  in);
      static TCharCode     charCode(QChar ch, TTextInBuffer* in = Q_NULLPTR);
      static void          initCharCodeMap();

      virtual  QString&    get(TTextInBuffer& in)     = 0;
      virtual  void        print(void)          const = 0;
};
//==============================================================================
class TEndOfFileToken : public TToken
{
   public:
                           TEndOfFileToken(TTextOutBuffer* pOut)
                             : TToken(pOut, ccEndOfFile)
                           {
                              _code = tcEndOfFile;
                           }
      virtual  QString&    get(TTextInBuffer& in);
      virtual  void        print(void) const;
};
//==============================================================================
class TErrorToken : public TToken
{
   public:
                           TErrorToken(TTextOutBuffer* pOut)
                             : TToken(pOut, ccError)
                           {
                              _code = tcError;
                           }
      virtual  QString&    get(TTextInBuffer& in);
      virtual  void        print(void) const;
};
//==============================================================================
#endif // TTOKEN_H
//==============================================================================
