#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include "PerceptualDiffWrapper.h"
#include "Metric.h"
#include "ArgsManager.h"

enum conclusion {
  IMAGES_EQUAL = 0,
  IMAGES_DIFFERENT = 1,
	COMPARISON_ERROR = 2
} CONCLUSION;


void copyErrorBuffer(ArgsManager &args, PDiffCompareResult* result) {
	strncpy(result->ErrorBuffer, args.ErrorStr.c_str(), result->ErrorBufferSize);
	if (result->ErrorBufferSize) {
		  result->ErrorBuffer[result->ErrorBufferSize - 1] = '\0';
	}
}

extern "C" int PDiffCompare(PDiffCompareParameters* parameters, PDiffCompareResult* result) {
	ArgsManager args;
	if (!args.parseArgs(parameters)) {
		result->conclusion = COMPARISON_ERROR;		
		copyErrorBuffer(args, result);
		return result->conclusion;
	}

	const bool passed = Yee_Compare(args);
	copyErrorBuffer(args, result);

	if (passed) {
		result->conclusion = IMAGES_EQUAL;		
	}
	else {
		result->conclusion = IMAGES_DIFFERENT;		
	}
	return result->conclusion;
}
