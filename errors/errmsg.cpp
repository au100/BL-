//==============================================================================
#include "errmsg.h"
#include <QSettings>
#include <QObject>
#include <QCoreApplication>
//==============================================================================
static MessageCode code[] = {
   //---------------------------------------------------------------------------
   // Application errors
   //---------------------------------------------------------------------------
   M_MSG_CODE(INVALID_COMMAND),
   //---------------------------------------------------------------------------
   // Translation errors
   //---------------------------------------------------------------------------
   M_MSG_CODE(TOO_MANY_ERROR),
   M_MSG_CODE(STACK_OVERFLOW),
   M_MSG_CODE(CODE_SEGMENT_OVERFLOW),
   M_MSG_CODE(NESTING_TOO_DEEP),
   M_MSG_CODE(RUNTIME_ERROR),
   M_MSG_CODE(UNIMPLEMENTED_FEATURE),
   M_MSG_CODE(SOURCE_FILE_OPEN_FAILED),
   M_MSG_CODE(FORM_FILE_OPEN_FAILED),
   M_MSG_CODE(ASSEMBLY_FILE_OPEN_FAILED),
   // digits translation
   M_MSG_CODE(UNRECOGNAZIBLE_ERROR),
   M_MSG_CODE(UNEXPECTED_ENDOFFIE),
   M_MSG_CODE(INVALID_NUMBER ),
   M_MSG_CODE(INVALID_FRACTION),
   M_MSG_CODE(INVALID_EXPONENT),
   M_MSG_CODE(TOO_MANY_DIGITS),
   M_MSG_CODE(INTEGER_OUT_OF_RANGE),
   M_MSG_CODE(REAL_OUT_OF_RANGE),
   //---------------------------------------------------------------------------
   // Memory errors
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Stream errors
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // File Stream Error
   //---------------------------------------------------------------------------
   M_MSG_CODE(FILE_OPEN_FAILED),
   M_MSG_CODE(FILE_NOT_EXIST),
   //---------------------------------------------------------------------------
   // end of errors codes
   //---------------------------------------------------------------------------
   { 0xFFFFFFFF, Q_NULLPTR }
};
//------------------------------------------------------------------------------
//==============================================================================
static QString getErrorMsg(quint32 codeErr)
{
   MessageCode* tmp = code;
   while(tmp->code != 0xFFFFFFFF)
   {
      if(tmp->code == codeErr)
         return QCoreApplication::tr(tmp->msg);
      tmp++;
   }
   return "";
}
//==============================================================================
class TErrorMsg : public QObject
{
   //Q_OBJECT
   //---------------------------------------------------------------------------
   private:
   //---------------------------------------------------------------------------
      static   TErrorMsg&  Instance()
                           {
                              if(self == Q_NULLPTR)
                                 new TErrorMsg();
                              else
                              {
                                 // exception
                              }
                              return *self;
                           }
      //------------------------------------------------------------------------
                          ~TErrorMsg()
                           {
                              self = Q_NULLPTR;
                              if(language != Q_NULLPTR)
                              {
//                                 TextCodec *codec = QTextCodec::codecForName("CP866");
//                                 QByteArray encodedString = codec->fromUnicode(string);
//                                 std::cout << encodedString.data();
                                 delete language;
                              }
                           }
      //------------------------------------------------------------------------
                           TErrorMsg()
                              : language(Q_NULLPTR)
                           {
                              if(self == Q_NULLPTR)
                                 self = this;
                              //------------------------------------------------
                              // set default language
                              //------------------------------------------------
                              language = setErrorLanguage("en");
                           }
      //------------------------------------------------------------------------
      QSettings*           setErrorLanguage(QString lang)
                           {
                              if(language != Q_NULLPTR)
                                 delete language;
                              QString path =
                                      qApp->applicationDirPath() +
                                      "/messages/errors/message." +
                                      lang;
//                              language = new QSettings(
//                                          qApp->applicationDirPath() +
//                                          "/messages/errors/message." +
//                                          lang,
//                                          QSettings::IniFormat);
                              language = new QSettings(path,
                                                       QSettings::IniFormat);
                              language->setIniCodec("UTF-8");
                              return language;
                           }
      //------------------------------------------------------------------------
      QString              getErrorMessage(quint32 code)
                           {
                              QString codeName = ::getErrorMsg(code);
                              if(codeName.length() == 0)
                              {
                                 return QString(
                                    //------------------------------
                                    // todo convert code to hex and add to string
                                    //------------------------------
                                    "Unknown Error: cannot find errorCode = "
                                    );
                              }
                              language->beginGroup("messages");
                              QString msg =
                                 tr(language->value(codeName, "").toString().toStdString().c_str());
                              if(msg.length() == 0)
                              {
                                 msg = "ERROR: " +
                                       codeName +
                                       " is not defined in Language file " +
                                       language->fileName();
                              }
                              language->endGroup();
                              return msg;
                           }
      //------------------------------------------------------------------------
      static      TErrorMsg*     self;
                  QSettings*     language;
      //------------------------------------------------------------------------
      friend      QString        getErrorMessage(quint32 code);
      friend      void           setErrorLanguage(QString fileName);
      friend      QSettings*     errorLanguage(QString fileName);
      //------------------------------------------------------------------------
};
//==============================================================================
QString  getErrorMessage(quint32 code)
{
   return TErrorMsg::Instance().getErrorMessage(code);
}
//------------------------------------------------------------------------------
QSettings* errorLanguage(QString fileName)
{
   return TErrorMsg::Instance().setErrorLanguage(fileName);
}

//==============================================================================
TErrorMsg*   TErrorMsg::self = Q_NULLPTR;
//==============================================================================

