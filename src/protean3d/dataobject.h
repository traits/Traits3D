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
      bool addColorData(std::vector<glm::vec4> const& data);

    private:
      bool initShader();
    };
  } // ns
} // ns
