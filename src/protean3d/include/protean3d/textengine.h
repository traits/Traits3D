#pragma once

#include <string>
#include "protean3d/types.h"

namespace Protean3D
{
  class TextEngine
  {
  public:   
    //! Possible anchor points for drawing operations
    enum class Anchor
    {
      BottomLeft,
      BottomRight,
      BottomCenter,
      TopLeft,
      TopRight,
      TopCenter,
      CenterLeft,
      CenterRight,
      Center
    };

    struct Position
    {
      explicit Position(TupleF const& c = TupleF(), Anchor a = Anchor::BottomLeft)
        : coordinates(c), anchor(a)
      {
      }
      TupleF coordinates;
      Anchor anchor;
    };

    virtual ~TextEngine() {};
    virtual bool initializeGL() = 0;
    virtual bool setText(
      std::vector<std::string> const& texts) = 0;

    //! View port origin always bottom-left
    virtual bool drawText(std::vector<Position> const& positions) = 0;
    virtual bool setColor(Color const &color) = 0;

    bool setText(std::string const& text);

    std::string d2t(double val);

  protected:
    struct Hull
    {
      Hull();
      TupleF bl, tr;
      float width() const { return tr.x - bl.x; }
      float height() const { return tr.y - bl.y; }
    };

    struct Text
    {
      Position position;
      Hull hull;
      std::string text;
    };
  };
}