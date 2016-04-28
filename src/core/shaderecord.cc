#include "shaderecord.h"

namespace leptus {

ShadeRecord::ShadeRecord(const World& world)
  : world_(world), is_hit_(false), color_(BLACK)
{}

} // namespace leptus