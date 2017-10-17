//==============================================================================
#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H
//==============================================================================
//#include "errors/errors.h"
#include "common/config.h"
#include "common/common.h"
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QTextCodec>
//==============================================================================
// This to remake stream to read from all device(sockets. etc). TODO
// Now we use only TTextStream
//==============================================================================
class IAbstractStream
{
   //---------------------------------------------------------------------------
   public:
   //---------------------------------------------------------------------------
                        IAbstractStream(QIODevice* io)
                           : _io(io)
                        {
                        }
      virtual          ~IAbstractStream()
                        {
                           if(_io != Q_NULLPTR)
                              delete _io;
                        }

   //---------------------------------------------------------------------------
   private:
   //---------------------------------------------------------------------------
      QIODevice*       _io;
};
//==============================================================================
class FileStream
{

};
//==============================================================================
class MemoryStream
{

};
//==============================================================================
enum  StreamType {
   IODevice = 0x0000,
   IOFile   = 0x0001,
   IOMemory = 0x0002
};
//==============================================================================
class IStream {
   //---------------------------------------------------------------------------
   private:
   //---------------------------------------------------------------------------
      bool              open(const QString& fileName,
                             QIODevice::OpenMode openMode);
      //------------------------------------------------------------------------------
      void              init(const QString& name,
                             StreamType t)
                        {
                           _objectName = name;
                           _type = t;
                           _lineNo = 0;
                           _pos = 0;
                        }
   //---------------------------------------------------------------------------
   public:
   //---------------------------------------------------------------------------
                        IStream(const QString&  fileName,
                                QIODevice::OpenMode openMode = QIODevice::ReadOnly);
                        IStream(FILE * fileHandle,
                                const QString& fileName,
                                QIODevice::OpenMode openMode = QIODevice::ReadOnly);
      virtual          ~IStream();
      //------------------------------------------------------------------------
      bool              status();
      //------------------------------------------------------------------------
      QString&          line()   {  return _line;      }
      int&              lineNo() { return _lineNo;     }
      int&              pos()    { return _pos;        }
      const QString&    name()   { return _objectName; }
      StreamType        type()   { return _type;       }
      QTextStream&      stream() { return *_stream;    }
      //------------------------------------------------------------------------
      virtual void      putLine(const QString& text) = 0;
   //---------------------------------------------------------------------------
   private:
      QTextStream*      _stream;
      QString           _objectName;
      StreamType        _type;
      QString           _line;
      int               _lineNo;
      int               _pos;
};
//==============================================================================
class TextStream : public IStream
{
   //---------------------------------------------------------------------------
   public:
   //---------------------------------------------------------------------------
                        TextStream(const QString&  fileName,
                                   QIODevice::OpenMode openMode = QIODevice::ReadOnly)
                           : IStream(fileName, openMode)
                        {
                        }
                        TextStream(FILE * fileHandle,
                                   const QString& fileName,
                                   QIODevice::OpenMode openMode = QIODevice::ReadOnly)
                           : IStream(fileHandle, fileName, openMode)
                        {
                        }
      //------------------------------------------------------------------------
      virtual QString&  getLine();
      virtual QChar     getChar();
      virtual void      putLine(const QString& text);
      QChar             putBackChar();
      void              flush();
      bool              atEnd();
      //------------------------------------------------------------------------
      void              setCodec(QTextCodec* codec);
      void              setCodec(const QString& codecName);
      QTextCodec*       codec();
      bool              status();
   //---------------------------------------------------------------------------
   // public operators
   //---------------------------------------------------------------------------
      template <class T>
                        TextStream& operator << (T value)
                        {
                           if(status())
                              stream() << value;
                           return *this;
                        }
};
//==============================================================================
// Source buffer subclass of TTextBuffer
//==============================================================================
class TTextInBuffer : public TextStream
{
   public:
      //------------------------------------------------------------------------
                        TTextInBuffer(const QString& fileName,
                                      QIODevice::OpenMode openMode = QIODevice::ReadOnly)
                           : TextStream(fileName, openMode)
                        {
                        }
      //------------------------------------------------------------------------
                        TTextInBuffer(FILE * fileHandle,
                                      const QString& fileName = "Unknown file name",
                                      QIODevice::OpenMode openMode = QIODevice::ReadOnly)
                          : TextStream(fileHandle, fileName, openMode)
                        {
                        }
      //------------------------------------------------------------------------
   private:
      //------------------------------------------------------------------------
};
//==============================================================================
// Destination buffer subclass of TTextBuffer
//==============================================================================
//#define maxLinesPerPage 60 // todo: make the option/config
//==============================================================================
class TTextOutBuffer : public TextStream
{
   public:
                        TTextOutBuffer(const QString& fileName)
                           : TextStream(fileName, QIODevice::WriteOnly)
                           , _pageNo(0)
                           , _lineCount(0)
                           , _maxLinesPerPage(getMaxLinesPerPage())
                        {
                        }
                        TTextOutBuffer(FILE * fileHandle,
                                       const QString& fileName = "Unknown file name")
                           : TextStream(fileHandle, fileName, QIODevice::WriteOnly)
                           , _pageNo(0)
                           , _lineCount(0)
                           , _maxLinesPerPage(getMaxLinesPerPage())
                        {
                        }
      int               maxLinesPerPage()
                        {
                           return _maxLinesPerPage;
                        }
      //------------------------------------------------------------------------
      void              printPageHeader();
      virtual void      putLine(const QString& text);
      //------------------------------------------------------------------------
   private:
      int               getMaxLinesPerPage()
                        {
                           return CONFIG.value("maxLinesPerPage").toInt();
                        }
      //------------------------------------------------------------------------
   private:
      int               _pageNo;
      int               _lineCount;
      int               _maxLinesPerPage;
};
//==============================================================================
#endif // TEXTBUFFER_H
//==============================================================================
