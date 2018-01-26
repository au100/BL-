//==============================================================================
#include "log.h"
//==============================================================================
void TLog::putLine(const QString& text)
{
   QString ret = codec()->toUnicode(text.toUtf8());
   *this
      << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")
      << ret
      << '\n';
   flush();
}
//==============================================================================
