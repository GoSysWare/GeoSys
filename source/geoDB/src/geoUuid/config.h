


#define HAVE_STDINT_H
#define HAVE_INTTYPES_H
//#define HAVE_SRANDOM
#define HAVE_UNISTD_H




#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;

typedef unsigned int mode_t;

#define _CRT_RAND_S
#endif

#ifndef _SUSECONDS_T
#define _SUSECONDS_T
typedef long useconds_t; /* signed # of microseconds */
#endif  /* _SUSECONDS_T */



//#define _CRT_SECURE_NO_DEPRECATE
//#define _CRT_NONSTDC_NO_WARNINGS
//
//
//#define _CRT_SECURE_NO_WARNINGS


#define HAVE_ERR
#define HAVE_ERRX
#define HAVE_WARN
#define HAVE_WARNX