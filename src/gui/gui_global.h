#include <QtCore/QtGlobal>

#if defined(QCADGUI_LIBRARY)
#   define QCADGUI_EXPORT Q_DECL_EXPORT
#else
#   define QCADGUI_EXPORT Q_DECL_IMPORT
#endif
