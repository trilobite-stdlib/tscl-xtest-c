/*  ----------------------------------------------------------------------------
    File: xtest.c

    Description:
    This source file contains the code entry point for the Trilobite Stdlib project.
    It demonstrates the usage of various utilities and functions provided by the
    Trilobite Stdlib to enhance software development.

    Author: Michael Gene Brockus (Dreamer)
    Email: michaelbrockus@gmail.com
    Website: [Trilobite Coder Blog](https://trilobite.code.blog)

    Project: Trilobite Stdlib

    License: Apache License 2.0
    SPDX Identifier: Apache-2.0

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0.

    Unless required by applicable law or agreed to in writing, software distributed under the License
    is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
    or implied. See the License for the specific language governing permissions and limitations
    under the License.

    Please review the full text of the Apache License 2.0 for the complete terms and conditions.

    (Apache License 2.0: http://www.apache.org/licenses/LICENSE-2.0)
    ----------------------------------------------------------------------------
*/
#include "trilobite/xtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ANSI escape code macros for text color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct {
    bool cutback;
    bool verbose;
    bool version;
    bool colored;
    bool dry_run;
    bool only_test;
    bool only_bench;
    bool help;
    bool repeat;
    int iter_repeat;
} XParser;

// Global XParser variable
XParser xcli;

// config file name for XParser config
static char CONFIG_FILENAME[555];

// Extra
const char *XTEST_VERSION = "0.5.1";

// Static control panel for assert/expect and marks
static bool XEXPECT_PASS_SCAN = true;
static bool XASSERT_PASS_SCAN = true;
static bool XIGNORE_TEST_CASE = false;

// Output for XUnit Test Case Assert/Expect.
static void xtest_output_xassert_expect(bool expression, const char *message, const char *assert_type,
                                        const char *file, int line, const char *func) {
    const char *color_start = xcli.colored ? ANSI_COLOR_BLUE : "";
    const char *color_reset = xcli.colored ? ANSI_COLOR_RESET : "";
    const char *color_fail = xcli.colored ? ANSI_COLOR_RED : "";
    const char *color_pass = xcli.colored ? ANSI_COLOR_GREEN : "";

    printf("%s", color_start);
    if (xcli.verbose && !xcli.verbose) {
        printf("[%s assumtion ]" ANSI_COLOR_RESET "\n%sline: %.4i\nfile: %s\nfunc: %s\n", assert_type, color_fail, line, file, func);
        printf("%smessage: %s\nresult: %s\n", color_fail, message, expression ? "PASS" : "FAIL");
    } else if (xcli.cutback && !xcli.verbose) {
        printf("%s[O]", (expression ? color_pass : color_fail));
    } else if (xcli.cutback && xcli.verbose) {
        printf("%smessage: %s\nresult: %s\n", color_fail, message, expression ? "PASS" : "FAIL");
    }
    printf("%s", color_reset);
} // end of func

// Output for XUnit Test Case Ignored.
static void xtest_output_xignore(const char *reason, const char *file, int line, const char *func) {
    const char *color_start = xcli.colored ? ANSI_COLOR_BLUE : "";
    const char *color_reset = xcli.colored ? ANSI_COLOR_RESET : "";
    const char *color_yellow = xcli.colored ? ANSI_COLOR_YELLOW : "";

    printf("%s", color_start);
    if (xcli.verbose && !xcli.cutback) {
        puts("[ assumtion skipped ]" ANSI_COLOR_RESET);
        printf("%sline: %.4i\nfile: %s\nfunc: %s\n", color_yellow, line, file, func);
        printf("%smessage: %s\n", color_yellow, reason);
    } else if (xcli.cutback && !xcli.verbose) {
        printf("%s", XIGNORE_TEST_CASE ? ANSI_COLOR_YELLOW "[I]" : ANSI_COLOR_RED "[X]");
    } else if (xcli.cutback && xcli.verbose) {
        printf("%smessage: %s\n", color_yellow, reason);
    }
    printf("%s", color_reset);
} // end of func

// Formats and displays information about the start/end of a test case.
static void xtest_output_xunittest_format(bool is_start, XTestCase *test_case, XTestStats *stats) {
    const char *color_start = xcli.colored ? ANSI_COLOR_BLUE : "";
    const char *color_reset = xcli.colored ? ANSI_COLOR_RESET : "";

    if (is_start) {
        printf("%s", color_start);
        if (xcli.verbose && !xcli.cutback) {
            puts("[Running Test Case]" ANSI_COLOR_RESET);
            printf("name  : %s\nnumber: %.4i\ntype: %s\n", test_case->name, stats->total_count + 1, !test_case->is_benchmark ? "Unit test" : "Benchmark");
        } else if (xcli.cutback && !xcli.verbose) {
            printf("name: %s, type: %s\n", test_case->name, !test_case->is_benchmark ? "unit" : "mark");
        } else {
            printf("name  : %s\nnumber: %.4i\ntype: %s\n", test_case->name, stats->total_count + 1, !test_case->is_benchmark ? "Unit test" : "Benchmark");
        }
        printf("%s", color_reset);
    } else if (!is_start) {
        printf("%stime: %.6lu \n", color_start, test_case->elapsed_time);
        if (xcli.verbose && !xcli.cutback) {
            printf("ignore: %s\n", test_case->ignored ? "yes" : "no");
            if (xcli.colored) {
                puts("[Current unit done]\n\n" ANSI_COLOR_RESET);
            } else {
                puts("[Current unit done]\n\n");
            }
        } else if (xcli.cutback && !xcli.verbose) {
            printf("\n");
        } else {
            printf("ignore: %s\n", test_case->ignored ? "yes" : "no");
        }
        printf("%s", color_reset);
    }
} // end of func

