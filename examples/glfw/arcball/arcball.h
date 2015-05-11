/** KempoApi: The Turloc Toolkit *****************************/
/** *    *                                                  **/
/** **  **  Filename: ArcBall.h                             **/
/**   **    Version:  Common                                **/
/**   **                                                    **/
/**                                                         **/
/**  Arcball class for mouse manipulation.                  **/
/**                                                         **/
/**                                                         **/
/**                                                         **/
/**                                                         **/
/**                              (C) 1999-2003 Tatewake.com **/
/**   History:                                              **/
/**   08/17/2003 - (TJG) - Creation                         **/
/**   09/23/2003 - (TJG) - Bug fix and optimization         **/
/**   09/25/2003 - (TJG) - Version for NeHe Basecode users  **/
/**                                                         **/
/*************************************************************/
#pragma once

#include <glm/glm.hpp>
#include <windows.h>											// Header File For Windows
#include <gl\glu.h>												// Header File For The GLu32 Library

// 8<--Snip here if you have your own math types/funcs-->8 

//Only support assertions in debug builds
#ifdef _DEBUG
# include "assert.h"
#else
# define assert(x) { }
#endif

//Math types derived from the KempoApi tMath library

using Tuple2fT = glm::vec2;
using Tuple3fT = glm::vec3;
using Tuple4fT = glm::vec4;

using Matrix3fT = glm::mat3;
using Matrix4fT = glm::mat4;

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


//"Inherited" types
#define Point2fT    Tuple2fT   //A 2 element point that is represented by single precision floating point x,y coordinates. 

#define Quat4fT     Tuple4fT   //A 4 element unit quaternion represented by single precision floating point x,y,z,w coordinates. 

#define Vector2fT   Tuple2fT   //A 2-element vector that is represented by single-precision floating point x,y coordinates. 
#define Vector3fT   Tuple3fT   //A 3-element vector that is represented by single-precision floating point x,y,z coordinates. 

//Custom math, or speed overrides
#define FuncSqrt    sqrtf

//utility macros
//assuming IEEE-754(GLfloat), which i believe has max precision of 7 bits
# define Epsilon 1.0e-5

