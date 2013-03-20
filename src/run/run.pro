include( ../../shared_app.pri )

macx {
    ICON = qcad.icns
}

win32 {
    RC_FILE = qcad.rc
}

win32 {
    QMAKE_LFLAGS_WINDOWS += /FORCE:MULTIPLE
}

linux-g++ {
    QMAKE_CXXFLAGS += -static-libgcc -static-libstdc++
    QMAKE_LFLAGS += -L.
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++
}

SOURCES = main.cpp
HEADERS = 
TEMPLATE = app
OTHER_FILES += run.dox

win32 {
    rtrial {
        TARGET = qcad-trial
    }
    else {
        TARGET = qcad
    }
}

macx {
#    rcam {
#        rtrial {
#            TARGET = QCADCAMTrial
#            QMAKE_INFO_PLIST = InfoCamTrial.plist
#        }
#        else {
#            TARGET = QCADCAM
#            QMAKE_INFO_PLIST = InfoCam.plist
#        }
#    }
#    else {
        rtrial {
            TARGET = QCADTrial
            QMAKE_INFO_PLIST = InfoTrial.plist
        }
        else {
            TARGET = QCAD
            QMAKE_INFO_PLIST = Info.plist
        }
#    }
} 
else {
    unix {
        rtrial {
            TARGET = qcad-trial-bin
        }
        else {
            TARGET = qcad-bin
        }
    }
}

#RESOURCES = ../../scripts/scripts.qrc
