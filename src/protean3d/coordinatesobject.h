#pragma once

#include <memory>
#include "globject.h"

namespace Protean3D
{
  namespace GL
  {
    class CoordinatesObject : public GL::Object
    {
    public:
      CoordinatesObject();

      void draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix) override;

      bool setHull(Protean3D::Box const& hull);
      //bool updatePositionData(std::vector<glm::vec3> const& data);

    private:
      GL::Shader shader_;
      Protean3D::Box hull_;

      std::vector<glm::vec3> axes_;

      std::unique_ptr<VBO> vbo_;
    };
  } // ns
} // ns
