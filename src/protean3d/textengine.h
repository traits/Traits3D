#pragma once

#include <string>
#include "types.h"

namespace Protean3D
{
  class TextEngine
  {
  public:
    virtual bool initializeGL() = 0;
    virtual bool drawText(
      std::vector<std::string> const& texts,
      std::vector<glm::vec2> const& positions,
      Protean3D::Color const& color) = 0;

    bool drawText(std::string const& text, glm::vec2 const& position, 
      Protean3D::Color const& color);
  };
}