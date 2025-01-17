#include "RGraphicsViewWorkerPainter.h"

#include <QTextLayout>

RGraphicsViewWorkerPainter::~RGraphicsViewWorkerPainter() {
}

void RGraphicsViewWorkerPainter::clear() {

}

void RGraphicsViewWorkerPainter::end() {
    if (painter==NULL) {
        return;
    }
    painter->end();
}

void RGraphicsViewWorkerPainter::begin() {
    if (painter==NULL) {
        qWarning() << "painter is NULL";
        return;
    }

    if (image.isNull()) {
        qWarning() << "image.isNull:" << image.isNull();
        return;
    }

    // Note: QPainter::begin resets all flags, pen, brush, etc:
    if (!painter->begin(&image)) {
        qWarning() << "cannot start painting";
        return;
    }

//    if (imageView.getAntialiasing()) {
//        painter->setRenderHint(QPainter::Antialiasing);
//    }

    QColor bg = imageView.getBackgroundColor();

    if (clearMode==ClearToTransparent || bg.alpha()==0) {
        painter->setCompositionMode(QPainter::CompositionMode_Clear);
        painter->eraseRect(0, 0, image.width(), image.height());
        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    }
    else if (clearMode==ClearToBackground) {
        painter->setBackground(QBrush(imageView.getBackgroundColor()));
        //painter->setBackground(QBrush(QColor(64,64,128,255)));
        painter->eraseRect(0, 0, image.width(), image.height());
    }

    painter->setWorldTransform(imageView.getTransform());
}

void RGraphicsViewWorkerPainter::setAntialiasing(bool on) {
    if (painter==NULL) {
        return;
    }
    //qDebug() << "RGraphicsViewWorkerPainter::setAntialiasing" << on;
    painter->setRenderHint(QPainter::Antialiasing, true);
}

bool RGraphicsViewWorkerPainter::getAntialiasing() const {
    if (painter==NULL) {
        return false;
    }
    return painter->testRenderHint(QPainter::Antialiasing);
}

void RGraphicsViewWorkerPainter::setBackground(const QColor& col) {
    if (painter==NULL) {
        return;
    }
    painter->setBackground(col);
}

void RGraphicsViewWorkerPainter::setCompositionMode(QPainter::CompositionMode mode) {
    if (painter==NULL) {
        return;
    }
    painter->setCompositionMode(mode);
}

void RGraphicsViewWorkerPainter::setFont(const QFont& font) {
    if (painter==NULL) {
        return;
    }
    painter->setFont(font);
}

void RGraphicsViewWorkerPainter::eraseRect(const QRectF& rect) {
    if (painter==NULL) {
        return;
    }
    painter->eraseRect(rect);
}

QImage RGraphicsViewWorkerPainter::getImage() const {
    return image;
}

void RGraphicsViewWorkerPainter::setImage(const QImage& img) {
    image = img;
    setPainter(new QPainter());
}

void RGraphicsViewWorkerPainter::setPainter(QPainter* p) {
    if (painter!=NULL) {
        //painter->end();
        delete painter;
    }
    painter = p;
}

QSize RGraphicsViewWorkerPainter::getImageSize() const {
    return image.size();
}

void RGraphicsViewWorkerPainter::initImageBuffer(const QSize& size) {
    //qDebug() << "RGraphicsViewWorkerPainter::initImageBuffer: " << size;
    QImage img = QImage(size, QImage::Format_ARGB32_Premultiplied);
    setImage(img);
}

void RGraphicsViewWorkerPainter::paint() {

//    painter->resetTransform();

//    if (erase) {
//        QRect r = rect;
//        if (rect.isNull()) {
//            r = QRect(0,0,lastSize.width(),lastSize.height());
//        }
//        // erase background to transparent:
//        painter->setCompositionMode(QPainter::CompositionMode_Clear);
//        painter->eraseRect(r);
//        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
//    }

    //if (threadId==0) {
        // first buffer: erase to background color:
//        QRect r = rect;
//        if (rect.isNull()) {
//            r = QRect(0,0,lastSize.width(),lastSize.height());
//        }
        // erase background to transparent:
        //qDebug() << "bg:" << imageView.getBackgroundColor();
        //painter->setBackground(QBrush(imageView.getBackgroundColor()));

        // bottom buffer contains background color:
//        if (threadId==0) {
//            painter->setBackground(QBrush(imageView.getBackgroundColor()));
//            //painter->setBackground(QBrush(QColor(64,64,128,255)));
//            painter->eraseRect(0, 0, image.width(), image.height());
//        }
//        else {
//            painter->setCompositionMode(QPainter::CompositionMode_Clear);
//            painter->eraseRect(0, 0, image.width(), image.height());
//            painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
//        }
    //}

    //if (!screen) {
//    painter->setWorldTransform(imageView.getTransform());
    //}

    RGraphicsViewWorker::paint();

    //delete painter;
    //painter = NULL;


    //qDebug() << "RGraphicsViewWorker::paint: emit finished";
    //emit finished();
    //qDebug() << "RGraphicsViewWorker::paint: DONE";
}


