#include "defs.h"
#include "test_collector.h"
#include "test_run_utils.h"

STATUS_T setupEnvironment() {
    if (setvbuf(stdout, NULL, _IONBF, 0) != 0) {
        LOG_ERROR("setvbuf failed on stdout");
        return STATUS_FAILURE;
    };

    if (setvbuf(stderr, NULL, _IONBF, 0) != 0) {
        LOG_ERROR("setvbuf failed on stderr");
        return STATUS_FAILURE;
    };
    return STATUS_SUCCESS;
}

int main(int argc, char** argv) {
    if (setupEnvironment() != STATUS_SUCCESS) {
        LOG_ERROR("Environment setup failed");
        return 1;
    }

    TestSuite suite = { EMPTY_FUNCTIONS_ARRAY, EMPTY_FUNCTIONS_ARRAY, EMPTY_FUNCTIONS_ARRAY };

    if (parseArguments(&suite, argc, (const char**)argv) != STATUS_SUCCESS) {
        LOG_ERROR("Failed parsing arguments");
        // Not returning because we need to destroy the test suite
        goto cleanup;
    }

    if (validateTestSuite(&suite) != STATUS_SUCCESS) {
        LOG_ERROR("Failed to validate test suite");
        // Not returning because we need to destroy the test suite
        goto cleanup;
    }
    if (testRunner(&suite) != STATUS_SUCCESS) {
        LOG_ERROR("Test runner failed");
    }
    
cleanup:
    if (destroyTestSuite(&suite) != STATUS_SUCCESS) {
        LOG_ERROR("destroyTestSuite failed, nothing to do");
    }
    return 0;
}
