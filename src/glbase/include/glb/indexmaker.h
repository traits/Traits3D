#pragma once

#include <vector>
#include "glb/glhelper.h"

namespace glb
{

class IndexMaker
{
public:
    IndexMaker();

    enum class RestartType
    {
        None,
        PrimitiveRestart
    };

    using IndexType = GLuint;
    using LinearizedContainer = std::vector <IndexType> ;
    using Container = std::vector <LinearizedContainer>;

    void setRestartBehavior(RestartType rtype, IndexType placeholder = 0);
    RestartType restartType() const
    {
        return restart_type_;
    }
    IndexType restartPLaceholder() const
    {
        return restart_placeholder_;
    }

    bool create(IndexType xsize, IndexType ysize, GLenum primitive_type);
    const Container &container() const
    {
        return container_;
    }
    void setRawData(LinearizedContainer const &data)
    {
        container_.resize(1);
        container_[0] = data;
    }
    size_t linearSize() const
    {
        size_t ret = 0;

        for (auto const &a : container_)
            ret += a.size();

        return ret;
    }

private:
    Container container_;

    IndexType restart_placeholder_;
    RestartType restart_type_ = RestartType::None;

    bool createLineStrips(Container &result, IndexType xsize, IndexType ysize);
    bool createRestartLineStrips(LinearizedContainer &result, IndexType xsize, IndexType ysize);
    bool createTriangleStrips(LinearizedContainer &result, IndexType xsize, IndexType ysize);
    bool createRestartTriangleStrips(LinearizedContainer &result, IndexType xsize, IndexType ysize);
};

}
