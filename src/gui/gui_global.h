#include <QtCore/QtGlobal>

#if defined(QCAD_DLL)
#   if defined(QCADGUI_LIBRARY)
#       define QCADGUI_EXPORT Q_DECL_EXPORT
#   else
#       define QCADGUI_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define QCADGUI_EXPORT
#endif
