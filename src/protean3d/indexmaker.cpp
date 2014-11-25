#include "indexmaker.h"


Protean3D::GL::IndexMaker::IndexMaker()
  :flag_(Flag::Normal)
{
}


bool Protean3D::GL::IndexMaker::create(std::vector<GLuint>& result, GLuint xsize, GLuint ysize, 
  GLenum drawType)
{
  if (2 > xsize || 2 > ysize /*|| xsize * ysize > ( (GLushort)-1)*/) // path. cases
  {
    result.clear();
    return false;
  }

  switch (drawType)
  {
  case GL_LINE_STRIP:
    flag_ = Flag::PrimitiveRestart;
    return createLineStrips(result, xsize, ysize);
  case GL_TRIANGLE_STRIP:
    flag_ = Flag::Normal;
    return createTriangleStrips(result, xsize, ysize);
  default:
    return false;
  }
}

bool Protean3D::GL::IndexMaker::createLineStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize)
{
  typedef GLuint T;

  T k = 0;

  T placeholder = std::numeric_limits<T>::max();
  T ph_count = xsize + ysize - 1; // necessary restart placeholders between strips

  result.resize(2*xsize*ysize + ph_count);

  // verticals
  for (auto y = 0; y != ysize; ++y)
  {
    auto start = y * xsize;
    for (auto x = 0; x != xsize; ++x)
    {
      result[k++] = start + x;
    }
    result[k++] = placeholder;
  }
  // horizontal
  for (auto x = 0; x != xsize; ++x)
  {
    for (auto y = 0; y != ysize; ++y)
    {
      result[k++] = x + y * xsize;
    }
    if (x == xsize-1)
      break;

    result[k++] = placeholder;
  }
  return true;
}

bool Protean3D::GL::IndexMaker::createTriangleStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize)
{
  typedef GLuint T;

  // a single stripe needs 2*ysize describing indexes
  const T stripesize = 2 * ysize;

  // All but the last stripe need degenerate triangles 
  // to connect them to the next stripe
  const T degindexes = 2;

  T size = (xsize - 1) * stripesize + (xsize - 2) * degindexes;

  result.resize(size);

  T colidx = 0;
  for (T x = 0; x != xsize; ++x)
  {
    colidx = x*(stripesize + degindexes);
    for (T y = 0; y != ysize; ++y)
    {
      result[colidx + 2 * y] = (x + 1) * ysize + y;
      result[colidx + 2 * y + 1] = x * ysize + y;
    }

    if (x == xsize - 2)
      break;

    // degenerated triangles 
    result[colidx + stripesize] = (x + 1) * ysize - 1;
    result[colidx + stripesize + 1] = (x + 2) * ysize;
  }
  return true;
}
