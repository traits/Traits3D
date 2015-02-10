#include "protean3d/helper.h"
#include "protean3d/surfaceplot.h"

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool Protean3D::SurfacePlot::addPositionData(std::vector<glm::vec3> const& data,
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

bool Protean3D::SurfacePlot::addMeshColor(glm::vec4 const& val)
{
  return data_object_p->addMeshColor(val);
}

bool Protean3D::SurfacePlot::updatePositionData(std::vector<glm::vec3> const& data)
{
  if (!data_object_p->updatePositionData(data))
    return false;

  coordinates_p->init(data_object_p->hull());
  
  return true;
}

bool Protean3D::SurfacePlot::initializeGL()
{
  if (!Plot3D::initializeGL())
    return false;
  data_object_p = std::make_unique<GL::DataObject>();
  return true;
}
