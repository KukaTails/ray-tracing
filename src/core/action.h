#ifndef LEPTUS_CORE_ACTION_H
#define LEPTUS_CORE_ACTION_H

#include <functional>
#include "core/timeslice.h"
#include "core/surface.h"


namespace leptus {

typedef std::function<void(const leptus::TimeSlice&)> Action;


} // namespace leptus

#endif // LEPTUS_CORE_ACTION_H