#pragma once

#include "globject.h"

namespace Protean3D
{
  namespace GL
  {
    class DataObject : public GL::Object
    {
    public:
      DataObject();

      void draw() override;

      bool addPositionData(std::vector<glm::vec3> const& data,
        size_t xsize, size_t ysize, GLenum drawtype = GL_STATIC_DRAW);

      bool updatePositionData(std::vector<glm::vec3> const& data);
      bool addColor(std::vector<glm::vec4> const& data);
      bool addMeshColor(glm::vec4 const& data);

      const Protean3D::Box& hull() const { return hull_; }

    private:
      bool initShader();
      Protean3D::Box hull_;
      void calcHull(std::vector<glm::vec3> const& data);
    };
  } // ns
} // ns
