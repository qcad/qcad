include( ../run/run.pri )

CONFIG += console
TARGET = qcad.com

QMAKE_POST_LINK = mv "$${DESTDIR}/qcad.com.exe" "$${DESTDIR}/qcad.com"
