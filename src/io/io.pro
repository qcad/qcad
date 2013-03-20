include( ../../shared.pri )

TEMPLATE = subdirs

OTHER_FILES += io.dox

!r_no_dxf {
    SUBDIRS += dxf
}
