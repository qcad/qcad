#include <QtCore/QtGlobal>

#if defined(QCAD_DLL)
#   if defined(QCADCORE_LIBRARY)
#       define QCADCORE_EXPORT Q_DECL_EXPORT
#   else
#       define QCADCORE_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define QCADCORE_EXPORT
#endif
