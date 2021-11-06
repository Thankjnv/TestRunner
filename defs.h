#ifndef _TEST_RUNNER_DEFS_H
#define _TEST_RUNNER_DEFS_H
#include <Windows.h>
#include <stdint.h>
#include <stdio.h>
#include "test_runner.h"
#include "test_runner_types.h"

#define LOG(fmt, ...) fprintf(stdout, "[Test Runner] " fmt "\n" __VA_OPT__(,) __VA_ARGS__);
#define LOG_ERROR(fmt, ...) fprintf(stderr, "[Test Runner] " fmt "\n" __VA_OPT__(,) __VA_ARGS__);
#define CHECK_NOT_NULL(var) \
    if (var == NULL) {\
        LOG_ERROR("%s is NULL", #var);\
        return STATUS_FAILURE;\
    }

#endif // _TEST_RUNNER_DEFS_H