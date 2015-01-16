#pragma once

#include <string>

namespace Protean3D
{
  class TextEngine
  {
  public:
    virtual bool initializeGL() = 0;
    virtual bool drawText(std::string const& text) = 0;
    virtual bool drawLabel(double val) = 0;
  };
}