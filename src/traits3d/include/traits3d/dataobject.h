#pragma once

#include <memory>
#include <map>
#include "traits3d/glbase/meshrenderer.h"
#include "traits3d/glbase/globject.h"

namespace Traits3D
{
  namespace GL
  {
    class DataObject : public GL::Object
    {
      public:
        DataObject();

        void draw(Transformation const& matrices) override;

        bool setPositionData(TripleVector const& data,
                             size_t xsize, size_t ysize, GLenum drawtype = GL_STATIC_DRAW);
        bool updatePositionData(TripleVector const& data);

        bool setPositionData(std::vector<TripleF> const& data,
                             size_t xsize, size_t ysize, GLenum drawtype = GL_STATIC_DRAW);
        bool updatePositionData(std::vector<TripleF> const& data);
        
        bool setColor(ColorVector const& data);
        bool setMeshColor(Color const& data);

        const Traits3D::Box& hull() const
        {
          return hull_;
        }

      private:
        bool initShader();
        Traits3D::Box hull_;
        ColorVector colors_;
        std::vector<TripleF> data_;

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

        GL::MeshRenderer mesh_renderer_;

        bool addPositionDataCommon(size_t xsize, size_t ysize, std::vector<TripleF> const& data, GLenum drawtype);
    };
  } // ns
} // ns
