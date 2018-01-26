//==============================================================================
#ifndef MISC_H
#define MISC_H
//==============================================================================
#include <QtGlobal>
#include <QString>
//==============================================================================
enum TCharCode {
      ccLetter,
      ccDigit,
      ccSpecial,
      ccQuote,
      ccSpace,
      ccEndOfFile,
//      ccEndOfLine,
      ccOk,
      ccError
};
//==============================================================================
enum TTokenCode {
      tcOk,
      tcDummy,

      tcIdentifier,
      tcNumber,
      tcSpecial,
      tcEndOfLine,
      tcEndOfFile,

      // Special characters TokenCodes defined in Special Token
      // Операторы
      tcPeriod,          // ,
      tcDot,             // .
      tcSingleQuote,     // '

      tcPlus,            // +
      tcMinus,           // -
      tcMul,             // *
      tcDevide,          // /
      tcMod,             // %

      tcPlusEqual,       // +=
      tcDoublePlus,      // ++
      tcMinusEqual,      // -=
      tcDoubleMinus,     // --
      tcMulEqual,        // *=
      tcDevideEqual,     // /=
      tcModEqual,        // %=

      tcLiken,           // =
      tcBitAnd,          // &
      tcAndEqual,        // &=
      tcAnd,             // &&
      tcBitOr,           // |
      tcOrEqual,         // |=
      tcOr,              // ||
      tcBitXor,          // ^
      tcXorEqual,        // ^=
      tcXor,             // ^^
      tcNot,             // !

      tcEqu,             // ==
      tcNeq,             // !=
      tcLs,              // <
      tcGt,              // >
      tcLeq,             // <=
      tcGeq,             // >=

      tcShiftLeft,       // <<
      tcShiftLeftEqual,  // <<=
      tcShiftRight,      // >>
      tcShiftRightEqual, // >>=

      tcStartArray,      // [
      tcEndArray,        // ]
      tcStartBlock,      // {
      tcEndBlock,        // }
      tcStartParam,      // (
      tcEndParam,        // )

      tcQuestion,        // ?
      tcChoice,          // :
      tcDelete,          // ~
      tcDollar,          // $
      tcBackSlash,
      tcBar,             // #

      tcEndOperator,     // ;

      // Комментарии
      tcCommentLine,     // //
      tcCommentStart,    // /*
      tcCommentEnd,      // */


