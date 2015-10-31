#pragma once

#include "traits3d/matrix.h"
#include "plot3d.h"

namespace traits3d
{
class TRAITS3D_EXPORT SurfacePlot : public Plot3D
{
public:
    bool initializeGL() override;
    bool addPositionData(std::vector<TripleF> const &data,
                         size_t xsize, size_t ysize);
    bool addPositionData(MatrixF const &data);
    bool updatePositionData(std::vector<TripleF> const &data);
    bool updatePositionData(MatrixF const &data);
    void setDataDrawType(GLenum val);

    void setDataColor(ColorVector const &val);
    ColorVector createColors(std::vector<TripleF> const &data, ColorVector const &color_field);
    bool setMeshColor(Color const &val);
};
} // ns