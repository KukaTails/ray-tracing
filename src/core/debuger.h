#ifndef LEPTUS_DEBUGER_H
#define LEPTUS_DEBUGER_H
#include <string>
#include <iostream>

namespace leptus {

class Debuger {
public:
  static int NOW_X, NOW_Y;
  static int CAPTURED_X, CAPTURED_Y;
  static std::ostream& os;

private:
  Debuger( ) = default;
public:
  static void SetOutputStream(std::ostream& output_stream);
  static void SetCurrentPixel(int x, int y);
  static void SetCapturedPixel(int x, int y);
  static void PrintInfo(const std::string& info);
};


} // namespace leptus

#endif // LEPTUS_DEBUGER_H