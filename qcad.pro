include (shared.pri)

TEMPLATE = subdirs
SUBDIRS = \
    src

win32 {
    dirs = $$system("dir /B ..\* | findstr qcad..*")
    for (dir, $$list($$dirs)) {
        message(..\\$$dir)
        SUBDIRS += ..\\$$dir
    }
}
else {
    SUBDIRS += $$system("ls -d ../qcad?* 2>/dev/null | grep -v $(basename $(pwd))$")
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
