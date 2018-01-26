#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T19:42:06
#
#-------------------------------------------------

QT       += core

QT       -= gui

<<<<<<< HEAD
TARGET = blc
=======
TARGET = prolog
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    errors/errors.cpp \
    log/log.cpp \
    errors/errmsg.cpp \
    streams/buffer.cpp \
    parser/parser.cpp \
    common/common.cpp \
    tokens/token.cpp \
    scanner/scanner.cpp \
    tokens/literaltoken.cpp \
    tokens/numbertoken.cpp \
    tokens/stringtoken.cpp \
    tokens/specialtoken.cpp \
    symtab/symtab.cpp

HEADERS += \
    streams/buffer.h \
    errors/errors.h \
    log/log.h \
    errors/errmsg.h \
    scanner/misc.h \
    scanner/scanner.h \
    parser/parser.h \
    common/common.h \
    tokens/token.h \
    tokens/literaltoken.h \
    tokens/numbertoken.h \
    tokens/stringtoken.h \
    tokens/specialtoken.h \
    symtab/symtab.h \
    common/config.h \
    common/templates.h


