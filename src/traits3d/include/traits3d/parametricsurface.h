#pragma once

#include "traits3d/gridmapping.h"

namespace Traits3D
{

//! Abstract base class for parametric surfaces
/**

*/
class TRAITS3D_EXPORT ParametricSurface : public GridMapping
{
public:
  ParametricSurface(); //!< Constructs ParametricSurface object.
  //! Overwrite this
  virtual Traits3D::Triple operator()(double u, double v) = 0; 
	//! Creates data representation.
  bool updateData() override;
  //! Provide information about periodicity of the 'u' resp. 'v' domains.
  void setPeriodic(bool u, bool v); 

  bool uPeriodic() const { return uperiodic_p; }
  bool vPeriodic() const { return vperiodic_p; }

  //! Returns data, created by updateData()
  const TripleVector& data() const { return data_p; }

protected:
  bool uperiodic_p = true;
  bool vperiodic_p = true;
  TripleVector data_p;
};

} // ns


