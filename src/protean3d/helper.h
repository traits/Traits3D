#pragma once

#include <memory>
#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>
#include "types.h"


namespace Protean3D
{

inline bool isPracticallyZero(double a, double b = 0)
{
  if (!b)
    return (std::abs(a) <= std::numeric_limits<double>::min());

  return (std::abs(a - b) <= 
    std::fmin(std::abs(a), std::abs(b)) * std::numeric_limits<double>::epsilon());
}

inline int round(double d)
{
  return (d > 0) ? int(d + 0.5) : int(d - 0.5);
}

template <typename TARGET, typename SOURCE>
inline std::shared_ptr<TARGET> safe_down_cast(std::shared_ptr<SOURCE> source)
{
  return dynamic_pointer_cast<TARGET>(source);
}

Box calcHull(std::vector<glm::vec3> const& data);

} //ns


