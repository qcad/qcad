include (shared.pri)

TEMPLATE = subdirs
SUBDIRS = \
    src \
    ts

# DO NOT REMOVE
# used by translation (lrelease, lupdate)
dummy {
    SUBDIRS += scripts
}
