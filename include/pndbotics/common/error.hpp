#ifndef __PND_ERROR_HPP__
#define __PND_ERROR_HPP__

#include <pndbotics/common/decl.hpp>

namespace pndbotics
{
//Declare error
PND_DECL_ERR(PND_OK,              0,      "Success")
PND_DECL_ERR(PND_ERR_COMMON,      1001,   "common error")
PND_DECL_ERR(PND_ERR_BADCAST,     1002,   "Bad cast error")
PND_DECL_ERR(PND_ERR_FUTURE,      1003,   "Future error")
PND_DECL_ERR(PND_ERR_FUTURE_FAULT,1004,   "Future fault error")
PND_DECL_ERR(PND_ERR_JSON,        1005,   "Json data error")
PND_DECL_ERR(PND_ERR_SYSTEM,      1006,   "System error")
PND_DECL_ERR(PND_ERR_FILE,        1007,   "File operation error")
PND_DECL_ERR(PND_ERR_SOCKET,      1008,   "Socket operaton error")
PND_DECL_ERR(PND_ERR_IO,          1009,   "IO operaton error")
PND_DECL_ERR(PND_ERR_LOCK,        1010,   "Lock operation error")
PND_DECL_ERR(PND_ERR_NETWORK,     1011,   "Network error")
PND_DECL_ERR(PND_ERR_TIMEOUT,     1012,   "Timeout error")
PND_DECL_ERR(PND_ERR_UNKNOWN,     -1,     "Unknown error")
}

#endif//__PND_ERROR_HPP__
