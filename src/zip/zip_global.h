#include <QtCore/QtGlobal>

#if defined(QCAD_DLL)
#   if defined(QCADZIP_LIBRARY)
#       define QCADZIP_EXPORT Q_DECL_EXPORT
#   else
#       define QCADZIP_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define QCADZIP_EXPORT
#endif
