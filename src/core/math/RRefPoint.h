#ifndef RREFPOINT_H
#define RREFPOINT_H

#include "../core_global.h"

#include <QFlags>
#include <QList>

#include "RVector.h"

/**
 * Represents a reference point of an entity.
 *
 * \ingroup math
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RRefPoint : public RVector {
public:
    enum Flag {
        NoFlags = 0x000,
        Secondary = 0x001,
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    static QList<RVector> toVectorList(const QList<RRefPoint>& list) {
        QList<RVector> ret;
        for (int i=0; i<list.length(); i++) {
            ret.append(list.at(i));
        }
        return ret;
    }

    static QList<RRefPoint> toRefPointList(const QList<RVector>& list) {
        QList<RRefPoint> ret;
        for (int i=0; i<list.length(); i++) {
            ret.append(list.at(i));
        }
        return ret;
    }

    RRefPoint() : RVector() {}
    RRefPoint(const RVector& v, RRefPoint::Flags f) : RVector(v), flags(f) {}
    RRefPoint(const RVector& v) : RVector(v) {}
    RRefPoint(double vx, double vy, double vz = 0.0, bool valid_in = true) : RVector(vx, vy, vz, valid_in) {}

    void setFlag(RRefPoint::Flag flag, bool on) {
        if (on) {
            flags |= flag;
        } else {
            flags &= ~flag;
        }
    }

    bool getFlag(RRefPoint::Flag flag) const {
        return (flags & flags) == flag;
    }

    RRefPoint::Flags getFlags() const {
        return flags;
    }

private:
    Flags flags;
};

Q_DECLARE_METATYPE(QList<RRefPoint>)
Q_DECLARE_METATYPE(QList<RRefPoint>*)
typedef QMultiMap<int, RRefPoint> _RMapIntRefPoint;
Q_DECLARE_METATYPE(_RMapIntRefPoint*)
Q_DECLARE_METATYPE(RRefPoint)
Q_DECLARE_METATYPE(RRefPoint*)
Q_DECLARE_METATYPE(const RRefPoint*)
Q_DECLARE_METATYPE(RRefPoint::Flag)
Q_DECLARE_METATYPE(RRefPoint::Flag*)
Q_DECLARE_METATYPE(QFlags<RRefPoint::Flag>)
Q_DECLARE_METATYPE(QFlags<RRefPoint::Flag>*)

#endif
