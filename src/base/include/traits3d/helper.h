#pragma once

#include <memory>
#include <limits>
#include <vector>
#include <algorithm>
#include "traits3d/types.h"


namespace Traits3D
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

  inline bool equal(Box const& a, Box const& b)
  {
    return equal(a.minVertex, b.minVertex)
      && equal(a.maxVertex, b.maxVertex);
  }

  inline int round(double d)
  {
    return (d > 0) ? int(d + 0.5) : int(d - 0.5);
  }

//// not part of C++11 (missing in some GCC versions, will be added to C++14)
//template<typename T, typename ...Args>
//inline std::unique_ptr<T> make_unique( Args&& ...args )
//{
//    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
//}

  template <typename TARGET, typename SOURCE>
  inline std::shared_ptr<TARGET> safe_down_cast(std::shared_ptr<SOURCE> source)
  {
    return std::dynamic_pointer_cast<TARGET>(source);
  }

  //! calculates enclosing AABB
  template <typename T>
  Box calculateBox(std::vector<T> const& data)
  {
    Traits3D::Box hull;
    for (auto p : data)
    {
      if (p.x < hull.minVertex.x)
        hull.minVertex.x = p.x;
      if (p.y < hull.minVertex.y)
        hull.minVertex.y = p.y;
      if (p.z < hull.minVertex.z)
        hull.minVertex.z = p.z;

      if (p.x > hull.maxVertex.x)
        hull.maxVertex.x = p.x;
      if (p.y > hull.maxVertex.y)
        hull.maxVertex.y = p.y;
      if (p.z > hull.maxVertex.z)
        hull.maxVertex.z = p.z;
    }
    return hull;
}
#ifndef TRAITS3D_NOT_FOR_DOXYGEN

  inline Triple normalizedCross(Triple const& u, Triple const& v)
  {
    Triple n;

    /* compute the cross product (u x v for right-handed [ccw]) */
    n[0] = u[1] * v[2] - u[2] * v[1];
    n[1] = u[2] * v[0] - u[0] * v[2];
    n[2] = u[0] * v[1] - u[1] * v[0];

    /* normalize */
    double l = glm::length(n);
    if (l)
    {
      n /= l;
    }
    else
    {
      n = Triple(0,0,0);
    }

    return n;
  }

  inline Triple normalizedCross(Triple const& center,
                                Triple const& v0,
                                Triple const& v1)
  {
    return normalizedCross(v0-center, v1-center);
  }

  inline double dotProduct(Triple const& u, Triple const& v)
  {
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
  }

  //! rad to degree
  inline double rad2deg(double rad)
  {
    return 180*rad/Traits3D::PI;
  }

  //! Angle of line ccw to positive x axis in degree's
  inline double angle(double sx, double sy, double ex, double ey)
  {
    const double dx = ex - sx;
    const double dy = ey - sy;

    const double theta = rad2deg(atan2(dy, dx));

    return theta < 0 ? theta + 360 : theta;
  }

  void convexhull2d( std::vector<size_t>& idx, const std::vector<Tuple>& src );

  //! Returns the sum over the sizes of the single cells
  size_t tesselationSize(Traits3D::CellVector const& t);

#endif // TRAITS3D_NOT_FOR_DOXYGEN 
} //ns


