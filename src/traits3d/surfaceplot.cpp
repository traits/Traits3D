#include "traits3d/helper.h"
#include "traits3d/surfaceplot.h"

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool Traits3D::SurfacePlot::addPositionData(std::vector<TripleF> const& data,
    size_t xsize, size_t ysize)
{
  if (!data_object_p->setPositionData(data, xsize, ysize))
    return false;

  coordinates_p->init(data_object_p->hull());
  return true;
}

bool Traits3D::SurfacePlot::addPositionData(Traits3D::MatrixF const& data)
{
  if (!data_object_p->setPositionData(data))
    return false;

  coordinates_p->init(data_object_p->hull());
  return true;
}

//todo check size against position vector[s]
void Traits3D::SurfacePlot::setDataColor(ColorVector const& val)
{
  data_object_p->setColor(val);
}

bool Traits3D::SurfacePlot::setMeshColor(Color const& val)
{
  return data_object_p->setMeshColor(val);
}

bool Traits3D::SurfacePlot::updatePositionData(std::vector<TripleF> const& data)
{
  if (!data_object_p->updatePositionData(data))
    return false;

  coordinates_p->init(data_object_p->hull());
  return true;
}

void Traits3D::SurfacePlot::setDataDrawType(GLenum val)
{
  data_object_p->setDrawType(val);
}

bool Traits3D::SurfacePlot::updatePositionData(Traits3D::MatrixF const& data)
{
  if (!data_object_p->updatePositionData(data.linearBuffer()))
    return false;

  coordinates_p->init(data_object_p->hull());
  return true;
}

bool Traits3D::SurfacePlot::initializeGL()
{
  if (!Plot3D::initializeGL())
  {
    gl_is_initialized_p = false;
    return false;
  }
  data_object_p = std::make_unique<GL::DataObject>();
  data_object_p->maintainNormals(true);
  gl_is_initialized_p = true;
  return true;
}
