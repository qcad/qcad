include (shared.pri)

TEMPLATE = subdirs
SUBDIRS = \
    src \
    ts

win32 {
    SUBDIRS += $$system("dir ..\* | findstr qcad..*")
}
else {
    SUBDIRS += $$system("ls -d ../qcad?* | grep -v qcadmobile")
}

!r_mobile {
    exists(support) {
        #SUBDIRS += support
    }
}

# DO NOT REMOVE
# used by translation (lrelease, lupdate)
dummy {
    SUBDIRS += scripts
}