// Output for XUnit Test Case Report.
static void xtest_output_xunittest_report(XUnitRunner *runner) {
    const char *color_start = xcli.colored ? ANSI_COLOR_BLUE : "";
    const char *color_reset = xcli.colored ? ANSI_COLOR_RESET : "";

    printf("%s[Xtest report system]\n%s", color_start, color_reset);
    if (!xcli.verbose && xcli.cutback) {
        printf("result: %s", runner->stats.failed_count? "fail" : "pass");
    } else if (xcli.verbose && !xcli.cutback) {
        printf("pass: %.3i, fail: %.3i, skip: %.3i, total: %.3i",
                runner->stats.passed_count, runner->stats.failed_count,
                runner->stats.ignored_count, runner->stats.total_count);
    } else {
        printf("pass: %.3i, fail: %.3i", runner->stats.passed_count, runner->stats.failed_count);
    }
    printf("%s\n", color_reset);
} // end of func

static void xparser_init(void) {
    // Initialize members individually
    xcli.cutback = false;
    xcli.verbose = false;
    xcli.version = false;
    xcli.colored = false;
    xcli.dry_run = false;
    xcli.help    = false;
    xcli.repeat  = false;
    xcli.only_test = false;
    xcli.only_bench = false;
} // end of func

// Prints usage instructions, including custom options, for a command-line program.
static void xparser_print_usage(void) {
    puts("Usage: Xtest.cli [options]");
    puts("Options:");
    puts("  --help        Display this help message");
    puts("  --version     Display program version");
    puts("  --config FILE Load configuration from FILE");
    puts("  --only-test   Run only test cases");
    puts("  --only-mark   Run only benchmark cases");
    puts("  --cutback     Enable cutback mode");
    puts("  --verbose     Enable verbose mode");
    puts("  --colored     Enable colored output");
    puts("  --repeat N    Repeat the test N times (requires a numeric argument)");
} // end of func

// Add this function to parse the config file
static void xparser_parse_config_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // TODO: must resolve issue to make load config feature work, fails upon opening almost there
        fprintf(stderr, "Error: Could not open config file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    // Read the file line by line and update XParser accordingly
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char key[256], value[256];
        if (sscanf(line, "%255[^=]=%255[^\n]", key, value) == 2) {
            // Update XParser members based on key-value pairs
            if (strcmp(key, "cutback") == 0) {
                xcli.cutback     = (strcmp(value, "true") == 0) ? true : false;
            } else if (strcmp(key, "verbose") == 0) {
                xcli.verbose     = (strcmp(value, "true") == 0) ? true : false;
            } else if (strcmp(key, "colored") == 0) {
                xcli.colored     = (strcmp(value, "true") == 0) ? true : false;
            } else if (strcmp(key, "dry_run") == 0) {
                xcli.dry_run     = (strcmp(value, "true") == 0) ? true : false;
            } else if (strcmp(key, "only_mark") == 0) {
                xcli.only_bench  = (strcmp(value, "true") == 0) ? true : false;
            } else if (strcmp(key, "only_test") == 0) {
                xcli.only_test   = (strcmp(value, "true") == 0) ? true : false;
            } else if (strcmp(key, "repeat") == 0) {
                xcli.repeat      = (strcmp(value, "true") == 0) ? true : false;
            } else if (strcmp(key, "iter_repeat") == 0) {
                xcli.iter_repeat = atoi(value);
            }
            // Add more options as needed
        }
        if (xcli.only_bench && xcli.only_test) {
            // Turn both off and run all test anyway
            xcli.only_bench = xcli.only_test = false;
        }
    }

    fclose(file);
} // end of func

