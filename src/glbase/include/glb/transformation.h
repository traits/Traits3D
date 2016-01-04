#pragma once

#include "glm/glm.hpp"

namespace glb
{

//! Index Buffer Objects
class Transformation
{
public:
    Transformation();
    virtual ~Transformation() {}

    glm::mat4 const &mv() const
    {
        return mv_;
    }
    glm::mat4 const &rotation() const
    {
        return rotation_;
    }
    glm::vec3 const &scale() const
    {
        return scale_;
    }
    glm::vec3 const &translation() const
    {
        return translation_;
    }
    glm::mat4 const &proj() const
    {
        return proj_;
    }
    glm::mat3 const &normalMatrix() const
    {
        return normal_mat_;
    }
    glm::mat4 const &lightMatrix() const
    {
        return light_mat_;
    }

    //! Set model-view as combination of scaling, rotation and translation
    void setModelView(glm::vec3 const &translation, glm::mat4 const &rotation, glm::vec3 const &scale);
    //! Set normal matrix
    void setNormal(glm::mat3 const &n);
    //! Set light matrix
    void setLight(glm::mat4 const &l);
    //! Set projection matrix
    void setProjection(glm::mat4 const &proj);

    //todo
    void setProjection(bool ortho, float l, float r, float b, float t, float n, float f);

    //float proj_l() const { return p_l_; }
    //float proj_r() const { return p_r_; }
    //float proj_b() const { return p_b_; }
    //float proj_t() const { return p_t_; }
    //float proj_n() const { return p_n_; }
    //float proj_f() const { return p_f_; }

private:
    glm::mat4 mv_;
    glm::mat4 rotation_;
    glm::vec3 translation_;
    glm::vec3 scale_;
    glm::mat4 proj_;
    glm::mat3 normal_mat_;
    glm::mat4 light_mat_;


    bool ortho_;
    float p_l_;
    float p_r_;
    float p_b_;
    float p_t_;
    float p_n_;
    float p_f_;
};
} // ns