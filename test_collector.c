#include "test_collector.h"

#define INITIAL_FUNCTION_ARRAY_SIZE (1)
#define MAX_FUNCTION_ARRAY_SIZE (((size_t)-1) / (sizeof(FunctionIdentifier)))

void* getFunction(const char* name) {
    HMODULE dll = GetModuleHandle(NULL);
    void* proc = GetProcAddress(dll, name);
    if (proc == NULL) {
        LOG_ERROR("Failed to find %s", name);
    }
    return proc;
}

STATUS_T addFunctionToArray(FunctionArray* functionArray, const char* name) {
    void* function = getFunction(name);
    if (function == NULL) {
        return STATUS_FAILURE;
    }
    
    if (functionArray->elementsCount >= functionArray->maxSize) {
        size_t newSize = 0;
        if (functionArray->maxSize == 0) {
            newSize = INITIAL_FUNCTION_ARRAY_SIZE;
        } else {
            newSize = functionArray->maxSize * 2;
        }
        if (newSize >= MAX_FUNCTION_ARRAY_SIZE) {
            LOG_ERROR("Can't add to array, new size too big: %Iu", newSize);
            return STATUS_FAILURE;
        }
        functionArray->functions = realloc(functionArray->functions, sizeof(*functionArray->functions) * newSize);
        if (functionArray->functions == NULL) {
            LOG_ERROR("Failed allocating new functions array");
            return STATUS_FAILURE;
        }
        functionArray->maxSize = newSize;
    }
    functionArray->functions[functionArray->elementsCount].name = name;
    functionArray->functions[functionArray->elementsCount].function = function;
    functionArray->elementsCount++;
    return STATUS_SUCCESS;
}

STATUS_T addTest(TestSuite* suite, const char* name) {
	CHECK_NOT_NULL(suite);
    return addFunctionToArray((FunctionArray*)(&(suite->testArray)), name);
}

STATUS_T addSetup(TestSuite* suite, const char* name) {
	CHECK_NOT_NULL(suite);
    return addFunctionToArray((FunctionArray*)(&(suite->setupArray)), name);
}

STATUS_T addTeardown(TestSuite* suite, const char* name) {
	CHECK_NOT_NULL(suite);
    return addFunctionToArray((FunctionArray*)(&(suite->teardownArray)), name);
}

STATUS_T parseArguments(TestSuite* suite, int argc, const char** argv) {
	CHECK_NOT_NULL(suite);
    int32_t i = 0;
    const char* currentArgument = NULL;
    const char* currentName = NULL;
    
    LOG("Parsing arguments");
    
    for (i = 1; i < argc; ++i) {
        currentArgument = argv[i];
        currentName = currentArgument + 1;
        
        switch(currentArgument[0]) {
        case COMMAND_LINE_TEST_PREFIX:
            LOG("Found test %s", currentName);
            if (addTest(suite, currentName) != STATUS_SUCCESS) {
                LOG_ERROR("Failed adding test %s", currentName);
                return STATUS_FAILURE;
            };
            break;
        case COMMAND_LINE_SETUP_PREFIX:
            LOG("Found setup %s", currentName);
            if (addSetup(suite, currentName) != STATUS_SUCCESS) {
                LOG_ERROR("Failed adding setup %s", currentName);
                return STATUS_FAILURE;
            };
            break;
        case COMMAND_LINE_TEARDOWN_PREFIX:
            LOG("Found teardown %s", currentName);
            if (addTeardown(suite, currentName) != STATUS_SUCCESS) {
                LOG_ERROR("Failed adding teardown %s", currentName);
                return STATUS_FAILURE;
            };
            break;
        default:
            LOG_ERROR("Unrecognized argument %s", currentArgument);
            return STATUS_FAILURE;
        }
    }
    
    LOG("Finished parsing arguments");
    return STATUS_SUCCESS;
}

STATUS_T validateTestSuite(TestSuite* suite) {
	CHECK_NOT_NULL(suite);
	if (suite->testArray.elementsCount == 0) {
		LOG_ERROR("No tests supplied");
		return STATUS_FATAL;
	}

    if (suite->setupArray.elementsCount != suite->teardownArray.elementsCount) {
        LOG_ERROR("Mismatch in number of setup functions (%Iu) and teardown functions (%Iu)",
                  suite->setupArray.elementsCount,
                  suite->teardownArray.elementsCount);
        return STATUS_FATAL;
    }
    
    // TODO: Validate matching names in the same indexes
    return STATUS_SUCCESS;
}
