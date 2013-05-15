include (shared.pri)

TEMPLATE = subdirs
SUBDIRS = \
    src \
    ts \
    support

# DO NOT REMOVE
# used by translation (lrelease, lupdate)
dummy {
    SUBDIRS += scripts
}
