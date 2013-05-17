include (shared.pri)

TEMPLATE = subdirs
SUBDIRS = \
    src \
    ts

exists(support) {
    SUBDIRS += support
}

# DO NOT REMOVE
# used by translation (lrelease, lupdate)
dummy {
    SUBDIRS += scripts
}
