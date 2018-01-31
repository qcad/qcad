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

#ifndef RRESTRICTANGLELENGTH_H
#define RRESTRICTANGLELENGTH_H

#include "snap_global.h"

#include "RSnapRestriction.h"

class RDocumentInterface;

/**
 * \brief Angle and length snap restriction implementation.
 *
 * \scriptable
 * \generateScriptShell
 *
 * \ingroup snap
 */
class QCADSNAP_EXPORT RRestrictAngleLength : public RSnapRestriction {
public:
    enum AngleLengthMode {
        None,
        Angle,
        Length,
        AngleLength
    };

    RRestrictAngleLength(RDocumentInterface* documentInterface = NULL) :
        RSnapRestriction(documentInterface),
        mode(RRestrictAngleLength::AngleLength),
        baseAngle(0.0),
        angle(0.0),
        baseLength(0.0),
        length(0.0) {}

    RRestrictAngleLength(RDocumentInterface* documentInterface, double baseAngle, double angle, double baseLength, double length)
        : RSnapRestriction(documentInterface), 
          mode(RRestrictAngleLength::AngleLength),
          baseAngle(baseAngle), angle(angle),
          baseLength(baseLength), length(length) {}

    virtual ~RRestrictAngleLength() {}

    virtual RVector restrictSnap(const RVector& position, const RVector& relativeZero);

    virtual void setBaseAngle(double a) {
        baseAngle = a;
    }

    virtual void setAngle(double a) {
        angle = a;
    }

    virtual void setBaseLength(double l) {
        baseLength = l;
    }

    virtual void setLength(double l) {
        length = l;
    }

    virtual void setRestrictAngle(bool on) {
        if (on) {
            if (mode==None) {
                mode = Angle;
            }
            if (mode==Length) {
                mode = AngleLength;
            }
        }
        else {
            if (mode==Angle) {
                mode = None;
            }
            if (mode==AngleLength) {
                mode = Length;
            }
        }
    }

    virtual void setRestrictLength(bool on) {
        if (on) {
            if (mode==None) {
                mode = Length;
            }
            if (mode==Angle) {
                mode = AngleLength;
            }
        }
        else {
            if (mode==Length) {
                mode = None;
            }
            if (mode==AngleLength) {
                mode = Angle;
            }
        }
    }

protected:
    AngleLengthMode mode;
    double baseAngle;
    double angle;
    double baseLength;
    double length;
};

Q_DECLARE_METATYPE(RRestrictAngleLength*)
Q_DECLARE_METATYPE(RRestrictAngleLength::AngleLengthMode)

#endif
