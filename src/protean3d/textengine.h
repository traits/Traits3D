#pragma once

#include <string>
#include "types.h"

namespace Protean3D
{
  class TextEngine
  {
  public:
    virtual bool initializeGL() = 0;
    virtual bool setText(
      std::vector<std::string> const& texts) = 0;

    //! View port origin always bottom-left
    virtual bool drawText(std::vector<TupleF> const& positions) = 0;

    virtual bool setColor(Protean3D::Color const &color) = 0;
    bool setText(std::string const& text);

    std::string d2t(double val);

  protected:
    struct Hull
    {
      Hull();
      TupleF bl, tr;
    };

    struct Text
    {
      TupleF position;
      Hull hull;
      std::string text;
    };
  };
}