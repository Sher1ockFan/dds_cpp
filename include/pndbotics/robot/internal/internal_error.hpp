#ifndef __PND_ROBOT_INTERNAL_ERROR_HPP__
#define __PND_ROBOT_INTERNAL_ERROR_HPP__

#include <pndbotics/common/decl.hpp>

namespace pndbotics
{
namespace robot
{
PND_DECL_ERR(PND_ROBOT_OK,                            0,      "Success.")
PND_DECL_ERR(PND_ROBOT_ERR_UNKNOWN,                   3001,   "Unknown error.")
PND_DECL_ERR(PND_ROBOT_ERR_CLIENT_SEND,               3102,   "Send request error.")
PND_DECL_ERR(PND_ROBOT_ERR_CLIENT_API_NOT_REG,        3103,   "Api is not registed.")
PND_DECL_ERR(PND_ROBOT_ERR_CLIENT_API_TIMEOUT,        3104,   "Call api timeout error.")
PND_DECL_ERR(PND_ROBOT_ERR_CLIENT_API_NOT_MATCH,      3105,   "Response api not match error.")
PND_DECL_ERR(PND_ROBOT_ERR_CLIENT_API_DATA,           3106,   "Response data error.")
PND_DECL_ERR(PND_ROBOT_ERR_CLIENT_LEASE_INVALID,      3107,   "Lease is invalid.")

PND_DECL_ERR(PND_ROBOT_ERR_SERVER_SEND,               3201,   "Send response error.")
PND_DECL_ERR(PND_ROBOT_ERR_SERVER_INTERNAL,           3202,   "Server internal error.")
PND_DECL_ERR(PND_ROBOT_ERR_SERVER_API_NOT_IMPL,       3203,   "Api not implement error.")
PND_DECL_ERR(PND_ROBOT_ERR_SERVER_API_PARAMETER,      3204,   "Api parameter error.")
PND_DECL_ERR(PND_ROBOT_ERR_SERVER_LEASE_DENIED,       3205,   "Request denied by lease.")
PND_DECL_ERR(PND_ROBOT_ERR_SERVER_LEASE_NOT_EXIST,    3206,   "Lease not exist in server cache.")
PND_DECL_ERR(PND_ROBOT_ERR_SERVER_LEASE_EXIST,        3207,   "Lease is already exist in server cache.")
}
}

#endif//__PND_ROBOT_INTERNAL_ERROR_HPP__
