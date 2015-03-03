#include "traits3d/glbase/indexmaker.h"


Traits3D::GL::IndexMaker::IndexMaker()
  :restart_placeholder_(std::numeric_limits<IndexType>::max())
{
}

bool Traits3D::GL::IndexMaker::create(IndexType xsize, IndexType ysize, GLenum primitive_type)
{
  if (2 > xsize || 2 > ysize /*|| xsize * ysize > ( (GLushort)-1)*/) // path. cases
  {
    container_.clear();
    return false;
  }

  container_.resize(1);
  if (restart_type_ == RestartType::PrimitiveRestart)
  {
    switch (primitive_type)
    {
    case GL_LINE_STRIP:
      return createRestartLineStrips(container_[0], xsize, ysize);
    case GL_TRIANGLE_STRIP:
      return createRestartTriangleStrips(container_[0], xsize, ysize);
    default:
      return false;
    }
  }
  else if (restart_type_ == RestartType::None)
  {
    switch (primitive_type)
    {
    case GL_LINE_STRIP:
      return createLineStrips(container_, xsize, ysize);
    case GL_TRIANGLE_STRIP:
      return createTriangleStrips(container_[0], xsize, ysize);
    default:
      return false;
    }
  }
  return false;
}

bool Traits3D::GL::IndexMaker::createLineStrips(Container& result, IndexType xsize, IndexType ysize)
{
  result.resize(xsize+ysize);
  for (IndexType i = 0; i != result.size(); ++i)
  {
    // first verticals than horizontals
    result[i].resize(i < ysize ? xsize : ysize);
  }

  // verticals
  for (IndexType y = 0; y != ysize; ++y)
  {
    auto start = y * xsize;
    for (IndexType x = 0; x != xsize; ++x)
    {
      result[y][x] = start + x;
    }
  }
  // horizontal
  for (IndexType x = 0; x != xsize; ++x)
  {
    for (IndexType y = 0; y != ysize; ++y)
    {
      result[ysize + x][y] = x + y * xsize;
    }
  }
  return true;
}

bool Traits3D::GL::IndexMaker::createRestartLineStrips(LinearizedContainer& result, IndexType xsize, IndexType ysize)
{
  IndexType k = 0;

  IndexType ph_count = xsize + ysize - 1; // necessary restart placeholders between strips

  result.resize(2*xsize*ysize + ph_count);

  // verticals
  for (IndexType y = 0; y != ysize; ++y)
  {
    auto start = y * xsize;
    for (IndexType x = 0; x != xsize; ++x)
    {
      result[k++] = start + x;
    }
    result[k++] = restart_placeholder_;
  }
  // horizontal
  for (IndexType x = 0; x != xsize; ++x)
  {
    for (IndexType y = 0; y != ysize; ++y)
    {
      result[k++] = x + y * xsize;
    }
    if (x == xsize-1)
      break;

    result[k++] = restart_placeholder_;
  }
  return true;
}

bool Traits3D::GL::IndexMaker::createTriangleStrips(LinearizedContainer& result, IndexType xsize, IndexType ysize)
{
  // a single stripe needs 2*xsize describing indexes
  const IndexType stripesize = 2 * xsize;

  // All but the last stripe need degenerate triangles 
  // to connect them to the next stripe
  const IndexType degindexes = 2;

  IndexType size = (ysize - 1) * stripesize + (ysize - 2) * degindexes;

  result.resize(size);

  IndexType colidx = 0;
  for (IndexType y = 0; y != ysize; ++y)
  {
    colidx = y*(stripesize + degindexes);
    for (IndexType x = 0; x != xsize; ++x)
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


bool Traits3D::GL::IndexMaker::createRestartTriangleStrips(LinearizedContainer& result, IndexType xsize, IndexType ysize)
{
  // a single stripe needs 2*xsize describing indexes
  const IndexType stripesize = 2 * xsize;

  IndexType size = (ysize - 1) * stripesize + (ysize - 2);

  result.resize(size);

  IndexType colidx = 0;
  for (IndexType y = 0; y != ysize; ++y)
  {
    colidx = y*(stripesize + 1);
    for (IndexType x = 0; x != xsize; ++x)
    {
      result[colidx + 2 * x] = (y + 1) * xsize + x;
      result[colidx + 2 * x + 1] = y * xsize + x;
    }

    if (y == ysize - 2)
      break;

    result[colidx + stripesize] = restart_placeholder_;
  }
  return true;
}

void Traits3D::GL::IndexMaker::setRestartBehavior(RestartType rtype, IndexType placeholder /*= 0*/)
{
  restart_type_ = rtype;
  restart_placeholder_ = placeholder;
}