      //------------------------------------------------------------------------
      // Зарезервированные слова
     //------------------------------------------------------------------------
      tcInclude,        // include
      tcDefine,         // define
//      tcTemplate,       // templates
      //------------------------------------------------------------------------
      tcDomains,        // domains
      tcClauses,        // clauses
      tcRules,          // rules
      tcGoal,           // goal
      tcFunctions,      // functions
      //------------------------------------------------------------------------
      // Определение классов
      //------------------------------------------------------------------------
      tcClass,          // class
      tcPrivate,        // private
      tcPublic,         // public
      tcProtected,      // protected
      tcConstructor,    // constructor
      tcDestructor,     // destructor
      tcVirtual,        // virtual
      tcOverride,       // override
      tcAbstract,       // abstract
      //------------------------------------------------------------------------
      // Определение функций
      //------------------------------------------------------------------------
      tcInline,         // inline
      tcStatic,         // static
      tcInternal,       // internal
      tcExtern,         // extern
      tcCdecl,          // cdecl
      tcStdcall,        // stdcall
      tcWinapi,         // winapi
      tcFastcall,       // fastcall
      tcThiscall,       // thiscall
//      tcPascal,         // pascal
      //------------------------------------------------------------------------
      // Типы переменных
      //------------------------------------------------------------------------
      tcTrue,           // true,
      tcFalse,          // false
      tcNull,           // null
      tcBool,           // bool
      tcInt8,           // int8
      tcUint8,          // uint8
      tcInt16,          // int16
      tcUint16,         // uint16
      tcInt32,          // int32
      tcUint32,         // uint32
      tcInt64,          // int64
      tcUint64,         // uint64
      tcInt128,         // int128
      tcUint128,        // uint128
//      tcInt256,         // int256
//      tcUint256,        // uint256
//      tcInt512,         // int512
//      tcUint512,        // uint512
      tcReal,           // real
      tcDouble,         // double,
      tcString,         // string
      tcCstring,        // cstring
      tcList,           // list
      tcTree,           // tree
      tcBtree,          // btree
      tcVariant,        // default type - all type dynamic
      //------------------------------------------------------------------------
      // Пользовательские типы даных
      //------------------------------------------------------------------------
      tcStruct,         // struct
      tcUnion,          // union
      tcArray,          // array
      tcPacked,         // packed
      //------------------------------------------------------------------------
      // Предопределенные типы
      //------------------------------------------------------------------------
      tcSizeof,         // sizeof
      tcTypeof,         // typeof
      //------------------------------------------------------------------------
      // Зарезервированые слова языка
      //------------------------------------------------------------------------
      tcWhile,          // while
      tcFor,            // for
      tcForeach,        // foreach
      tcFail,           // fail
      tcSuccess,        // success
      tcIf,             // if
      tcElse,           // else
      tcCopyof,         // copyof
      tcVar,            // var
      tcConst,          // const
      tcIs,             // is
      tcCase,           // case
      //------------------------------------------------------------------------
      tcError
};
//==============================================================================
enum TTokenType {
      //------------------------------------------------------------------------
      // data
      //------------------------------------------------------------------------
      ttDummy,
      ttInt8,
      ttInt16,
      ttInt32,
      ttInt64,
//      ttInt128, // not supported yet
//      ttInt256, // not supported yet
//      ttInt512, // not supported yet
      ttuInt8,
      ttuInt16,
      ttuInt32,
      ttuInt64,
//      ttuInt128, // not supported yet
//      ttuInt256, // not supported yet
//      ttuInt512, // not supported yet
      ttReal32,
      ttReal64,
      ttString,
      //------------------------------------------------------------------------
      // pointers
      //------------------------------------------------------------------------
      pttInt8,
      pttInt16,
      pttInt32,
      pttInt64,
//      pttInt128, // not supported yet
//      pttInt256, // not supported yet
//      pttInt512, // not supported yet
      pttuInt8,
      pttuInt16,
      pttuInt32,
      pttuInt64,
//      pttuInt128, // not supported yet
//      pttuInt256, // not supported yet
//      pttuInt512, // not supported yet
      pttReal32,
      pttReal64,
      pttString,
      pttVoid
};
//==============================================================================
union TTokenValue {
      //------------------------------------------------------------------------
      // data
      //------------------------------------------------------------------------
      qint8       Int8;
      qint16      Int16;
      qint32      Int32;
      qint64      Int64;
//      qint128     Int128; // not supported yet
//      qint256     Int256; // not supported yet
//      qint512     Int512; // not supported yet
      quint8      uInt8;
      quint16     uInt16;
      quint32     uInt32;
      quint64     uInt64;
//      quint128    uint128; // not supported yet
//      quint256    uint256; // not supported yet
//      quint512    uint512; // not supported yet
      float       Real32;
      double      Real64;
      QString*    String;    // pointer to the real data String
                             // do not forget to delete
      //------------------------------------------------------------------------
      // pointers
      //------------------------------------------------------------------------
      qint8*      pInt8;
      qint16*     pInt16;
      qint32*     pInt32;
      qint64*     pInt64;
//      qint128*    pInt128; // not supported yet
//      qint256*    pInt256; // not supported yet
//      qint512*    pInt512; // not supported yet
      quint8*     puInt8;
      quint16*    puInt16;
      quint32*    puInt32;
      quint64*    puInt64;
//      quint128*   puint128; // not supported yet
//      quint256*   puInt256; // not supported yet
//      quint512*   puInt512; // not supported yet
      float*      pReal32;
      double*     pReal64;
      QString*    pString;
      void*       pVoid;
};
//==============================================================================
#endif // MISC_H
//==============================================================================

