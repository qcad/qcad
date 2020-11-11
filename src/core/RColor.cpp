/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */
#include <QPainter>
#include <QPixmap>
#include <QBrush>

#include "RColor.h"
#include "RCircle.h"
#include "RDebug.h"
#include "RMath.h"
#include "RSettings.h"

QColor RColor::CompatByLayer = QColor(1,1,1);
QColor RColor::CompatByBlock = QColor(2,2,2);
QList<QPair<QString, RColor> > RColor::list;
QMap<QPair<RColor, QPair<int, int> >, QIcon> RColor::iconMap;
bool RColor::isInitialized = false;
#include "RColorCodes.h"

/**
 * Constructs an invalid color with the fixed RGB value (0, 0, 0).
 */
RColor::RColor() :
    QColor(), mode(RColor::Fixed) {
}

RColor::RColor(const QColor& color, RColor::Mode mode) :
    QColor(color), mode(mode) {
}

RColor::RColor(int r, int g, int b, int a, RColor::Mode mode) :
    QColor(r, g, b, a), mode(mode) {
}

RColor::RColor(Qt::GlobalColor color, RColor::Mode mode) :
    QColor(color), mode(mode) {
}

RColor::RColor(RColor::Mode mode) :
    QColor(), mode(mode) {
}

RColor::RColor(const QString& name, RColor::Mode mode) :
    QColor(name), mode(mode) {
}

//bool RColor::equalsCorrected(const RColor & color) const {
//    return operator==(color);
//}

bool RColor::operator==(const RColor & color) const {
    if (mode == RColor::ByLayer) {
        return color.mode == RColor::ByLayer;
    }
    if (mode == RColor::ByBlock) {
        return color.mode == RColor::ByBlock;
    }
    return mode == color.mode && QColor::operator==(color);
}

bool RColor::operator!=(const RColor & color) const {
    return !operator==(color);
}

bool RColor::operator<(const RColor & color) const {
    return getHash() < color.getHash();
}

unsigned long long RColor::getHash() const {
    return ((unsigned long long)rgba())
            + (((unsigned long long)mode) << (4 * 8))
            + (((unsigned long long)isValid()) << (4 * 8 + 4));
}

/**
 * \return Highlighted color for the given color.
 */
RColor RColor::getHighlighted(const RColor& color, const QColor& bgColor, int minDist) {
    if (!color.isValid()) {
        return Qt::gray;
    }

    RColor ret = color;

    int vColor = color.value();
    int vBgColor = bgColor.value();

    // 0     vColor                      vBgColor              255
    // |--------^----------------------------^------------------|
    // |<--d1-->|<------------d2------------>|<-------d3------->|
    int d1 = qMin(vColor, vBgColor);
    //int d2 = qAbs(vColor - vBgColor);
    int d3 = 255 - qMax(vColor, vBgColor);

    // d3 is big enough: set value to max (highlight):
    if (d3>=minDist) {
        ret.setHsv(color.hue(), color.saturation(), 255);
    }

    // d1 is big enough: set value to half (lowlight):
    else if (d1>=minDist) {
        ret.setHsv(color.hue(), color.saturation(), qMin(vColor, vBgColor)/2);
    }

    // black on white:
    else if (vColor<32 && vBgColor>224) {
        ret.setHsv(color.hue(), color.saturation(), 160);
    }

    // d2 is the only significant distance, set value to medium:
    else if (vColor<vBgColor) {
        ret.setHsv(color.hue(), color.saturation(), qMin(vColor+minDist, 255));
    }
    else {
        ret.setHsv(color.hue(), color.saturation(), qMax(vColor-minDist, 0));
    }

    return ret;
}

RColor RColor::getFaded(const RColor& color, const QColor& bgColor, double factor) {
    RColor ret = color;

    // mix color with background color:
    ret.setRedF((color.redF() + bgColor.redF()*factor) / (factor+1));
    ret.setGreenF((color.greenF() + bgColor.greenF()*factor) / (factor+1));
    ret.setBlueF((color.blueF() + bgColor.blueF()*factor) / (factor+1));

    return ret;
}

bool RColor::isValid() const {
    if (mode == RColor::ByBlock || mode == RColor::ByLayer) {
        return true;
    }
    return QColor::isValid();
}

bool RColor::isByLayer() const {
    return mode == RColor::ByLayer;
}

bool RColor::isByBlock() const {
    return mode == RColor::ByBlock;
}

bool RColor::isFixed() const {
    return mode == RColor::Fixed;
}

