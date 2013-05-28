#include "ArgsManager.h"
/* This header can be read by both C and C++ compilers */
#ifndef PerceptualDiffWrapper_H
#define PerceptualDiffWrapper_H

enum conclusion {
  IMAGES_EQUAL = 0,
  IMAGES_DIFFERENT = 1,
	COMPARISON_ERROR = 2
} CONCLUSION;

#ifdef __cplusplus
extern "C" {
	int PDiffCompare(PDiffCompareParameters* parameters, PDiffCompareResult* result);
#endif

#ifdef __cplusplus
}
#endif

#endif /*PerceptualDiffWrapper_H*/

