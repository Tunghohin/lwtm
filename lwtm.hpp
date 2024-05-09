#ifndef _TEST_MACRO_H
#define _TEST_MACRO_H

#include <iostream>
#include <chrono>

#define STRINGIFY(expr) #expr

#define MACRO_START \
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf(); \
    std::streambuf* oldCerrStreamBuf = std::cerr.rdbuf(); \
    std::cout.rdbuf(std::cerr.rdbuf());

#define MACRO_END \
    std::cout.rdbuf(oldCoutStreamBuf); \
    std::cerr.rdbuf(oldCerrStreamBuf);

#define EXPR_TEST_MACRO_IMPL(expr, goodlambda, badlambda) \
do { \
    if (expr) { \
        goodlambda(); \
    } else {\
        badlambda(); \
    }\
} while (false)

#define EXPR_TEST_MACRO(expr, goodlambda, badlambda) \
do { \
    MACRO_START \
    std::cout << "{ case: \"" \
    << STRINGIFY(expr) \
    << "\", output: \""; \
    EXPR_TEST_MACRO_IMPL(expr, goodlambda, badlambda); \
    std::cout << "\" }\n"; \
    MACRO_END \
} while (false)

#define EXPR_TEST_MACRO_TIME(expr, goodlambda, badlambda) \
do { \
    MACRO_START \
    std::cout << "{ case: \"" \
    << STRINGIFY(expr) \
    << "\", output: \""; \
    auto start_time = std::chrono::steady_clock::now(); \
    EXPR_TEST_MACRO_IMPL(expr, goodlambda, badlambda); \
    auto end_time = std::chrono::steady_clock::now(); \
    auto duration = \
            std::chrono::duration<double, std::milli>(end_time - start_time); \
    std::cout << "\", time: \"" \
    << "" << duration.count() \
    << "ms\" }\n"; \
    MACRO_END \
} while (false)

#endif