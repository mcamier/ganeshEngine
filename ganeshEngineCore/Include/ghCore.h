#ifndef GANESHENGINE_GLCORE_H
#define GANESHENGINE_GLCORE_H

#include <cstdint>
#include <string>
#include <cstdio>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "ghILogger.h"

/**
 * Transform a given string into an hash
 *
 * @see http://lolengine.net/blog/2011/12/20/cpp-constant-string-hash
 * @note Could be used as runtime as well as compile time
 */
#define H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<strlen(s)?strlen(s)-1-(i):strlen(s)])
#define H4(s,i,x)   H1(s,i,H1(s,i+1,H1(s,i+2,H1(s,i+3,x))))
#define H16(s,i,x)  H4(s,i,H4(s,i+4,H4(s,i+8,H4(s,i+12,x))))
#define H64(s,i,x)  H16(s,i,H16(s,i+16,H16(s,i+32,H16(s,i+48,x))))
#define H256(s,i,x) H64(s,i,H64(s,i+64,H64(s,i+128,H64(s,i+192,x))))

#define GH_HASH(s)    ((uint32_t)(H256(s,0,0)^(H256(s,0,0)>>16)))





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
void gAssertFailure(const char *expr, const char *file, U32 line) ;

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
void gLog(LOG_LEVEL logLevel, const char *file, int line, std::string &string);

}
#endif //GANESHENGINE_GLCORE_H
