#ifndef LEPTUS_CORE_TIMESLICE_H
#define LEPTUS_CORE_TIMESLICE_H

namespace leptus {

class TimeSlice {
public:
  TimeSlice(float time_interval);
  float Interval() const;

private:
  float time_interval_;
};

} // namespace leptus

#endif // LEPTUS_TIMESLICE_H