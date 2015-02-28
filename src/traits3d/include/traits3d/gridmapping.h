#pragma once

#include "traits3d/types.h"

namespace Traits3D
{
  //! Abstract base class for mappings acting on rectangular grids
  /**

  */
  class TRAITS3D_EXPORT GridMapping
  {
  public:
    GridMapping(); //!< Constructs GridMapping object.

    bool setMeshSize(size_t u_size, size_t v_size); //!< Sets number of rows (u) and columns (v). 
    const Box& hull() const { return hull_p; } //!< Return the mappings effective x-y-z hull
    size_t uMeshSize() const { return umesh_p; }
    size_t vMeshSize() const { return vmesh_p; }

  protected:
    //! Creates data representation.
    virtual bool updateData() = 0;
   
    Traits3D::Box hull_p;
    size_t umesh_p = 0;
    size_t vmesh_p = 0;

    bool dirty_data_p = true;
  };
} // ns


