#include <QtCore/QtGlobal>

#if defined(QCAD_DLL)
#   if defined(QCADENTITY_LIBRARY)
#       define QCADENTITY_EXPORT Q_DECL_EXPORT
#   else
#       define QCADENTITY_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define QCADENTITY_EXPORT
#endif
