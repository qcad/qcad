#include <QtCore/QtGlobal>

#if defined(QCADENTITY_LIBRARY)
#   define QCADENTITY_EXPORT Q_DECL_EXPORT
#else
#   define QCADENTITY_EXPORT Q_DECL_IMPORT
#endif
