#if defined(GVLIBRARY_EXPORT) // ������ DLL
#   define GVAPI   __declspec(dllexport)
#else // ��� DLL
#   define GVAPI   __declspec(dllimport)
#endif  // GVLIBRARY_EXPORT
