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
  map_vertices.resize(MAP_NUM_VERTICES_X, MAP_NUM_VERTICES_Y);
  for (unsigned i = 0; i != coordinates_p->axes.size(); ++i)
  {
    coordinates_p->axes[i].setMajors(5);
    coordinates_p->axes[i].setMinors(3);
    coordinates_p->axes[i].setSymmetricTics(true);
  }

  init_map();
  setZoom(0.8f);
}

bool HeightMap::loadData()
{
  if (!addPositionData(map_vertices))
    return false;

  setDataDrawType(GL_DYNAMIC_DRAW);

  Traits3D::ColorVector colors = Traits3D::ColorTable::stdColor(100);
  setDataColor(colors);
    
  return setMeshColor(Traits3D::Color(0, 0, 0, 1));
}

void HeightMap::updateData()
{
  update_map(1);

  updatePositionData(map_vertices);
}


/* Generate vertices and indices for the heightmap
*/
void HeightMap::init_map()
{
  GLfloat step = MAP_SIZE / (MAP_NUM_VERTICES_X - 1);
  /* Create a flat grid */
  for (auto y = 0; y < MAP_NUM_VERTICES_Y; ++y)
  {
    for (auto x = 0; x < MAP_NUM_VERTICES_X; ++x)
    {
      map_vertices(x,y).x = step*x;
      map_vertices(x,y).y = step*y;
      map_vertices(x,y).z = 0.0f;
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
    float center_y;
    float circle_size;
    float disp;
    generate_heightmap_circle(center_x, center_y, circle_size, disp);

    //center_x = 2;
    //center_y = 1;
    //circle_size = 1;

    disp = disp / 2.0f;
    for (auto y = 0; y < MAP_NUM_VERTICES_Y; ++y)
    {
      for (auto x = 0; x < MAP_NUM_VERTICES_X; ++x)
      {
        GLfloat dx = center_x - map_vertices(x,y).x;
        GLfloat dy = center_y - map_vertices(x,y).y;
        GLfloat pd = (2.0f * sqrtf((dx * dx) + (dy * dy))) / circle_size;
        //if (fabs(pd) <= 1.0f)
        {
          /* tx,ty is within the circle */
          GLfloat new_height = disp + (float)(cos(pd*3.14f)*disp);
          map_vertices(x, y).z = 3 * new_height;
        }
      }
    }
    --num_iter;
  }
}
