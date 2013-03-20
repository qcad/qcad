# ccache win32 port: http://code.google.com/p/ccache-win32/
win32-g++ {
    exists(C:\MinGW\bin\ccache.exe) {
        QMAKE_CXX = C:\MinGW\bin\ccache.exe g++  
    }
}

!win32 {
    # check if ccache is available:
    CCACHE = $$system(ccache -V)
    contains(CCACHE, Andrew) {
        QMAKE_CXX = ccache g++
        QMAKE_CC = ccache gcc
    }
    else {
        message("ccache not found")
    }
}

