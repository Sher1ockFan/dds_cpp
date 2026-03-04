#ifndef __PND_ROBOT_INTERNAL_REQUEST_RESPONSE_HPP__
#define __PND_ROBOT_INTERNAL_REQUEST_RESPONSE_HPP__

#include <pndbotics/robot/internal/internal_idl_decl/Request_.hpp>
#include <pndbotics/robot/internal/internal_idl_decl/Response_.hpp>

namespace pndbotics
{
namespace robot
{
using RequestIdentity = pndbotics_api::msg::dds_::RequestIdentity_;
using RequestLease = pndbotics_api::msg::dds_::RequestLease_;
using RequestPolicy = pndbotics_api::msg::dds_::RequestPolicy_;
using RequestHeader = pndbotics_api::msg::dds_::RequestHeader_;
using Request = pndbotics_api::msg::dds_::Request_;

using ResponseStatus = pndbotics_api::msg::dds_::ResponseStatus_;
using ResponseHeader = pndbotics_api::msg::dds_::ResponseHeader_;
using Response = pndbotics_api::msg::dds_::Response_;
}
}

#endif//__PND_ROBOT_INTERNAL_REQUEST_RESPONSE_HPP__
