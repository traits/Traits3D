#pragma once

#include "glb/glhelper.h"
#include "traits3d/global.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
//#include <windows.h>                      // Header File For Windows
//#include <GL\gl.h>                        // Header File For The GLu32 Library

// 8<--Snip here if you have your own math types/funcs-->8


//typedef union Matrix3f_t
//    {
//            struct
//            {
//                //column major
//                GLfloat M00;  //XAxis.X and Scale X
//                GLfloat M10;  //XAxis.Y
//                GLfloat M20;  //XAxis.Z
//                GLfloat M01;  //YAxis.X
//                GLfloat M11;  //YAxis.Y and Scale Y
//                GLfloat M21;  //YAxis.Z
//                GLfloat M02;  //ZAxis.X
//                GLfloat M12;  //ZAxis.Y
//                GLfloat M22;  //ZAxis.Z and Scale Z
//            } s;
//            GLfloat M[9];
//    } Matrix3fT;     //A single precision floating point 3 by 3 matrix.
//
//    typedef union Matrix4f_t
//    {
//            struct
//            {
//                //column major
//                GLfloat M00;  //XAxis.X and Scale X
//                GLfloat M10;  //XAxis.Y
//                GLfloat M20;  //XAxis.Z
//                GLfloat M30;  //XAxis.W
//                GLfloat M01;  //YAxis.X
//                GLfloat M11;  //YAxis.Y and Scale Y
//                GLfloat M21;  //YAxis.Z
//                GLfloat M31;  //YAxis.W
//                GLfloat M02;  //ZAxis.X
//                GLfloat M12;  //ZAxis.Y
//                GLfloat M22;  //ZAxis.Z and Scale Z
//                GLfloat M32;  //ZAxis.W
//                GLfloat M03;  //Trans.X
//                GLfloat M13;  //Trans.Y
//                GLfloat M23;  //Trans.Z
//                GLfloat M33;  //Trans.W and Scale W
//            } s;
//            GLfloat M[16];
//    } Matrix4fT;     //A single precision floating point 4 by 4 matrix.


namespace traits3d
{
class TRAITS3D_EXPORT ArcBall
{
public:
    //Create/Destroy
    explicit ArcBall(GLfloat width = 1.1f, GLfloat height = 1.1f);
    ~ArcBall() = default;

    //Set new bounds
    void setBounds(GLfloat width, GLfloat height);

    //Mouse down
    void start(glm::vec2 const &pos2d);

    //Mouse drag, calculate rotation
    glm::quat quaternion(glm::vec2 const &pos2d);

    /**
    * Returns matrix conversion of the
    * quaternion argument.
    * @param q1 the quaternion to be converted
    */
    //$hack this can be optimized some(if s == 0)
    static glm::mat3 rotationMatrix(const glm::quat &q1);

    /**
    * Sets the rotational component (upper 3x3) of this matrix to the matrix
    * values in the T precision Matrix3d argument; the other elements of
    * this matrix are unchanged; a singular value decomposition is performed
    * on this object's upper 3x3 matrix to factor out the scale, then this
    * object's upper 3x3 matrix components are replaced by the passed rotation
    * components, and then the scale is reapplied to the rotational
    * components.
    * @param m1 T precision 3x3 matrix
    */
    static void setRotationalComponent(glm::mat4 &NewObj, const glm::mat3 &m1);

private:
    const float Epsilon_ = 1.0e-5f;

    glm::vec3   start_position_ = glm::vec3(0);          //Saved click vector
    GLfloat     adjust_width_;    //Mouse bounds width
    GLfloat     adjust_height_;   //Mouse bounds height

    glm::vec3 mapToSphere(glm::vec2 const &pos2d) const;

    //Math functions

    static void matrix4fSetRotationScaleFromMatrix4f(glm::mat4 &NewObj, const glm::mat4 &m1);

    /**
    * Performs SVD on this matrix and gets scale and rotation.
    * Rotation is placed into rot3, and rot4.
    * @param rot3 the rotation factor(Matrix3d). if null, ignored
    * @param rot4 the rotation factor(Matrix4) only upper 3x3 elements are changed. if null, ignored
    * @return scale factor
    */
    static GLfloat Matrix4fSVD(const glm::mat4 &NewObj);

    static void matrix4fSetRotationScaleFromMatrix3f(glm::mat4 &NewObj, const glm::mat3 &m1);

    static void matrix4fMulRotationScale(glm::mat4 &NewObj, GLfloat scale);


    // 8<--Snip here if you have your own math types/funcs-->8
};

} //ns
