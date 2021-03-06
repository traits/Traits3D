#pragma once

#include "traits3d/types.h"

namespace traits3d
{
class TRAITS3D_EXPORT ColorTable
{
public:
    virtual ~ColorTable() {}
    static Color color(float z, ColorVector const &vec, float zmin, float zmax);
    static ColorVector stdColor(size_t len);
    static ColorVector createColors(TripleVector const &data, ColorVector const &color_field);
    static ColorVector createColors(std::vector<TripleF> const &data, ColorVector const &color_field);
};
} // ns


