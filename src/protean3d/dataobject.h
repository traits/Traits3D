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
      bool addMeshColor(Color const& data);

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

      std::map<ShaderIndex, Shader> shader_;
      std::map<VBOindex, std::unique_ptr<VBO>> vbos_;
      std::map<IBOindex, std::unique_ptr<IBO>> ibos_;
    };

  } // ns
} // ns
