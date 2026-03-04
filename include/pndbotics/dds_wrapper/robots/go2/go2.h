// Copyright (c) 2025, pndbotics Robotics Co., Ltd.
// All rights reserved.

#pragma once

#include <pndbotics/dds_wrapper/robots/go2/defines.h>
#include <pndbotics/dds_wrapper/robots/go2/go2_pub.h>
#include <pndbotics/dds_wrapper/robots/go2/go2_sub.h>
#include <pndbotics/robot/b2/motion_switcher/motion_switcher_client.hpp>

namespace pndbotics
{
namespace robot
{
namespace go2
{

// Close the default controller
// Run this function before publishing to rt/lowcmd.
inline void shutdown()
{
    auto msc = std::make_shared<pndbotics::robot::b2::MotionSwitcherClient>();
    msc->SetTimeout(3.f);
    msc->Init();

    std::string form, name;
    while (msc->CheckMode(form, name), !name.empty()) {
      if (msc->ReleaseMode()) {
        spdlog::warn("Failed to switch to Release Mode.");
      }
      sleep(3);
    }
}

} // namespace go2
} // namespace robot
} // namespace pndbotics