#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <sstream>
#include "ArgsManager.h"
#include "RGBAImageExt.h"
#include "Metric.h"
#include "FreeImage.h"

ArgsManager::ArgsManager() {	
	ImgA = NULL;
	ImgB = NULL;
	ImgDiff = NULL;
	Verbose = false;
	LuminanceOnly = false;
	SumErrors = false;
	FieldOfView = 45.0f;
	Gamma = 2.2f;
	ThresholdPixels = 100;
	Luminance = 100.0f;
	ColorFactor = 1.0f;
	DownSample = 0;
}

ArgsManager::~ArgsManager() {
}


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


static RGBAImageExt* ReadFromArray(BYTE *imageArray, DWORD arraySize) {

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


bool ArgsManager::parseArgs(PDiffCompareParameters* parameters) {
	if ( (!parameters->PathToImageA) && //check for empty filenames 
 			 (!parameters->PathToImageB)) {

			if ((!parameters->ImageA) && (!parameters->ImageB) ) { //check then for empty image bodies
				std::stringstream ss;
				ss << "Neither file name nor images were provided for comparison.\n";
				ErrorStr = ss.str();
				return false;
			}
	}
	FieldOfView = parameters->FieldOfView ? parameters->FieldOfView : FieldOfView;
	Verbose = parameters->Verbose ? parameters->Verbose : Verbose;
	ThresholdPixels = parameters->ThresholdPixels ? parameters->ThresholdPixels : ThresholdPixels;
	Gamma = parameters->Gamma ? parameters->Gamma : Gamma;
	Luminance = parameters->Luminance ? parameters->Luminance : Luminance;
	LuminanceOnly = parameters->LuminanceOnly ? parameters->LuminanceOnly : LuminanceOnly;
	ColorFactor = parameters->ColorFactor ? parameters->ColorFactor : ColorFactor;
	DownSample = parameters->DownSample ? parameters->DownSample : DownSample;
	bool scale = parameters->Scale ? parameters->Scale : false;
  const char* output_file_name = parameters->PathToOutputImage ? parameters->PathToOutputImage : NULL; 

	if ( (parameters->PathToImageA != NULL) &&
 			 (parameters->PathToImageB != NULL)) {

		ImgA = RGBAImage::ReadFromFile(parameters->PathToImageA);
		if (!ImgA) {
			ErrorStr = "FAIL: Cannot open ";
			ErrorStr += parameters->PathToImageA;
			ErrorStr += "\n";
			return false;
		} 

		ImgB = RGBAImage::ReadFromFile(parameters->PathToImageB);
		if (!ImgA) {
			ErrorStr = "FAIL: Cannot open ";
			ErrorStr += parameters->PathToImageB;
			ErrorStr += "\n";
			return false;
		} 
	}
	else {
		if ( (parameters->ImageA != NULL) && (parameters->ImageB!= NULL) ) { 
			ImgA = ReadFromArray(parameters->ImageA, parameters->ImageAsize);
			if (!ImgA) {
				ErrorStr = "FAIL: Cannot open ";
				ErrorStr += parameters->PathToImageB;
				ErrorStr += "\n";
				return false;
			} 
			ImgB = ReadFromArray(parameters->ImageB, parameters->ImageBsize);
			if (!ImgB) {
				ErrorStr = "FAIL: Cannot open ";
				ErrorStr += parameters->PathToImageB;
				ErrorStr += "\n";
				return false;
			} 
		}
	}

	for (int i = 0; i < DownSample; i++) {
		if (Verbose) printf("Downsampling by %d\n", 1 << (i+1));
		RGBAImage *tmp = ImgA->DownSample();
		if (tmp) {
			delete ImgA;
			ImgA = tmp;
		}
		tmp = ImgB->DownSample();
		if (tmp) {
			delete ImgB;
			ImgB = tmp;
		}
	}

	if (scale &&
	    (ImgA->Get_Width() != ImgB->Get_Width() ||
	     ImgA->Get_Height() != ImgB->Get_Height())) {
		int min_width = ImgA->Get_Width();
		if (ImgB->Get_Width() < min_width) {
			min_width = ImgB->Get_Width();
		}

		int min_height = ImgA->Get_Height();
		if (ImgB->Get_Height() < min_height) {
			min_height = ImgB->Get_Height();
		}

		if (Verbose) printf("Scaling to %d x %d\n", min_width, min_height);
		RGBAImage *tmp = ImgA->DownSample(min_width, min_height);
		if (tmp) {
			delete ImgA;
			ImgA = tmp;
		}
		tmp = ImgB->DownSample(min_width, min_height);
		if (tmp) {
			delete ImgB;
			ImgB = tmp;
		}
	}
	if (output_file_name) {
		ImgDiff = new RGBAImage(ImgA->Get_Width(), ImgA->Get_Height(), output_file_name);
	}

	return true;
}


