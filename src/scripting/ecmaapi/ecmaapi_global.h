#include <QtCore/QtGlobal>

#if defined(QCADECMAAPI_LIBRARY)
#   define QCADECMAAPI_EXPORT Q_DECL_EXPORT
#else
#   define QCADECMAAPI_EXPORT Q_DECL_IMPORT
#endif
