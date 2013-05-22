#include <stdbool.h> 

#ifndef __ArgsManager_h_included_
#define __ArgsManager_h_included_

#ifdef __cplusplus
	#include "CompareArgs.h"
	extern "C" {
#endif
		typedef struct tagPDiffCompareResult {
					unsigned int PixelsDifferent;
					char* ErrorBuffer;
					unsigned int ErrorBufferSize;
			} PDiffCompareResult;

			typedef struct tagPDiffCompareParameters {
				char *PathToImageA;  // Image A
				char *PathToImageB;  // Image B
				char *PathToOutputImage;  // Diff image
				bool Verbose;  // Print lots of text or not
				bool LuminanceOnly;  // Only consider luminance; ignore chroma channels in the comparison.
				bool Scale;         // Scale images to match each other's dimensions.
				float FieldOfView;  // Field of view in degrees
				float Gamma;  // The gamma to convert to linear color space
				float Luminance;  // the display's luminance
				unsigned int ThresholdPixels;  // How many pixels different to ignore
			
				// How much color to use in the metric.
				// 0.0 is the same as LuminanceOnly = true,
				// 1.0 means full strength.
				float ColorFactor;

				// How much to down sample image before comparing, in powers of 2.
				int DownSample;
			} PDiffCompareParameters;

#ifdef __cplusplus
		class ArgsManager : public CompareArgs {
		public:
			ArgsManager();
			~ArgsManager();
			bool parseArgs(PDiffCompareParameters* parameters);
		};
#endif
#ifdef __cplusplus
		}
#endif
#endif
