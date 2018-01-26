//==============================================================================
#ifndef COMMON_H
#define COMMON_H
//==============================================================================
#include <stddef.h>
#include <QString>
#include <vector>
//-----------------------------------------------------------------------------
template <class T> class Singleton
{
   private:
            Singleton() {}
            Singleton(const Singleton&);
            Singleton& operator=(Singleton&);
public:
      static	T& Instance()
            {
               static T _instance;
               return _instance;
            }
};
//-----------------------------------------------------------------------------
#define SINGLETON(T)    Singleton<T>::Instance()
//==============================================================================
/*
//==============================================================================
class Object
{
   protected:
      static                  QMap<void*, void*> _obj;
   public:
      //------------------------------------------------------------------------
                              Object()
                                 : destructorIsRunning(false)
                              {
                              }
      virtual                ~Object()
                              {
                                 destructorIsRunning = true;
                                 _obj.remove(this);
                              }
      //------------------------------------------------------------------------
      virtual  void           free()
                              {
                                 if(destructorIsRunning == false)
                                    delete this;
                              }
   private:
               bool           destructorIsRunning;
};
#define singleton(T)       SingleObject<T>::instance(#T)
//==============================================================================
class SingletonObject : public Object
{
   //---------------------------------------------------------------------------
   private:
      QString                 _name;
      static SingletonObject* _inst;
      QMap<QString, void*>    _map;
                              SingletonObject(const QString& name);
   //---------------------------------------------------------------------------
   public:
      virtual                ~SingletonObject();
      //------------------------------------------------------------------------
      static SingletonObject& instance();
      const QString&          check(void* obj);
      void*                   check(const QString& name);
      void*                   add(const QString& name, void* obj);
      void                    remove(const QString& name);
      QList<QString>          names();
};
//==============================================================================
template <class T> class SingleObject : public Object
{
   private:
                              SingleObject<T>()
                              {
                              }
      virtual                ~SingleObject<T>()
                              {
                                 SingletonObject& s=SingletonObject::instance();
                                 QString name = s.check(this);
                                 if(name.length() != 0)
                                    s.remove(name);
                                 delete static_cast<T*>(_obj.value(this));
                              }
   //---------------------------------------------------------------------------
   public:
      //------------------------------------------------------------------------
      static T*               instance(const QString& objName)
                              {
                                 T* inst;
                                 SingletonObject& s=SingletonObject::instance();
                                 void* th = s.check(objName);
                                 if(th == Q_NULLPTR)
                                 {
                                    th = new SingleObject<T>;
                                    inst = new T;
                                    _obj.insert(th, inst);
                                    s.add(objName, th);
                                 }
                                 else
                                    inst = static_cast<T*>(_obj.value(th));
                                 return inst;
                              }
      //------------------------------------------------------------------------
};
*/
//==============================================================================
#endif // COMMON_H
//==============================================================================
