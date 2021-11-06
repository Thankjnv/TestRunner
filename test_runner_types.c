#include "test_runner_types.h"

void destroyFunctionArray(FunctionArray* functionArray) {
    if (functionArray->functions) {
        free(functionArray->functions);
        functionArray->functions = NULL;
        functionArray->elementsCount = 0;
        functionArray->maxSize = 0;
    }
}

STATUS_T destroyTestSuite(TestSuite* suite) {
	CHECK_NOT_NULL(suite);
    destroyFunctionArray((FunctionArray*)(&(suite->setupArray)));
    destroyFunctionArray((FunctionArray*)(&(suite->teardownArray)));
    destroyFunctionArray((FunctionArray*)(&(suite->testArray)));
    return STATUS_SUCCESS;
}
