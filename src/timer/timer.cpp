/**
* Timestamp Functions
* (C) 1999-2009 Jack Lloyd
*
* Distributed under the terms of the Botan license
*/

#include <botan/timer.h>
#include <botan/loadstor.h>
#include <ctime>

namespace Botan {

/**
* Get the system clock
*/
u64bit system_time()
   {
   return static_cast<u64bit>(std::time(0));
   }

/*
* Convert a time_t to a struct tm
*/
std::tm time_t_to_tm(u64bit timer)
   {
   std::time_t time_val = static_cast<std::time_t>(timer);

   std::tm* tm_p = std::gmtime(&time_val);
   if (tm_p == 0)
      throw Encoding_Error("time_t_to_tm could not convert");
   return (*tm_p);
   }

/**
* Read the clock and return the output
*/
void Timer::poll(Entropy_Accumulator& accum)
   {
   const u64bit clock_value = this->clock();
   accum.add(clock_value, 0);
   }

/**
* Combine a two time values into a single one
*/
u64bit Timer::combine_timers(u32bit seconds, u32bit parts, u32bit parts_hz)
   {
   static const u64bit NANOSECONDS_UNITS = 1000000000;

   u64bit res = seconds * NANOSECONDS_UNITS;
   res += parts * (NANOSECONDS_UNITS / parts_hz);
   return res;
   }

/**
* ANSI Clock
*/
u64bit ANSI_Clock_Timer::clock() const
   {
   return combine_timers(std::time(0), std::clock(), CLOCKS_PER_SEC);
   }

}
