#include "glb/glhelper.h"

#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include "traits3d/textengine/stb_truetype.h"

#include "glb/vao.h"
#include "glb/vbo.h"
#include "glb/shader.h"
#include "traits3d/textengine/textengine_std.h"

namespace traits3d
{

class StandardTextEngine::FontAtlas
{
public:
    GLuint texture_atlas;
    std::vector<stbtt_bakedchar> bc_vec;
    std::string font_name;
    size_t font_height = 0;
};


StandardTextEngine::~StandardTextEngine() = default;

StandardTextEngine::StandardTextEngine()
    : VertexCode_(
          #ifdef GL_ES_VERSION_3_0
          "#version 300 es\n"
          #else
          "#version 330\n"
          #endif
          "in vec4 coord;\n"
          "out vec2 texpos; \n"
          "uniform mat4 proj_mat; \n"
          "void main()\n"
          "{\n"
          "  gl_Position = proj_mat * vec4(coord.xy, 0, 1); \n"
          "  texpos = coord.zw; \n"
          "}"
      ),
      FragmentCode_(
          #ifdef GL_ES_VERSION_3_0
          "#version 300 es\n"
          #else
          "#version 330\n"
          #endif
          "in vec2 texpos;\n"
          "uniform sampler2D tex;\n"
          "uniform vec3 color;\n"
          "void main()\n"
          "{\n"
          "  gl_FragColor = vec4(color, texture2D(tex, texpos).r);\n"
          "}"
      )
{
}

bool StandardTextEngine::initializeGL()
{
    shader_ = std::make_unique<glb::Shader>();

    if (!shader_->create(VertexCode_, FragmentCode_))
        return false;

    vao_ = std::make_unique<glb::VAO>();
    vbo_ = std::make_unique<glb::VBO>(vao_.get(), 4);
    return vbo_->bindAttribute(shader_->programId(), "coord");
}

bool StandardTextEngine::setText(std::string const &text, size_t index /*= 0*/)
{
    if (index >= quadded_texts_.size())
        return false;

    if (quadded_texts_[index].text.text == text)
        return true;

    data_changed_ = true;
    return createQuaddedText(quadded_texts_[index], text, quadded_texts_[index].font_info);
}

bool StandardTextEngine::createQuaddedText(QuaddedText &qt, std::string const &text, FontInfo const &font_info)
{
    if (text.empty())
        return false;

    //if (qt.atlas.get() == nullptr)
    {
        size_t idx;

        if (!requestFontTexture(idx, font_info.font_name, 96, font_info.font_height))
            return false;

        qt.atlas = font_atlases_[idx];
    }
    Text &t = qt.text;
    Quads &qv = qt.coordinates;
    FontAtlas &atlas = *qt.atlas;
    t.text = text;
    t.hull = Hull(); // reset //todo?
    qv.resize(text.size());
    float dx = 0;
    float dy = 0;

    for (size_t i = 0; i != t.text.size(); ++i)
    {
        auto &ch = t.text[i];

        if (ch >= 32 /*&& ch < 128*/)
        {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(&atlas.bc_vec[0], 512, 512, ch - 32, &dx, &dy, &q, 1);
            qv[i][0] = glm::vec4(q.x0, q.y0, q.s0, q.t0);
            qv[i][1] = glm::vec4(q.x0, q.y1, q.s0, q.t1);
            qv[i][2] = glm::vec4(q.x1, q.y0, q.s1, q.t0);
            qv[i][3] = glm::vec4(q.x0, q.y1, q.s0, q.t1);
            qv[i][4] = glm::vec4(q.x1, q.y0, q.s1, q.t0);
            qv[i][5] = glm::vec4(q.x1, q.y1, q.s1, q.t1);

            if (q.x0 < t.hull.bl.x)
                t.hull.bl.x = q.x0;

            if (q.x1 > t.hull.tr.x)
                t.hull.tr.x = q.x1;

            if (q.y0 < t.hull.bl.y)
                t.hull.bl.y = q.y0;

            if (q.y1 > t.hull.tr.y)
                t.hull.tr.y = q.y1;
        }
    }

    return true;
}

bool StandardTextEngine::setTexts(std::vector<std::string> const &texts, std::vector<FontInfo> const &font_info)
{
    if (texts.size() != font_info.size())
        return false;

    data_changed_ = quadded_texts_.size() != texts.size();

    if (!data_changed_)
    {
        for (size_t i = 0; i != texts.size(); ++i)
        {
            if (texts[i] != quadded_texts_[i].text.text || font_info[i] != quadded_texts_[i].font_info)
            {
                data_changed_ = true;
                break;
            }
        }
    }

    if (data_changed_)
    {
        clear();

        for (size_t j = 0; j != texts.size(); ++j)
            if (!appendText(texts[j], font_info[j]))
                return false;
    }

    return true;
}

bool StandardTextEngine::appendText(std::string const &text, FontInfo const &font_info)
{
    QuaddedText qt;

    if (!createQuaddedText(qt, text, font_info))
        return false;

    quadded_texts_.push_back(qt);
    data_changed_ = true;
    return true;
}

bool StandardTextEngine::draw(
    std::vector<TextEngine::Position> const &positions,
    std::vector<Color> const &colors)
{
    if (quadded_texts_.empty())
        return true;

    if (positions.size() != quadded_texts_.size()
        || colors.size() != quadded_texts_.size())
        return false;

    if (!shader_->use())
        return false;

    for (size_t i = 0; i != quadded_texts_.size(); ++i)
    {
        quadded_texts_[i].text.position = positions[i];
        quadded_texts_[i].text.color = colors[i];
    }

    if (data_changed_)
    {
        std::vector<glm::vec4> coords;

        for (size_t i = 0; i != quadded_texts_.size(); ++i)
        {
            for (auto ch : quadded_texts_[i].coordinates)
                coords.insert(coords.end(), ch.begin(), ch.end());
        }

        if (!vbo_->setData(coords))
            return false;

        data_changed_ = false;
    }

    GLint oldtex = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldtex);
    GLint oldactivetex = 0;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &oldactivetex);
    glActiveTexture(GL_TEXTURE0);
    glb::State blend(GL_BLEND, GL_TRUE), depth_test(GL_DEPTH_TEST, GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //if (wireframe)
    //{
    //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //}
    glm::ivec4 viewport = glb::viewPort();
    size_t sidx = 0;
    size_t step = 0;
    glm::vec2 tpos;

    for (auto qt : quadded_texts_)
    {
        auto t = qt.text;
        tpos = t.position.coordinates;

        switch (t.position.anchor)
        {
            case Anchor::BottomCenter:
                tpos.x -= 0.5f * t.hull.width();
                break;

            case Anchor::BottomRight:
                tpos.x -= t.hull.width();
                break;

            case Anchor::CenterLeft:
                tpos.y -= 0.5f * t.hull.height();
                break;

            case Anchor::Center:
                tpos -= 0.5f * glm::vec2(t.hull.width(), t.hull.height());
                break;

            case Anchor::CenterRight:
                tpos -= glm::vec2(t.hull.width(), 0.5 * t.hull.height());
                break;

            case Anchor::TopLeft:
                tpos.y -= t.hull.height();
                break;

            case Anchor::TopCenter:
                tpos -= glm::vec2(0.5f * t.hull.width(), t.hull.height());
                break;

            case Anchor::TopRight:
                tpos -= glm::vec2(t.hull.width(), t.hull.height());
                break;

            default:
                break;
        }

        // move viewport to make text appear at the right position
        glm::mat4 pmat = glm::ortho<float>(
                             static_cast<float>(viewport[0] - tpos.x),
                             static_cast<float>(viewport[0] + viewport[2] - tpos.x),
                             // reverse y axis
                             static_cast<float>(tpos.y),
                             static_cast<float>(tpos.y - viewport[3])
                         );
        shader_->setUniformMatrix(pmat, "proj_mat");
        shader_->setUniformVec3(glm::vec3(t.color.r, t.color.g, t.color.b), "color");
        glBindTexture(GL_TEXTURE_2D, qt.atlas->texture_atlas);
        GLuint texture_sampler = glGetUniformLocation(shader_->programId(), "tex");
        glUniform1i(texture_sampler, 0);
        step = std::tuple_size<Quad>::value *  t.text.size();
        vbo_->draw(GL_TRIANGLES, sidx, step);
        sidx += step;
    }

    //if (wireframe)
    //{
    //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //}
    glBindTexture(GL_TEXTURE_2D, oldtex);
    glActiveTexture((GLenum)oldactivetex);
    return true;
}

