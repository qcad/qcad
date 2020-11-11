#include "RGraphicsSceneDrawable.h"

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RGraphicsSceneDrawable& other) :
    type(Invalid), modes(NoMode), painterPath(NULL), image(NULL), text(NULL), transform(NULL) {

    operator =(other);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RPainterPath& pp, const RVector& os) :
    type(PainterPath), offset(os), modes(NoMode), painterPath(NULL), image(NULL), text(NULL), transform(NULL) {

    painterPath = new RPainterPath(pp);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RImageData& img, const RVector& os) :
    type(Image), offset(os), modes(NoMode), painterPath(NULL), image(NULL), text(NULL), transform(NULL) {

    image = new RImageData(img);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RTextBasedData& txt, const RVector& os) :
    type(Text), offset(os), modes(NoMode), painterPath(NULL), image(NULL), text(NULL), transform(NULL) {

    text = new RTextBasedData(txt);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RTransform& tf, const RVector& os) :
    type(Transform), offset(os), modes(NoMode), painterPath(NULL), image(NULL), text(NULL), transform(NULL) {

    transform = new RTransform(tf);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const Type& t, const RVector& os) :
    type(t), offset(os), modes(NoMode), painterPath(NULL), image(NULL), text(NULL), transform(NULL) {
}

RGraphicsSceneDrawable::~RGraphicsSceneDrawable() {
    uninit();
}

RGraphicsSceneDrawable RGraphicsSceneDrawable::createFromPainterPath(const RPainterPath& pp, const RVector& offset) {
    return RGraphicsSceneDrawable(pp, offset);
}

RGraphicsSceneDrawable RGraphicsSceneDrawable::createFromImage(const RImageData& img, const RVector& offset) {
    return RGraphicsSceneDrawable(img, offset);
}

RGraphicsSceneDrawable RGraphicsSceneDrawable::createFromText(const RTextBasedData& txt, const RVector& offset) {
    return RGraphicsSceneDrawable(txt, offset);
}

RGraphicsSceneDrawable RGraphicsSceneDrawable::createFromTransform(const RTransform& transform, const RVector& offset) {
    return RGraphicsSceneDrawable(transform, offset);
}

RGraphicsSceneDrawable RGraphicsSceneDrawable::createEndTransform(const RVector& offset) {
    return RGraphicsSceneDrawable(EndTransform, offset);
}

void RGraphicsSceneDrawable::uninit() {
    switch (type) {
    case PainterPath:
    case PainterPathRay:
    case PainterPathXLine:
        delete painterPath;
        break;
    case Image:
        delete image;
        break;
    case Text:
        delete text;
        break;
    case Transform:
        delete transform;
        break;
    default:
        break;
    }

    painterPath = NULL;
    image = NULL;
    text = NULL;
    transform = NULL;

    type = Invalid;
    modes = NoMode;
}

RDocument* RGraphicsSceneDrawable::getDocument() const {
    if (type==Image) {
        return image->getDocument();
    }
    if (type==Text) {
        return text->getDocument();
    }
    return NULL;
}

void RGraphicsSceneDrawable::setSelected(bool on) {
    switch (type) {
    case PainterPath:
    case PainterPathRay:
    case PainterPathXLine:
        painterPath->setSelected(on);
        break;
    case Image:
        image->setSelected(on);
        break;
    case Text:
        text->setSelected(on);
        break;
    case Transform:
        break;
    default:
        break;
    }
}

void RGraphicsSceneDrawable::setHighlighted(bool on) {
    switch (type) {
    case PainterPath:
    case PainterPathRay:
    case PainterPathXLine:
        painterPath->setHighlighted(on);
        break;
    case Image:
        break;
    case Text:
        text->setHighlighted(on);
        break;
    case Transform:
        break;
    default:
        break;
    }
}

RGraphicsSceneDrawable& RGraphicsSceneDrawable::operator=(const RGraphicsSceneDrawable& other) {
    uninit();

    switch (other.type) {
    case PainterPath:
    case PainterPathRay:
    case PainterPathXLine:
        Q_ASSERT(other.painterPath!=NULL);
        painterPath = new RPainterPath(*other.painterPath);
        break;
    case Image:
        Q_ASSERT(other.image!=NULL);
        image = new RImageData(*other.image);
        break;
    case Text:
        Q_ASSERT(other.text!=NULL);
        text = new RTextBasedData(*other.text);
        break;
    case Transform:
        Q_ASSERT(other.transform!=NULL);
        transform = new RTransform(*other.transform);
        break;
    default:
        break;
    }

    type = other.type;
    modes = other.modes;
    offset = other.offset;

    return *this;
}

QDebug operator<<(QDebug dbg, const RGraphicsSceneDrawable& d) {
    dbg.nospace() << "RGraphicsSceneDrawable(";

    switch (d.getType()) {
    case RGraphicsSceneDrawable::PainterPath:
    case RGraphicsSceneDrawable::PainterPathRay:
    case RGraphicsSceneDrawable::PainterPathXLine:
        dbg.nospace() << d.getPainterPath();
        break;
    case RGraphicsSceneDrawable::Image:
        dbg.nospace() << "Image";
        break;
    case RGraphicsSceneDrawable::Text:
        dbg.nospace() << d.getText();
        break;
    case RGraphicsSceneDrawable::Transform:
        dbg.nospace() << d.getTransform();
        break;
    case RGraphicsSceneDrawable::EndTransform:
        dbg.nospace() << "end transform";
        break;
    default:
        break;
    }
    dbg.nospace() << ")";
    return dbg.space();
}
