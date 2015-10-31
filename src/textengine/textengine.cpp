#include <numeric>
#include <iomanip>
#include <sstream>
#include "traits3d/helper.h"
#include "traits3d/textengine/textengine.h"

namespace traits3d
{

TextEngine::Hull::Hull()
    : bl(std::numeric_limits<float>::max(), std::numeric_limits<float>::max())
    , tr(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max())
{
}

std::string TextEngine::double2text(double value)
{
    std::ostringstream os;
    os << std::setprecision(dprecision_) << value;
    return os.str();
    //os.clear();
    //os.str(std::string()); // clear stream
}

void TextEngine::adjustPosition(Position &pos, float shift)
{
    if (isZero(shift))
        return;

    glm::vec2 &c = pos.coordinates;

    switch (pos.anchor)
    {
        case Anchor::BottomLeft:
            c.x += shift;
            c.y += shift;
            break;

        case Anchor::BottomCenter:
            c.y += shift;
            break;

        case Anchor::BottomRight:
            c.x -= shift;
            c.y += shift;
            break;

        case Anchor::CenterLeft:
            c.x += shift;
            break;

        case Anchor::Center:
            //ret;
            break;

        case Anchor::CenterRight:
            c.x -= shift;
            break;

        case Anchor::TopLeft:
            c.x += shift;
            c.y -= shift;
            break;

        case Anchor::TopCenter:
            c.y -= shift;
            break;

        case Anchor::TopRight:
            c.x -= shift;
            c.y -= shift;
            break;

        default:
            break;
    }
}

} // ns