#include <QtCore/QtGlobal>

#if defined(QCAD_DLL)
#   if defined(QCADDXF_LIBRARY)
#       define QCADDXF_EXPORT Q_DECL_EXPORT
#   else
#       define QCADDXF_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define QCADDXF_EXPORT
#endif
