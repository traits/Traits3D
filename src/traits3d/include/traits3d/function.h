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
		
    bool setDomain(double min_x, double max_x, double min_y, double max_y); //!< Sets x-y domain boundaries.
    bool limitRange(double min_z, double max_z);

	  //! Creates data representation (consecutive row vectors for this standard implementation).
	  bool updateData() override;

    //! Returns data, created by updateData()
    const std::vector<double>& data() const { return data_p; }

  protected:
    std::vector<double> data_p;
  };
} // ns


