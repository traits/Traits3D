#pragma once

#include "traits3d/gridmapping.h"

namespace Traits3D
{
  //! Abstract base class for mathematical functions
  /**
	  A Function encapsulates a mathematical function with rectangular domain. The user has to adapt the pure virtual operator() 
	  to get a working object. Also, the client code should call setDomain, setMesh and create for reasonable operating conditions.
  */
  class TRAITS3D_EXPORT Function : public GridMapping
  {
  public:
    Function(); //!< Constructs Function object w/o assigned SurfacePlot.
	  virtual double operator()(double x, double y) = 0; //!< Overwrite this.
		
	  void setMinZ(double val); //!< Sets minimal z value.
	  void setMaxZ(double val); //!< Sets maximal z value.

	  //! Creates data representation (consecutive row vectors for this standard implementation).
	  bool updateData() override;

    //! Returns data, created by updateData()
    const std::vector<double>& data() const { return data_p; }

  protected:
    std::vector<double> data_p;
  };
} // ns


