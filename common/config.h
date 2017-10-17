//==============================================================================
#ifndef CONFIG_H
#define CONFIG_H
//==============================================================================
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVariant>
#include <QCoreApplication>
#include <QDir>
//==============================================================================
class Config {   // Singleton classs
   public:
                     Config()
                        : _modified(false)
                     {
                        QSettings ini("bl.ini", QSettings::IniFormat);
                        QStringList keys = ini.allKeys();
                        for(QStringList::const_iterator it = keys.cbegin();
                            it != keys.cend();
                            ++it)
                        {
                           _settings.insert(*it, ini.value(*it).toString());
                        }
                     }
      virtual       ~Config()
                     {
                     }
      QVariant       value(const QString& key)
                     {
                        return QVariant(_settings[key]);
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