/**
 * \return Localized name of the color if known, otherwise "#RRGGBB".
 * For a localization neutral name use name() instead.
 */
QString RColor::getName() const {
    init();

    QListIterator<QPair<QString, RColor> > it(list);
    while (it.hasNext()) {
        QPair<QString, RColor> p = it.next();
        if (p.second == *this) {
            return p.first;
        }
    }

    return QColor::name();
}

/**
 * \return List of known colors.
 *
 * \param onlyFixed Only fixed colors, not ByLayer, ByBlock, ...
 */
QList<QPair<QString, RColor> > RColor::getList(bool onlyFixed) {
    init();
    QList<QPair<QString, RColor> > l = list;
    //if (combineBw) {
    //    QString name = RColor(Qt::black).getName();
    //    l.removeAll(QPair<QString, RColor> (name, Qt::black));
    //    name = RColor(Qt::white).getName();
    //    l.removeAll(QPair<QString, RColor> (name, Qt::white));
    //} else {
    //    QString name = RColor(Qt::black, RColor::BlackWhite).getName();
    //    l.removeAll(QPair<QString, RColor> (name, RColor(Qt::black,
    //            RColor::BlackWhite)));
    //}
    if (!onlyFixed) {
        return l;
    }

    // remove "By Layer"
    QString name = RColor(RColor::ByLayer).getName();
    l.removeAll(QPair<QString, RColor> (name, RColor(RColor::ByLayer)));

    // remove "By Block"
    name = RColor(RColor::ByBlock).getName();
    l.removeAll(QPair<QString, RColor> (name, RColor(RColor::ByBlock)));

    return l;
}

/**
 * \return CAD index of this color used in MTEXT strings.
 */
int RColor::getColorIndex() const {
    if (isByBlock()) {
        return 0;
    }
    if (isByLayer()) {
        return 256;
    }

    for (int i=1; i<255; i++) {
        if (red()==RMath::mround(cadColors[i][0]*255) &&
            green()==RMath::mround(cadColors[i][1]*255) &&
            blue()==RMath::mround(cadColors[i][2]*255)) {

            return i;
        }
    }

    return -1;
}

int RColor::getCustomColorCode() const {
     return (red() << 0) + (green() << 8) + (blue() << 16);
}

/**
 * Creates a color from the given CAD code (index 0...256).
 */
RColor RColor::createFromCadIndex(int code) {
    // special colors:
    if (code==0) {
        return RColor(RColor::ByBlock);
    }
    if (code==256) {
        return RColor(RColor::ByLayer);
    }

    // normal indexed colors:
    if (code>0 && code<256) {
        RColor c;
        c.setRgbF(cadColors[code][0], cadColors[code][1], cadColors[code][2]);
        return c;
    }

    return RColor();
}

/**
 * Creates a color from the given CAD code (RGB encoded int).
 */
RColor RColor::createFromCadCustom(int code) {
    return RColor(
              (code&0x0000ff) >> 0,
              (code&0x00ff00) >> 8,
              (code&0xff0000) >> 16
           );
}

RColor RColor::createFromName(const QString& name) {
    init();

    QListIterator<QPair<QString, RColor> > it(list);
    while (it.hasNext()) {
        QPair<QString, RColor> p = it.next();
        if (p.first == name) {
            return p.second;
        }
    }

    return RColor(name);
}

void RColor::init() {
    if (isInitialized) {
        return;
    }

    isInitialized = true;

    init(tr("By Layer"), RColor(RColor::ByLayer));
    init(tr("By Block"), RColor(RColor::ByBlock));
    init(tr("Red"), RColor(Qt::red));
    init(tr("Green"), RColor(Qt::green));
    init(tr("Blue"), RColor(Qt::blue));
    init(tr("Cyan"), RColor(Qt::cyan));
    init(tr("Magenta"), RColor(Qt::magenta));
    init(tr("Yellow"), RColor(Qt::yellow));
    init(tr("Orange"), RColor(255,127,0));
    init(tr("Dark Red"), RColor(Qt::darkRed));
    init(tr("Dark Green"), RColor(Qt::darkGreen));
    init(tr("Dark Blue"), RColor(Qt::darkBlue));
    init(tr("Dark Cyan"), RColor(Qt::darkCyan));
    init(tr("Dark Magenta"), RColor(Qt::darkMagenta));
    init(tr("Dark Yellow"), RColor(Qt::darkYellow));
    init(tr("Black"), RColor(Qt::black));
    init(tr("Gray"), RColor(Qt::gray));
    init(tr("Light Gray"), RColor(Qt::lightGray));
    init(tr("White"), RColor(Qt::white));
    init(tr("Others..."), RColor());
}

