#include <string.h>
#include <stdlib.h>
#include "com_drillinginfo_global_test_utils_ImagesComparer.h"
#include "PerceptualDiffWrapper.h"
#include "ArgsManager.h"

JNIEXPORT jboolean JNICALL Java_com_drillinginfo_global_test_utils_ImagesComparer_compare
	(JNIEnv *jenv, jobject obj, jstring jImage1path, jstring jImage2path) {

	PDiffCompareParameters *params  = malloc(sizeof(PDiffCompareParameters)); 
	memset( params, 0x0, sizeof(PDiffCompareParameters) );
	PDiffCompareResult *result = malloc(sizeof(PDiffCompareResult)) ; 
	memset( result, 0x0, sizeof( PDiffCompareResult ) );

	const char *cImage1path = (*jenv)->GetStringUTFChars(jenv, jImage1path, 0);
	const char *cImage2path = (*jenv)->GetStringUTFChars(jenv, jImage2path, 0);
	char *p1 = malloc(strlen(cImage1path) + 1);
	char *p2 = malloc(strlen(cImage2path) + 1);
	strcpy(p1, cImage1path);
	strcpy(p2, cImage2path);
	params->PathToImageA = p1;
	params->PathToImageB = p2;

	bool isDifferent = PDiffCompare(params, result);

	free(result);
	free(params);
	free(p1);
	free(p2);
	(*jenv)->ReleaseStringUTFChars(jenv, jImage1path, cImage1path);
	(*jenv)->ReleaseStringUTFChars(jenv, jImage2path, cImage2path);

	return isDifferent;
}
