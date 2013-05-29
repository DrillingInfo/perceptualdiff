#include "ArgsManager.h"
/* This header can be read by both C and C++ compilers */
#ifndef PerceptualDiffWrapper_H
#define PerceptualDiffWrapper_H

#ifdef __cplusplus
extern "C" {
	int PDiffCompare(PDiffCompareParameters* parameters, PDiffCompareResult* result);
#endif

#ifdef __cplusplus
}
#endif

#endif /*PerceptualDiffWrapper_H*/

