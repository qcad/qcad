#include <QtCore/QtGlobal>

#if defined(QCADGRID_LIBRARY)
#   define QCADGRID_EXPORT Q_DECL_EXPORT
#else
#   define QCADGRID_EXPORT Q_DECL_IMPORT
#endif
