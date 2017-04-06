#pragma once

namespace fly_hard
{

struct NonCopyable
{
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(NonCopyable const &) = delete;
    NonCopyable& operator=(NonCopyable const &) = delete;

    NonCopyable(NonCopyable &&) = default;
    NonCopyable & operator=(NonCopyable &&) = default;
};

}
