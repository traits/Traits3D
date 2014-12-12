#include "heightmap.h"

/* Map height updates */
#define MAX_CIRCLE_SIZE (5.0f)
#define MAX_DISPLACEMENT (1.0f)
#define DISPLACEMENT_SIGN_LIMIT (0.3f)

/* Map general information */
#define MAP_SIZE (10.0f)
#define MAP_NUM_VERTICES_X (100)
#define MAP_NUM_VERTICES_Y (60)
#define MAP_NUM_TOTAL_VERTICES (MAP_NUM_VERTICES_X*MAP_NUM_VERTICES_Y)

HeightMap::HeightMap()
{
  map_vertices.resize(MAP_NUM_TOTAL_VERTICES);

  init_map();
}

bool HeightMap::loadData()
{
  if (!addPositionData(map_vertices, MAP_NUM_VERTICES_X, MAP_NUM_VERTICES_Y, GL_DYNAMIC_DRAW))
    return false;

  size_t size = map_vertices.size();
  float fsize = size;
  std::vector<glm::vec4> colors(size);
  for (auto i = 0; i != size; ++i)
  {
    glm::vec4& elem = colors[i];
    elem[0] = i / fsize;
    elem[1] = i / fsize / 4;
    elem[2] = 1 - i / fsize;
    elem[3] = 1.0f;
  }
  
  return addDataColor(colors) && addMeshColor(glm::vec4(0,0,0,0));
}

bool HeightMap::setData()
{
  update_map(1);

  return updatePositionData(map_vertices);
}


/* Generate vertices and indices for the heightmap
*/
void HeightMap::init_map()
{
  GLfloat step = MAP_SIZE / (MAP_NUM_VERTICES_X - 1);
  GLfloat x = 0.0f;
  GLfloat y = 0.0f;
  /* Create a flat grid */
  auto k = 0;
  for (auto yy = 0; yy < MAP_NUM_VERTICES_Y; ++yy)
  {
    for (auto xx = 0; xx < MAP_NUM_VERTICES_X; ++xx)
    {
      map_vertices[k].x = x;
      map_vertices[k].y = y;
      map_vertices[k].z = 0.0f;
      x += step;
      ++k;
    }
    y += step;
    x = 0.0f;
  }
}

void HeightMap::generate_heightmap_circle(float& center_x, float& center_y,
  float& size, float& displacement)
{
  float sign;
  /* random value for element in between [0-1.0] */
  center_x = (MAP_SIZE * rand()) / (1.0f * RAND_MAX);
  center_y = (MAP_SIZE * rand()) / (1.0f * RAND_MAX);
  size = (MAX_CIRCLE_SIZE * rand()) / (1.0f * RAND_MAX);
  sign = (1.0f * rand()) / (1.0f * RAND_MAX);
  sign = (sign < DISPLACEMENT_SIGN_LIMIT) ? -1.0f : 1.0f;
  displacement = (sign * (MAX_DISPLACEMENT * rand())) / (1.0f * RAND_MAX);
}

/* Run the specified number of iterations of the generation process for the
* heightmap
*/
void HeightMap::update_map(size_t num_iter)
{
  while (num_iter)
  {
    /* center of the circle */
    float center_x;
    float center_y;
    float circle_size;
    float disp;
    generate_heightmap_circle(center_x, center_y, circle_size, disp);

    //center_x = 2;
    //center_y = 1;
    //circle_size = 1;

    disp = disp / 2.0f;
    for (auto i = 0; i < MAP_NUM_TOTAL_VERTICES; ++i)
    {
      GLfloat dx = center_x - map_vertices[i].x;
      GLfloat dy = center_y - map_vertices[i].y;
      GLfloat pd = (2.0f * sqrtf((dx * dx) + (dy * dy))) / circle_size;
      //if (fabs(pd) <= 1.0f)
      {
        /* tx,ty is within the circle */
        GLfloat new_height = disp + (float)(cos(pd*3.14f)*disp);
        map_vertices[i].z = new_height;
      }
    }
    --num_iter;
  }
}
