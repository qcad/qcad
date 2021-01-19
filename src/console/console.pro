include( ../run/run.pri )

CONFIG += console
TARGET = qcadcmd.com

QMAKE_POST_LINK = mv "$${DESTDIR}/qcadcmd.com.exe" "$${DESTDIR}/qcadcmd.com"
