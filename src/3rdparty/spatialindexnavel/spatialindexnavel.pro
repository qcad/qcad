include( ../../../shared.pri )

TARGET = spatialindexnavel
TEMPLATE = lib
r_static_libs {
    CONFIG += staticlib
}
else {
    CONFIG += plugin
}

# this is required to compile the spatial index library from navel ltd:
#DEFINES += PACKAGE_BUGREPORT=\\\"mhadji@gmail.com\\\"

# suppress spatial debug messages
DEFINES += NDEBUG
DEFINES += SPATIALINDEX_CREATE_DLL

!win32-msvc2010 {
    DEFINES += HAVE_BZERO
}

!win32 {
    DEFINES += PTHREADS
    DEFINES += HAVE_PTHREAD_H
    DEFINES += HAVE_SRAND48
}

CONFIG -= warn_on
CONFIG += warn_off

INCLUDEPATH += include

HEADERS = \
    src/rtree/BulkLoader.h \
    src/rtree/Index.h \
    src/rtree/Leaf.h \
    src/rtree/Node.h \
    src/rtree/PointerPoolNode.h \
    src/rtree/RTree.h \
    src/rtree/Statistics.h \
    src/storagemanager/Buffer.h \
    src/storagemanager/DiskStorageManager.h \
    src/storagemanager/MemoryStorageManager.h \
    src/storagemanager/RandomEvictionsBuffer.h

SOURCES = \
    src/rtree/BulkLoader.cc \
    src/rtree/Index.cc \
    src/rtree/Leaf.cc \
    src/rtree/Node.cc \
    src/rtree/RTree.cc \
    src/rtree/Statistics.cc \
    src/spatialindex/LineSegment.cc \
    src/spatialindex/MovingPoint.cc \
    src/spatialindex/MovingRegion.cc \
    src/spatialindex/Point.cc \
    src/spatialindex/Region.cc \
    src/spatialindex/SpatialIndexImpl.cc \
    src/spatialindex/TimePoint.cc \
    src/spatialindex/TimeRegion.cc \
    src/storagemanager/Buffer.cc \
    src/storagemanager/DiskStorageManager.cc \
    src/storagemanager/MemoryStorageManager.cc \
    src/storagemanager/RandomEvictionsBuffer.cc \
    src/tools/rand48.cc \
    src/tools/Tools.cc
