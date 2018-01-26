//==============================================================================
<<<<<<< HEAD
#include "common/config.h"
=======
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
#include "symtab.h"
//==============================================================================
TSymtabNode* TSymtab::search(const QString& str, TSymtabNode* top)
{
   TSymtabNode* ret = Q_NULLPTR;
<<<<<<< HEAD
   // TODO: Необходимо сохранять в дереве имена сразу с нижнем регистре, если
   // определена caseInsensitive. Тогда вызов toLower нужен будет только
   // для в выражении QString srch = caseSensitive ? str: str.toLower();
   // А иначе необходимо преобразование top->left()->symbol() и
   // top->right()->symbol()
   QString srch = CONFIG.caseSensitive() ? str: str.toLower();
   if(top != Q_NULLPTR)
   {
      if(top->left() != Q_NULLPTR &&
         top->left()->symbol() == srch)
         return top->left();

      if(top->right() != Q_NULLPTR &&
         top->right()->symbol() == srch)
         return top->right();

=======
   if(top != Q_NULLPTR)
   {
      if(top->left() != Q_NULLPTR && top->left()->symbol() == str)
         return top->left();
      if(top->right() != Q_NULLPTR && top->right()->symbol() == str)
         return top->right();
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
      if(top->left() != Q_NULLPTR)
         ret = search(str, top->left());
      if(ret == Q_NULLPTR)
      {
         if(top->right() != Q_NULLPTR)
            ret = search(str, top->right());
      }
   }
   return ret;
}
//------------------------------------------------------------------------------
TSymtabNode* TSymtab::search(const QString& str)
{
<<<<<<< HEAD
   return search(str, root());
=======
   return search(str, _root);
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
}
//------------------------------------------------------------------------------
TSymtabNode* TSymtab::enter(const QString& str)
{
   TSymtabNode* ret = search(str);
   if(ret == Q_NULLPTR)
   {

   }
   return ret;
}
//==============================================================================
