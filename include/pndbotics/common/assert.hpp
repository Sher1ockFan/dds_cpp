#ifndef __PND_ASSERT_HPP__
#define __PND_ASSERT_HPP__

#include <pndbotics/common/decl.hpp>

/*
 * Declare assert output
 */
#define PND_ASSERT_OUT(debug, file, func, line, r)           \
    if (debug)                                              \
    {                                                       \
        std::cout << "[" << ::time(NULL)                    \
            << "] [" << ::syscall(SYS_gettid)               \
            << "] PND_ASSERT DEBUG at __FILE__:" << file     \
            << ", __FUNCTION__:" << func                    \
            << ", __LINE__:" << line                        \
            << ", r:" << r                                  \
            << ", errno:" << errno                          \
            << std::endl;                                   \
    }                                                       \
    else                                                    \
    {                                                       \
        std::cout << "[" << ::time(NULL)                    \
            << "] [" << ::syscall(SYS_gettid)               \
            << "] PND_ASSERT ABORT at __FILE__:" << file     \
            << ", __FUNCTION__:" << func                    \
            << ", __LINE__:" << line                        \
            << ", r:" << r                                  \
            << ", errno:" << errno                          \
            << std::endl;                                   \
    }

#define PND_ASSERT_ABORT(debug, file, func, line, r)         \
    if (debug)                                              \
    {                                                       \
        PND_ASSERT_OUT(1, file, func, line, r);              \
    }                                                       \
    else                                                    \
    {                                                       \
        PND_ASSERT_OUT(0, file, func, line, r);              \
        abort();                                            \
    }

/*
 * Declare assert return value
 */
#define PND_ASSERT_EQ(x, r)                                  \
    pndbotics::common::AssertEqual(x, r, 0, __FILE__,                 \
        __PRETTY_FUNCTION__, __LINE__)

#define PND_ASSERT_EQ_DEBUG(x, r)                            \
    pndbotics::common::AssertEqual(x, r, 1, __FILE__,                 \
        __PRETTY_FUNCTION__, __LINE__)

#define PND_ASSERT_NOT_EQ(x, r)                              \
    pndbotics::common::AssertNotEqual(x, r, 0, __FILE__,              \
        __PRETTY_FUNCTION__, __LINE__)

#define PND_ASSERT_NOT_EQ_DEBUG(x, r)                        \
    pndbotics::common::AssertNotEqual(x, r, 1, __FILE__,              \
        __PRETTY_FUNCTION__, __LINE__)

/*
 * Declare assert return value and errno
 */
#define PND_ASSERT_ENO_EQ(x, r, eno)                         \
    pndbotics::common::AssertEqual(x, r, eno, 0, __FILE__,            \
        __PRETTY_FUNCTION__, __LINE__)

#define PND_ASSERT_ENO_EQ_DEBUG(x, r, eno)                   \
    pndbotics::common::AssertEqual(x, r, eno, 1, __FILE__,            \
        __PRETTY_FUNCTION__, __LINE__)

#define PND_ASSERT_ENO_EQ_EX(x, r, eno)                      \
    pndbotics::common::AssertEqualEx(x, r, eno, 0, __FILE__,          \
        __PRETTY_FUNCTION__, __LINE__)

#define PND_ASSERT_ENO_EQ_EX_DEBUG(x, r, eno)                \
    pndbotics::common::AssertEqualEx(x, r, eno, 1, __FILE__,          \
        __PRETTY_FUNCTION__, __LINE__)

/*
 * Declare assert wrapper
 */
#define PND_ASSERT_0(x)                  \
    PND_ASSERT_EQ(x, 0)

#define PND_ASSERT_DEBUG_0(x)            \
    PND_ASSERT_EQ_DEBUG(x, 0)

#define PND_ASSERT_ENO_0(x, eno)         \
    PND_ASSERT_ENO_EQ(x, 0, eno)

#define PND_ASSERT_ENO_DEBUG_0(x, eno)   \
    PND_ASSERT_ENO_EQ_DEBUG(x, 0, eno)


//Declare assert function
namespace pndbotics
{
namespace common
{
inline int AssertEqual(int r, int expectRet, bool debug,
    const char* file, const char* func, int line)
{
    if (PND_UNLIKELY(r != expectRet))
    {
        PND_ASSERT_ABORT(debug, file, func, line, r);
    }

    return r;
}

inline int AssertNotEqual(int r, int expectRet, bool debug,
    const char* file, const char* func, int line)
{
    if (PND_UNLIKELY(r == expectRet))
    {
        PND_ASSERT_ABORT(debug, file, func, line, r);
    }

    return r;
}

inline int AssertEqual(int r, int expectRet, int expectErrno, bool debug,
    const char* file, const char* func, int line)
{
    if (PND_UNLIKELY(r != expectRet) && PND_UNLIKELY(errno != expectErrno))
    {
        PND_ASSERT_ABORT(debug, file, func, line, r);
    }

    return r;
}

inline int AssertEqualEx(int r, int expectRet, int expectErrno, bool debug,
    const char* file, const char* func, int line)
{
    if (PND_UNLIKELY(r != 0) && PND_UNLIKELY(r != expectRet) && 
        PND_UNLIKELY(errno != expectErrno))
    {
        PND_ASSERT_ABORT(debug, file, func, line, r);
    }

    return r; 
}
}
}
#endif//__PND_ASSERT_HPP__
