#include "arcball.h"  

//ArcbBall sphere constants:
//Diameter is       2.0f
//Radius is         1.0f
//Radius squared is 1.0f

//Create/Destroy
ArcBall::ArcBall(GLfloat NewWidth /*= 1.1f*/, GLfloat NewHeight /*= 1.1f*/)
{
    //Clear initial values
    this->StVec.x     =
    this->StVec.y     = 
    this->StVec.z     = 
               
    this->EnVec.x     =
    this->EnVec.y     = 
    this->EnVec.z     = 0.0f;

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

