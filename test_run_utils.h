#ifndef _TEST_RUN_UTILS_H
#define _TEST_RUN_UTILS_H
#include "defs.h"

/**
 * @brief The main logic of running tests with their setup and teardown
 *
 * @param suite The TestSuite to run
 */
STATUS_T testRunner(TestSuite* suite);

/**
 * @brief Run all the setups of the suite
 *
 * @param suite The TestSuite to run setups from
 * @returns The amount of setups successfully executed
 * @note If the return value doesnt equal the amount of setup it means a setup has failed
 */
size_t runSetup(TestSuite* suite);

/**
 * @brief Run the requested amount of teardowns from the suite, in reverse order
 * @note This function expects that matching setup and teardown will appear in the same index
 *
 * @param suite The TestSuite to run teardowns from
 * @param teardownsToRun The number of teardowns to execute
 * @returns The amount of teardowns successfully executed
 * @note If the return value doesnt equal teardownsToRun it means a teardown has failed
 */
size_t runTeardown(TestSuite* suite, size_t teardownsToRun);

#endif // _TEST_RUN_UTILS_H