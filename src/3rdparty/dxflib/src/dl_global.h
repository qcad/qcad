#if defined(DXFLIB_LIBRARY)
#   define DXFLIB_EXPORT __declspec(dllexport)
#else
#   define DXFLIB_EXPORT __declspec(dllimport)
#endif
