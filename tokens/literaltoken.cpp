//==============================================================================
#include "literaltoken.h"
//==============================================================================
//  Reserved language words:
//     preprocessor: include, define, template,
//     data type:    auto, bool, int8, uint8, int16, uint16, int32, uint32,
//                   int64, uint64, int128, uint128, real, double,
//                   string, cstring, list, tree, btree, variant
//                   true, false, null
//     complex data type:
//                   struct, union, array, packed
//     predefined words:
//                   sizeof, typeof, var
//     language alphabetic:
//                   for, while, foreach, fail, success, if, else, copyof, case
//     class words:
//                   class, private, protected, private, virtual,
//                   abstract, override
//     generic words:
//                   is, static, internal, inline
//     external function definition:
//                   extern, cdecl, stdcall, winapi, fastcall, thiscall
//     block of definition:
//                   domains, clauses, rules, functions, goal
//==============================================================================
WordToken TLiteralToken::parseToken[] = {
   //---------------------------------------------------------------------------
   // препроцессор
   //---------------------------------------------------------------------------
   { tcInclude,               "include"      },
   { tcDefine,                "define"       },
//   { tcTemplate,              "template"     },
   //---------------------------------------------------------------------------
   // блоки определения правил, типов, фактов, функций, начало программы
   //---------------------------------------------------------------------------
   { tcDomains,               "domains"      },
   { tcClauses,               "clauses"      },
   { tcRules,                 "rules"        },
   { tcFunctions,             "functions"    },
   { tcGoal,                  "goal"         },
   //---------------------------------------------------------------------------
   // Классы, объекты
   //---------------------------------------------------------------------------
   { tcClass,                 "class"        },
   { tcPublic,                "public"       },
   { tcProtected,             "protected"    },
   { tcPrivate,               "private"      },
   { tcVirtual,               "virtual"      },
   { tcConstructor,           "constructor"  },
   { tcDestructor,            "destructor"   },
   { tcOverride,              "override"     },
   { tcAbstract,              "abstract"     },
   //---------------------------------------------------------------------------
   // типы данных
   //---------------------------------------------------------------------------
   { tcTrue,                  "true"         },
   { tcFalse,                 "false"        },
   { tcNull,                  "null"         },
   { tcBool,                  "bool"         },
   { tcInt8,                  "int8"         },
   { tcUint8,                 "uint8"        },
   { tcInt16,                 "int16"        },
   { tcUint16,                "uint16"       },
   { tcInt32,                 "int"          },
   { tcUint32,                "uint"         },
   { tcInt64,                 "int64"        },
   { tcUint64,                "uint64"       },
   { tcInt128,                "int128"       },
   { tcUint128,               "uint128"      },
//   { tcInt256,                "int256"       },
//   { tcUint256,               "uint256"      },
//   { tcInt512,                "int512"       },
//   { tcUint512,               "uint512"      },
   { tcReal,                  "real"         },
   { tcDouble,                "double"       },
   { tcString,                "string"       },
   { tcCstring,               "cstring"      },
   { tcList,                  "list"         },
   { tcTree,                  "tree"         },
   { tcBtree,                 "btree"        },
   { tcVariant,               "variant"      },
   //---------------------------------------------------------------------------
   // Пользовательские типы даных
   //---------------------------------------------------------------------------
   { tcStruct,                "struct"       },
   { tcUnion,                 "union"        },
   { tcArray,                 "array"        },
   { tcPacked,                "packed"       },
   //---------------------------------------------------------------------------
   // Предопределенные типы
   //---------------------------------------------------------------------------
   { tcSizeof,                "sizeof"       },
   { tcTypeof,                "typeof"       },
   //-----------------------------------------------------------------10----------
   { tcInline,                "inline"       },
   { tcStatic,                "static"       },
   { tcInternal,              "internal"     },
   { tcExtern,                "extern"       },
   { tcCdecl,                 "cdecl"        },
   { tcStdcall,               "stdcall"      },
   { tcWinapi,                "winapi"       },
   { tcFastcall,              "fastcall"     },
   { tcThiscall,              "thiscall"     },
//   { tcPascal,                "pascal"       },
   //---------------------------------------------------------------------------
   // Зарезервированые слова языка
   //---------------------------------------------------------------------------
   { tcWhile,                 "while"        },
   { tcFor,                   "for"          },
   { tcForeach,               "foreach"      },
   { tcFail,                  "fail"         },
   { tcSuccess,               "success"      },
   { tcIf,                    "if"           },
   { tcElse,                  "else"         },
   { tcCopyof,                "copyof"       },
   { tcVar,                   "var"          },
   { tcConst,                 "const"        },
   { tcIs,                    "is"           },
   { tcCase,                  "case"         },
   //---------------------------------------------------------------------------
   // Логические операции (дополнение с && || ^^  !
   //---------------------------------------------------------------------------
   { tcAnd,                   "and"          },
   { tcOr,                    "or"           },
   { tcXor,                   "xor"          },
   { tcNot,                   "not"          },
   //---------------------------------------------------------------------------
   { tcError,                 ""             }
   //---------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
TTokenCode TLiteralToken::find()
{
   WordToken* tmp = parseToken;
   while(tmp->word.length() != 0)
   {
//      if(parse.toLower() == tmp->word)
      if(_parse == tmp->word)
         return tmp->code;
      tmp++;
   }
   return tcIdentifier;
}
//------------------------------------------------------------------------------
QString& TLiteralToken::get(TTextInBuffer& in)
{
   QChar      ch = initParse(in);
   TCharCode  cc = charCode(ch);
   while(cc == ccLetter || cc == ccDigit)
   {
      _parse += ch;
      ch = in.getChar();
      cc = charCode(ch);
   }
   in.putBackChar();
   _code = find();
   return _parse;
}
//------------------------------------------------------------------------------
void TLiteralToken::print(void) const
{
   if(code() == tcIdentifier)
      _out.putLine("\t>> Identifier:\t\t\t" + _parse);
   else
      _out.putLine("\t>> Reserved:  \t\t\t" + _parse);
}
//==============================================================================
