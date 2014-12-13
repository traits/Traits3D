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

      template <typename P, typename... Params>
      class EnumedContainer;

      template <typename C, typename E>
      class EnumedContainer < VAO, C, E >
      {

      };

      template <>
      class EnumedContainer < Shader, ShaderIndex >
      {
      public:
        explicit EnumedContainer(std::vector<Shader>& data)
        : data_(data) {}
  
        Shader& operator[](ShaderIndex idx) { return data_[idx_map.at(idx)]; }

      private:
        static const std::map<ShaderIndex, size_t> idx_map;
        std::vector<Shader>& data_;
      };
      

      EnumedContainer<VAO, VBO, VBOindex> vbos;
      EnumedContainer<VAO, IBO, IBOindex> ibos;
      EnumedContainer<Shader, ShaderIndex> shader_;

    };

  } // ns
} // ns
