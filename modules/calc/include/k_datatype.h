#ifndef k_datatype_h
#define k_datatype_h

#include <opencv2/opencv.hpp>
// #ifdef __cplusplus
// extern "C" {
// #endif

#define PMC_OK 0
#define PMC_FAIL 1

#define PL_TRUE 1
#define PL_FALSE 0



typedef int Bool;
typedef unsigned short Word;
typedef int Int;
typedef float Real;
typedef double LReal;
typedef double Time;
typedef cv::Mat CvMat;
typedef std::string String;

typedef void**  Any;

// #ifdef __cplusplus
// }
// #endif
#endif
