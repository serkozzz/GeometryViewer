#if defined(GVLIBRARY_EXPORT) // внутри DLL
#   define GVAPI   __declspec(dllexport)
#else // вне DLL
#   define GVAPI   __declspec(dllimport)
#endif  // GVLIBRARY_EXPORT
