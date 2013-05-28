/*
RGBAImageExt.h
*/

#ifndef _RGBAIMAGEEXT_H
#define _RGBAIMAGEEXT_H

#include <string>
#include "RGBAImage.h"
#include "FreeImage.h"

/** Class extends RGBAImage and adds the method
 *  static RGBAImageExt* ReadFromArray(char* imageArray, long arraySize);
 */
class RGBAImageExt : public RGBAImage {
	RGBAImageExt(const RGBAImageExt&);
	RGBAImageExt& operator=(const RGBAImageExt&);
public:
	RGBAImageExt();
	~RGBAImageExt();
	static RGBAImageExt* ReadFromArray(BYTE* imageArray, DWORD arraySize);
};

#endif
