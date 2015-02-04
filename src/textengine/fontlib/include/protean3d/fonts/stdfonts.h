#pragma once

#include <string>
#include <vector>

namespace Protean3D
{
  class Font
  {
  public:
    Font(const unsigned char* buffer = 0, size_t buflen = 0, std::string fname = std::string())
    :data(buffer, buffer + buflen), name(fname)
    {}
    const std::vector<unsigned char> data;
    const std::string name;
  };

  struct StandardFont
  {
    static const Font OpenSans_Italic;
    static const Font OpenSans_Regular;
  };
} // ns
