//==============================================================================
#include "symtab.h"
//==============================================================================
TSymtabNode* TSymtab::search(const QString& str, TSymtabNode* top)
{
   TSymtabNode* ret = Q_NULLPTR;
   if(top != Q_NULLPTR)
   {
      if(top->left() != Q_NULLPTR && top->left()->symbol() == str)
         return top->left();
      if(top->right() != Q_NULLPTR && top->right()->symbol() == str)
         return top->right();
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
   return search(str, _root);
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
