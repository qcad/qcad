cmake_minimum_required(VERSION 3.16)
project(spatialindexnavel VERSION 1.0 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

add_library(spatialindexnavel SHARED
    src/storagemanager/RandomEvictionsBuffer.h
    src/storagemanager/MemoryStorageManager.h
    src/storagemanager/Buffer.h
    src/storagemanager/DiskStorageManager.h
    src/tprtree/Index.h
    src/tprtree/Leaf.h
    src/tprtree/Node.h
    src/tprtree/Statistics.h
    src/tprtree/TPRTree.h
    src/tprtree/PointerPoolNode.h
    src/rtree/Index.h
    src/rtree/Leaf.h
    src/rtree/RTree.h
    src/rtree/Node.h
    src/rtree/Statistics.h
    src/rtree/PointerPoolNode.h
    src/rtree/BulkLoader.h
    src/mvrtree/Index.h
    src/mvrtree/Leaf.h
    src/mvrtree/Node.h
    src/mvrtree/MVRTree.h
    src/mvrtree/Statistics.h
    src/mvrtree/PointerPoolNode.h
    src/storagemanager/Buffer.cc
    src/storagemanager/RandomEvictionsBuffer.cc
    src/storagemanager/DiskStorageManager.cc
    src/storagemanager/MemoryStorageManager.cc
    src/tools/Tools.cc
    src/tools/rand48.cc
    src/capi/IdVisitor.cc
    src/capi/LeafQuery.cc
    src/capi/BoundsQuery.cc
    src/capi/sidx_api.cc
    src/capi/CustomStorage.cc
    src/capi/Utility.cc
    src/capi/ObjVisitor.cc
    src/capi/DataStream.cc
    src/capi/Index.cc
    src/capi/CountVisitor.cc
    src/capi/Error.cc
    src/tprtree/Statistics.cc
    src/tprtree/Node.cc
    src/tprtree/TPRTree.cc
    src/tprtree/Leaf.cc
    src/tprtree/Index.cc
    src/spatialindex/TimeRegion.cc
    src/spatialindex/LineSegment.cc
    src/spatialindex/TimePoint.cc
    src/spatialindex/MovingRegion.cc
    src/spatialindex/Point.cc
    src/spatialindex/SpatialIndexImpl.cc
    src/spatialindex/Region.cc
    src/spatialindex/MovingPoint.cc
    src/rtree/Statistics.cc
    src/rtree/Node.cc
    src/rtree/BulkLoader.cc
    src/rtree/Leaf.cc
    src/rtree/RTree.cc
    src/rtree/Index.cc
    src/mvrtree/Statistics.cc
    src/mvrtree/Node.cc
    src/mvrtree/Leaf.cc
    src/mvrtree/MVRTree.cc
    src/mvrtree/Index.cc
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(spatialindexnavel PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../release)
    target_link_libraries(spatialindexnavel PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../../release)
else()
    set_target_properties(spatialindexnavel PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../debug)
    target_link_libraries(spatialindexnavel PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../../debug)
endif()

target_include_directories(spatialindexnavel PUBLIC
    include
)

target_compile_definitions(spatialindexnavel PRIVATE
    NDEBUG
    QCAD_DLL
    SPATIALINDEX_CREATE_DLL
)

if(NOT win32-msvc2010)
    target_compile_definitions(spatialindexnavel PRIVATE
        HAVE_BZERO
    )
endif()

if(UNIX)
    target_compile_definitions(spatialindexnavel PRIVATE
        HAVE_PTHREAD_H
        HAVE_SRAND48
        PTHREADS
    )
endif()

if(win32-msvc2010)
    target_compile_definitions(spatialindexnavel PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()
