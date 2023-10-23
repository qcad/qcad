#include "RGraphicsViewWorker.h"

RGraphicsViewWorker::~RGraphicsViewWorker() {
}

void RGraphicsViewWorker::run() {
    paint();
    emit finished();
}

void RGraphicsViewWorker::init(QList<REntity::Id>& list, int startIndex, int endIndex) {
    this->list = &list;
    this->startIndex = startIndex;
    this->endIndex = endIndex;
}

void RGraphicsViewWorker::paint() {
    // paint entities of worker slice:
    for (int i=startIndex; i<endIndex; i++) {
        //qDebug() << "RGraphicsViewWorker::paint: " << i;
        imageView.paintEntityThread(this, list->at(i));
    }

    //qDebug() << "RGraphicsViewWorker::paint: emit finished";
    //emit finished();
    //qDebug() << "RGraphicsViewWorker::paint: DONE";
}

void RGraphicsViewWorker::paintImage(const RImageData& img, bool workingSet) {
    imageView.paintImage(this, img, workingSet);
}

void RGraphicsViewWorker::paintText(const RTextBasedData& text, bool workingSet) {
    imageView.paintText(this, text, workingSet);
}
