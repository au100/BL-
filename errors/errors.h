//==============================================================================
#ifndef TERROR_H
#define TERROR_H
//==============================================================================
<<<<<<< HEAD
=======
#include <QtGlobal>
#include "errmsg.h"
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
#include "log/log.h"
//==============================================================================
quint32           getLastError();
void              setError(quint32 code, ...);
void              setOutputHandlers(TLog* error = Q_NULLPTR,
                                    TLog* info  = Q_NULLPTR,
                                    TLog* debug = Q_NULLPTR,
                                    TLog* log   = Q_NULLPTR);
void              setDebugLevel(quint32 lvl);
bool              setErrorLanguage(QString lang);
//==============================================================================
#endif // TERROR_H
//==============================================================================
