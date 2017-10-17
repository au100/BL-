//==============================================================================
#include "parser.h"
//==============================================================================
void TParser::parse(void)
{
   do
   {
      getToken();
      if(_code != tcError)
         _token->print();
      else
      {
         _errorCount++;
         // todo - error definition
         _scanner->textOutput() << "Error in line="
                                << _scanner->textInput().lineNo()
                                << "  Position="
                                << _scanner->textInput().pos()
                                << "  line: "
                                << _scanner->textInput().line()
                                << '\n';
         _scanner->textOutput().flush();
         _token->skipLine(_scanner->textInput());
      }
   } while(_code != tcEndOfFile);
   _scanner->textOutput() << _scanner->textInput().lineNo()
                          << " source lines."
                          << '\n';
   if(_errorCount == 0)
      _scanner->textOutput() << "No Errors!!!\n";
   else
      _scanner->textOutput() << _errorCount
                            << " syntax errors.\n";
   _scanner->textOutput().flush();
}
//==============================================================================

