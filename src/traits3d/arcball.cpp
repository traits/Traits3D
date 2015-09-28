#include "traits3d/arcball.h"

//ArcbBall sphere constants:
//Diameter is       2.0f
//Radius is         1.0f
//Radius squared is 1.0f

//Create/Destroy
Traits3D::ArcBall::ArcBall(GLfloat width /*= 1.1f*/, GLfloat height /*= 1.1f*/)
{
    //Set initial bounds
    setBounds(width, height);
}

glm::vec3 Traits3D::ArcBall::mapToSphere(glm::vec2 const &pos2d) const
{
    glm::vec2 tmp = pos2d;
    // adjusting point coordinates and scaling down into [-1,1]
    tmp.x = (tmp.x * adjust_width_) - 1.0f;
    tmp.y = 1.0f - (tmp.y * adjust_height_);
    GLfloat length = (tmp.x * tmp.x) + (tmp.y * tmp.y);

    // if the point is mapped outside of the sphere... (length > radius squared)
    if (length > 1.0f)
    {
        //Compute a normalizing factor (radius / sqrt(length))
        GLfloat norm = 1.0f / std::sqrt(length);
        //Return the "normalized" vector, a point on the sphere
        return glm::vec3(tmp.x * norm, tmp.y * norm, 0.0f);
    }
    else    // it's on the inside
    {
        //Return a vector to a point mapped inside the sphere sqrt(radius squared - length)
        return glm::vec3(tmp.x, tmp.y, std::sqrt(1.0f - length));
    }
}

void Traits3D::ArcBall::matrix4fSetRotationScaleFromMatrix4f(glm::mat4 &NewObj, const glm::mat4 &m1)
{
    NewObj[0][0] = m1[0][0];
    NewObj[1][0] = m1[1][0];
    NewObj[2][0] = m1[2][0];
    NewObj[0][1] = m1[0][1];
    NewObj[1][1] = m1[1][1];
    NewObj[2][1] = m1[2][1];
    NewObj[0][2] = m1[0][2];
    NewObj[1][2] = m1[1][2];
    NewObj[2][2] = m1[2][2];
}

GLfloat Traits3D::ArcBall::Matrix4fSVD(const glm::mat4 &NewObj)
{
    //Matrix3fT rot3; //todo
    //Matrix4fT rot4;
    GLfloat s/*, n*/;
    // this is a simple svd.
    // Not complete but fast and reasonable.
    // See comment in Matrix3d.
    s = std::sqrt(
            ((NewObj[0][0] * NewObj[0][0]) + (NewObj[0][1] * NewObj[0][1]) + (NewObj[0][2] * NewObj[0][2]) +
             (NewObj[1][0] * NewObj[1][0]) + (NewObj[1][1] * NewObj[1][1]) + (NewObj[1][2] * NewObj[1][2]) +
             (NewObj[2][0] * NewObj[2][0]) + (NewObj[2][1] * NewObj[2][1]) + (NewObj[2][2] * NewObj[2][2])) / 3.0f);
    //if (rot3)   //if pointer not null
    //{
    //    //getRotationScale(rot3);
    //    rot3[0][0] = NewObj[0][0]; rot3[0][1] = NewObj[0][1]; rot3[0][2] = NewObj[0][2];
    //    rot3[1][0] = NewObj[1][0]; rot3[1][1] = NewObj[1][1]; rot3[1][2] = NewObj[1][2];
    //    rot3[2][0] = NewObj[2][0]; rot3[2][1] = NewObj[2][1]; rot3[2][2] = NewObj[2][2];
    //    // zero-div may occur.
    //    n = 1.0f / std::sqrt( (NewObj[0][0] * NewObj[0][0]) +
    //                              (NewObj[0][1] * NewObj[0][1]) +
    //                              (NewObj[0][2] * NewObj[0][2]) );
    //    rot3[0][0] *= n;
    //    rot3[0][1] *= n;
    //    rot3[0][2] *= n;
    //    n = 1.0f / std::sqrt( (NewObj[1][0] * NewObj[1][0]) +
    //                              (NewObj[1][1] * NewObj[1][1]) +
    //                              (NewObj[1][2] * NewObj[1][2]) );
    //    rot3[1][0] *= n;
    //    rot3[1][1] *= n;
    //    rot3[1][2] *= n;
    //    n = 1.0f / std::sqrt( (NewObj[2][0] * NewObj[2][0]) +
    //                              (NewObj[2][1] * NewObj[2][1]) +
    //                              (NewObj[2][2] * NewObj[2][2]) );
    //    rot3[2][0] *= n;
    //    rot3[2][1] *= n;
    //    rot3[2][2] *= n;
    //}
    //if (rot4)   //if pointer not null
    //{
    //    if (rot4 != NewObj)
    //    {
    //        Matrix4fSetRotationScaleFromMatrix4f(rot4, NewObj);  // private method
    //    }
    //    // zero-div may occur.
    //    n = 1.0f / std::sqrt( (NewObj[0][0] * NewObj[0][0]) +
    //                              (NewObj[0][1] * NewObj[0][1]) +
    //                              (NewObj[0][2] * NewObj[0][2]) );
    //    rot4[0][0] *= n;
    //    rot4[0][1] *= n;
    //    rot4[0][2] *= n;
    //    n = 1.0f / std::sqrt( (NewObj[1][0] * NewObj[1][0]) +
    //                              (NewObj[1][1] * NewObj[1][1]) +
    //                              (NewObj[1][2] * NewObj[1][2]) );
    //    rot4[1][0] *= n;
    //    rot4[1][1] *= n;
    //    rot4[1][2] *= n;
    //    n = 1.0f / std::sqrt( (NewObj[2][0] * NewObj[2][0]) +
    //                              (NewObj[2][1] * NewObj[2][1]) +
    //                              (NewObj[2][2] * NewObj[2][2]) );
    //    rot4[2][0] *= n;
    //    rot4[2][1] *= n;
    //    rot4[2][2] *= n;
    //}
    return s;
}

