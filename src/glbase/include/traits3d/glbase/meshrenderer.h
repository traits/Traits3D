#pragma once

#include <memory>
#include <map>
#include "traits3d/types.h"
#include "traits3d/glbase/shader.h"
#include "traits3d/glbase/vao.h"
#include "traits3d/glbase/vbo.h"
#include "traits3d/glbase/ibo.h"

namespace Traits3D
{
  namespace GL
  {
    class MeshRenderer
    {
    public:
      static const char* Traits3D::GL::MeshRenderer::VertexCoreCode;
      static const char* Traits3D::GL::MeshRenderer::VertexSeamCode;
      static const char* Traits3D::GL::MeshRenderer::FragmentCode;

      MeshRenderer();
      
      void createData(std::vector<TripleF> const& mesh_data, IndexMaker::IndexType xsize, IndexMaker::IndexType ysize);
      void draw(MatrixStack const& matrices);
    
    private:
      VAO vao_;
      Shader core_shader_;
      Shader seam_shader_;
      std::unique_ptr<VBO> core_vbo_;
      std::unique_ptr<VBO> seam_color_vbo_;
      std::unique_ptr<IBO> core_ibo_;
      std::unique_ptr<IBO> seam_ibo_;
    };
  } // ns
} // ns