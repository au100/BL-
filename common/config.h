//==============================================================================
#ifndef CONFIG_H
#define CONFIG_H
//==============================================================================
#include "common.h"
//#include "errors/errors.h"
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVariant>
#include <QCoreApplication>
#include <QDir>
//==============================================================================
class Config {   // Singleton class
   public:
                     Config()
                        : _modified(false)
                     {
                        QFile file("bl.ini");
                        if(file.exists() == false)
                        {
//                           setError(FILE_OPEN_FAILED, "bl.ini");
                           printf("File not found\n");
                           qApp->exit();
                        }
                        QSettings ini("bl.ini", QSettings::IniFormat);
                        QStringList keys = ini.allKeys();
                        for(QStringList::const_iterator it = keys.cbegin();
                            it != keys.cend();
                            ++it)
                        {
                           _settings.insert((*it).toLower(),
                                            ini.value(*it).toString().trimmed());
                        }
                     }
      virtual       ~Config()
                     {
                     }
      bool           caseSensitive()
                     {
                        QString s = value("caseSensitive").toString().toLower();
                        if(s == "TRUE" ||
                           s == 1)
                            return true;
                        else
                            return false;

                     }
      QVariant       value(const QString& key)
                     {
                        return QVariant(_settings[key.toLower().trimmed()]);
                     }
      template <class Q>
      void setValue(const QString& key, const Q& value)
                     {
                        QVariant var(value);
                        _settings.insert(key, var.toString());
                        _modified = true;
                     }
   private:
      QString        _configName;
      QMap<QString, QString>  _settings;
      bool           _modified;
};
//==============================================================================
#define CONFIG    SINGLETON(Config)
//==============================================================================
#endif // CONFIG_H
//==============================================================================

