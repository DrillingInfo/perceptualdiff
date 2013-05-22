#include <stdbool.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "PerceptualDiffWrapper.h"
#include "ArgsManager.h"

bool entryPointTest(char *cImage1path, char *cImage2path) {
	PDiffCompareParameters *params  = malloc(sizeof(PDiffCompareParameters)); 
	memset( params, 0x0, sizeof(PDiffCompareParameters) );
	PDiffCompareResult *result = malloc(sizeof(PDiffCompareResult)) ; 
	memset( result, 0x0, sizeof( PDiffCompareResult ) );

	params->PathToImageA = cImage1path;
	params->PathToImageB = cImage2path;

	bool isDifferent = PDiffCompare(params, result);

	free(result);
	free(params);
	return isDifferent;
}


int main() {   
	char *i1 = "test/Image.jpg";
	char *i2 = "test/ImageBad.jpg";
	bool result = entryPointTest(i1, i2);
	if (result) {
		printf("Images are perceptually indistinguishable\n");		
	}
	else {
		printf("Images are visibly different\n");
	}
  return 0;
}


