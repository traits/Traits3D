#pragma once

#include <memory>
#include <limits>
#include <vector>
#include <algorithm>
#include <numeric>
#include <glm/gtc/matrix_transform.hpp>
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

  /**
   Pair-wise compare sizes of the aarguments sub-vectors 
  
   \param tvec                 1st vector tvec.
   \param svec                 2nd vector
   \param check_empty_elements Check for empty sub-vectors
  
   \return true, if all sub-vectors have the same size and for check_empty_elements==true no empty sub-vector exists, false else 
   */
  template<typename T, typename S>
  bool equalSizes(std::vector<std::vector<T>> const& tvec, std::vector<std::vector<S>> const& svec, bool check_empty_elements)
  {
    return std::equal(tvec.begin(), tvec.end(), svec.begin(),
        [=](std::vector<T> const& t, std::vector<S> const& s) 
        { 
          return (check_empty_elements) ? !t.empty() && t.size() == s.size() : t.size() == s.size(); 
        }
      );
  }

  // Calculate total sum of sub-vector sizes 
  template<typename T>
  size_t addSizes(std::vector<std::vector<T>> const& tvec)
  {
    return std::accumulate<std::vector<std::vector<T>>::const_iterator, size_t>(tvec.begin(), tvec.end(), 0,
      [](size_t part_sum, std::vector<T> const& t) -> size_t
        {
          return part_sum + t.size() ;
        }
      );
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

  /**
  Checks, if the argument fits in a GLfloat by returning the scaling factor
  associated with values position in (+/-)[0 ... max(GLfloat) ... max(double)]
  \return m>=0, with (+/-)m*max(GLfloat) == value (>1 for values, exceeding the range of GLfloat)
  */
  inline float excess(double value)
  {
    return (value > 0)
      ? static_cast<float>(value / std::numeric_limits<float>::max())
      : -static_cast<float>(value / std::numeric_limits<float>::max());
  }

  //! \return maximal excess for all three components
  inline float excess(Traits3D::Triple value)
  {
    return std::max({ excess(value.x), excess(value.y), excess(value.z) });
  }

  //! \return maximal excess for val
  float excess(std::vector<glm::dvec3> const& val);

  /**
  Scale vector by maximal excess, if exc > 1;
  simply convert to vector<glm::vec3> else

  \param [in,out] exc The maximal excess
  \param val          The vector to scale

  \return Scaled/converted vector
  */
  std::vector<Traits3D::TripleF> scale(double& exc, Traits3D::TripleVector const& val);

  //! Enforce scaling of val with 2nd argument 
  std::vector<Traits3D::TripleF> scale(Traits3D::TripleVector const& val, double excess);
  //! Converts value into vec3 vector - only casts are applied
  std::vector<Traits3D::TripleF> convert(Traits3D::TripleVector const& val);

  ///////////////////////////////////////////////////////////////////////////////
  // compute transform axis from object position and target point
  ///////////////////////////////////////////////////////////////////////////////
  TripleF calculateUpVector(const TripleF& position, const TripleF& target);

  glm::mat4 rotMatrix(const TripleF& direction);


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

  //! radians to degree
  inline double rad2deg(double val)
  {
    return 180 * val / Traits3D::PI;
  }

  //! degree to radians
  inline double deg2rad(double val)
  {
    return val * Traits3D::PI / 180;
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


