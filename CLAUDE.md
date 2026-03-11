# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

QCAD uses CMake (3.16+) with Ninja. Qt 6 is the primary target.

```bash
# Configure (one-time, from repo root)
CMAKE_PREFIX_PATH=/path/to/qt6 cmake -DBUILD_QT6=ON -G Ninja .

# Build
ninja -j20
```

The `build_qt6.sh` script in the root also builds the companion `qcadpro` project (sibling directory) — it is not a standalone build script for this repo alone.

JavaScript API bindings are auto-generated via `generate_qt6.sh`, which invokes generator scripts across several sibling `*jsapi` repositories (`qtjsapi`, `qcadjsapi`, etc.). Regeneration is only needed when C++ API changes.

## Architecture

QCAD has a dual-layer architecture: a **C++ core** with **ECMAScript/JavaScript actions** on top.

### C++ Core (`src/`)

Libraries are compiled separately and linked into the main executable (`src/run/`). Key libraries:

- `core` — CAD engine, entities, scripting bridge, document model
- `entity` — All CAD entity classes (`RArc`, `RCircle`, `RPolyline`, `RLine`, `RDimension`, etc.)
- `operations` — Transactional CAD operations (Add, Delete, Transform, etc.)
- `gui` — Main window, graphics views, custom Qt widgets
- `io` — File I/O (DXF, DWG, PDF, SVG)
- `scripting` — ECMAScript execution engine (Qt Script / QJSEngine)
- `snap` — Snap logic
- `spatialindex` — Spatial index for entity lookup

**C++ naming conventions:**
- Core classes: `R` prefix (`RDocument`, `REntity`, `RVector`, `RColor`, etc.)
- Entity data/proxy split: `RCircleData` + `RCircleEntity` + `RCircleProxy`
- `RStorage` / `RTransaction` for document storage and undo/redo

### JavaScript Layer (`scripts/`)

All user-facing actions (Draw, Modify, File, Edit, etc.) are implemented as ECMAScript scripts. Each action lives in its own subdirectory:

```
scripts/Draw/Circle/Circle2PR/
    Circle2PR.js      # Action logic, extends EAction or a base draw class
    Circle2PR.ui      # Qt Designer UI for the options toolbar
    Tests/
        Circle2PRTest00.js    # TdbTest-based test
        required/             # Expected output DXF files
        actual/               # Actual output (generated at test time)
```

**JavaScript action pattern:**
- Inherit from `EAction` (base) or a category base class (e.g., `Draw`, `Modify`)
- Implement a state machine via `setState()`, handle `beginEvent()`, `escapeEvent()`, `coordinateEvent()`, `mouseReleaseEvent()`, etc.
- Call C++ via the exposed ECMA API (e.g., `new RAddObjectOperation(entity)`)

`scripts/EAction.js` is the base class for all script actions. `scripts/autostart.js` is the script initialization entry point.

### C++/JavaScript Bridge

C++ classes are exposed to ECMAScript via generated API wrappers in the sibling `*jsapi` repositories. Changes to C++ public APIs require regenerating bindings with `generate_qt6.sh`.

## Tests

Tests are JavaScript files using the `TdbTest` framework:

```js
include('scripts/Developer/TestingDashboard/TdbTest.js');

function MyTest() {
    TdbTest.call(this, 'scripts/Path/To/Tests/MyTest.js');
}
MyTest.prototype = new TdbTest();

MyTest.prototype.test00 = function() {
    this.setUp();
    // simulate GUI interactions via clickOnWidget, sendMouseEventModelPos, etc.
    this.verifyDrawing('MyTest.dxf');  // compares against required/
};
```

Tests simulate full GUI interaction (mouse events, widget clicks, dialog input) and verify output DXF files against `Tests/required/` snapshots. Updating a test's expected output means replacing the file in `required/`.

The `Testing/` directory at the repo root is the test runner infrastructure (currently sparse).

## Adding a New JavaScript Action

1. Create `scripts/<Category>/<ActionName>/`
2. `<ActionName>.js` — extend `EAction` or appropriate base
3. `<ActionName>.ui` — Qt Designer UI file for options toolbar (may be empty)
4. Register in the parent category's menu/toolbar JavaScript if needed
5. Optionally add `Tests/<ActionName>Test00.js` with `required/` DXF snapshots

## Key Files

| File | Purpose |
|------|---------|
| `src/run/main.cpp` | Application entry point |
| `scripts/autostart.js` | Script initialization |
| `scripts/EAction.js` | Base class for all script actions |
| `scripts/library.js` | Shared script utilities |
| `src/core/RDocumentInterface.h` | Primary document API exposed to scripts |
| `src/core/RAction.h` | C++ base action class |
| `CMakeInclude.txt` | Shared CMake configuration |
