#include "plot3d.h"


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

Protean3D::Plot3D::Plot3D()
{
  modelview_matrix_ = glm::mat4
  (
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
  projection_matrix_ = glm::mat4
  (  
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );

  vertex_shader_src_ =
#ifdef GL_ES_VERSION_2_0
    "#version 100\n"
#else
    "#version 150\n"
#endif
    "uniform mat4 project;\n"
    "uniform mat4 modelview;\n"
    "in float x;\n"
    "in float y;\n"
    "in float z;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = project * modelview * vec4(x, y, z, 1.0);\n"
    "}\n";

  fragment_shader_src_ =
#ifdef GL_ES_VERSION_2_0
    "#version 100\n"
#else
    "#version 150\n"
#endif
    "out vec4 gl_FragColor;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
    "}\n";

  view_angle = 45.0f;
  aspect_ratio = 4.0f / 3.0f;
  z_near = 1.0f;
  z_far = 100.f;
  map_line_indices.resize(2 * MAP_NUM_LINES);

  for (auto i = 0; i != 3; ++i)
    map_vertices.push_back(std::vector<GLfloat>(MAP_NUM_TOTAL_VERTICES));

  initMatrices();
  init_map();
}

Protean3D::Plot3D::~Plot3D()
{

}


/**********************************************************************
* OpenGL helper functions
*********************************************************************/

/**********************************************************************
* Geometry creation functions
*********************************************************************/

/* Generate vertices and indices for the heightmap
*/
void Protean3D::Plot3D::init_map(void)
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

void Protean3D::Plot3D::generate_heightmap_circle(float& center_x, float& center_y,
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
void Protean3D::Plot3D::update_map(size_t num_iter)
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

/**********************************************************************
* OpenGL helper functions
*********************************************************************/

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
void Protean3D::Plot3D::createBuffers(GLuint program)
{
  //  GLuint program = shader_.
  glGenVertexArrays(1, &mesh);
  glGenBuffers(4, mesh_vbo);
  glBindVertexArray(mesh);
  /* Prepare the data for drawing through a buffer indices */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_vbo[3]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* MAP_NUM_LINES * 2, &map_line_indices[0], GL_STATIC_DRAW);

  /* Prepare the attributes for rendering */
  GLuint attrloc;

  glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* MAP_NUM_TOTAL_VERTICES, &map_vertices[0][0], GL_STATIC_DRAW);
  attrloc = glGetAttribLocation(program, "x");
  glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(attrloc);

  glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* MAP_NUM_TOTAL_VERTICES, &map_vertices[1][0], GL_DYNAMIC_DRAW);
  attrloc = glGetAttribLocation(program, "y");
  glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(attrloc);

  glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* MAP_NUM_TOTAL_VERTICES, &map_vertices[2][0], GL_STATIC_DRAW);
  attrloc = glGetAttribLocation(program, "z");
  glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(attrloc);

  glBindVertexArray(0);
}

void Protean3D::Plot3D::initMatrices()
{
  /* Compute the projection matrix */
  float f = 1.0f / tanf(view_angle / 2.0f);
  projection_matrix_[0][0] = f / aspect_ratio;
  projection_matrix_[1][1] = f;
  projection_matrix_[2][2] = (z_far + z_near) / (z_near - z_far);
  projection_matrix_[2][3] = -1.0f;
  projection_matrix_[3][2] = 2.0f * (z_far * z_near) / (z_near - z_far);

  /* Set the camera position */
  modelview_matrix_[3][0] = -5.0f;
  modelview_matrix_[3][1] = -5.0f;
  modelview_matrix_[3][2] = -20.0f;
}

void Protean3D::Plot3D::prepareNextDraw()
{
  update_map(1);

  // Update IBO vertices from source data
  glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[1]); // otherwise, the current bound buffer would be replaced
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)* MAP_NUM_TOTAL_VERTICES, &map_vertices[1][0]);
}

bool Protean3D::Plot3D::prepareDraw()
{
  /* Prepare opengl resources for rendering */

  if (!shader_.create(vertex_shader_src_, fragment_shader_src_))
    return false;

  glUseProgram(shader_.programId());
  GLint uloc_project = glGetUniformLocation(shader_.programId(), "project");
  GLint uloc_modelview = glGetUniformLocation(shader_.programId(), "modelview");

  glUniformMatrix4fv(uloc_project, 1, GL_FALSE, &projection_matrix_[0][0]);
  glUniformMatrix4fv(uloc_modelview, 1, GL_FALSE, &modelview_matrix_[0][0]);

  /* Create mesh data */
  createBuffers(shader_.programId());

  return true;
}

void Protean3D::Plot3D::draw()
{
  /* render the next frame */
  glClear(GL_COLOR_BUFFER_BIT);
  glBindVertexArray(mesh);
  glDrawElements(GL_LINES, 2 * MAP_NUM_LINES, GL_UNSIGNED_INT, 0);
}
