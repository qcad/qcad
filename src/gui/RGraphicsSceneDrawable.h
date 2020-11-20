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

#ifndef RGRAPHICSSCENEDRAWABLE_H
#define RGRAPHICSSCENEDRAWABLE_H

#include "gui_global.h"

#include "RPainterPath.h"
#include "RImageData.h"
#include "RTextBasedData.h"

/**
 * \scriptable
 * \copyable
 */
class QCADGUI_EXPORT RGraphicsSceneDrawable {
public:
    enum Type {
        Invalid,
        PainterPath,
        PainterPathRay,
        PainterPathXLine,
        Image,
        Text,
        Transform,
        EndTransform
    };

    enum Mode {
        NoMode = 0x0000,
        NoPlot = 0x0001,               //!< not plotted (from not plottable layers)
        PixelUnit = 0x0002,            //!< unit interpreted as pixels
        WorkingSet = 0x0004            //!< in current working set
    };
    Q_DECLARE_FLAGS(Modes, Mode)

public:
    RGraphicsSceneDrawable() : type(Invalid), modes(NoMode), painterPath(NULL), image(NULL), text(NULL), transform(NULL) {}
    RGraphicsSceneDrawable(const RGraphicsSceneDrawable& other);

    /**
     * \nonscriptable
     */
    RGraphicsSceneDrawable(const RPainterPath& pp, const RVector& os = RVector::nullVector);

    /**
     * \nonscriptable
     */
    RGraphicsSceneDrawable(const RImageData& img, const RVector& os = RVector::nullVector);

    /**
     * \nonscriptable
     */
    RGraphicsSceneDrawable(const RTextBasedData& txt, const RVector& os = RVector::nullVector);

    /**
     * \nonscriptable
     */
    RGraphicsSceneDrawable(const RTransform& tf, const RVector& os = RVector::nullVector);

    /**
     * \nonscriptable
     */
    RGraphicsSceneDrawable(const Type& t, const RVector& os = RVector::nullVector);

    ~RGraphicsSceneDrawable();

    static RGraphicsSceneDrawable createFromPainterPath(const RPainterPath& pp, const RVector& offset = RVector::nullVector);
    static RGraphicsSceneDrawable createFromImage(const RImageData& img, const RVector& offset = RVector::nullVector);
    static RGraphicsSceneDrawable createFromText(const RTextBasedData& txt, const RVector& offset = RVector::nullVector);
    static RGraphicsSceneDrawable createFromTransform(const RTransform& transfrom, const RVector& offset = RVector::nullVector);
    static RGraphicsSceneDrawable createEndTransform(const RVector& offset);

    void uninit();

    RGraphicsSceneDrawable::Type getType() const {
        return type;
    }

    bool isPainterPath() {
        return type==PainterPath || type==PainterPathRay || type==PainterPathXLine;
    }

    bool isText() {
        return type==Text;
    }

    bool isImage() {
        return type==Image;
    }

    void setMode(RGraphicsSceneDrawable::Mode mode, bool on = true) {
        if (on) {
            modes |= mode;
        } else {
            modes &= ~mode;
        }
    }
    bool getMode(RGraphicsSceneDrawable::Mode mode) const {
        return (modes & mode) == mode;
    }

    void setNoPlot(bool on) {
        setMode(RGraphicsSceneDrawable::NoPlot, on);
    }
    bool getNoPlot() const {
        return getMode(RGraphicsSceneDrawable::NoPlot);
    }

    void setPixelUnit(bool on) {
        setMode(RGraphicsSceneDrawable::PixelUnit, on);
    }
    bool getPixelUnit() const {
        return getMode(RGraphicsSceneDrawable::PixelUnit);
    }

    void setWorkingSet(bool on) {
        setMode(RGraphicsSceneDrawable::WorkingSet, on);
    }
    bool isWorkingSet() const {
        return getMode(RGraphicsSceneDrawable::WorkingSet);
    }

    RPainterPath& getPainterPath() const {
        Q_ASSERT(painterPath!=NULL);
        return *painterPath;
    }

    RImageData& getImage() const {
        Q_ASSERT(image!=NULL);
        return *image;
    }

    RTextBasedData& getText() const {
        Q_ASSERT(text!=NULL);
        return *text;
    }

    RTransform& getTransform() const {
        Q_ASSERT(transform!=NULL);
        return *transform;
    }

    RVector getOffset() const {
        return offset;
    }

    void setOffset(const RVector& o) {
        offset = o;
    }

    RDocument* getDocument() const;

    void setSelected(bool on);
    void setHighlighted(bool on);

    RGraphicsSceneDrawable& operator=(const RGraphicsSceneDrawable& other);

protected:
     Type type;
     RVector offset;
     Modes modes;

    //union {
        RPainterPath* painterPath;
        RImageData* image;
        RTextBasedData* text;
        RTransform* transform;
    //};
};

QCADGUI_EXPORT QDebug operator<<(QDebug dbg, const RGraphicsSceneDrawable& d);

Q_DECLARE_METATYPE(RGraphicsSceneDrawable)
Q_DECLARE_METATYPE(RGraphicsSceneDrawable*)
Q_DECLARE_METATYPE(RGraphicsSceneDrawable::Type)
Q_DECLARE_METATYPE(RGraphicsSceneDrawable::Mode)
Q_DECLARE_METATYPE(RGraphicsSceneDrawable::Mode*)

#endif
