//==============================================================================
<<<<<<< HEAD
#include <QtGlobal>
#include <QSettings>
#include "errors.h"
#include "errmsg.h"
=======
#include "errors.h"
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
#include "common/common.h"
#include <iostream>
#include <QTextCodec>
#include <QSettings>
#include <QCoreApplication>
#include <QtGui/QGuiApplication>
//==============================================================================
class TError {
   Q_DECLARE_TR_FUNCTIONS(TError)
   public:
   //---------------------------------------------------------------------------
                        TError()
                           : error(new TLog(stderr, "stderr"))
                           , info (new TLog(stdout, "stdout"))
                           , debug(new TLog(stdout, "stdout"))
                           , log(Q_NULLPTR)
                           , dbgLevel(0)

                        {
                        }
      //------------------------------------------------------------------------
                       ~TError()
                        {
                           if(error != Q_NULLPTR) delete error;
                           if(info  != Q_NULLPTR) delete info;
                           if(debug != Q_NULLPTR) delete debug;
                           if(log   != Q_NULLPTR) delete log;
                        }
      //------------------------------------------------------------------------
      void              setDebugLevel(quint32 level)
                        {
                           dbgLevel = level;
                        }
      //------------------------------------------------------------------------
      quint32           getLastError()
                        {
                           return lastErrorCode;
                        }
      //------------------------------------------------------------------------
      QString           format(quint32  code, va_list str)
                        {
                           QString fmt = getErrorMessage(code);
                           for(int i = 1 ; i <= 9; i++)
                           {
                              QString fr = "%" + QString::number(i);
                              if(fmt.indexOf(fr) == -1)
                                 break;
                              QString* arg = va_arg(str, QString*);
                              fmt = fmt.replace(fr, *arg);
                           }
                           return fmt;
                        }
      //------------------------------------------------------------------------
      void              setError(quint32  code,
                                 va_list str)
                        {
                           lastErrorCode = code;
                           QString errType  = "";

                           TLog* logOut = Q_NULLPTR;
                           if(FATAL(code))
                           {
                              errType = "!!!FATAL ERROR!!! ";
                              logOut = error;
                           }
                           else if(ERROR(code))
                           {
                              errType = "ERROR: ";
                              logOut = error;
                           }
                           else if(WARNING(code))
                           {
                              errType = "WARNING: ";
                              logOut = info;
                           }
                           else if(INFO(code))
                           {
                              errType = "INFO: ";
                              logOut = info;
                           }
                           else if(DEBUG(code))
                           {
                              if(DEBUG_LEVEL(code, dbgLevel))
                              {
                                 errType = "DEBUG: ";
                                 logOut = debug;
                              }
                           }
                           if(logOut != Q_NULLPTR)
                           {
                              errType += format(code, str);
                              logOut->putLine(errType);
                              if(log != Q_NULLPTR)
                                 log->putLine(errType);
                           }
                        }
      //------------------------------------------------------------------------
      bool              setErrorLanguage(QString lang)
                        {
                           QSettings* ini = errorLanguage(lang);
                           if(ini != Q_NULLPTR)
                           {
                              QString codec;
                              ini->beginGroup("codec");
                              #ifdef Q_OS_WIN
                                 codec = ini->value("WINDOWS", "").toString();
                              #else
                                 codec = ini->value("LINUX", "").toString();
                              #endif
                              ini->endGroup();
                              if(codec.length() != 0)
                              {
                                 const char *name = codec.toStdString().c_str();
                                 error->setCodec(name);
                                 error->setCodec(name);
                                 info->setCodec(name);
                                 debug->setCodec(name);
<<<<<<< HEAD
                                 if(log != Q_NULLPTR)
                                    log ->setCodec(name);
=======
                                 log ->setCodec(name);
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
                              }
                              return true;
                           }
                           return false;
                        }
      //------------------------------------------------------------------------
      void              setOutputHandlers(TLog* _error = Q_NULLPTR,
                                          TLog* _info  = Q_NULLPTR,
                                          TLog* _debug = Q_NULLPTR,
                                          TLog* _log   = Q_NULLPTR)
                        {
                           if(_error != Q_NULLPTR)
                           {
                              if(error != Q_NULLPTR)
                                 delete error;
                              error = _error;
                           }
                           if(_info != Q_NULLPTR)
                           {
                              if(info != Q_NULLPTR)
                                 delete info;
                              info = _info;
                           }
                           if(_debug != Q_NULLPTR)
                           {
                              if(debug != Q_NULLPTR)
                                 delete debug;
                              debug = _debug;
                           }
                           if(_log != Q_NULLPTR)
                           {
                              if(log != Q_NULLPTR)
                                 delete log;
                              log = _log;
                           }
                        }
      //------------------------------------------------------------------------
      quint32           lastErrorCode;
      TLog *            error; // output handle for fatal, errors
                               // default: std::cerr
      TLog *            info;  // output handle for warning and info
                               // default std::cout
      TLog *            debug; // output handle for debug
                               // default std::cout
      TLog *            log;   // handler for the logs (fatal, error,
                               // warning, info, no debug) default NULL
      quint32           dbgLevel;
};
//==============================================================================
void setDebugLevel(quint32 lvl)
{
   SINGLETON(TError).setDebugLevel(lvl);
}
//------------------------------------------------------------------------------
void setError(quint32 code, ...)
{
   va_list str;
   va_start(str, code);
   SINGLETON(TError).setError(code, str);
   va_end(str);
}
//------------------------------------------------------------------------------
void  setOutputHandlers(TLog* error,
                        TLog* info,
                        TLog* debug,
                        TLog* log)
{
   SINGLETON(TError).setOutputHandlers(error, info, debug, log);
}
//------------------------------------------------------------------------------
quint32 getLastError()
{
   return SINGLETON(TError).getLastError();
}
//------------------------------------------------------------------------------
bool  setErrorLanguage(QString lang)
{
   return SINGLETON(TError).setErrorLanguage(lang);
}
//==============================================================================
