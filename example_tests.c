#include "test_runner.h"
#include "stdio.h"

TEST_SETUP(printer) {
    printf("Before is running\n");
    return STATUS_SUCCESS;
}

TEST_TEARDOWN(printer) {
    printf("After is running\n");
    return STATUS_SUCCESS;
}

TEST_CASE(bla) {
    printf("test_bla is running\n");
    return STATUS_SUCCESS;
}

TEST_CASE(foo) {
    printf("test_foo is running\n");
    return STATUS_SUCCESS;
}
