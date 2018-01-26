//==============================================================================
#ifndef PARSER_H
#define PARSER_H
//==============================================================================
#include "../scanner/scanner.h"
#include "../scanner/misc.h"
#include <QtGlobal>
//==============================================================================
class TParser
{
   private:
            TTextScanner*     _scanner;
            TToken*           _token;
            TTokenCode        _code;
            int               _errorCount;
   private:
            void              getToken(void)
                              {
                                 _token = _scanner->get();
                                 _code  = _token->code();
                              }

   public:
                              TParser(TTextInBuffer  *in,
                                      TTextOutBuffer *out)
                                : _scanner(new TTextScanner(in, out))
                                , _errorCount(0)
                              {
                              }
      virtual                ~TParser(void)
                              {
                                 delete _scanner;
                              }
            void              parse(void);
};
//==============================================================================
#endif // PARSER_H
//==============================================================================

