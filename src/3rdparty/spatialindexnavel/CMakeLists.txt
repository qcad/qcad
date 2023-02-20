cmake_minimum_required(VERSION 3.16)
project(spatialindexnavel VERSION 1.0 LANGUAGES CXX)

add_library(spatialindexnavel SHARED
    src/rtree/BulkLoader.cc src/rtree/BulkLoader.h
    src/rtree/Index.cc src/rtree/Index.h
    src/rtree/Leaf.cc src/rtree/Leaf.h
    src/rtree/Node.cc src/rtree/Node.h
    src/rtree/PointerPoolNode.h
    src/rtree/RTree.cc src/rtree/RTree.h
    src/rtree/Statistics.cc src/rtree/Statistics.h
    src/spatialindex/LineSegment.cc
    src/spatialindex/MovingPoint.cc
    src/spatialindex/MovingRegion.cc
    src/spatialindex/Point.cc
    src/spatialindex/Region.cc
    src/spatialindex/SpatialIndexImpl.cc
    src/spatialindex/TimePoint.cc
    src/spatialindex/TimeRegion.cc
    src/storagemanager/Buffer.cc src/storagemanager/Buffer.h
    src/storagemanager/DiskStorageManager.cc src/storagemanager/DiskStorageManager.h
    src/storagemanager/MemoryStorageManager.cc src/storagemanager/MemoryStorageManager.h
    src/storagemanager/RandomEvictionsBuffer.cc src/storagemanager/RandomEvictionsBuffer.h
    src/tools/Tools.cc
    src/tools/rand48.cc
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
