#ifndef QTSCRIPTSHELL_QIMAGEIOHANDLER_H
#define QTSCRIPTSHELL_QIMAGEIOHANDLER_H

#include <qimageiohandler.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QImageIOHandler : public QImageIOHandler
{
public:
    QtScriptShell_QImageIOHandler();
    ~QtScriptShell_QImageIOHandler();

    bool  canRead() const;
    int  currentImageNumber() const;
    QRect  currentImageRect() const;
    int  imageCount() const;
    bool  jumpToImage(int  imageNumber);
    bool  jumpToNextImage();
    int  loopCount() const;
    int  nextImageDelay() const;
    QVariant  option(QImageIOHandler::ImageOption  option) const;
    bool  read(QImage*  image);
    void setOption(QImageIOHandler::ImageOption  option, const QVariant&  value);
    bool  supportsOption(QImageIOHandler::ImageOption  option) const;
    bool  write(const QImage&  image);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QIMAGEIOHANDLER_H
