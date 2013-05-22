------------------
**PerceptualDiff** is a library that compares two images using a perceptually based image metric.<br>
Originally comes from 
<a href="https://github.com/myint/perceptualdiff">https://github.com/myint/perceptualdiff</a>

------------------
# C/C++ #
Because originally **PerceptualDiff** distributes like a standalone application we've made a wraper :
**PerceptualDiffWrapper.cpp**. It provides  a function 

    extern "C" bool PDiffCompare(PDiffCompareParameters* parameters, PDiffCompareResult* result)

it takes two parameters - pointers to structures (see ArgsManager.cpp)
Also it can be called from pure C.

For build a library use follow commands:<br>    


    g++ -c -fPIC PerceptualDiffWrapper.cpp ArgsManager.cpp CompareArgs.cpp LPyramid.cpp Metric.cpp RGBAImage.cpp
    gcc -c -fPIC -I$JAVA_HOME/include -I$JAVA_HOME/include/linux JNIperceptualDiff.c
    gcc -shared -fPIC PerceptualDiffWrapper.o ArgsManager.o CompareArgs.o LPyramid.o Metric.o RGBAImage.o JNIperceptualDiff.o -L. libfreeimage.so.3 -o libPdiff.so

They make a **libPdiff.so** that can be used letter, like this for example:

    gcc -fPIC -o test_main test_main.c libPdiff.so -Werror

This command makes an executable `test_main` that tests the entry point to PerceptualDiffWrapper.
Don't forget to run<br> 

    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

**libfreeimage.so.3** is a common library that contains image routines, I put it here for convenient build.

# Java	 #
Java class should has a name <br>
**com.drillinginfo.global.test.utils.ImageDiff**<br>
and has a method

    public boolean compare(byte[] imag1, byte[] image2)
it takes two files represented by byte arrays, calls perceptualDiff native function for compare and returns result : are given images visibly different or not.

The package name and class name could be other but in that case you need to rebuild a header file `com_drillinginfo_global_content_utils_ImageDiff.h` and to change the entry point method in **JNIperceptualDiff.c** according to JNI specification.
