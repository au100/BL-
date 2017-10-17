//==============================================================================
#ifndef COMMON_H
#define COMMON_H
//==============================================================================
#include <stddef.h>
#include <QString>
#include <vector>
//-----------------------------------------------------------------------------
// class MemPtr
//-----------------------------------------------------------------------------
const size_t IncreaseSize = 256;
//-----------------------------------------------------------------------------
template <class T>
class MemPtr
{
   public:
               MemPtr()
                  : _data(NULL)
                  , _size(0)
                  , _bufferSize(0)
               {
                  resize(IncreaseSize);
               }
               MemPtr(const MemPtr& copyMem)
                  : _data(NULL)
                  , _size(0)
                  , _bufferSize(0)
               {
                  copyFrom(copyMem);
               }
               MemPtr(size_t newSize)
                  : _data(NULL)
                  , _size(0)
                  , _bufferSize(0)
               {
                  resize(newSize);
               }
      virtual ~MemPtr()
               {
                  if (_data != NULL)
                     delete[] _data;
               }
      T&			operator[](int idx)
               {
                  return _data[idx];
               }
      MemPtr&  clone(const QString& str)
               {
                  resize(str.size() + 1);
                  _size = str.size() + 1;
                  memcpy(data(), (const void*)str.data(), _size);
                  return *this;
               }
      MemPtr&  clone(const MemPtr& copyMem)
               {
                  resize(copyMem._bufferSize);
                  _size = copyMem._size;
                  memcpy(data(), (const void*)copyMem.data(), copyMem.sizeInBytes());
                  return *this;
               }
      MemPtr&  add(const T& element)
               {
                  if (_size == _bufferSize)
                     resize(_size + IncreaseSize);
                  _data[_size++] = element;
                  return *this;
               }
      void*		data() const
               {
                  return (void*)_data;
               }
      size_t   sizeInBytes() const
               {
                  return sizeof(T) * _size;
               }
      MemPtr&  resize(size_t newSize)
               {
                  if (newSize > _bufferSize)
                  {
                     T* newData = NULL;
                     newData = new T[newSize];
                     if (_data != NULL)
                     {
                        memcpy(newData, _data, sizeInBytes());
                        delete[] _data;
                     }
                     _bufferSize = newSize;
                     _data = newData;
                  }
                  return *this;
               }
      size_t   size()
               {
                  return _size;
               }
      int      elementSize()
               {
                  return sizeof(T);
               }
   private:
      T*       _data;
      size_t   _size;
      size_t   _bufferSize;
};
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
