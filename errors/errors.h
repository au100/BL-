//==============================================================================
#ifndef TERROR_H
#define TERROR_H
//==============================================================================
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
