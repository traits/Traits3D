#include "arcball.h"  

//ArcbBall sphere constants:
//Diameter is       2.0f
//Radius is         1.0f
//Radius squared is 1.0f

//Create/Destroy
ArcBall::ArcBall(GLfloat NewWidth /*= 1.1f*/, GLfloat NewHeight /*= 1.1f*/)
{
  //Set initial bounds
  this->setBounds(NewWidth, NewHeight);
}

void ArcBall::mapToSphere(glm::vec3& NewVec, const glm::vec2& NewPt) const
{
  glm::vec2 TempPt;
  GLfloat length;

  //Copy parameter into temp point
  TempPt = NewPt;

  //Adjust point coords and scale down to range of [-1 ... 1]
  TempPt.x = (TempPt.x * this->AdjustWidth) - 1.0f;
  TempPt.y = 1.0f - (TempPt.y * this->AdjustHeight);

  //Compute the square of the length of the vector to the point from the center
  length = (TempPt.x * TempPt.x) + (TempPt.y * TempPt.y);

  //If the point is mapped outside of the sphere... (length > radius squared)
  if (length > 1.0f)
  {
    GLfloat norm;

    //Compute a normalizing factor (radius / sqrt(length))
    norm = 1.0f / std::sqrt(length);

    //Return the "normalized" vector, a point on the sphere
    NewVec.x = TempPt.x * norm;
    NewVec.y = TempPt.y * norm;
    NewVec.z = 0.0f;
  }
  else    //Else it's on the inside
  {
    //Return a vector to a point mapped inside the sphere sqrt(radius squared - length)
    NewVec.x = TempPt.x;
    NewVec.y = TempPt.y;
    NewVec.z = std::sqrt(1.0f - length);
  }
}

void ArcBall::Matrix4fSetRotationScaleFromMatrix4f(glm::mat4& NewObj, const glm::mat4& m1)
{
  NewObj[0][0] = m1[0][0]; NewObj[1][0] = m1[1][0]; NewObj[2][0] = m1[2][0];
  NewObj[0][1] = m1[0][1]; NewObj[1][1] = m1[1][1]; NewObj[2][1] = m1[2][1];
  NewObj[0][2] = m1[0][2]; NewObj[1][2] = m1[1][2]; NewObj[2][2] = m1[2][2];
}

GLfloat ArcBall::Matrix4fSVD(const glm::mat4& NewObj)
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
  //    //this->getRotationScale(rot3);
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

void ArcBall::Matrix4fSetRotationScaleFromMatrix3f(glm::mat4& NewObj, const glm::mat3& m1)
{
  NewObj[0][0] = m1[0][0]; NewObj[1][0] = m1[1][0]; NewObj[2][0] = m1[2][0];
  NewObj[0][1] = m1[0][1]; NewObj[1][1] = m1[1][1]; NewObj[2][1] = m1[2][1];
  NewObj[0][2] = m1[0][2]; NewObj[1][2] = m1[1][2]; NewObj[2][2] = m1[2][2];
}

void ArcBall::Matrix4fMulRotationScale(glm::mat4& NewObj, GLfloat scale)
{
  NewObj[0][0] *= scale; NewObj[1][0] *= scale; NewObj[2][0] *= scale;
  NewObj[0][1] *= scale; NewObj[1][1] *= scale; NewObj[2][1] *= scale;
  NewObj[0][2] *= scale; NewObj[1][2] *= scale; NewObj[2][2] *= scale;
}

void ArcBall::setBounds(GLfloat NewWidth, GLfloat NewHeight)
{
  assert((NewWidth > 1.0f) && (NewHeight > 1.0f));

  //Set adjustment factor for width/height
  this->AdjustWidth = 1.0f / ((NewWidth - 1.0f) * 0.5f);
  this->AdjustHeight = 1.0f / ((NewHeight - 1.0f) * 0.5f);
}

//Mouse down
void ArcBall::click(const glm::vec2& NewPt)
{
    //Map the point to the sphere
    this->mapToSphere(StVec, NewPt);
}

//Mouse drag, calculate rotation
glm::quat ArcBall::drag(const glm::vec2& NewPt)
{
  glm::quat NewRot;
  //Map the point to the sphere
  this->mapToSphere(EnVec, NewPt);

  //Return the quaternion equivalent to the rotation
  //Compute the vector perpendicular to the begin and end vectors
  glm::vec3  Perp = glm::cross(StVec, EnVec);

  //Compute the length of the perpendicular vector
  if (Perp.length() > Epsilon)    //if its non-zero
  {
    //We're ok, so return the perpendicular vector as the transform after all
    NewRot.x = Perp.x;
    NewRot.y = Perp.y;
    NewRot.z = Perp.z;
    //In the quaternion values, w is cosine (theta / 2), where theta is rotation angle
    NewRot.w= glm::dot(StVec, EnVec);
  }
  else                                    //if its zero
  {
    //The begin and end vectors coincide, so return an identity transform
    NewRot.x = 
    NewRot.y = 
    NewRot.z = 
    NewRot.w = 0.0f;
  }

  return NewRot;
}

glm::mat3 ArcBall::rotationMatrix(const glm::quat& q1)
{
  glm::mat3 NewObj;

  GLfloat n, s;
  GLfloat xs, ys, zs;
  GLfloat wx, wy, wz;
  GLfloat xx, xy, xz;
  GLfloat yy, yz, zz;

  n = (q1.x * q1.x) + (q1.y * q1.y) + (q1.z * q1.z) + (q1.w * q1.w);
  s = (n > 0.0f) ? (2.0f / n) : 0.0f;

  xs = q1.x * s;  ys = q1.y * s;  zs = q1.z * s;
  wx = q1.w * xs; wy = q1.w * ys; wz = q1.w * zs;
  xx = q1.x * xs; xy = q1.x * ys; xz = q1.x * zs;
  yy = q1.y * ys; yz = q1.y * zs; zz = q1.z * zs;

  NewObj[0][0] = 1.0f - (yy + zz); NewObj[1][0] = xy - wz;  NewObj[2][0] = xz + wy;
  NewObj[0][1] = xy + wz;  NewObj[1][1] = 1.0f - (xx + zz); NewObj[2][1] = yz - wx;
  NewObj[0][2] = xz - wy;  NewObj[1][2] = yz + wx;  NewObj[2][2] = 1.0f - (xx + yy);

  return NewObj;
}

void ArcBall::setRotationalComponent(glm::mat4& NewObj, const glm::mat3& m1)
{
  GLfloat scale;

  scale = Matrix4fSVD(NewObj/*, NULL, NULL*/);

  Matrix4fSetRotationScaleFromMatrix3f(NewObj, m1);
  Matrix4fMulRotationScale(NewObj, scale);
}

