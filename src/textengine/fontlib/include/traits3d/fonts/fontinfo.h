#pragma once

#include <string>

namespace Traits3D
{
  class FontInfo
  {
  public:
    explicit FontInfo(std::string const& f_name = std::string(), size_t f_height = 0)
      : font_name(f_name), font_height(f_height)
    {}

    const std::string font_name;
    const size_t font_height;
  };
} // ns