void RColor::init(const QString& cn, const RColor& c) {
    list.append(QPair<QString, RColor> (cn, c));
}

void RColor::removeColor(const QString& cn) {
    init();
    for (int i=0; i<list.length(); i++) {
        if (list.at(i).first==cn) {
            list.removeAt(i);
            break;
        }
    }
}

void RColor::addColor(const QString& cn, const RColor& c) {
    list.append(QPair<QString, RColor> (cn, c));
}

QIcon RColor::getIcon(const RColor& color, const QSize& size) {
    init();

    if (iconMap.contains(QPair<RColor, QPair<int, int> >(color, QPair<int, int>(size.width(), size.height())))) {
        return iconMap[QPair<RColor, QPair<int, int> >(color, QPair<int, int>(size.width(), size.height()))];
    }

    RColor col = color;
    if (color.isByLayer() || color.isByBlock() || /*color == RColor(Qt::black,
            RColor::BlackWhite) ||*/ !color.isValid()) {
        col = Qt::white;
    }
    QImage img(size, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);
    QPainter painter(&img);
    int w = img.width();
    int h = img.height();
    //    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(0, 0, w, h, col);
    if (!color.isValid()) {
        // icon for "Other colors..."
        QLinearGradient grad(0, 0, w, 0);
        grad.setColorAt(0, Qt::red);
        grad.setColorAt(0.33, Qt::yellow);
        grad.setColorAt(0.66, Qt::blue);
        grad.setColorAt(1, Qt::green);
        painter.fillRect(QRect(0, 0, w, h), grad);
    } /*else if (color == RColor(Qt::black, RColor::BlackWhite) || color
            == RColor(Qt::white, RColor::BlackWhite)) {
        // icon for black / white
        painter.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.moveTo(0, 0);
        path.lineTo(w, 0);
        path.lineTo(w, h);
        painter.fillPath(path, Qt::black);
        painter.setRenderHint(QPainter::Antialiasing, false);
    }*/ else if (col.alpha() != 255) {
        // indicate alpha by an inset
        QBrush opaqueBrush = col;
        col.setAlpha(255);
        opaqueBrush.setColor(col);
        painter.fillRect(w / 4, h / 4, w / 2, h / 2, opaqueBrush);
    }
    if (RSettings::hasDarkGuiBackground()) {
        painter.setPen(Qt::gray);
    }
    else {
        painter.setPen(Qt::black);
    }
    painter.drawRect(0, 0, w - 1, h - 1);
    painter.end();
    QIcon ret(QPixmap::fromImage(img));
    iconMap.insert(QPair<RColor, QPair<int, int> >(color, QPair<int, int>(size.width(), size.height())), ret);
    return ret;
}

/**
 * \return QColor compatibility equivalent of the current color.
 */
QColor RColor::toCompat() const {
    if (isByLayer()) {
        return CompatByLayer;
    }
    if (isByBlock()) {
        return CompatByBlock;
    }

    return *this;
}

/**
 * Initializes this color based on the given compatibility color.
 */
void RColor::setCompat(const QColor& col) {
    if (col==CompatByLayer) {
        *this = RColor(ByLayer);
    }
    else if (col==CompatByBlock) {
        *this = RColor(ByBlock);
    }
    else {
        *this = col;
        mode = Fixed;
    }
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RColor& c) {
    if (c.isValid()) {
        if (c.isByLayer()) {
            dbg.nospace() << "RColor(ByLayer)";
        } else if (c.isByBlock()) {
            dbg.nospace() << "RColor(ByBlock)";
        } else {
            dbg.nospace() << "RColor(RGBA: " << c.red() << ", " << c.green() << ", "
                    << c.blue() << ", " << c.alpha() << ")";
        }
    } else {
        dbg.nospace() << "RColor(invalid)";
    }
    return dbg.space();
}

/**
 * Serializes the given RColor object. Used for RSettings, keep in sync
 * with operator>>.
 */
QDataStream& operator<<(QDataStream& stream, const RColor& color) {
    stream << (const QColor&) color;
    stream << (quint16) color.mode;
    return stream;
}

/**
 * Deserializes the given RColor object.
 */
QDataStream& operator>>(QDataStream& stream, RColor& color) {
    stream >> (QColor&) color;
    quint16 mode;
    stream >> mode;
    color.mode = (RColor::Mode) mode;
    return stream;
}
