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

	  void setMesh(size_t columns, size_t rows); //!< Sets number of rows and columns. 
	  bool setDomain(double minu, double maxu, double minv, double maxv); //!< Sets u-v domain boundaries.
    void restrictRange(Traits3D::Box const&); //!< Restrict the mappings range to the box 
    
    //! Creates data representation.
    virtual bool updateData() = 0;
   
  protected:
    Traits3D::Box range_p;
	  size_t umesh_p, vmesh_p;
	  double minu_p, maxu_p, minv_p, maxv_p;
  };
} // ns


