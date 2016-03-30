/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
        Image,
        Text
    };

    RGraphicsSceneDrawable() : type(Invalid), painterPath(NULL), image(NULL), text(NULL) {}
    RGraphicsSceneDrawable(const RGraphicsSceneDrawable& other);

    /**
     * \nonscriptable
     */
    RGraphicsSceneDrawable(const RPainterPath& pp);

    /**
     * \nonscriptable
     */
    RGraphicsSceneDrawable(const RImageData& img);

    /**
     * \nonscriptable
     */
    RGraphicsSceneDrawable(const RTextBasedData& txt);

    ~RGraphicsSceneDrawable();

    static RGraphicsSceneDrawable createFromPainterPath(const RPainterPath& pp);
    static RGraphicsSceneDrawable createFromImage(const RImageData& img);
    static RGraphicsSceneDrawable createFromText(const RTextBasedData& txt);

    void uninit();

    RGraphicsSceneDrawable::Type getType() const {
        return type;
    }

    RPainterPath getPainterPath() const {
        Q_ASSERT(painterPath!=NULL);
        return *painterPath;
    }

    RImageData getImage() const {
        Q_ASSERT(image!=NULL);
        return *image;
    }

    RTextBasedData getText() const {
        Q_ASSERT(text!=NULL);
        return *text;
    }

    RGraphicsSceneDrawable& operator=(const RGraphicsSceneDrawable& other);

protected:
     Type type;

    //union {
        RPainterPath* painterPath;
        RImageData* image;
        RTextBasedData* text;
    //};
};

QCADGUI_EXPORT QDebug operator<<(QDebug dbg, const RGraphicsSceneDrawable& d);

Q_DECLARE_METATYPE(RGraphicsSceneDrawable)
Q_DECLARE_METATYPE(RGraphicsSceneDrawable*)
Q_DECLARE_METATYPE(RGraphicsSceneDrawable::Type)

#endif
