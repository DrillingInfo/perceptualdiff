#include "RGBAImageExt.h"
#include <cstdio>
#include <cstring>
#include <cassert>


static RGBAImageExt *ToRGBAImage(FIBITMAP *image, const char *filename=NULL) {
	const int w = FreeImage_GetWidth(image);
	const int h = FreeImage_GetHeight(image);

	RGBAImageExt* result = (RGBAImageExt*)new RGBAImage(w, h, filename);
	// Copy the image over to our internal format, FreeImage has the scanlines bottom to top though.
	unsigned int* dest = result->Get_Data();
	for( int y=0; y < h; y++, dest += w )
	{
		const unsigned int* scanline = reinterpret_cast<const unsigned int*>(FreeImage_GetScanLine(image, h - y - 1));
		memcpy(dest, scanline, sizeof(dest[0]) * w);
	}

	return result;
}


RGBAImageExt* RGBAImageExt::ReadFromArray(BYTE *imageArray, DWORD arraySize) {

	FIMEMORY *memBuffer = FreeImage_OpenMemory(imageArray, arraySize);
	FREE_IMAGE_FORMAT imageType = FreeImage_GetFileTypeFromMemory(memBuffer, arraySize);
	if(FIF_UNKNOWN == imageType) {
		printf("Unknown filetype.\n");
		return 0;
	}

	FIBITMAP* temporary = FreeImage_LoadFromMemory(imageType, memBuffer, 0);
	FIBITMAP* freeImage = 0;
	freeImage = FreeImage_ConvertTo32Bits(temporary);
	FreeImage_Unload(temporary);

	if(!freeImage) {
		printf( "Failed to load the image. \n");
		return 0;
	}

	RGBAImageExt *result = ToRGBAImage(freeImage);

	FreeImage_Unload(freeImage);
	FreeImage_CloseMemory(memBuffer);

	return result;
}
