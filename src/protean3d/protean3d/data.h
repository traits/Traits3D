#pragma once

#include "types.h"

namespace Protean3D
{
  class Data
  {
  public:
    virtual ~Data() {}
    virtual bool empty() const { return true; } //!< no data
    //void setHull(Protean3D::Box const& h) { hull_p = h; }
    Protean3D::Box const& hull() const { return hull_p; }

  protected:
    Protean3D::Box hull_p;
  };
} // ns