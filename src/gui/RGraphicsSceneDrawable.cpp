#include "RGraphicsSceneDrawable.h"

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RGraphicsSceneDrawable& other) : type(Invalid), painterPath(NULL), image(NULL), text(NULL) {
    operator =(other);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RPainterPath& pp, const RVector& os) : type(PainterPath), offset(os), painterPath(NULL), image(NULL), text(NULL) {
    painterPath = new RPainterPath(pp);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RImageData& img, const RVector& os) : type(Image), offset(os), painterPath(NULL), image(NULL), text(NULL) {
    image = new RImageData(img);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RTextBasedData& txt, const RVector& os) : type(Text), offset(os), painterPath(NULL), image(NULL), text(NULL) {
    text = new RTextBasedData(txt);
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

void RGraphicsSceneDrawable::uninit() {
    if (type==PainterPath) {
        delete painterPath;
    }
    if (type==Image) {
        delete image;
    }
    if (type==Text) {
        delete text;
    }

    painterPath = NULL;
    image = NULL;
    text = NULL;
    type = Invalid;
}

void RGraphicsSceneDrawable::setSelected(bool on) {
    switch (type) {
    case PainterPath:
        painterPath->setSelected(on);
        break;
    case Image:
        image->setSelected(on);
        break;
    case Text:
        text->setSelected(on);
        break;
    default:
        break;
    }
}

void RGraphicsSceneDrawable::setHighlighted(bool on) {
    switch (type) {
    case PainterPath:
        painterPath->setHighlighted(on);
        break;
    case Image:
        break;
    case Text:
        text->setHighlighted(on);
        break;
    default:
        break;
    }
}

RGraphicsSceneDrawable& RGraphicsSceneDrawable::operator=(const RGraphicsSceneDrawable& other) {
    uninit();

    if (other.type==PainterPath) {
        Q_ASSERT(other.painterPath!=NULL);
        painterPath = new RPainterPath(*other.painterPath);
    }
    else if (other.type==Image) {
        Q_ASSERT(other.image!=NULL);
        image = new RImageData(*other.image);
    }
    else if (other.type==Text) {
        Q_ASSERT(other.text!=NULL);
        text = new RTextBasedData(*other.text);
    }
    type = other.type;
    offset = other.offset;

    return *this;
}

QDebug operator<<(QDebug dbg, const RGraphicsSceneDrawable& d) {
    dbg.nospace() << "RGraphicsSceneDrawable(";
    if (d.getType()==RGraphicsSceneDrawable::PainterPath) {
        dbg.nospace() << d.getPainterPath();
    }
    else if (d.getType()==RGraphicsSceneDrawable::Image) {
        dbg.nospace() << "Image";
    }
    else if (d.getType()==RGraphicsSceneDrawable::Text) {
        dbg.nospace() << d.getText();
    }
    dbg.nospace() << ")";
    return dbg.space();
}
