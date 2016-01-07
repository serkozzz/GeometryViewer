#pragma once

#if defined(GVLIBRARY_EXPORT) // ������ DLL
#   define GVAPI   __declspec(dllexport)
#else // ��� DLL
#   define GVAPI   __declspec(dllimport)
#endif  // GVLIBRARY_EXPORT

#include <memory>

#include "GeometryData.h"


extern "C"
{
	GVAPI void createWindow();
	GVAPI void addGeometry(std::shared_ptr<GeometryData> geometryDataPtr);

	GVAPI void gvTest();
	GVAPI int tutorial2();
}