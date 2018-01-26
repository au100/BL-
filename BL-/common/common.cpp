//==============================================================================
#include "common.h"
//==============================================================================
/*
SingletonObject*     SingletonObject::_inst = Q_NULLPTR;
QMap<void*, void*>   Object::_obj;
//==============================================================================
SingletonObject::SingletonObject(const QString& name)
               : _name(name)
{
   SingletonObject::_inst = this;
   //------------------------------------------------------------------------
   // вставляем себя в Map. Теперь данный класс доступен отовсюду
   //------------------------------------------------------------------------
   _map.insert(name, this);
   _obj.insert(this, this);
}
//------------------------------------------------------------------------------
SingletonObject& SingletonObject::instance()
{
   if(SingletonObject::_inst == Q_NULLPTR)
      //------------------------------------------------------------------------
      // Создаем сами себя
      //------------------------------------------------------------------------
      new SingletonObject("SingletonObject");
   return *SingletonObject::_inst;
}
//------------------------------------------------------------------------------
SingletonObject::~SingletonObject()
{
   //---------------------------------------------------------------------------
   // Удаляем себя из Map
   //---------------------------------------------------------------------------
   _map.remove(_name);
   //---------------------------------------------------------------------------
   QList<QString> keys = names();
   for(int i = _map.count(); i > 0; i--)
   {
      Object* obj = (Object*)_map.value(keys.at(i - 1));
      obj->free();
      remove(keys.at(i - 1));
   }
   SingletonObject::_inst = Q_NULLPTR;
}
//------------------------------------------------------------------------------
const QString& SingletonObject::check(void* obj)
{
   static QString _emptyName = "";
   QList<QString> keys = names();
   for(int i = 0; i < keys.count(); i++)
   {
      if(_map.value(keys[i]) == obj)
         return keys[i];
   }
   return _emptyName;
}
//------------------------------------------------------------------------------
void* SingletonObject::check(const QString& name)
{
   if(_map.contains(name))
      return _map.value(name);
   else
      return Q_NULLPTR;
}
//------------------------------------------------------------------------------
void* SingletonObject::add(const QString& name, void* obj)
{
   if(check(name) == false)
      _map.insert(name, obj);
   return _map.value(name);
}
//------------------------------------------------------------------------------
void SingletonObject::remove(const QString& name)
{
   _map.remove(name);
}
//------------------------------------------------------------------------------
QList<QString> SingletonObject::names()
{
   return _map.keys();
}
*/
//==============================================================================

