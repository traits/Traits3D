#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"

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
      explicit Position(glm::vec2 const& c = glm::vec2(), Anchor a = Anchor::BottomLeft)
        : coordinates(c), anchor(a)
      {
      }
      glm::vec2 coordinates;
      Anchor anchor;
    };

    virtual ~TextEngine() {};
    virtual bool initializeGL() = 0;
    virtual bool setTexts(
      std::vector<std::string> const& texts) = 0;
    bool setDoubleStrings(
      std::vector<double> const& values,
      int precision = 6);

    //! View port origin always bottom-left
    virtual bool drawText(
      std::vector<Position> const& positions,
      std::vector<glm::vec4> const& colors
      ) = 0;

    //! convenience functions
    bool setText(std::string const& val);

  protected:
    struct Hull
    {
      Hull();
      glm::vec2 bl, tr;
      float width() const { return tr.x - bl.x; }
      float height() const { return tr.y - bl.y; }
    };

    struct Text
    {
      Position position;
      Hull hull;
      std::string text;
      glm::vec4 color;
    };
  };
}