void Traits3D::ArcBall::matrix4fSetRotationScaleFromMatrix3f(glm::mat4 &NewObj, const glm::mat3 &m1)
{
    NewObj[0][0] = m1[0][0];
    NewObj[1][0] = m1[1][0];
    NewObj[2][0] = m1[2][0];
    NewObj[0][1] = m1[0][1];
    NewObj[1][1] = m1[1][1];
    NewObj[2][1] = m1[2][1];
    NewObj[0][2] = m1[0][2];
    NewObj[1][2] = m1[1][2];
    NewObj[2][2] = m1[2][2];
}

void Traits3D::ArcBall::matrix4fMulRotationScale(glm::mat4 &NewObj, GLfloat scale)
{
    NewObj[0][0] *= scale;
    NewObj[1][0] *= scale;
    NewObj[2][0] *= scale;
    NewObj[0][1] *= scale;
    NewObj[1][1] *= scale;
    NewObj[2][1] *= scale;
    NewObj[0][2] *= scale;
    NewObj[1][2] *= scale;
    NewObj[2][2] *= scale;
}

void Traits3D::ArcBall::setBounds(GLfloat width, GLfloat height)
{
    assert((width > 1.0f) && (height > 1.0f));
    //Set adjustment factor for width/height
    adjust_width_ = 1.0f / ((width - 1.0f) * 0.5f);
    adjust_height_ = 1.0f / ((height - 1.0f) * 0.5f);
}

//Mouse down
void Traits3D::ArcBall::start(glm::vec2 const &pos2d)
{
    start_position_ = mapToSphere(pos2d);
}

//Mouse dragged to pos2d, calculate rotation quaternion
glm::quat Traits3D::ArcBall::quaternion(glm::vec2 const &pos2d)
{
    //Map the point to the sphere
    glm::vec3 current_pos =  mapToSphere(pos2d);
    //Return the quaternion equivalent to the rotation
    //Compute the vector perpendicular to the begin and end vectors
    glm::vec3 cp = glm::cross(start_position_, current_pos);

    //Compute the length of the perpendicular vector
    if (cp.length() > Epsilon_)    //if its non-zero
    {
        //We're ok, so return the perpendicular vector as the transform after all
        //In the quaternion values, w is cosine (theta / 2), where theta is rotation angle
        return glm::quat(glm::dot(start_position_, current_pos), cp);
    }
    else                                    //if its zero
    {
        //The begin and end vectors coincide, so return an identity transform
        return glm::quat(0, 0, 0, 0);
    }
}

glm::mat3 Traits3D::ArcBall::rotationMatrix(const glm::quat &q1)
{
    glm::mat3 ret;
    GLfloat n, s;
    GLfloat xs, ys, zs;
    GLfloat wx, wy, wz;
    GLfloat xx, xy, xz;
    GLfloat yy, yz, zz;
    n = (q1.x * q1.x) + (q1.y * q1.y) + (q1.z * q1.z) + (q1.w * q1.w);
    s = (n > 0.0f) ? (2.0f / n) : 0.0f;
    xs = q1.x * s;
    ys = q1.y * s;
    zs = q1.z * s;
    wx = q1.w * xs;
    wy = q1.w * ys;
    wz = q1.w * zs;
    xx = q1.x * xs;
    xy = q1.x * ys;
    xz = q1.x * zs;
    yy = q1.y * ys;
    yz = q1.y * zs;
    zz = q1.z * zs;
    ret[0][0] = 1.0f - (yy + zz);
    ret[1][0] = xy - wz;
    ret[2][0] = xz + wy;
    ret[0][1] = xy + wz;
    ret[1][1] = 1.0f - (xx + zz);
    ret[2][1] = yz - wx;
    ret[0][2] = xz - wy;
    ret[1][2] = yz + wx;
    ret[2][2] = 1.0f - (xx + yy);
    return ret;
}

void Traits3D::ArcBall::setRotationalComponent(glm::mat4 &NewObj, const glm::mat3 &m1)
{
    GLfloat scale;
    scale = Matrix4fSVD(NewObj/*, NULL, NULL*/);
    matrix4fSetRotationScaleFromMatrix3f(NewObj, m1);
    matrix4fMulRotationScale(NewObj, scale);
}

