#ifndef _TEST_COLLECTOR_H
#define _TEST_COLLECTOR_H
#include "defs.h"

#define COMMAND_LINE_TEST_PREFIX 'T'
#define COMMAND_LINE_SETUP_PREFIX 'U'
#define COMMAND_LINE_TEARDOWN_PREFIX 'D'

/**
 * @brief Get function from the current module by name
 *
 * @param name The name of the function
 * @returns The function's address if it was found, NULL on failure
 */
void* getFunction(const char* name);

/**
 * @brief Find the function "name" and add it to "functionArray"
 * @note The array of FunctionArray is enlarged if necessary
 * 
 * @param functionArray The FunctionArray to add the function to
 * @param name The name of the function to add
 */
STATUS_T addFunctionToArray(FunctionArray* functionArray, const char* name);

/**
 * @brief Add a test to the suite
 *
 * @param suite The TestSuite to add the test to
 * @param name The name of the test
 */
STATUS_T addTest(TestSuite* suite, const char* name);

/**
 * @brief Add a setup to the suite
 *
 * @param suite The TestSuite to add the setup to
 * @param name The name of the setup
 */
STATUS_T addSetup(TestSuite* suite, const char* name);

/**
 * @brief Add a teardown to the suite
 *
 * @param suite The TestSuite to add the teardown to
 * @param name The name of the teardown
 */
STATUS_T addTeardown(TestSuite* suite, const char* name);

/**
 * @brief Parse the arguments into suite
 *
 * @param suite [OUT] The TestSuite to fill
 * @param argc The amount of elemnts in argv
 * @param argv The arguments for the program. The first letter ('T', 'U' or 'D')
 *             is the type and following it is the name of the function
 */
STATUS_T parseArguments(TestSuite* suite, int argc, const char** argv);

/**
 * @brief Validate that the suite is in a valid state for test running
 *
 * @param suite The TestSuite to validate
 */
STATUS_T validateTestSuite(TestSuite* suite);

#endif // _TEST_COLLECTOR_H