void StandardTextEngine::clear()
{
    quadded_texts_.clear();
    data_changed_ = true;
}

bool StandardTextEngine::requestFontTexture(size_t &index, std::string const &font_name, size_t glyph_cnt, size_t font_height)
{
    auto it = std::find_if(font_atlases_.begin(), font_atlases_.end(),
                           [&font_name, font_height](std::shared_ptr<FontAtlas> e)
    {
        return font_name == e->font_name && e->font_height == font_height;
    }
                          );

    if (it == font_atlases_.end())
    {
        font_atlases_.push_back(std::make_shared<FontAtlas>());
        index = font_atlases_.size() - 1;
    }
    else
    {
        index = it - font_atlases_.begin();

        if ((*it)->bc_vec.size() == glyph_cnt)
            return true;
    }

    std::shared_ptr<FontAtlas> curr = font_atlases_[index];
    curr->bc_vec.resize(glyph_cnt); // ASCII 32..126 is 95 glyphs
    const int bmsize = 512;
    unsigned char bitmap[bmsize * bmsize];

    try // map.at()
    {
        if (-1 == stbtt_BakeFontBitmap(&Font::repository().at(font_name)->data[0], 0, static_cast<float>(font_height),
                                       bitmap, bmsize, bmsize, 32, int(glyph_cnt), &curr->bc_vec[0])) // no guarantee this fits!
            return false;
    }
    catch (std::out_of_range &)
    {
        return false;
    }

    curr->font_name = font_name;
    curr->font_height = font_height;
    glGenTextures(1, &curr->texture_atlas);
    GLint oldtex = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldtex);
    glBindTexture(GL_TEXTURE_2D, curr->texture_atlas);
    // GL_RED here, because GL_ALPHA is not longer supported from newer OpenGL versions
    // requires change from .a to .r component in fragment shader too
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, GLsizei(bmsize), GLsizei(bmsize), 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
    // temp_bitmap free-able from this point
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, oldtex);
    return true;
}

} // ns