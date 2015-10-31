#include "traits3d/helper.h"
#include "traits3d/surfaceplot.h"

namespace traits3d
{

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool SurfacePlot::addPositionData(std::vector<TripleF> const &data,
                                  size_t xsize, size_t ysize)
{
    if (!data_object_p->setPositionData(data, xsize, ysize))
        return false;

    coordinates_p->init(data_object_p->hull());
    return true;
}

bool SurfacePlot::addPositionData(MatrixF const &data)
{
    if (!data_object_p->setPositionData(data))
        return false;

    coordinates_p->init(data_object_p->hull());
    return true;
}

//todo check size against position vector[s]
void SurfacePlot::setDataColor(ColorVector const &val)
{
    data_object_p->setColor(val);
}

bool SurfacePlot::setMeshColor(Color const &val)
{
    return data_object_p->setMeshColor(val);
}

bool SurfacePlot::updatePositionData(std::vector<TripleF> const &data)
{
    if (!data_object_p->updatePositionData(data))
        return false;

    coordinates_p->init(data_object_p->hull());
    return true;
}

void SurfacePlot::setDataDrawType(GLenum val)
{
    data_object_p->setDrawType(val);
}

bool SurfacePlot::updatePositionData(MatrixF const &data)
{
    if (!data_object_p->updatePositionData(data.linearBuffer()))
        return false;

    coordinates_p->init(data_object_p->hull());
    return true;
}

bool SurfacePlot::initializeGL()
{
    if (!Plot3D::initializeGL())
    {
        gl_is_initialized_p = false;
        return false;
    }

    data_object_p = std::make_unique<gl::DataObject>();
    data_object_p->maintainNormals(true);
    gl_is_initialized_p = true;
    return true;
}

} // ns