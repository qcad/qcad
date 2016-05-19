#include "RRefPoint.h"

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RRefPoint& v) {
    dbg.nospace() << "RRefPoint(" << v.x << ", " << v.y << ", " << v.z << ", " << v.valid << ", " << v.getFlags() << ")";
    return dbg;
}
