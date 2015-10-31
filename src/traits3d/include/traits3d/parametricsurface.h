#pragma once

#include "traits3d/gridmapping.h"

namespace traits3d
{

//! Abstract base class for parametric surfaces
/**

*/
class TRAITS3D_EXPORT ParametricSurface : public GridMapping
{
public:
    ParametricSurface(); //!< Constructs ParametricSurface object.
    //! Overwrite this
    virtual Triple operator()(double u, double v) = 0;

    bool setDomain(double minu, double maxu, double minv, double maxv); //!< Sets u-v domain boundaries.
    bool setHull(Box const &hull); //!< Limit the mappings value range to the box

    //! Provide information about periodicity of the 'u' resp. 'v' domains.
    void setPeriodic(bool u, bool v);
    bool uPeriodic() const
    {
        return uperiodic_p;
    }
    bool vPeriodic() const
    {
        return vperiodic_p;
    }

    bool setDomainResolution(size_t u_size, size_t v_size)
    {
        return setMeshSizeImpl(u_size, v_size);
    }
    size_t uSize() const
    {
        return umesh_p;
    }
    size_t vSize() const
    {
        return vmesh_p;
    }

    //! Returns data, created by updateData()
    const TripleVector &data();

protected:
    bool uperiodic_p = true;
    bool vperiodic_p = true;
    TripleVector data_p;
    double minu_p, maxu_p, minv_p, maxv_p;

    //! Creates data representation.
    bool updateData() override;
};

} // ns


