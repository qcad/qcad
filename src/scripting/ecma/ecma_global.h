#include <QtCore/QtGlobal>

#if defined(QCADECMA_LIBRARY)
#   define QCADECMA_EXPORT Q_DECL_EXPORT
#else
#   define QCADECMA_EXPORT Q_DECL_IMPORT
#endif
