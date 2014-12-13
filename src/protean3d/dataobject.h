#pragma once

#include <memory>
#include <map>
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
      bool addColor(ColorVector const& data);
      bool addMeshColor(glm::vec4 const& data);

      const Protean3D::Box& hull() const { return hull_; }

    private:
      bool initShader();
      Protean3D::Box hull_;
      ColorVector colors_;

      enum class VBOindex
      {
        Position,
        DataColor
      };
    
      enum class IBOindex
      {
        Mesh,
        Polygons
      };
      
      enum class ShaderIndex
      {
        Lines,
        TriangleStrip
      };

      static const std::map<VBOindex, size_t> vidx;

      VBO& vbo(VBOindex idx) { return vao_p.vbo(vidx.at(idx)); }

      template <typename T>
      bool updateVBO(VBOindex idx, std::vector<T> const& data)
      {
        return vao_p.updateVBO(vidx.at(idx), data);
      }

      std::map<ShaderIndex, Shader> shader_;

    };

  } // ns
} // ns
