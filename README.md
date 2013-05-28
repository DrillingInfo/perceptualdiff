# Changes #
------------------
Added a wrapper for use **PerceptualDiff** functional as a library.<br>
Call a method `int PDiffCompare(PDiffCompareParameters* parameters, PDiffCompareResult* result);` <br>
from `PerceptualDiffWrapper`<br>
It compares given images and returns int value as a conclusion (see `PerceptualDiffWrapper.h`).<br>
Also added the ability to pass buffers of images instead of names of files :
struct PDiffCompareParameters contains appropriate fields:

	unsigned char *ImageA;  // Image A
	unsigned char *ImageB;  // Image B
	uint32_t ImageAsize;  // Image A length
	uint32_t ImageBsize;  // Image B length


------------------
# Build Instructions #
For build use the same CMake script (see original `README.rst`), now it also creates a `Pdiff` library that can be used later.
Also it may be called from pure C.
