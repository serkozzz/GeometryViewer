#pragma once

#if defined(GVLIBRARY_EXPORT) // ������ DLL
#   define GVAPI   __declspec(dllexport)
#else // ��� DLL
#   define GVAPI   __declspec(dllimport)
#endif  // GVLIBRARY_EXPORT


extern "C"
{
	GVAPI void gvTest();
	GVAPI int tutorial2();
}