#include "RGraphicsViewWorkerPainter.h"

RGraphicsViewWorkerPainter::~RGraphicsViewWorkerPainter() {
}

void RGraphicsViewWorkerPainter::clear() {

}

void RGraphicsViewWorkerPainter::end() {
    painter->end();
}

void RGraphicsViewWorkerPainter::begin() {
    if (!image.isNull()) {
        if (!painter->begin(&image)) {
            qWarning() << "image.isNull:" << image.isNull();
            qWarning() << "cannot start painting";
            return;
        }
    }

    if (clearMode==ClearToBackground) {
        painter->setBackground(QBrush(imageView.getBackgroundColor()));
        //painter->setBackground(QBrush(QColor(64,64,128,255)));
        painter->eraseRect(0, 0, image.width(), image.height());
    }
    else if (clearMode==ClearToTransparent) {
        painter->setCompositionMode(QPainter::CompositionMode_Clear);
        painter->eraseRect(0, 0, image.width(), image.height());
        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    }

    painter->setWorldTransform(imageView.getTransform());
}

void RGraphicsViewWorkerPainter::setAntialiasing(bool on) {
    painter->setRenderHint(QPainter::Antialiasing, on);
}

void RGraphicsViewWorkerPainter::setBackground(const QColor& col) {
    painter->setBackground(col);
}

void RGraphicsViewWorkerPainter::setCompositionMode(QPainter::CompositionMode mode) {
    painter->setCompositionMode(mode);
}

void RGraphicsViewWorkerPainter::setFont(const QFont& font) {
    painter->setFont(font);
}

void RGraphicsViewWorkerPainter::eraseRect(const QRectF& rect) {
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
    if (imageView.getAntialiasing()) {
        painter->setRenderHint(QPainter::Antialiasing);
    }
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
    painter->setClipRect(rect);
}

void RGraphicsViewWorkerPainter::setClipping(bool on) {
    //qDebug() << "painter:" << (unsigned long long int)painter;
    painter->setClipping(on);
}

void RGraphicsViewWorkerPainter::setOpacity(double opacity) {
    painter->setOpacity(opacity);
}

void RGraphicsViewWorkerPainter::save() {
    painter->save();
}

void RGraphicsViewWorkerPainter::restore() {
    painter->restore();
}

QTransform RGraphicsViewWorkerPainter::getTransform() {
    return painter->transform();
}

void RGraphicsViewWorkerPainter::setTransform(const QTransform& t, bool combine) {
    painter->setTransform(t, combine);
}

void RGraphicsViewWorkerPainter::translate(double x, double y) {
    painter->translate(x, y);
}

void RGraphicsViewWorkerPainter::scale(double x, double y) {
    painter->scale(x, y);
}

QTransform RGraphicsViewWorkerPainter::getWorldTransform() const {
    return painter->worldTransform();
}

void RGraphicsViewWorkerPainter::setWorldTransform(const QTransform& t, bool combine) {
    painter->setWorldTransform(t, combine);
}

void RGraphicsViewWorkerPainter::setBrush(const QBrush& brush) {
    painter->setBrush(brush);
}

QPen RGraphicsViewWorkerPainter::getPen() const {
    return painter->pen();
}

void RGraphicsViewWorkerPainter::setPen(const QPen& pen) {
    painter->setPen(pen);
}

void RGraphicsViewWorkerPainter::drawPoint(const QPointF& p) {
    painter->drawPoint(p);
}

void RGraphicsViewWorkerPainter::drawImage(int x, int y, const QImage& image) {
    painter->drawImage(x, y, image);
}

void RGraphicsViewWorkerPainter::drawTextLayout(const QTextLayout& textLayout) {
    //painter->drawImage(x, y, image);
    textLayout.draw(painter, QPoint(0,0));
}

void RGraphicsViewWorkerPainter::drawText(const QRectF& rectangle, int flags, const QString& text) {
    painter->drawText(rectangle, flags, text);
}

void RGraphicsViewWorkerPainter::fillPath(const RPainterPath& path, const QBrush& brush) {
    painter->fillPath(path, brush);
}

void RGraphicsViewWorkerPainter::drawPath(const RPainterPath& path) {
    painter->drawPath(path);
}

void RGraphicsViewWorkerPainter::drawLine(const QLineF& line) {
    painter->drawLine(line);
}

void RGraphicsViewWorkerPainter::strokePath(const QPainterPath& path, const QPen& pen) {
    painter->strokePath(path, pen);
}

void RGraphicsViewWorkerPainter::drawEllipse(const QRectF& rectangle) {
    painter->drawEllipse(rectangle);
}

void RGraphicsViewWorkerPainter::drawRect(const QRectF& rectangle) {
    painter->drawRect(rectangle);
}

void RGraphicsViewWorkerPainter::fillRect(const QRectF& rectangle, const QBrush& brush) {
    painter->fillRect(rectangle, brush);
}


