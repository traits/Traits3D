#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "traits3d/types.h"

namespace Traits3D
{
  class FontInfo;

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

    virtual bool setTexts(std::vector<std::string> const& texts, std::vector<FontInfo> const& font_info) = 0;
    virtual bool appendText(std::string const& text, FontInfo const& font_info) = 0;
    virtual bool setText(std::string const& val, size_t index) = 0;

    //! View port origin always bottom-left
    virtual bool draw(
      std::vector<Position> const& positions,
      std::vector<Traits3D::Color> const& colors
      ) = 0;

    void setDoublePrecision(std::streamsize val) { dprecision_ = val; }
    bool appendDouble(double value, FontInfo const& font_info);
    bool setDouble(double value, size_t index = 0);
    std::string double2text(double value);

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
      Traits3D::Color color;
    };

    virtual void clear() = 0;

  private:
    std::streamsize dprecision_ = 6;
  };
}