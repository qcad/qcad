include (shared.pri)

CONFIG += debug_and_release

TEMPLATE = subdirs
SUBDIRS = \
    src \
    ts

!r_mobile {
    exists(support) {
        SUBDIRS += support
    }
}

# DO NOT REMOVE
# used by translation (lrelease, lupdate)
dummy {
    SUBDIRS += scripts
}
