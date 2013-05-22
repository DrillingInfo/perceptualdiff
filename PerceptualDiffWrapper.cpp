#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include "PerceptualDiffWrapper.h"
#include "Metric.h"
#include "ArgsManager.h"


extern "C" bool PDiffCompare(PDiffCompareParameters* parameters, PDiffCompareResult* result) {
	ArgsManager args;
	if (!args.parseArgs(parameters)) {
	 //  print error message about arguments
		printf("not enoght arguments\n");	
	}
	const bool passed = Yee_Compare(args);
	result->ErrorBuffer = (char*)args.ErrorStr.c_str();
	result->ErrorBufferSize = strlen(args.ErrorStr.c_str()) + 1;
	if (passed) {
		//we need to extract the number of 'failred' pexels from
		//the error message - args.ErrorStr
		std::string searchPhrase = " pixels are different";
		int startPos = args.ErrorStr.find_first_of('\n') + 1;
		int endPos = args.ErrorStr.find(searchPhrase);
		std::string diffPixelsStr = args.ErrorStr.substr(startPos, endPos - startPos);	
		result->PixelsDifferent = atoi(diffPixelsStr.c_str());
	}
	return passed;
}
