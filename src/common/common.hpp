#ifndef GE_COMMON_HPP
#define GE_COMMON_HPP

#include <string>
#include <vector>

#ifdef _DEBUG

#include <stdio.h>
#include <string>

#ifdef _WIN32
//#include <intrin.h>
#define BREAK() __debugbreak()
#else
#define BREAK() __builtin_trap()
#endif

#define ASSERT_SUB_STRING " evaluated to false"
#define ASSERT(expr) \
        if(expr) {} \
        else \
        { \
            throw std::runtime_error(#expr ASSERT_SUB_STRING); \
        }
#define ASSERT_FLAG(expr_flag, has_to_flag) \
        if( (expr_flag & has_to_flag) == has_to_flag) {} \
        else { \
            throw std::runtime_error(#expr_flag ASSERT_SUB_STRING); \
        }
#else
#define ASSERT(expr)
#define ASSERT_FLAG(expr_flag, has_to_flag)
#define BREAK()
#endif


namespace ge
{

std::vector<char> readFile(const std::string &filename);

}

#endif //GE_COMMON_HPP
