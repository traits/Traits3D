#include "indexmaker.h"


Protean3D::GL::IndexMaker::IndexMaker()
{
}

bool Protean3D::GL::IndexMaker::create(std::vector<GLuint>& result, RestartType& restart_type, GLuint xsize, GLuint ysize,
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
    restart_type = RestartType::PrimitiveRestart;
    return createLineStrips(result, xsize, ysize);
  case GL_TRIANGLE_STRIP:
    restart_type = RestartType::DegeneratedElements;
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

  // a single stripe needs 2*xsize describing indexes
  const T stripesize = 2 * xsize;

  // All but the last stripe need degenerate triangles 
  // to connect them to the next stripe
  const T degindexes = 2;

  T size = (ysize - 1) * stripesize + (ysize - 2) * degindexes;

  result.resize(size);

  T colidx = 0;
  for (T y = 0; y != ysize; ++y)
  {
    colidx = y*(stripesize + degindexes);
    for (T x = 0; x != xsize; ++x)
    {
      result[colidx + 2 * x] = (y + 1) * xsize + x;
      result[colidx + 2 * x + 1] = y * xsize + x;
    }

    if (y == ysize - 2)
      break;

    // degenerated triangles 
    result[colidx + stripesize] = (y + 1) * xsize - 1;
    result[colidx + stripesize + 1] = (y + 2) * xsize;
  }
  return true;
}
