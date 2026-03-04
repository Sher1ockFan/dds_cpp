#ifndef __PND_SLEEP_HPP__
#define __PND_SLEEP_HPP__

#include <pndbotics/common/time/time_tool.hpp>

namespace pndbotics
{
namespace common
{
void MicroSleep(uint64_t microsecond);
void MilliSleep(uint64_t millisecond);
void Sleep(uint64_t second);

}
}

#endif//__PND_SLEEP_HPP__
