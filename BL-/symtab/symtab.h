//==============================================================================
#ifndef TSYMTAB_H
#define TSYMTAB_H
//==============================================================================
#include <QString>
//==============================================================================
class TSymtabNode {
   private:
      TSymtabNode*            _left;         // left subtree
      TSymtabNode*            _right;        // right subtree
      QString                 _symbol;       // symbol string
      qint16                  _idxSymtab;    // symbol to table index
      qint16                  _idxNode;      // node index
   public:
                              TSymtabNode(const QString& sym);
      virtual                ~TSymtabNode();  
      TSymtabNode*            left()      { return _left;      }
      TSymtabNode*            right()     { return _right;     }
      const QString&          symbol()    { return _symbol;    }
      qint16                  idxSymtab() { return _idxSymtab; }
      qint16                  idxNode()   { return _idxNode;   }
      void                    print();
};
//==============================================================================
class TSymtab 
{
   private:
      TSymtabNode*            _root;         // tree root
      qint16                  _countNode;    // node counter
      qint16                  _idxSymtab;    // symbol table index
   public:
                              TSymtab()
                                 : _root(Q_NULLPTR)
                                 , _countNode(0)
                                 , _idxSymtab(0)
                              {
                              }
      virtual                ~TSymtab()
                              {
                                 if(_root != Q_NULLPTR)
                                    delete _root;
                              }
      TSymtabNode*            search(const QString& str);
      TSymtabNode*            enter (const QString& str);
      TSymtabNode*            root()      { return _root;     }
      qint16                  countNode() { return _countNode; }
      qint16                  idxSymtab() { return _idxSymtab; }
      void                    print()     
                              {
                                 if(_root != Q_NULLPTR)
                                    _root->print();
                              }
   private:
      TSymtabNode*            search(const QString& str, TSymtabNode* top);

};
//==============================================================================
#endif // TSYMTAB_H
//==============================================================================

