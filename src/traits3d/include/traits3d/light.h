#include "traits3d/types.h"
#include "traits3d/glbase/glhelper.h"

namespace traits3d
{
//! Light sources
class TRAITS3D_EXPORT Light
{
public:

    //!< Constructs standard light
    explicit Light(bool enabled = false) : enabled_(enabled) {}
    virtual ~Light() = default;

    bool enabled() const
    {
        return enabled_;
    }
    void enable(bool val)
    {
        enabled_ = val;
    }

    TripleF const &position() const
    {
        return pos_;
    }
    void setPosition(TripleF const &pos)
    {
        pos_ = pos;
    }

    Color color() const
    {
        return color_;
    }
    void setColor(Color val)
    {
        color_ = val;
    }

    // [0,1]
    float ambientIntensity() const
    {
        return ambient_intensity_;
    }
    void setAmbientIntensity(float val)
    {
        ambient_intensity_ = val;
    }

    // [0,1]
    float specularIntensity() const
    {
        return specular_intensity_;
    }
    void setSpecularIntensity(float val)
    {
        specular_intensity_ = val;
    }

private:
    bool enabled_ = false;
    TripleF pos_ = TripleF(0, 0, 0);

    Color color_ = Color(1.0f, 1.0f, 1.0f, 0.5f);
    float ambient_intensity_ = 0.0f;
    float specular_intensity_ = 0.0f;
};
}  //ns

