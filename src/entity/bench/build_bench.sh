#!/bin/sh
# Builds the RHatchData::getPainterPaths() benchmark against the libraries in
# the release/ directory of this source tree.
#
#   src/entity/bench/build_bench.sh && release/hatchbench
#
# QTDIR can be set to point at the Qt installation to use, otherwise the path
# recorded in build/CMakeCache.txt is used.

set -e

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
SRC_ROOT=$(cd "$SCRIPT_DIR/../../.." && pwd)

if [ -z "$QTDIR" ]; then
    if [ -f "$SRC_ROOT/build/CMakeCache.txt" ]; then
        QTDIR=$(grep -m1 '^Qt6_DIR:PATH=' "$SRC_ROOT/build/CMakeCache.txt" | \
                sed 's|^Qt6_DIR:PATH=||; s|/lib/cmake/Qt6$||')
    fi
fi

if [ -z "$QTDIR" ] || [ ! -d "$QTDIR" ]; then
    echo "error: cannot locate Qt. set QTDIR." >&2
    exit 1
fi

OUT="$SRC_ROOT/release/hatchbench"

echo "Qt:  $QTDIR"
echo "out: $OUT"

CXX=${CXX:-c++}

$CXX \
    -std=gnu++17 -O3 -DNDEBUG \
    -DQT_NO_DEBUG -DQT_SHAREDPOINTER_TRACK_POINTERS -DQT_CORE_LIB -DQT_GUI_LIB \
    -I"$SRC_ROOT/src/core" \
    -I"$SRC_ROOT/src/core/math" \
    -I"$SRC_ROOT/src/entity" \
    -I"$SRC_ROOT/src/3rdparty" \
    -isystem "$QTDIR/include" \
    -isystem "$QTDIR/include/QtCore" \
    -isystem "$QTDIR/include/QtGui" \
    -iframework "$QTDIR/lib" \
    -isystem "$QTDIR/lib/QtCore.framework/Headers" \
    -isystem "$QTDIR/lib/QtGui.framework/Headers" \
    -F"$QTDIR/lib" \
    -framework QtCore -framework QtGui \
    -L"$SRC_ROOT/release" -lqcadcore -lqcadentity -lopennurbs \
    -Wl,-rpath,"$SRC_ROOT/release" -Wl,-rpath,"$QTDIR/lib" \
    -o "$OUT" \
    "$SCRIPT_DIR/RHatchDataBenchmark.cpp"

echo "built $OUT"
