#include <pndbotics/common/time/sleep.hpp>

namespace pndbotics
{
namespace common
{
void MicroSleep(uint64_t microsecond)
{
    ::usleep(static_cast<useconds_t>(microsecond));
}

void MilliSleep(uint64_t millisecond)
{
    MicroSleep(millisecond * 1000ULL);
}

void Sleep(uint64_t second)
{
    ::sleep(static_cast<unsigned int>(second));
}

}
}
