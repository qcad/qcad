include( ../../../shared.pri )

TEMPLATE = lib
r_static_libs {
    CONFIG += staticlib
}
else {
    DESTDIR = ../../../plugins
    CONFIG += plugin
}

# this is required to compile the spatial index library from navel ltd:
DEFINES += PACKAGE_BUGREPORT=\\\"mhadji@gmail.com\\\"

# suppress spatial debug messages
DEFINES += NDEBUG
DEFINES += SPATIALINDEX_CREATE_DLL

!win32-msvc2010 {
    DEFINES += HAVE_BZERO
}

CONFIG -= warn_on
CONFIG += warn_off

HEADERS = \
    include/tools/PointerPool.h \
    include/tools/PoolPointer.h \
    include/tools/SmartPointer.h \
    include/tools/Tools.h \
    include/tools/rand48.h \
    include/Version.h \
    include/MovingPoint.h \
    include/Point.h \
    include/LineSegment.h \
    include/RTree.h \
    include/TimeRegion.h \
    include/MovingRegion.h \
    include/Region.h \
    include/MVRTree.h \
    include/SpatialIndex.h \
    include/TPRTree.h \
    include/TimePoint.h \
    src/storagemanager/Buffer.h \
    src/storagemanager/DiskStorageManager.h \
    src/storagemanager/RandomEvictionsBuffer.h \
    src/storagemanager/MemoryStorageManager.h \
    src/rtree/RIndex.h \
    src/rtree/RLeaf.h \
    src/rtree/RNode.h \
    src/rtree/RStatistics.h \
    src/rtree/RTree.h \
    src/rtree/RBulkLoader.h \
    src/rtree/RPointerPoolNode.h \
    src/mvrtree/MVRStatistics.h \
    src/mvrtree/MVRLeaf.h \
    src/mvrtree/MVRTree.h \
    src/mvrtree/MVRIndex.h \
    src/mvrtree/MVRNode.h \
    src/mvrtree/MVRPointerPoolNode.h \
    src/spatialindex/SpatialIndexImpl.h \
    src/tprtree/TPRTree.h \
    src/tprtree/TPRStatistics.h \
    src/tprtree/TPRIndex.h \
    src/tprtree/TPRLeaf.h \
    src/tprtree/TPRNode.h \
    src/tprtree/TPRPointerPoolNode.h

SOURCES = \
    src/storagemanager/RandomEvictionsBuffer.cc \
    src/storagemanager/MemoryStorageManager.cc \
    src/storagemanager/Buffer.cc \
    src/storagemanager/DiskStorageManager.cc \
    src/tools/rand48.cc \
    src/tools/Tools.cc \
    src/rtree/RIndex.cc \
    src/rtree/RLeaf.cc \
    src/rtree/RNode.cc \
    src/rtree/RTree.cc \
    src/rtree/RBulkLoader.cc \
    src/rtree/RStatistics.cc \
    src/mvrtree/MVRStatistics.cc \
    src/mvrtree/MVRIndex.cc \
    src/mvrtree/MVRTree.cc \
    src/mvrtree/MVRLeaf.cc \
    src/mvrtree/MVRNode.cc \
    src/spatialindex/TimeRegion.cc \
    src/spatialindex/MovingRegion.cc \
    src/spatialindex/Region.cc \
    src/spatialindex/SpatialIndexImpl.cc \
    src/spatialindex/TimePoint.cc \
    src/spatialindex/MovingPoint.cc \
    src/spatialindex/Point.cc \
    src/spatialindex/LineSegment.cc \
    src/tprtree/TPRTree.cc \
    src/tprtree/TPRIndex.cc \
    src/tprtree/TPRNode.cc \
    src/tprtree/TPRLeaf.cc \
    src/tprtree/TPRStatistics.cc
