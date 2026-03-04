#ifndef __PND_EXCEPTION_HPP__
#define __PND_EXCEPTION_HPP__

#include <pndbotics/common/error.hpp>

#define PND_MAX_TRACE_ADDR_NUMBER 64

namespace pndbotics
{
namespace common
{
class Exception : public std::exception
{
public:
    Exception() throw()
        : Exception(PND_ERR_UNKNOWN, PND_DESC_ERR(PND_ERR_UNKNOWN))
    {}

    Exception(int32_t code, const std::string& message) throw()
        : mCode(code), mMessage(message), mLine(0)
    {}

    virtual ~Exception()
    {}

    int32_t GetCode() const
    {
        return mCode;
    }

    const std::string& GetMessage() const
    {
        return mMessage;
    }

    virtual const char* what() const noexcept
    {
        return mMessage.c_str();
    }

    virtual std::string GetClassName() const
    {
        return "Exception";
    }

    void Init(const char* file, const char* func, int32_t line)
    {
        mFile = file;
        mFunc = func;
        mLine = line;
    }

    std::string ToString() const
    {
        std::ostringstream os;
        AddDetail(os);

        return os.str();
    }

    std::string StackTrace() const
    {
        std::ostringstream os;
        AddDetail(os);
        AddBackTrace(os);

        return os.str();
    }

protected:
    void AddDetail(std::ostringstream& os) const
    {
        os << "Catch " << GetClassName() << " code:" << mCode
            << ", message:" << mMessage << std::endl;

        if (!mFile.empty() && !mFunc.empty() && mLine > 0)
        {
            os << " at __FILE__:" << mFile << ", __LINE__:"
                << mLine << ", __FUNCTION__:" << mFunc << std::endl;
        }
    }

    void AddBackTrace(std::ostringstream& os) const
    {
        os << "Stack:" << std::endl;

        void* addr[PND_MAX_TRACE_ADDR_NUMBER];
        int32_t number = backtrace(addr, PND_MAX_TRACE_ADDR_NUMBER);

        char **info = backtrace_symbols(addr, number);
        if(info == NULL)
        {
            return;
        }

        for(int32_t i=0; i<number; i++)
        {
            os << info[i] << std::endl;
        }

        free(info);
    }

protected:
    int32_t mCode;
    std::string mMessage;

    std::string mFile;
    std::string mFunc;
    int32_t mLine;

    std::string mWhat;
};

#define PND_THROW_0(ExceptionType)           \
    do                                      \
    {                                       \
        ExceptionType __temp_except_r38e2d; \
        __temp_except_r38e2d.Init(__FILE__,__PRETTY_FUNCTION__,__LINE__); \
        throw(__temp_except_r38e2d);        \
    } while(0);

#define PND_THROW(ExceptionType, args...)    \
    do                                      \
    {                                       \
        ExceptionType __temp_except_r38e2d(args);       \
        __temp_except_r38e2d.Init(__FILE__,__PRETTY_FUNCTION__,__LINE__); \
        throw(__temp_except_r38e2d);        \
    } while(0);

#define PND_THROW_IF(condition, ExceptionType, args...)  \
    if (condition)                          \
    {                                       \
        PND_THROW(ExceptionType, args);      \
    }

#define PND_EXCEPTION_TRY                    \
    try                                     \
    {

#define __PND_EXCEPTION_CATCH(except, l, t)  \
    catch (const except& e)                 \
    {                                       \
        if (l)                              \
        {                                   \
            LOG_ERROR(l, e.what());         \
        }                                   \
        if (t)                              \
        {                                   \
            throw e;                        \
        }                                   \
    }

#define PND_EXCEPTION_CATCH(l, t)            \
    }                                       \
    __PND_EXCEPTION_CATCH(pndbotics::common::Exception, l, t)      \
    __PND_EXCEPTION_CATCH(std::exception, l, t)

#define PND_DECL_EXCEPTION(ExceptionType, code, desc)    \
class ExceptionType : public pndbotics::common::Exception \
{                                           \
public:                                     \
    ExceptionType() throw()                 \
        : Exception(code, desc)             \
    {}                                      \
                                            \
    ExceptionType(const std::string& message) throw()   \
        : Exception(code, message)          \
    {}                                      \
                                            \
    std::string GetClassName() const        \
    {                                       \
        return #ExceptionType;              \
    }                                       \
};

PND_DECL_EXCEPTION(CommonException, PND_ERR_COMMON, PND_DESC_ERR(PND_ERR_COMMON))

PND_DECL_EXCEPTION(SystemException, PND_ERR_SYSTEM, PND_DESC_ERR(PND_ERR_SYSTEM))

PND_DECL_EXCEPTION(NetworkException, PND_ERR_NETWORK, PND_DESC_ERR(PND_ERR_NETWORK))

PND_DECL_EXCEPTION(FileException, PND_ERR_FILE, PND_DESC_ERR(PND_ERR_FILE))

PND_DECL_EXCEPTION(SocketException, PND_ERR_SOCKET, PND_DESC_ERR(PND_ERR_SOCKET))

PND_DECL_EXCEPTION(IOException, PND_ERR_IO, PND_DESC_ERR(PND_ERR_IO))

PND_DECL_EXCEPTION(LockException, PND_ERR_LOCK, PND_DESC_ERR(PND_ERR_LOCK))

PND_DECL_EXCEPTION(TimeoutException, PND_ERR_TIMEOUT, PND_DESC_ERR(PND_ERR_TIMEOUT))

PND_DECL_EXCEPTION(BadCastException, PND_ERR_BADCAST, PND_DESC_ERR(PND_ERR_BADCAST))

PND_DECL_EXCEPTION(JsonException, PND_ERR_JSON, PND_DESC_ERR(PND_ERR_JSON))

PND_DECL_EXCEPTION(FutureException, PND_ERR_FUTURE, PND_DESC_ERR(PND_ERR_FUTURE))

PND_DECL_EXCEPTION(FutureFaultException, PND_ERR_FUTURE_FAULT, PND_DESC_ERR(PND_ERR_FUTURE_FAULT))

}
}
#endif//__PND_EXCEPTION_HPP__
