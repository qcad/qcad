#include <QtCore/QtGlobal>

#if defined(QCAD_DLL)
#   if defined(QCADECMAAPI_LIBRARY)
#       define QCADECMAAPI_EXPORT Q_DECL_EXPORT
#   else
#       define QCADECMAAPI_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define QCADECMAAPI_EXPORT
#endif
