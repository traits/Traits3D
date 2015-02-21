#pragma once

#include <memory>
#include <map>
#include "globject.h"

namespace Traits3D
{
  namespace GL
  {
    class DataObject : public GL::Object
    {
      public:
        DataObject();

        void draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix) override;

        bool addPositionData(TripleVector const& data,
                             size_t xsize, size_t ysize, GLenum drawtype = GL_STATIC_DRAW);

        bool updatePositionData(TripleVector const& data);

        bool addPositionData(std::vector<TripleF> const& data,
                             size_t xsize, size_t ysize, GLenum drawtype = GL_STATIC_DRAW);

        bool addPositionDataCommon(size_t xsize, size_t ysize, std::vector<TripleF> const& data, GLenum drawtype);

        bool updatePositionData(std::vector<TripleF> const& data);
        bool addColor(ColorVector const& data);
        bool addMeshColor(Color const& data);

        const Traits3D::Box& hull() const
        {
          return hull_;
        }

      private:
        bool initShader();
        Traits3D::Box hull_;
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

        void calculateBox(std::vector<TripleF> const& data);
    };
  } // ns
} // ns