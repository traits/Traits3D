#include "heightmap.h"

/* Map height updates */
#define MAX_CIRCLE_SIZE (5.0f)
#define MAX_DISPLACEMENT (1.0f)
#define DISPLACEMENT_SIGN_LIMIT (0.3f)

/* Map general information */
#define MAP_SIZE (10.0f)
#define MAP_NUM_VERTICES (80)
#define MAP_NUM_TOTAL_VERTICES (MAP_NUM_VERTICES*MAP_NUM_VERTICES)
#define MAP_NUM_LINES (3* (MAP_NUM_VERTICES - 1) * (MAP_NUM_VERTICES - 1) + \
  2 * (MAP_NUM_VERTICES - 1))

HeightMap::HeightMap()
{
  map_line_indices.resize(2 * MAP_NUM_LINES);

  for (auto i = 0; i != 3; ++i)
    map_vertices[i] = std::vector<GLfloat>(MAP_NUM_TOTAL_VERTICES);

  init_map();
}

bool HeightMap::loadData()
{
  return addPositionData(map_vertices, map_line_indices, 
    GL_LINES, 
    GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STATIC_DRAW);
}

bool HeightMap::updateAfter()
{
  update_map(1);

  return updatePositionData(1, map_vertices[1]);

  //glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[1]); // otherwise, the current bound buffer would be replaced
  //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)* MAP_NUM_TOTAL_VERTICES, &map_vertices[1][0]);
}


/* Generate vertices and indices for the heightmap
*/
void HeightMap::init_map()
{
  GLfloat step = MAP_SIZE / (MAP_NUM_VERTICES - 1);
  GLfloat x = 0.0f;
  GLfloat z = 0.0f;
  /* Create a flat grid */
  auto k = 0;
  for (auto i = 0; i < MAP_NUM_VERTICES; ++i)
  {
    for (auto j = 0; j < MAP_NUM_VERTICES; ++j)
    {
      map_vertices[0][k] = x;
      map_vertices[1][k] = 0.0f;
      map_vertices[2][k] = z;
      z += step;
      ++k;
    }
    x += step;
    z = 0.0f;
  }
  /* create indices */
  /* line fan based on i
  * i+1
  * |  / i + n + 1
  * | /
  * |/
  * i --- i + n
  */

  /* close the top of the square */
  k = 0;
  for (auto i = 0; i < MAP_NUM_VERTICES - 1; ++i)
  {
    map_line_indices[k++] = (i + 1) * MAP_NUM_VERTICES - 1;
    map_line_indices[k++] = (i + 2) * MAP_NUM_VERTICES - 1;
  }
  /* close the right of the square */
  for (auto i = 0; i < MAP_NUM_VERTICES - 1; ++i)
  {
    map_line_indices[k++] = (MAP_NUM_VERTICES - 1) * MAP_NUM_VERTICES + i;
    map_line_indices[k++] = (MAP_NUM_VERTICES - 1) * MAP_NUM_VERTICES + i + 1;
  }

  for (auto i = 0; i < (MAP_NUM_VERTICES - 1); ++i)
  {
    for (auto j = 0; j < (MAP_NUM_VERTICES - 1); ++j)
    {
      int ref = i * (MAP_NUM_VERTICES)+j;
      map_line_indices[k++] = ref;
      map_line_indices[k++] = ref + 1;

      map_line_indices[k++] = ref;
      map_line_indices[k++] = ref + MAP_NUM_VERTICES;

      map_line_indices[k++] = ref;
      map_line_indices[k++] = ref + MAP_NUM_VERTICES + 1;
    }
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
    float center_z;
    float circle_size;
    float disp;
    generate_heightmap_circle(center_x, center_z, circle_size, disp);
    disp = disp / 2.0f;
    for (auto i = 0; i < MAP_NUM_TOTAL_VERTICES; ++i)
    {
      GLfloat dx = center_x - map_vertices[0][i];
      GLfloat dz = center_z - map_vertices[2][i];
      GLfloat pd = (2.0f * sqrtf((dx * dx) + (dz * dz))) / circle_size;
      if (fabs(pd) <= 1.0f)
      {
        /* tx,tz is within the circle */
        GLfloat new_height = disp + (float)(cos(pd*3.14f)*disp);
        map_vertices[1][i] = new_height;
      }
    }
    --num_iter;
  }
}
