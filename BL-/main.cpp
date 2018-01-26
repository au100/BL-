#include <QCoreApplication>
#include "streams/buffer.h"
//#include "errors/errors.h"
#include "parser/parser.h"
#include <QFile>
#include <QDir>



int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);
   QCoreApplication::setOrganizationName("Ushakov Co");
   QCoreApplication::setApplicationName("BL Compiler");

   TTextOutBuffer out(stdout, QString("Output stream"));
   if(setErrorLanguage("ru") == true)
   {
//   TTextInBuffer in(qApp->applicationDirPath() +
//                    QString("/messages/errors/message.ru"));
      QString f = qApp->applicationDirPath() 
                + QDir::separator() 
                + QString("armte.cpp");
      TTextInBuffer in(f);
      if(in.status() == true)
      {
         TParser parser(&in, &out);
         parser.parse();
      }
   }
   return getLastError();
}
