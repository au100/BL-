//==============================================================================
#include "streams/buffer.h"
#include "errors/errors.h"
#include "errors/errmsg.h"
<<<<<<< HEAD
#include "common/config.h"
#include "common/common.h"
=======
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
//==============================================================================
bool IStream::open(const QString&  fileName,
                   QIODevice::OpenMode openMode)
{
   QFile* file = new QFile(fileName);
   if(openMode == QIODevice::ReadOnly)
   {
      if(file->exists() == false)
      {
         setError(FILE_NOT_EXIST, &fileName);
         return false;
      }
   }
   if(file->open(openMode | QIODevice::Text) == false)
   {
      setError(FILE_OPEN_FAILED, &fileName);
      return false;
   }

   init(fileName, IOFile);
   _stream = new QTextStream();
   _stream->setDevice(file);
   return true;
}
//------------------------------------------------------------------------------
IStream::IStream(const QString&  fileName,
                 QIODevice::OpenMode openMode)
         : _stream(Q_NULLPTR)
{
   open(fileName, openMode);
}
//------------------------------------------------------------------------------
IStream::IStream(FILE * fileHandle,
                 const QString& fileName,
                 QIODevice::OpenMode openMode)
{
<<<<<<< HEAD
    Q_UNUSED(openMode);
   _stream = new QTextStream(fileHandle);
   init(fileName, IOFile);
=======
   _stream = new QTextStream(fileHandle);
   init(fileName, IODevice);
>>>>>>> dbdcb0220f45a6115fa7329f944f5e8540a18a52
}
//------------------------------------------------------------------------------
IStream::~IStream()
{
   if(_stream != Q_NULLPTR)
      delete _stream;
}
//-----------------------------------------------------------------------------
bool TextStream::atEnd()
{
   if(status())
      return stream().atEnd();
   else
      return true;
}
//-----------------------------------------------------------------------------
QString& TextStream::getLine()
{
   static QString emptyLine = "";
   if(status())
   {
      if(stream().atEnd() == false)
         line() = stream().readLine();
      else
         line() = emptyLine;
      lineNo()++;
      pos() = 0;
      return line();
   }
   else
      return emptyLine;
}
//------------------------------------------------------------------------------
QChar TextStream::getChar()
{
   if(status())
   {
      if(line().length() > pos())
         return line().data()[pos()++];
      else
      {
         if(stream().atEnd() == true)
            return QChar(0);
         if(lineNo() == 0)
         {
            getLine();
            return getChar();
         }
         else
         {
            getLine();
            return QChar('\n');
         }
      }
   }
   else
      return QChar(0);
}
//------------------------------------------------------------------------------
void TextStream::putLine(const QString& text)
{
   if(status())
   {
      stream() << text << endl;
      flush();
   }
}
//------------------------------------------------------------------------------
QChar TextStream::putBackChar()
{
   if(pos() != 0)
      pos()--;
   return line().data()[pos()];
}
//------------------------------------------------------------------------------
void TextStream::setCodec(QTextCodec* codec)
{
   if(status())
      stream().setCodec(codec);
}
//------------------------------------------------------------------------------
void TextStream::setCodec(const QString& codecName)
{
   if(status())
      stream().setCodec(codecName.toStdString().c_str());
}
//------------------------------------------------------------------------------
QTextCodec* TextStream::codec()
{
   if(status())
      return stream().codec();
   else
      return Q_NULLPTR;
}
//------------------------------------------------------------------------------
void TextStream::flush()
{
   stream().flush();
}
//------------------------------------------------------------------------------
bool TextStream::status()
{
   if(&stream() != Q_NULLPTR && stream().status() == QTextStream::Ok)
      return true;
   else
      return false;
}
//==============================================================================
// Destination buffer subclass of TTextBuffer
//==============================================================================
void TTextOutBuffer::printPageHeader()
{
   *this
      <<
"==============================================================================="
         "\n\tPage #"
      << ++_pageNo
      << "\t" << name()
      << "\t("
      << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss")
      << ")\n"
"==============================================================================="
         "\n";
   flush();
   _lineCount = 0;
}
//------------------------------------------------------------------------------
void TTextOutBuffer::putLine(const QString& text)
{
   if(_lineCount >= maxLinesPerPage())
      printPageHeader();
   TextStream::putLine(text);
   _lineCount++;
}
//==============================================================================
