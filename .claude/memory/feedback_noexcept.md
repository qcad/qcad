---
name: No noexcept keyword
description: Do not add noexcept specifier to functions in this codebase
type: feedback
---

Do not add `noexcept` to function declarations or definitions. Do not replace `NULL` with `nullptr`.

**Why:** Not all compilers/platforms used for this project support these C++11 keywords.

**How to apply:** Leave `NULL` as-is and never suggest adding `noexcept`. This applies to all C++ source files in this project.