static void xparser_parse_args(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--dry-run") == 0) {
            xcli.dry_run = true;
        } else if (strcmp(argv[i], "--cutback") == 0) {
            xcli.cutback = true;
        } else if (strcmp(argv[i], "--verbose") == 0) {
            xcli.verbose = true;
        } else if (strcmp(argv[i], "--only-test") == 0) {
            xcli.only_test = true;
        } else if (strcmp(argv[i], "--only-mark") == 0) {
            xcli.only_bench = true;
        } else if (strcmp(argv[i], "--version") == 0) {
            xcli.version = true;
            puts(XTEST_VERSION);
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "--colored") == 0) {
            xcli.colored = true;
        } else if (strcmp(argv[i], "--help") == 0) {
            xcli.help = true;
            xparser_print_usage();
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "--repeat") == 0) {
            xcli.repeat = true;
            if (++i < argc) {
                int iter_repeat = atoi(argv[i]);
                if (iter_repeat >= 1 && iter_repeat <= 100) {
                    xcli.iter_repeat = iter_repeat;
                } else {
                    fprintf(stderr, "Error: --repeat value must be between 1 and 100.\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "Error: --repeat option requires a numeric argument.\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "--config") == 0) {
            // Process the --config option and the next argument should be the filename
            if (++i < argc) {
                // Check if the specified file name is "xtest_config.ini"
                if (strcmp(argv[i], "xtest_config.ini") == 0) {
                    strncpy(CONFIG_FILENAME, argv[i], sizeof(CONFIG_FILENAME) - 1);
                    CONFIG_FILENAME[sizeof(CONFIG_FILENAME) - 1] = '\0';
                } else {
                    fprintf(stderr, "Error: Configuration file must be named 'xtest_config.ini'.\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "Error: --config option requires a file argument.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    // If a config file is specified, parse it
    if (CONFIG_FILENAME[0] != '\0') {
        xparser_parse_config_file(CONFIG_FILENAME);
    }
} // end of func

// Initializes an XUnitRunner and processes command-line arguments.
XUnitRunner xtest_start(int argc, char **argv) {
    XUnitRunner runner;
    xparser_init();
    xparser_parse_args(argc, argv);

    runner.stats = (XTestStats){0, 0, 0, 0};

    if (xcli.dry_run) { // Check if it's a dry run
        printf("Simulating a test run to ensure Xcli can run...\n");
        exit(xtest_end(&runner)); // Exit the program
    }

    return runner;
} // end of func

// Finalizes the execution of a Trilobite XUnit runner and displays test results.
int xtest_end(XUnitRunner *runner) {
    if (!xcli.dry_run) {
        xtest_output_xunittest_report(runner);
    }
    return runner->stats.failed_count;
} // end of func

// Common functionality for running a test case and updating test statistics.
void xtest_run_test(XTestCase* test_case, XTestStats* stats, XTestFixture* fixture) {
    xtest_output_xunittest_format(true, test_case, stats);

    // Check if the test should be ignored
    if (XIGNORE_TEST_CASE || (xcli.only_test && test_case->is_benchmark) || (xcli.only_bench && !test_case->is_benchmark)) {
        // Skip the test if it doesn't match the desired type
        stats->ignored_count++;
        XIGNORE_TEST_CASE = false;
        test_case->ignored = true;
        return;
    }

    // Record start time
    clock_t start_time = clock();

    // Run tests sequentially
    for (int iter = 0; iter < xcli.iter_repeat; iter++) {
        // Execute setup function if provided
        if (fixture && fixture->setup) {
            fixture->setup();
        }

        // Run the actual test function
        test_case->test_function();

        // Execute teardown function if provided
        if (fixture && fixture->teardown) {
            fixture->teardown();
        }
    }

    // Record end time
    clock_t end_time = clock();

    // Calculate elapsed time and store it in the test case
    test_case->elapsed_time = end_time - start_time;

    // Update the appropriate count based on your logic
    if (!XEXPECT_PASS_SCAN || !XASSERT_PASS_SCAN) {
        // If any expectations fail, consider the test as failed
        stats->failed_count++;
    } else {
        stats->passed_count++;
    }
    stats->total_count++;

    // Output test format information
    xtest_output_xunittest_format(false, test_case, stats);
} // end of func

// Runs a test case and updates test statistics.
void xtest_run_test_unit(XTestCase* test_case, XTestStats* stats) {
    // Initialize the test as not ignored
    test_case->ignored = false;

    // Run the test
    xtest_run_test(test_case, stats, NULL);
} // end of func

// Runs a test case within a test fixture and updates test statistics.
void xtest_run_test_fixture(XTestCase* test_case, XTestFixture* fixture, XTestStats* stats) {
    // Initialize the test as not ignored
    test_case->ignored = false;

    // Run the test with the specified fixture
    xtest_run_test(test_case, stats, fixture);
}  // end of func

// Marks a test case as ignored with a specified reason and prints it to stderr.
void xignore(const char* reason, const char* file, int line, const char* func) {
    XIGNORE_TEST_CASE = true;
    xtest_output_xignore(reason, file, line, func);
} // end of func

// Custom assertion function with optional message.
void xassert(bool expression, const char *message, const char* file, int line, const char* func) {
    if (!XASSERT_PASS_SCAN) {
        return;
    } else if (!expression) {
        XASSERT_PASS_SCAN = false;
    }
    xtest_output_xassert_expect(expression, message, "Assert", file, line, func);
} // end of func

// Custom expectation function with optional message.
void xexpect(bool expression, const char *message, const char* file, int line, const char* func) {
    XEXPECT_PASS_SCAN = true;

    if (!expression) {
        XEXPECT_PASS_SCAN = false;
    }
    xtest_output_xassert_expect(expression, message, "Expect", file, line, func);
} // end of func
