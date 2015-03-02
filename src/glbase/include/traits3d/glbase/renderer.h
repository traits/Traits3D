#pragma once

#include <memory>
#include <map>
#include "traits3d/glbase/shader.h"
#include "traits3d/glbase/vao.h"
#include "traits3d/glbase/vbo.h"
#include "traits3d/glbase/ibo.h"

namespace Traits3D
{
  namespace GL
  {
    template <typename S_ENUM, typename V_ENUM>
    struct SV_Tuple
    {
    public:
      Shader& shader(S_ENUM val){ return *shaders_p.at(val); }
      Shader const& shader(S_ENUM val) const { return *shaders_p.at(val); }
      VBO& vbo(V_ENUM val){ return *vbos_p.at(val); }
      VBO const& vbo(V_ENUM val) const { return *vbos_p.at(val); }

    protected:
      VAO vao_p;
      std::map<S_ENUM, std::unique_ptr<Shader>> shaders_p;
      std::map<V_ENUM, std::unique_ptr<VBO>> vbos_p;
    };

    template <typename S_ENUM, typename V_ENUM, typename I_ENUM>
    struct SVI_Tuple : public SV_Tuple<S_ENUM, V_ENUM>
    {
    public:
      IBO& ibo(I_ENUM val){ return *ibos_p.at(val); }
      IBO const& ibo(I_ENUM val) const { return *ibos_p.at(val); }

    protected:
      std::map<I_ENUM, std::unique_ptr<IBO>> ibos_p;
    };

    enum class VBOindex
    {
      Position,
      DataColor
    };

    //enum class IBOindex
    //{
    //  Mesh,
    //  Polygons
    //};

    enum class ShaderIndex
    {
      Lines,
      TriangleStrip
    };


    class Renderer : SV_Tuple<ShaderIndex,VBOindex>
    {
    public:
      Renderer()
      {
        shaders_p[ShaderIndex::Lines] = std::make_unique<Shader>();
        if (!shader(ShaderIndex::Lines).create(GL::ShaderCode::Vertex::Line, GL::ShaderCode::Fragment::Simple))
          return; //todo throw

        vbos_p[VBOindex::Position] = std::make_unique<VBO>(&vao_p, 3);
        vbos_p[VBOindex::DataColor] = std::make_unique<VBO>(&vao_p, 4);
      }

    private:
    };
  } // ns
} // ns