#ifndef __PND_LOG_BUFFER_HPP__
#define __PND_LOG_BUFFER_HPP__

#include <pndbotics/common/log/log_decl.hpp>

namespace pndbotics
{
namespace common
{
class LogBuffer
{
public:
    explicit LogBuffer();
    virtual ~LogBuffer();

    virtual bool Append(const std::string& s);
    virtual bool Get(std::string& s);
    virtual bool Empty();

protected:
    std::string mData;
};

typedef std::shared_ptr<LogBuffer> LogBufferPtr;

class LogBlockBuffer : public LogBuffer
{
public:
    explicit LogBlockBuffer();
    ~LogBlockBuffer();

    bool Append(const std::string& s);
    bool Get(std::string& s);
    bool Empty();

private:
    Mutex mLock;
};

typedef std::shared_ptr<LogBlockBuffer> LogBlockBufferPtr;
}
}

#endif//__PND_LOG_BUFFER_HPP__
