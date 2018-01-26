//==============================================================================
#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H
//==============================================================================
<<<<<<< HEAD
#include "common/config.h"
=======
//#include "errors/errors.h"
#include "common/config.h"
#include "common/common.h"
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QTextCodec>
//==============================================================================
<<<<<<< HEAD
enum  StreamType {
   IOAbstractSocket  = 0x0001,   // QAbstractSocket
   IOBluetooth       = 0x0002,   // QBluetoothSocket
   IOMemory          = 0x0003,   // QBUffer
   IOFile            = 0x0004,   // QFileDevice
   IOLocalSocket     = 0x0005,   // QLocalSocket
   IONetworkRepaly   = 0x0006,   // QNetworkReply
   IOProcess         = 0x0007,   // QProcess
   IOSerialPort      = 0x0008    // QSerialPort
};
//==============================================================================
// This to remake stream to read from all device(sockets. etc). TODO
// Now we use only TTextStream
//==============================================================================
//class IAbstractStream
//{
   //---------------------------------------------------------------------------
//   public:
   //---------------------------------------------------------------------------
//                        IAbstractStream(QIODevice* io,
//                                        StreamType tp = IOFile)
//                           : _io(io),
//                             _type(tp)
//                        {
//                        }
//      virtual          ~IAbstractStream()
//                        {
//                           if(_io != Q_NULLPTR)
//                              delete _io;
//                        }
//      StreamType        type()
//                        {
//                           return _type;
//                        }
//      QIODevice&        device()
//                        {
//                           return *_io;
//                        }
   //---------------------------------------------------------------------------
//   private:
//      QIODevice*       _io;
//      StreamType       _type;
//};
//==============================================================================
//class FileStream
//{
//
//};
//==============================================================================
//class MemoryStream
//{
//
//};
=======
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
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
//==============================================================================
class IStream {
   //---------------------------------------------------------------------------
   private:
   //---------------------------------------------------------------------------
      bool              open(const QString& fileName,
                             QIODevice::OpenMode openMode);
<<<<<<< HEAD
      //------------------------------------------------------------------------
=======
      //------------------------------------------------------------------------------
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
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
<<<<<<< HEAD
                                QIODevice::OpenMode md = QIODevice::ReadOnly);
                        IStream(FILE * fileHandle,
                                const QString& fileName,
                                QIODevice::OpenMode md = QIODevice::ReadOnly);
=======
                                QIODevice::OpenMode openMode = QIODevice::ReadOnly);
                        IStream(FILE * fileHandle,
                                const QString& fileName,
                                QIODevice::OpenMode openMode = QIODevice::ReadOnly);
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
      virtual          ~IStream();
      //------------------------------------------------------------------------
      bool              status();
      //------------------------------------------------------------------------
<<<<<<< HEAD
      QString&          line()   { return _line;       }
=======
      QString&          line()   {  return _line;      }
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
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
<<<<<<< HEAD
                                   QIODevice::OpenMode md = QIODevice::ReadOnly)
                           : IStream(fileName, md)
=======
                                   QIODevice::OpenMode openMode = QIODevice::ReadOnly)
                           : IStream(fileName, openMode)
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
                        {
                        }
                        TextStream(FILE * fileHandle,
                                   const QString& fileName,
<<<<<<< HEAD
                                   QIODevice::OpenMode md = QIODevice::ReadOnly)
                           : IStream(fileHandle, fileName, md)
=======
                                   QIODevice::OpenMode openMode = QIODevice::ReadOnly)
                           : IStream(fileHandle, fileName, openMode)
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
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
<<<<<<< HEAD
                        TTextInBuffer(
                              const QString& fileName,
                              QIODevice::OpenMode md = QIODevice::ReadOnly)
                           : TextStream(fileName, md)
                        {
                        }
      //------------------------------------------------------------------------
                        TTextInBuffer(
                              FILE * fileHandle,
                              const QString& name = "Unknown file name",
                              QIODevice::OpenMode md = QIODevice::ReadOnly)
                          : TextStream(fileHandle, name, md)
=======
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
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
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
<<<<<<< HEAD
                                       const QString& nm = "Unknown file name")
                           : TextStream(fileHandle, nm, QIODevice::WriteOnly)
=======
                                       const QString& fileName = "Unknown file name")
                           : TextStream(fileHandle, fileName, QIODevice::WriteOnly)
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
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
