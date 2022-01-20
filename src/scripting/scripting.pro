include( ../../shared.pri )

lessThan(QT_MAJOR_VERSION, 6) {
    SUBDIRS = ecmaapi
}

TEMPLATE = subdirs
