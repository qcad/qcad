#include <QtCore/QtGlobal>

#if defined(QCAD_DLL)
#   if defined(QCADSPATIALINDEX_LIBRARY)
#       define QCADSPATIALINDEX_EXPORT Q_DECL_EXPORT
#   else
#       define QCADSPATIALINDEX_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define QCADSPATIALINDEX_EXPORT
#endif
