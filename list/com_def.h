#pragma once
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cassert>
#include <vector>
#include <queue>

using namespace std;

constexpr int MAX_SIZE = 10;

enum error_no
{
    ERR_CMP_FAILED = -100,
    ERR_NEW_FAILED = 100,
    ERR_POS_INVALID = 101,
    ERR_STACK_EMPTY = 102,
    ERR_STACK_FULL = 103,
    ERR_QUEUE_EMPTY = 104,
    ERR_QUEUE_FULL = 105,
};

#define SAVE_DELETE(x) { \
        if (x) { \
            delete x; \
            x = nullptr; \
        } \
    }
