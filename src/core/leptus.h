#ifndef LEPTUS_CORE_LEPTUS_H
#define LEPTUS_CORE_LEPTUS_H
#include <cassert>
#include <limits>

#pragma warning(disable : 4244) // int -> float conversion
#pragma warning(disable : 4843) // double -> float conversion
#pragma warning(disable : 4305) // double constant assigned to float

namespace leptus {

template <typename T>
class Point2;
template <typename T>
class Point3;
template <typename T>
class Vector2;
template <typename T>
class Vector3;
template <typename T>
class Normal3;

#ifdef LEPTUS_FLOAT_AS_DOUBLE
using Float = double;
#else
using Float = float;
#endif // LEPTUS_FLOAT_AS_DOUBLE

#ifdef NDEBUG
#define Assert(expr) ((void)0)
#else
#define Assert(expr) assert(expr)
#endif // NDEBUG

#define M_PI 3.141592653589793
#define INV_PI (1 / M_PI)

const Float BIAS = 1e-4;
const Float EPSILON = 1e-4;
const Float INFINITY_FLOAT = std::numeric_limits<Float>::infinity();

} // namespace leptus

#endif // LEPTUS_CORE_LEPTUS_H