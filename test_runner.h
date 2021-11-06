#ifndef _TEST_RUNNER_H
#define _TEST_RUNNER_H

#define TEST_CASE(test_name) \
    __declspec(dllexport) STATUS_T test_##test_name();\
    STATUS_T test_##test_name()
#define TEST_SETUP(setup_name) \
    __declspec(dllexport) STATUS_T setup_##setup_name();\
    STATUS_T setup_##setup_name()
#define TEST_TEARDOWN(teardown_name) \
    __declspec(dllexport) STATUS_T teardown_##teardown_name();\
    STATUS_T teardown_##teardown_name()

typedef enum STATUS_T {
    STATUS_SUCCESS = 0,
    STATUS_FAILURE = 1,
    STATUS_FATAL = 2
} STATUS_T;

#endif // _TEST_RUNNER_H