#pragma once
#include <cstdint>
class Timer{
    std::uint64_t _start;
    std::uint32_t _buf;
public:
    Timer(){_start = 0;}
    static inline uint64_t now(std::uint32_t& aux) noexcept{
        uint64_t rax,rdx;
        asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux): : );
        return (rdx << 32) + rax;
    }
    inline void start() noexcept{_start = now(_buf);}
    inline std::uint64_t stop() noexcept{return now(_buf) - _start;}
};