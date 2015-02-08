#pragma once

#include <memory>
#include <limits>
#include <vector>
#include <algorithm>
#include "types.h"


namespace Protean3D
{

inline bool equal(double a, double b)
{
  if (!b)
    return (std::abs(a) <= std::numeric_limits<double>::min());

  return (std::abs(a - b) <= 
    std::min(std::abs(a), std::abs(b)) * std::numeric_limits<double>::epsilon());
}

inline bool isZero(double x)
{
  return equal(x, 0.0);
}

inline bool equal(Triple const& a, Triple const& b)
{
  return equal(a.x, b.x)
    && equal(a.y, b.y)
    && equal(a.z, b.z);
}

inline int round(double d)
{
  return (d > 0) ? int(d + 0.5) : int(d - 0.5);
}

template <typename TARGET, typename SOURCE>
inline std::shared_ptr<TARGET> safe_down_cast(std::shared_ptr<SOURCE> source)
{
  return std::dynamic_pointer_cast<TARGET>(source);
}

Box calcHull(std::vector<glm::vec3> const& data);

} //ns


