/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.code.blog>
*/
#ifndef TRILOBITE_XTEST_H
#define TRILOBITE_XTEST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "xassert.h"

/**
    @param passed_count: the number of tests that have passed
    @param failed_count: the number of tests that have failed
    @param run_tag: a tag that identifies the test run
    @returns XUnitRunner: a struct that contains the test results
*/
typedef struct {
    int passed_count;
    int failed_count;
    char *run_tag;
} XUnitRunner;

/**
    @param XBench - Structure containing the benchmark name, benchmark function, setup function, teardown function, and elapsed time.
    @returns The elapsed time of the benchmark.
*/
typedef struct {
    const char *name;
    void (*benchmark_function)(void);
    void (*setup_function)(void);
    void (*teardown_function)(void);
    clock_t elapsed_time;
} XBench;


/**
    This is the definition of an XTestCase structure.

    @param name: A pointer to a constant character string that holds the name of the test case.
    @param test_function: A pointer to a function that holds the actual test code.
    @param setup_function: A pointer to a function that is used to setup the test, usually used to initialize variables and resources that are needed for the test.
    @param teardown_function: A pointer to a function that is used to clean up after the test, usually used to free resources allocated during the setup_function.
    @param assertions: A pointer to an array of XAssert structures that hold the assertions used in the test.
    @param num_assertions: An integer that holds the number of assertions in the assertions array.

    @returns: The XTestCase structure that holds the information about the test case.
*/
typedef struct {
    const char *name;
    void (*test_function)(void);
    void (*setup_function)(void);
    void (*teardown_function)(void);
    XAssert *assertions;
    size_t num_assertions;
} XTestCase;

/**
    This code defines a test case for the framework with the given name.

    @param name: The name of the test case
    @returns: A XTestCase structure with the given name and the test function pointer
              set to the function with the same name as the given name.
*/
#define XTEST_CASE(name) \
    void name##_test_func(void); \
    XTestCase name = { #name, name##_test_func, NULL, NULL, NULL, 0 }; \
    void name##_test_func(void)

/**
    This code defines a XBench structure which can be used to benchmark functions.

    @param name: The name of the function to be benchmarked
    @returns: The XBench structure with the function name, the benchmark function, and
              other necessary details for the benchmarking process.
*/
#define XBENCH(name) \
    void name##_benchmark_function(void); \
    XBench name = { #name, name##_benchmark_function, NULL, NULL, 0 }; \
    void name##_benchmark_function(void)

//
// Helper function to run a test case
//

XUnitRunner xtest_start(int argc, char **argv);
int xtest_end(XUnitRunner *runner);
void xtest_run(XTestCase *test_case, XUnitRunner *runner);
void xbench_run(XBench *benchmark, XUnitRunner *runner);

#ifdef __cplusplus
}
#endif

#endif
