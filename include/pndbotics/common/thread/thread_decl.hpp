#ifndef __PND_THREAD_DECL_HPP__
#define __PND_THREAD_DECL_HPP__

#include <pndbotics/common/any.hpp>
#include <pndbotics/common/exception.hpp>
#include <pndbotics/common/lock/lock.hpp>
#include <pndbotics/common/time/time_tool.hpp>

#define __PND_THREAD_DECL_TMPL_FUNC_ARG__    \
    template<class Func, class... Args>

#define __PND_THREAD_TMPL_FUNC_ARG__         \
    Func&& func, Args&&... args

#define __PND_THREAD_BIND_FUNC_ARG__         \
    std::forward<Func>(func), std::forward<Args>(args)...

#define PND_CPU_ID_NONE  -1

#endif//__THREAD_DECL_HPP__
