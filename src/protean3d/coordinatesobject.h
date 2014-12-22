#pragma once

#include "coordinates.h"
#include "globject.h"

namespace Protean3D
{
  namespace GL
  {
    class CoordinatesObject : public GL::Object
    {
    public:
      CoordinatesObject();

      void draw() override;

      bool setHull(Protean3D::Box const& hull);
      //bool updatePositionData(std::vector<glm::vec3> const& data);

    private:
      GL::Shader shader_;
      Coordinates coordinates_;
      Protean3D::Box hull_;

      std::vector<glm::vec3> axes_;

      std::unique_ptr<VBO> vbo_;
    };
  } // ns
} // ns