//Math functions

    /**
     * Sets the value of this tuple to the vector sum of itself and tuple t1.
     * @param t1  the other tuple
     */
    inline
    static void Point2fAdd(Point2fT* NewObj, const Tuple2fT* t1)
    {
        assert(NewObj && t1);

        NewObj->x += t1->x;
        NewObj->y += t1->y;
    }

    /**
      * Sets the value of this tuple to the vector difference of itself and tuple t1 (this = this - t1).
      * @param t1 the other tuple
      */
    inline
    static void Point2fSub(Point2fT* NewObj, const Tuple2fT* t1)
    {
        assert(NewObj && t1);

        NewObj->x -= t1->x;
        NewObj->y -= t1->y;
    }

    /**
      * Sets this vector to be the vector cross product of vectors v1 and v2.
      * @param v1 the first vector
      * @param v2 the second vector
      */
    inline
    static void Vector3fCross(Vector3fT* NewObj, const Vector3fT* v1, const Vector3fT* v2)
    {
        Vector3fT Result; //safe not to initialize

        assert(NewObj && v1 && v2);

        // store on stack once for aliasing-safty
        // i.e. safe when a.cross(a, b)

        Result.x = (v1->y * v2->z) - (v1->z * v2->y);
        Result.y = (v1->z * v2->x) - (v1->x * v2->z);
        Result.z = (v1->x * v2->y) - (v1->y * v2->x);

        //copy result back
        *NewObj = Result;
    }

    /**
      * Computes the dot product of the this vector and vector v1.
      * @param  v1 the other vector
      */
    inline
    static GLfloat Vector3fDot(const Vector3fT* NewObj, const Vector3fT* v1)
    {
        assert(NewObj && v1);

        return  (NewObj->x * v1->x) +
                (NewObj->y * v1->y) +
                (NewObj->z * v1->z);
    }

    /**
      * Returns the squared length of this vector.
      * @return the squared length of this vector
      */
    inline
    static GLfloat Vector3fLengthSquared(const Vector3fT* NewObj)
    {
        assert(NewObj);

        return  (NewObj->x * NewObj->x) +
                (NewObj->y * NewObj->y) +
                (NewObj->z * NewObj->z);
    }

    /**
      * Returns the length of this vector.
      * @return the length of this vector
      */
    inline
    static GLfloat Vector3fLength(const Vector3fT* NewObj)
    {
        assert(NewObj);

        return FuncSqrt(Vector3fLengthSquared(NewObj));
    }

    inline
    static void Matrix3fSetZero(Matrix3fT& NewObj)
    {
        NewObj[0][0] = NewObj[1][0] = NewObj[2][0] = 
        NewObj[0][1] = NewObj[1][1] = NewObj[2][1] = 
        NewObj[0][2] = NewObj[1][2] = NewObj[2][2] = 0.0f;
    }

    /**
     * Sets this Matrix3 to identity.
     */
    inline
    static void Matrix3fSetIdentity(Matrix3fT& NewObj)
    {
        Matrix3fSetZero(NewObj);

        //then set diagonal as 1
        NewObj[0][0] = 
        NewObj[1][1] = 
        NewObj[2][2] = 1.0f;
    }

    /**
      * Sets the value of this matrix to the matrix conversion of the
      * quaternion argument. 
      * @param q1 the quaternion to be converted 
      */
    //$hack this can be optimized some(if s == 0)
    inline
    static void Matrix3fSetRotationFromQuat4f(Matrix3fT& NewObj, const Quat4fT* q1)
    {
        GLfloat n, s;
        GLfloat xs, ys, zs;
        GLfloat wx, wy, wz;
        GLfloat xx, xy, xz;
        GLfloat yy, yz, zz;

        assert(q1);

        n = (q1->x * q1->x) + (q1->y * q1->y) + (q1->z * q1->z) + (q1->w * q1->w);
        s = (n > 0.0f) ? (2.0f / n) : 0.0f;

        xs = q1->x * s;  ys = q1->y * s;  zs = q1->z * s;
        wx = q1->w * xs; wy = q1->w * ys; wz = q1->w * zs;
        xx = q1->x * xs; xy = q1->x * ys; xz = q1->x * zs;
        yy = q1->y * ys; yz = q1->y * zs; zz = q1->z * zs;

        NewObj[0][0] = 1.0f - (yy + zz); NewObj[1][0] =         xy - wz;  NewObj[2][0] =         xz + wy;
        NewObj[0][1] =         xy + wz;  NewObj[1][1] = 1.0f - (xx + zz); NewObj[2][1] =         yz - wx;
        NewObj[0][2] =         xz - wy;  NewObj[1][2] =         yz + wx;  NewObj[2][2] = 1.0f - (xx + yy);
    }

    /**
     * Sets the value of this matrix to the result of multiplying itself
     * with matrix m1. 
     * @param m1 the other matrix 
     */
    inline
    static void Matrix3fMulMatrix3f(Matrix3fT& NewObj, const Matrix3fT& m1)
    {
        Matrix3fT Result; //safe not to initialize

        // alias-safe way.
        Result[0][0] = (NewObj[0][0] * m1[0][0]) + (NewObj[1][0] * m1[0][1]) + (NewObj[2][0] * m1[0][2]);
        Result[1][0] = (NewObj[0][0] * m1[1][0]) + (NewObj[1][0] * m1[1][1]) + (NewObj[2][0] * m1[1][2]);
        Result[2][0] = (NewObj[0][0] * m1[2][0]) + (NewObj[1][0] * m1[2][1]) + (NewObj[2][0] * m1[2][2]);

        Result[0][1] = (NewObj[0][1] * m1[0][0]) + (NewObj[1][1] * m1[0][1]) + (NewObj[2][1] * m1[0][2]);
        Result[1][1] = (NewObj[0][1] * m1[1][0]) + (NewObj[1][1] * m1[1][1]) + (NewObj[2][1] * m1[1][2]);
        Result[2][1] = (NewObj[0][1] * m1[2][0]) + (NewObj[1][1] * m1[2][1]) + (NewObj[2][1] * m1[2][2]);

        Result[0][2] = (NewObj[0][2] * m1[0][0]) + (NewObj[1][2] * m1[0][1]) + (NewObj[2][2] * m1[0][2]);
        Result[1][2] = (NewObj[0][2] * m1[1][0]) + (NewObj[1][2] * m1[1][1]) + (NewObj[2][2] * m1[1][2]);
        Result[2][2] = (NewObj[0][2] * m1[2][0]) + (NewObj[1][2] * m1[2][1]) + (NewObj[2][2] * m1[2][2]);

        //copy result back to this
        NewObj = Result;
    }

    inline
    static void Matrix4fSetRotationScaleFromMatrix4f(Matrix4fT& NewObj, const Matrix4fT& m1)
    {
        NewObj[0][0] = m1[0][0]; NewObj[1][0] = m1[1][0]; NewObj[2][0] = m1[2][0];
        NewObj[0][1] = m1[0][1]; NewObj[1][1] = m1[1][1]; NewObj[2][1] = m1[2][1];
        NewObj[0][2] = m1[0][2]; NewObj[1][2] = m1[1][2]; NewObj[2][2] = m1[2][2];
    }

    /**
      * Performs SVD on this matrix and gets scale and rotation.
      * Rotation is placed into rot3, and rot4.
      * @param rot3 the rotation factor(Matrix3d). if null, ignored
      * @param rot4 the rotation factor(Matrix4) only upper 3x3 elements are changed. if null, ignored
      * @return scale factor
      */
    inline
    static GLfloat Matrix4fSVD(const Matrix4fT& NewObj)
    {
        //Matrix3fT rot3; //todo 
        //Matrix4fT rot4;
        
        GLfloat s, n;

        // this is a simple svd.
        // Not complete but fast and reasonable.
        // See comment in Matrix3d.

        s = FuncSqrt(
                ( (NewObj[0][0] * NewObj[0][0]) + (NewObj[0][1] * NewObj[0][1]) + (NewObj[0][2] * NewObj[0][2]) + 
                  (NewObj[1][0] * NewObj[1][0]) + (NewObj[1][1] * NewObj[1][1]) + (NewObj[1][2] * NewObj[1][2]) +
                  (NewObj[2][0] * NewObj[2][0]) + (NewObj[2][1] * NewObj[2][1]) + (NewObj[2][2] * NewObj[2][2]) ) / 3.0f );

        //if (rot3)   //if pointer not null
        //{
        //    //this->getRotationScale(rot3);
        //    rot3[0][0] = NewObj[0][0]; rot3[0][1] = NewObj[0][1]; rot3[0][2] = NewObj[0][2];
        //    rot3[1][0] = NewObj[1][0]; rot3[1][1] = NewObj[1][1]; rot3[1][2] = NewObj[1][2];
        //    rot3[2][0] = NewObj[2][0]; rot3[2][1] = NewObj[2][1]; rot3[2][2] = NewObj[2][2];

        //    // zero-div may occur.

        //    n = 1.0f / FuncSqrt( (NewObj[0][0] * NewObj[0][0]) +
        //                              (NewObj[0][1] * NewObj[0][1]) +
        //                              (NewObj[0][2] * NewObj[0][2]) );
        //    rot3[0][0] *= n;
        //    rot3[0][1] *= n;
        //    rot3[0][2] *= n;

        //    n = 1.0f / FuncSqrt( (NewObj[1][0] * NewObj[1][0]) +
        //                              (NewObj[1][1] * NewObj[1][1]) +
        //                              (NewObj[1][2] * NewObj[1][2]) );
        //    rot3[1][0] *= n;
        //    rot3[1][1] *= n;
        //    rot3[1][2] *= n;

        //    n = 1.0f / FuncSqrt( (NewObj[2][0] * NewObj[2][0]) +
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

        //    n = 1.0f / FuncSqrt( (NewObj[0][0] * NewObj[0][0]) +
        //                              (NewObj[0][1] * NewObj[0][1]) +
        //                              (NewObj[0][2] * NewObj[0][2]) );
        //    rot4[0][0] *= n;
        //    rot4[0][1] *= n;
        //    rot4[0][2] *= n;

        //    n = 1.0f / FuncSqrt( (NewObj[1][0] * NewObj[1][0]) +
        //                              (NewObj[1][1] * NewObj[1][1]) +
        //                              (NewObj[1][2] * NewObj[1][2]) );
        //    rot4[1][0] *= n;
        //    rot4[1][1] *= n;
        //    rot4[1][2] *= n;

        //    n = 1.0f / FuncSqrt( (NewObj[2][0] * NewObj[2][0]) +
        //                              (NewObj[2][1] * NewObj[2][1]) +
        //                              (NewObj[2][2] * NewObj[2][2]) );
        //    rot4[2][0] *= n;
        //    rot4[2][1] *= n;
        //    rot4[2][2] *= n;
        //}

        return s;
    }

    inline
    static void Matrix4fSetRotationScaleFromMatrix3f(Matrix4fT& NewObj, const Matrix3fT& m1)
    {
        NewObj[0][0] = m1[0][0]; NewObj[1][0] = m1[1][0]; NewObj[2][0] = m1[2][0];
        NewObj[0][1] = m1[0][1]; NewObj[1][1] = m1[1][1]; NewObj[2][1] = m1[2][1];
        NewObj[0][2] = m1[0][2]; NewObj[1][2] = m1[1][2]; NewObj[2][2] = m1[2][2];
    }

    inline
    static void Matrix4fMulRotationScale(Matrix4fT& NewObj, GLfloat scale)
    {
        NewObj[0][0] *= scale; NewObj[1][0] *= scale; NewObj[2][0] *= scale;
        NewObj[0][1] *= scale; NewObj[1][1] *= scale; NewObj[2][1] *= scale;
        NewObj[0][2] *= scale; NewObj[1][2] *= scale; NewObj[2][2] *= scale;
    }

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
    inline
    static void Matrix4fSetRotationFromMatrix3f(Matrix4fT& NewObj, const Matrix3fT& m1)
    {
        GLfloat scale;

        scale = Matrix4fSVD(NewObj/*, NULL, NULL*/);

        Matrix4fSetRotationScaleFromMatrix3f(NewObj, m1);
        Matrix4fMulRotationScale(NewObj, scale);
    }

// 8<--Snip here if you have your own math types/funcs-->8 

    class ArcBall
    {
      public:
          //Create/Destroy
        explicit ArcBall(GLfloat NewWidth = 1.1f, GLfloat NewHeight = 1.1f);
        ~ArcBall() { /* nothing to do */ };

          //Set new bounds
          void setBounds(GLfloat NewWidth, GLfloat NewHeight)
          {
            assert((NewWidth > 1.0f) && (NewHeight > 1.0f));

            //Set adjustment factor for width/height
            this->AdjustWidth  = 1.0f / ((NewWidth  - 1.0f) * 0.5f);
            this->AdjustHeight = 1.0f / ((NewHeight - 1.0f) * 0.5f);
          }

          //Mouse down
          void    click(const Point2fT* NewPt);

          //Mouse drag, calculate rotation
          void    drag(const Point2fT* NewPt, Quat4fT* NewRot);

      protected:
        void mapToSphere(const Point2fT* NewPt, Vector3fT* NewVec) const;

        Vector3fT   StVec;          //Saved click vector
        Vector3fT   EnVec;          //Saved drag vector
        GLfloat     AdjustWidth;    //Mouse bounds width
        GLfloat     AdjustHeight;   //Mouse bounds height
      };


