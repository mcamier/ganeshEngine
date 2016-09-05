#ifndef GANESHENGINE_GLCORE_H
#define GANESHENGINE_GLCORE_H

#include <cstdint>
#include <string>
#include <cstdio>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "ghILogger.h"

#ifdef DEBUG_ASSERTION_ENABLED

#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <intrin.h>
#define BREAK() __debugbreak()
#else
#define BREAK() __builtin_trap()
#endif

#define ASSERT(expr) \
        if(expr) {} \
        else \
        { \
            ganeshEngine::gAssertFailure(#expr, __FILE__, __LINE__); \
            BREAK(); \
        }
#define ASSERT_FLAG(expr_flag, has_to_flag) \
        if( (expr_flag & has_to_flag) == has_to_flag) {} \
        else { \
            const char *msgPart = " doesn't match flag : "; \
            int sizeMsg = strlen(#expr_flag) + strlen(#has_to_flag) + strlen(msgPart) + 1; \
            char msg[sizeMsg]; \
            strcpy(msg, #expr_flag); \
            strcat(msg, msgPart); \
            strcat(msg, #has_to_flag); \
            msg[sizeMsg-1] = '\0'; \
            ganeshEngine::gAssertFailure(msg, __FILE__, __LINE__); \
            BREAK(); \
        }
#else
#define ASSERT(expr)
#define ASSERT_FLAG(expr_flag, has_to_flag)
#define BREAK()
#endif

namespace ganeshEngine {

    using U8 = std::uint8_t;
    using I8 = std::int8_t;

    using U16 = std::uint16_t;
    using I16 = std::int16_t;

    using U32 = std::uint32_t;
    using I32 = std::int32_t;

    using U64 = std::uint64_t;
    using I64 = std::int64_t;

    using F32 = float;
    using F64 = double;

/**
 * Print an error message and break the program execution where the assertion failed
 *
 * @param expr expression that make assert fails
 * @param file where the failing statement is located
 * @param line in the file of the failing statement
 */
    void gAssertFailure(const char *expr, const char *file, U32 line);

/**
 * Generate random number within the given range
 *
 * @param min the lowest bound
 * @param max the larger bound
 * @return random number generated as U32
 */
    U32 gRandr(unsigned int min, unsigned int max);


/**
 *
 *
 * @param logLevel
 * @param file
 * @param line
 * @param string
 */
    void gLog(LOG_LEVEL logLevel, LOG_CHANNEL channels, const char *file, int line, std::string &string);

}
#endif //GANESHENGINE_GLCORE_H
