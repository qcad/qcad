#include "RGraphicsSceneDrawable.h"

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RGraphicsSceneDrawable& other) : type(Invalid), painterPath(NULL), image(NULL), text(NULL) {
    operator =(other);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RPainterPath& pp) : type(PainterPath), painterPath(NULL), image(NULL), text(NULL) {
    painterPath = new RPainterPath(pp);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RImageData& img) : type(Image), painterPath(NULL), image(NULL), text(NULL) {
    image = new RImageData(img);
}

RGraphicsSceneDrawable::RGraphicsSceneDrawable(const RTextBasedData& txt) : type(Text), painterPath(NULL), image(NULL), text(NULL) {
    text = new RTextBasedData(txt);
}

RGraphicsSceneDrawable::~RGraphicsSceneDrawable() {
    uninit();
}

RGraphicsSceneDrawable RGraphicsSceneDrawable::createFromPainterPath(const RPainterPath& pp) {
    return RGraphicsSceneDrawable(pp);
}

RGraphicsSceneDrawable RGraphicsSceneDrawable::createFromImage(const RImageData& img) {
    return RGraphicsSceneDrawable(img);
}

RGraphicsSceneDrawable RGraphicsSceneDrawable::createFromText(const RTextBasedData& txt) {
    return RGraphicsSceneDrawable(txt);
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
