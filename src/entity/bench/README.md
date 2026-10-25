# RHatchData::getPainterPaths benchmark

Standalone benchmark for hatch pattern generation
(`RHatchData::getPainterPaths`), used to measure and to guard optimizations of
the hatch generator.

## Build and run

```sh
src/entity/bench/build_bench.sh     # links against release/libqcadcore + libqcadentity
release/hatchbench
```

The libraries have to be built first (`ninja qcadentity` in the build
directory). `QTDIR` can be set to select the Qt installation, otherwise the one
recorded in `build/CMakeCache.txt` is used.

## What it measures

Thirteen hatches covering the cases that behave differently in the generator:
plain and dense single direction patterns, multi line and dashed patterns, dot
patterns, curved boundaries (circle with a hole, ellipse, arcs), boundaries
with very many elements, boundaries with many loops, solid fills and draft
mode. `-l` lists them with their loop count, complexity and boundary path size.

For every case the hatch is invalidated and fully regenerated; the median and
minimum of the timed repetitions are reported.

## The checksum is the regression guard

Every run prints a checksum over all generated painter paths (element types,
coordinates and points, quantized to 1e-6). Optimizations of the generator must
not change it.

```sh
release/hatchbench -b mybaseline.txt              # record
release/hatchbench -c mybaseline.txt              # compare: speedup + OK / CHANGED
```

`baseline_unoptimized.txt` holds the state of the generator before the
optimizations of 2026-07 (checksums are portable, the timings in it are from an
Apple M-series machine and are only meaningful relative to each other).

Comparing against a baseline exits non zero if any geometry changed.

## Options

```
-n <count>       timed repetitions per case (default 5)
-w <count>       warm up repetitions per case (default 1)
-f <substring>   only run cases whose name contains <substring>
-l               list cases and exit
-b <file>        write results as a baseline
-c <file>        compare against a baseline
-v               verbose: per repetition timings, and warnings from the generator
```

Note that running a single case with `-f` gives cleaner numbers for the small
cases than a full run, where they inherit the allocator state of the heavy
cases before them.

## Limitations

Splines as hatch boundaries are not covered: `RSplineProxy` is only installed by
the application, so splines degrade to invalid shapes in a standalone binary.
