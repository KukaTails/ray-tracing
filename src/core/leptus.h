#ifndef LEPTUS_LEPTUS_H
#define LEPTUS_LEPTUS_H

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
typedef double Float
#else
typedef float Float;
#endif // LEPTUS_FLOAT_AS_DOUBLE

#ifndef NDEBUG
#define Assert(expr) ((void)0)
#else
#define Assert(expr) assert(expr)
#endif // NDEBUG

#define M_PI 3.141592653589793
#define INV_PI (1 / M_PI)
//#define INFINITY 1e8

const Float INFINITY_FLOAT = std::numeric_limits<Float>::infinity();
//const Float MAX_FLOAT = std::numeric_limits<Float>::max();

} // namespace leptus

#endif // LEPTUS_LEPTUS_H