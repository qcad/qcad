#include <QtCore/QtGlobal>

#if defined(QCAD_DLL)
#   if defined(QCADOPERATIONS_LIBRARY)
#       define QCADOPERATIONS_EXPORT Q_DECL_EXPORT
#   else
#       define QCADOPERATIONS_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define QCADOPERATIONS_EXPORT
#endif
