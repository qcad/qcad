include( ../run/run.pri )

CONFIG += console
TARGET = qcadcmd.com

win32:QMAKE_POST_LINK = rename "$$replace(DESTDIR, /, \\)\\qcadcmd.com.exe" "qcadcmd.com"
unix:QMAKE_POST_LINK = mv "$${DESTDIR}/qcadcmd.com.exe" "$${DESTDIR}/qcadcmd.com"
