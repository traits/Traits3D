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

  bool setDomain(double minu, double maxu, double minv, double maxv, bool update = true); //!< Sets u-v domain boundaries.
  bool setHull(Traits3D::Box const& hull, bool update = true); //!< Limit the mappings value range to the box 

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
  double minu_p, maxu_p, minv_p, maxv_p;

  //! Creates data representation.
  bool updateData() override;
};

} // ns


