#include <QtCore/QtGlobal>

#if defined(QCADSTEMMER_LIBRARY)
#   define QCADSTEMMER_EXPORT Q_DECL_EXPORT
#else
#   define QCADSTEMMER_EXPORT Q_DECL_IMPORT
#endif
