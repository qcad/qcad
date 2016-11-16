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
        NoFlags   = 0x000,
        Secondary = 0x001,        /**< Secondary reference point (typically shown with different color) */
        Center    = 0x002,        /**< Reference point is a center point */
        Ignore    = 0x004,        /**< Ignore reference point for drag and drop */
        Start     = 0x008,        /**< Reference point is a start point */
        End       = 0x010         /**< Reference point is a start point */
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    static QList<RVector> toVectorList(const QList<RRefPoint>& list) {
        QList<RVector> ret;
        for (int i=0; i<list.length(); i++) {
            ret.append(list.at(i));
        }
        return ret;
    }

    static QList<RRefPoint> toRefPointList(const QList<RVector>& list, RRefPoint::Flags flags = RRefPoint::NoFlags) {
        QList<RRefPoint> ret;
        for (int i=0; i<list.length(); i++) {
            ret.append(RRefPoint(list.at(i), flags));
        }
        return ret;
    }

    RRefPoint() : RVector() {}
    RRefPoint(const RVector& v, RRefPoint::Flags f) : RVector(v), flags(f) {}
    RRefPoint(const RVector& v) : RVector(v) {}
    RRefPoint(double vx, double vy, double vz = 0.0, bool valid_in = true) : RVector(vx, vy, vz, valid_in) {}

    bool isSecondary() const {
        return getFlag(RRefPoint::Secondary);
    }

    void setSecondary(bool on) {
        setFlag(RRefPoint::Secondary, on);
    }

    bool isIgnore() const {
        return getFlag(RRefPoint::Ignore);
    }

    void setIgnore(bool on) {
        setFlag(RRefPoint::Ignore, on);
    }

    bool isCenter() const {
        return getFlag(RRefPoint::Center);
    }

    void setCenter(bool on) {
        setFlag(RRefPoint::Center, on);
    }

    bool isStart() const {
        return getFlag(RRefPoint::Start);
    }

    void setStart(bool on) {
        setFlag(RRefPoint::Start, on);
    }

    bool isEnd() const {
        return getFlag(RRefPoint::End);
    }

    void setEnd(bool on) {
        setFlag(RRefPoint::End, on);
    }

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

    void setFlags(RRefPoint::Flags f) {
        flags = f;
    }

private:
    Flags flags;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RRefPoint& v);

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
