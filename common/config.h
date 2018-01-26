//==============================================================================
#ifndef CONFIG_H
#define CONFIG_H
//==============================================================================
<<<<<<< HEAD
#include "common.h"
//#include "errors/errors.h"
=======
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVariant>
#include <QCoreApplication>
#include <QDir>
//==============================================================================
<<<<<<< HEAD
class Config {   // Singleton class
=======
class Config {   // Singleton classs
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
   public:
                     Config()
                        : _modified(false)
                     {
<<<<<<< HEAD
                        QFile file("bl.ini");
                        if(file.exists() == false)
                        {
//                           setError(FILE_OPEN_FAILED, "bl.ini");
                           printf("File not found\n");
                           qApp->exit();
                        }
=======
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
                        QSettings ini("bl.ini", QSettings::IniFormat);
                        QStringList keys = ini.allKeys();
                        for(QStringList::const_iterator it = keys.cbegin();
                            it != keys.cend();
                            ++it)
                        {
<<<<<<< HEAD
                           _settings.insert((*it).toLower(),
                                            ini.value(*it).toString().trimmed());
=======
                           _settings.insert(*it, ini.value(*it).toString());
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
                        }
                     }
      virtual       ~Config()
                     {
                     }
<<<<<<< HEAD
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
=======
      QVariant       value(const QString& key)
                     {
                        return QVariant(_settings[key]);
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
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

