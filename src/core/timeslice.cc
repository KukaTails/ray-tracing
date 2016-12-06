#include "core/timeslice.h"

namespace leptus {

TimeSlice::TimeSlice(float time_interval)
  :time_interval_(time_interval)
{ }


float TimeSlice::Interval() const
{
  return time_interval_;
}

} // namespace leptus