#include <QtCore/QtGlobal>

#if defined(QCAD_DLL)
#   if defined(QCADSNAP_LIBRARY)
#       define QCADSNAP_EXPORT Q_DECL_EXPORT
#   else
#       define QCADSNAP_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define QCADSNAP_EXPORT
#endif
