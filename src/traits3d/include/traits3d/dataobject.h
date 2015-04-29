#pragma once

#include <memory>
#include <map>
#include "traits3d/matrix.h"
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
      void setDrawType(GLenum val);

      bool setPositionData(MatrixF const& data);
      bool setPositionData(TripleVector const& data,
        size_t xsize, size_t ysize);
      bool updatePositionData(TripleVector const& data);

      bool setPositionData(std::vector<TripleF> const& data,
        size_t xsize, size_t ysize);
      bool updatePositionData(std::vector<TripleF> const& data);


      void setColor(ColorVector const& data);
      bool setMeshColor(Color const& data);

      const Traits3D::Box& hull() const { return data_.value.hull(); }

    private:
      bool initShader();
      StateEntity<ColorVector> colors_;
      StateEntity<MatrixF> data_;

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

      //GL::MeshRenderer mesh_renderer_;
    };
  } // ns
} // ns
