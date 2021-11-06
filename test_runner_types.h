#ifndef _TEST_RUNNER_TYPES_H
#define _TEST_RUNNER_TYPES_H
#include "defs.h"

#define EMPTY_FUNCTIONS_ARRAY {0, 0, NULL}

typedef STATUS_T (*TestCase)(void);
typedef STATUS_T (*TestSetup)(void);
typedef STATUS_T (*TestTeardown)(void);

/**
 * This is the generic function identifier and dynamic array for functions
 * Used to allow unified work with the different function types in the suite
 */
typedef struct FunctionIdentifier {
    const char* name;
    void* function;
} FunctionIdentifier;

typedef struct FunctionArray {
    size_t elementsCount;
    size_t maxSize;
    FunctionIdentifier* functions;
} FunctionArray;

/**
 * Specialized for test
 */
typedef struct TestIdentifier {
    const char* name;
    TestCase test;
} TestIdentifier;

typedef struct TestArray {
    size_t elementsCount;
    size_t maxSize;
    TestIdentifier* tests;
} TestArray;

/**
 * Specialized for setup
 */
typedef struct SetupIdentifier {
    const char* name;
    TestSetup setup;
} SetupIdentifier;

typedef struct SetupArray {
    size_t elementsCount;
    size_t maxSize;
    SetupIdentifier* setups;
} SetupArray;

/**
 * Specialized for teardown
 */
typedef struct TeardownIdentifier {
    const char* name;
    TestTeardown teardown;
} TeardownIdentifier;

typedef struct TeardownArray {
    size_t elementsCount;
    size_t maxSize;
    TeardownIdentifier* teardowns;
} TeardownArray;


/**
 * Holds the entire data about the tests to run - setup, tests and teardown
 */
typedef struct TestSuite {
    SetupArray setupArray;
    TeardownArray teardownArray;
    TestArray testArray;
} TestSuite;

/**
 * @brief Destroy "functionArray" and free the memory it uses
 * @note You mustn't use "functionArray" after this function returns
 *
 * @param functionArray The FunctionArray to destroy
 */
void destroyFunctionArray(FunctionArray* functionArray);

/**
 * @brief Destory "suite" and free the memory it uses
 * @note You mustn't use "suite" after this function returns
 *
 * @param suite The TestSuite to destroy
 */
STATUS_T destroyTestSuite(TestSuite* suite);

#endif // _TEST_RUNNER_TYPES