void RGraphicsViewWorkerPainter::setClipRect(const QRectF& rect) {
    if (painter==NULL) {
        return;
    }
    painter->setClipRect(rect);
}

void RGraphicsViewWorkerPainter::setClipping(bool on) {
    if (painter==NULL) {
        return;
    }
    //qDebug() << "painter:" << (unsigned long long int)painter;
    painter->setClipping(on);
}

void RGraphicsViewWorkerPainter::setOpacity(double opacity) {
    if (painter==NULL) {
        return;
    }
    painter->setOpacity(opacity);
}

void RGraphicsViewWorkerPainter::save() {
    if (painter==NULL) {
        return;
    }
    painter->save();
}

void RGraphicsViewWorkerPainter::restore() {
    if (painter==NULL) {
        return;
    }
    painter->restore();
}

QTransform RGraphicsViewWorkerPainter::getTransform() {
    if (painter==NULL) {
        return QTransform();
    }
    return painter->transform();
}

void RGraphicsViewWorkerPainter::setTransform(const QTransform& t, bool combine) {
    if (painter==NULL) {
        return;
    }
    painter->setTransform(t, combine);
}

void RGraphicsViewWorkerPainter::translate(double x, double y) {
    if (painter==NULL) {
        return;
    }
    painter->translate(x, y);
}

void RGraphicsViewWorkerPainter::scale(double x, double y) {
    if (painter==NULL) {
        return;
    }
    painter->scale(x, y);
}

QTransform RGraphicsViewWorkerPainter::getWorldTransform() const {
    if (painter==NULL) {
        return QTransform();
    }
    return painter->worldTransform();
}

void RGraphicsViewWorkerPainter::setWorldTransform(const QTransform& t, bool combine) {
    if (painter==NULL) {
        return;
    }
    painter->setWorldTransform(t, combine);
}

void RGraphicsViewWorkerPainter::setBrush(const QBrush& brush) {
    if (painter==NULL) {
        return;
    }
    painter->setBrush(brush);
}

QPen RGraphicsViewWorkerPainter::getPen() const {
    if (painter==NULL) {
        return QPen();
    }
    return painter->pen();
}

void RGraphicsViewWorkerPainter::setPen(const QPen& pen) {
    if (painter==NULL) {
        return;
    }
    painter->setPen(pen);
}

void RGraphicsViewWorkerPainter::drawPoint(const QPointF& p) {
    if (painter==NULL) {
        return;
    }
    painter->drawPoint(p);
}

void RGraphicsViewWorkerPainter::drawImage(int x, int y, const QImage& image) {
    if (painter==NULL) {
        return;
    }
    painter->drawImage(x, y, image);
}

void RGraphicsViewWorkerPainter::drawTextLayout(const QTextLayout& textLayout) {
    if (painter==NULL) {
        return;
    }
    //painter->drawImage(x, y, image);
    textLayout.draw(painter, QPoint(0,0));
}

void RGraphicsViewWorkerPainter::drawText(const QRectF& rectangle, int flags, const QString& text) {
    if (painter==NULL) {
        return;
    }
    painter->drawText(rectangle, flags, text);
}

void RGraphicsViewWorkerPainter::fillPath(const RPainterPath& path, const QBrush& brush) {
    if (painter==NULL) {
        return;
    }
    painter->fillPath(path, brush);
}

void RGraphicsViewWorkerPainter::drawPath(const RPainterPath& path) {
    if (painter==NULL) {
        return;
    }
    painter->drawPath(path);
}

void RGraphicsViewWorkerPainter::drawLine(const QLineF& line) {
    if (painter==NULL) {
        return;
    }
    painter->drawLine(line);
}

void RGraphicsViewWorkerPainter::strokePath(const QPainterPath& path, const QPen& pen) {
    if (painter==NULL) {
        return;
    }
    painter->strokePath(path, pen);
}

void RGraphicsViewWorkerPainter::drawEllipse(const QRectF& rectangle) {
    if (painter==NULL) {
        return;
    }
    painter->drawEllipse(rectangle);
}

void RGraphicsViewWorkerPainter::drawRect(const QRectF& rectangle) {
    if (painter==NULL) {
        return;
    }
    painter->drawRect(rectangle);
}

void RGraphicsViewWorkerPainter::fillRect(const QRectF& rectangle, const QBrush& brush) {
    if (painter==NULL) {
        return;
    }
    painter->fillRect(rectangle, brush);
}
