/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.code.blog>
*/
#ifndef TRILOBITE_XBDD_H
#define TRILOBITE_XBDD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "xtest.h"

// Define macros for BDD structure
#define GIVEN(description) \
    if (1) { \
        printf("Given %s\n", description); \
        static bool givenExecuted = true; \
        (void)givenExecuted; \
    } else

#define WHEN(description) \
    if (1) { \
        static bool whenExecuted = true; \
        if (!givenExecuted || whenExecuted) { \
            fprintf(stderr, "Error: Invalid use of WHEN\n"); \
        } else { \
            printf("When %s\n", description); \
            whenExecuted = true; \
        } \
    } else

#define THEN(description) \
    if (1) { \
        static bool thenExecuted = true; \
        if (!givenExecuted || !whenExecuted || thenExecuted) { \
            fprintf(stderr, "Error: Invalid use of THEN\n"); \
        } else { \
            printf("Then %s\n", description); \
            thenExecuted = true; \
        } \
    } else

#ifdef __cplusplus
}
#endif

#endif