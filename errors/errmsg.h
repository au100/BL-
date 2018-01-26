//==============================================================================
#ifndef ERRMSG_H
#define ERRMSG_H
//==============================================================================
#include <QtGlobal>
#include <QSettings>
//------------------------------------------------------------------------------
// Flags definition (ERROR, WARNING, INFO, DEBUG
//------------------------------------------------------------------------------
#define  FATAL_FLAG           0x80000000
#define  ERROR_FLAG           0x40000000
#define  WARNING_FLAG         0x20000000
#define  DEBUG_FLAG           0x10000000
#define  INFO_FLAG            0x08000000
#define  SUCCESS_FLAG         0x00000000
//------------------------------------------------------------------------------
// Levels flags for debug and info
//------------------------------------------------------------------------------
#define  DEBUG_NOLVL          0x00000000
#define  DEBUG_LVL1           0x01000000
#define  DEBUG_LVL2           0x02000000
#define  DEBUG_LVL3           0x03000000
#define  DEBUG_LVL4           0x04000000
#define  DEBUG_LVL5           0x05000000
#define  DEBUG_LVL6           0x06000000
#define  DEBUG_LVL7           0x07000000
//------------------------------------------------------------------------------
// Flags that define the objects of error, warning, info, debug
// 32 objects from 0x00010000 to 0x00800000
//------------------------------------------------------------------------------
#define  APP_ERROR            0x00010000
#define  COMPILE_ERROR        0x00020000
#define  FILE_ERROR           0x00040000
#define  MEMORY_ERROR         0x00080000
//------------------------------------------------------------------------------
// Errors, warning, debug, info codes
// 65535 codes for each object from 0x00000001 to 0x0000FFFF
//------------------------------------------------------------------------------
#define NO_CODE               0x00000000
#define MAX_CODE              0x0000FFFF
//------------------------------------------------------------------------------
// Macros to define succes, warning, erros, info
//------------------------------------------------------------------------------
#define SUCCESS(Code)              ((Code & (FATAL_ERROR | ERROR_FLAG) ) == 0)
#define FATAL(Code)                ((Code & FATAL_FLAG  ) == FATAL_FLAG  )
#define ERROR(Code)                ((Code & ERROR_FLAG  ) == ERROR_FLAG  )
#define WARNING(Code)              ((Code & WARNING_FLAG) == WARNING_FLAG)
#define DEBUG(Code)                ((Code & DEBUG_FLAG  ) == DEBUG_FLAG  )
#define INFO(Code)                 ((Code & INFO_FLAG   ) == INFO_FLAG   )
#define DEBUG_LEVEL(Code, level)  (((Code & DEBUG_FLAG  ) == DEBUG_FLAG  ) && \
                                  (((Code >> 24) & 0x07 ) <= level))
//------------------------------------------------------------------------------
#define MAKE_CODE(FLG, LVL, OBJ, CODE)   (FLG          | LVL | OBJ | CODE)
#define MAKE_FATAL(OBJ, CODE)            (FATAL_FLAG         | OBJ | CODE)
#define MAKE_ERROR(OBJ, CODE)            (ERROR_FLAG         | OBJ | CODE)
#define MAKE_WARNING(OBJ, CODE)          (WARNING_FLAG       | OBJ | CODE)
#define MAKE_DEBUG(LVL, OBJ, CODE)       (DEBUG_FLAG   | LVL | OBJ | CODE)
#define MAKE_INFO(OBJ, CODE)             (INFO_FLAG          | OBJ | CODE)
//------------------------------------------------------------------------------
typedef struct tagMessageCode {
      quint32        code;
      const char*    msg;
} MessageCode;
//------------------------------------------------------------------------------
#define M_MSG_CODE(code)            { code, #code }
//------------------------------------------------------------------------------
// Application errors
//------------------------------------------------------------------------------
#define INVALID_COMMAND             MAKE_FATAL(APP_ERROR, 0x1)
//------------------------------------------------------------------------------
// Translation errors
//------------------------------------------------------------------------------
#define TOO_MANY_ERROR              MAKE_FATAL(COMPILE_ERROR, 0x0001)
#define STACK_OVERFLOW              MAKE_FATAL(COMPILE_ERROR, 0x0002)
#define CODE_SEGMENT_OVERFLOW       MAKE_FATAL(COMPILE_ERROR, 0x0003)
#define NESTING_TOO_DEEP            MAKE_FATAL(COMPILE_ERROR, 0x0004)
#define RUNTIME_ERROR               MAKE_FATAL(COMPILE_ERROR, 0x0005)
#define UNIMPLEMENTED_FEATURE       MAKE_FATAL(COMPILE_ERROR, 0x0006)
#define SOURCE_FILE_OPEN_FAILED     MAKE_FATAL(COMPILE_ERROR, 0x0007)
#define FORM_FILE_OPEN_FAILED       MAKE_FATAL(COMPILE_ERROR, 0x0008)
#define ASSEMBLY_FILE_OPEN_FAILED   MAKE_FATAL(COMPILE_ERROR, 0x0009)

#define UNRECOGNAZIBLE_ERROR        MAKE_ERROR(COMPILE_ERROR, 0x0001)
#define UNEXPECTED_ENDOFFIE         MAKE_ERROR(COMPILE_ERROR, 0x0002)
#define INVALID_NUMBER              MAKE_ERROR(COMPILE_ERROR, 0x0003)
#define INVALID_FRACTION            MAKE_ERROR(COMPILE_ERROR, 0x0004)
#define INVALID_EXPONENT            MAKE_ERROR(COMPILE_ERROR, 0x0005)
#define TOO_MANY_DIGITS             MAKE_ERROR(COMPILE_ERROR, 0x0006)
#define INTEGER_OUT_OF_RANGE        MAKE_ERROR(COMPILE_ERROR, 0x0007)
#define REAL_OUT_OF_RANGE           MAKE_ERROR(COMPILE_ERROR, 0x0008)
//------------------------------------------------------------------------------
// Memory errors
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Stream errors
//------------------------------------------------------------------------------
#define FILE_OPEN_FAILED            MAKE_ERROR(FILE_ERROR, 0x0001)
#define FILE_NOT_EXIST              MAKE_ERROR(FILE_ERROR, 0x0002)
//------------------------------------------------------------------------------
QString     getErrorMessage(quint32 code);
QSettings*  errorLanguage(QString lang);
//==============================================================================
#endif // ERRMSG_H
//==============================================================================

