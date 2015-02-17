#include "protean3d/helper.h"
#include "protean3d/surfaceplot.h"

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool Protean3D::SurfacePlot::addPositionData(std::vector<TripleF> const& data,
  size_t xsize, size_t ysize, GLenum drawtype /*= GL_STATIC_DRAW*/)
{
  if (!data_object_p->addPositionData(data, xsize, ysize, drawtype))
    return false;

  coordinates_p->init(data_object_p->hull());
  return true;
}

// todo check size against position vector[s]
bool Protean3D::SurfacePlot::addDataColor(ColorVector const& val)
{
  return data_object_p->addColor(val);
}

bool Protean3D::SurfacePlot::addMeshColor(Color const& val)
{
  return data_object_p->addMeshColor(val);
}

bool Protean3D::SurfacePlot::updatePositionData(std::vector<TripleF> const& data)
{
  if (!data_object_p->updatePositionData(data))
    return false;

  coordinates_p->init(data_object_p->hull());
  
  return true;
}

bool Protean3D::SurfacePlot::initializeGL()
{
  if (!Plot3D::initializeGL())
  {
    gl_is_initialized_p = false;
    return false;
  }
  data_object_p = std::make_unique<GL::DataObject>();
  gl_is_initialized_p = true;
  return true;
}
