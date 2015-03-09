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
      static const char* Traits3D::GL::MeshRenderer::VertexCode;
      static const char* Traits3D::GL::MeshRenderer::FragmentCode;

      MeshRenderer();
      
      void createData(std::vector<TripleF> const& mesh_data, IndexMaker::IndexType xsize, IndexMaker::IndexType ysize);
      void draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix);
    
    private:
      Shader shader_;
      VAO vao_;
      std::unique_ptr<VBO> vbo_;
      std::unique_ptr<IBO> ibo_core_;
//      std::unique_ptr<IBO> ibo_border_;
    };
  } // ns
} // ns