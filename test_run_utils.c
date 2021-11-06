#include "test_run_utils.h"

STATUS_T testRunner(TestSuite* suite) {
    CHECK_NOT_NULL(suite);

    STATUS_T finalStatus = STATUS_SUCCESS;
    size_t successfulTests = 0;
    size_t i = 0;
    for(i = 0; i < suite->testArray.elementsCount && finalStatus != STATUS_FATAL; ++i) {
        LOG("Starting setup for %s", suite->testArray.tests[i].name)
        STATUS_T testStatus = STATUS_SUCCESS;
        size_t setupsExecuted = runSetup(suite);
        if (setupsExecuted == suite->setupArray.elementsCount) {
        	LOG("Running test %s", suite->testArray.tests[i].name)
            testStatus = suite->testArray.tests[i].test();
            if (testStatus != STATUS_SUCCESS) {
                LOG_ERROR("Test %s failed", suite->testArray.tests[i].name);
                finalStatus = testStatus;
            } else {
                LOG("Test %s succeeded", suite->testArray.tests[i].name);
                ++successfulTests;
            }
        } else {
            LOG_ERROR("Not all setups executed, skipping test %s and executing teardown for successful setups",
                      suite->testArray.tests[i].name);
            finalStatus = STATUS_FAILURE;
            testStatus = STATUS_FAILURE;
        }
        LOG("Starting teardown for %s", suite->testArray.tests[i].name)
        size_t teardownsExecuted = runTeardown(suite, setupsExecuted);
        if (teardownsExecuted != setupsExecuted) {
            LOG_ERROR("Fatal error: Not all teardowns succeeded, aborting. Actual=%Iu, Expected=%Iu",
                      teardownsExecuted,
                      setupsExecuted);
            finalStatus = STATUS_FATAL;
            if (testStatus == STATUS_SUCCESS) {
                --successfulTests;
            }
        };
    }
    LOG("Finished running tests");
    LOG("Total tests - %Iu", suite->testArray.elementsCount);
    LOG("Tests executed - %Iu", i);
    LOG("Successful tests - %Iu", successfulTests);
    return finalStatus;
}

size_t runSetup(TestSuite* suite) {
	CHECK_NOT_NULL(suite);
    size_t setupsExecuted = 0;
    LOG("Running setup");
    if (suite->setupArray.setups == NULL) {
        LOG("No setup functions found, skipping step");
        return setupsExecuted;
    }
    
    for (setupsExecuted = 0; setupsExecuted < suite->setupArray.elementsCount; ++setupsExecuted) {
        LOG("Running setup function %s", suite->setupArray.setups[setupsExecuted].name);
        int8_t setupSucceeded = suite->setupArray.setups[setupsExecuted].setup();
        if (setupSucceeded != STATUS_SUCCESS) {
            LOG_ERROR("Setup function failed");
            return setupsExecuted;
        }
    }
    
    LOG("Finished setup");
    return setupsExecuted;
}

size_t runTeardown(TestSuite* suite, size_t teardownsToRun) {
	CHECK_NOT_NULL(suite);
    size_t teardownsExecuted = 0;
    if (teardownsToRun > suite->teardownArray.elementsCount) {
        LOG_ERROR("Attempt to execute more teardowns than existing amount. %Iu > %Iu",
                  teardownsToRun,
                  suite->teardownArray.elementsCount);
        return teardownsExecuted;
    }
    LOG("Running teardown");
    if (suite->teardownArray.teardowns == NULL) {
        LOG("No teardown functions found, skipping teardown");
        return teardownsExecuted;
    }
    
    for (teardownsExecuted = 0; teardownsExecuted < teardownsToRun; ++teardownsExecuted) {
    	TeardownIdentifier* currentTeardown = &(suite->teardownArray.teardowns[teardownsToRun - teardownsExecuted - 1]);
        LOG("Running teardown function %s", currentTeardown->name);
        int8_t teardownSucceeded = currentTeardown->teardown();
        if (teardownSucceeded != STATUS_SUCCESS) {
            LOG_ERROR("Teardown function failed");
            return teardownsExecuted;
        }
    }
    
    LOG("Finished teardown");
    return teardownsExecuted;
}
