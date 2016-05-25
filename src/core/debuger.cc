#include "core/debuger.h"

#include <fstream>

namespace leptus {

int Debuger::NOW_X = -1;
int Debuger::NOW_Y = -1;
int Debuger::CAPTURED_X = -1;
int Debuger::CAPTURED_Y = -1;
std::ostream& Debuger::os = std::ofstream("E:\\ray_debug.txt");

void Debuger::SetOutputStream(std::ostream& output_stream)
{ }


void Debuger::SetCurrentPixel(int x, int y)
{
  NOW_X = x;
  NOW_Y = y;
}

void Debuger::SetCapturedPixel(int x, int y)
{
  CAPTURED_X = x;
  CAPTURED_Y = y;
}

void Debuger::PrintInfo(const std::string& info)
{
  if (NOW_X == CAPTURED_X && NOW_Y == CAPTURED_Y) {
    os << info << std::endl;
  }
}

} // namespace leptus