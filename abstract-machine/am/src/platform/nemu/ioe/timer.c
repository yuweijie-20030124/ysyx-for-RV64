#include <am.h>
#include <nemu.h>

void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
    // 必须先读高32位(offset 4): NEMU 的 RTC 设备在读到 offset 4 时才锁存最新时间,
    // 随后读低32位(offset 0)得到的就是同一时刻快照的低32位, 否则会读到上一次的旧值
    uint64_t hi = inl(RTC_ADDR + 4);
    uint64_t lo = inl(RTC_ADDR);
    uptime->us = (hi << 32) | lo;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
