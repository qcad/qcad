#include <QtCore/QtGlobal>

#if defined(QCADCORE_LIBRARY)
#   define QCADCORE_EXPORT Q_DECL_EXPORT
#else
#   define QCADCORE_EXPORT Q_DECL_IMPORT
#endif
