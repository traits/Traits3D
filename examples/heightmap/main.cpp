#include "heightmap.h"

/**********************************************************************
* GLFW callback functions
*********************************************************************/

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  switch (key)
  {
  case GLFW_KEY_ESCAPE:
    /* Exit program on Escape */
    glfwSetWindowShouldClose(window, GL_TRUE);
    break;
  }
}

int main()
{
  GLFWwindow* window;
  double dt;
  double last_update_time;
  int frame;
  GLint uloc_modelview;
  GLint uloc_project;

  GLuint shader_program;

  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: Unable to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

  window = glfwCreateWindow(800, 600, "GLFW OpenGL3 Heightmap demo", NULL, NULL);
  if (!window)
  {
    fprintf(stderr, "ERROR: Unable to create the OpenGL context and associated window\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  /* Register events callback */
  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  if (GLEW_OK != glewInit())
  {
    fprintf(stderr, "ERROR: unable to resolve OpenGL function pointers\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  HeightMap hm;

  /* Prepare opengl resources for rendering */
  shader_program = hm.make_shader_program();

  if (shader_program == 0u)
  {
    fprintf(stderr, "ERROR: during creation of the shader program\n");

    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glUseProgram(shader_program);
  uloc_project = glGetUniformLocation(shader_program, "project");
  uloc_modelview = glGetUniformLocation(shader_program, "modelview");

  glUniformMatrix4fv(uloc_project, 1, GL_FALSE, &hm.projection_matrix[0]);
  glUniformMatrix4fv(uloc_modelview, 1, GL_FALSE, &hm.modelview_matrix[0]);

  /* Create mesh data */
  hm.make_mesh(shader_program);

  /* Create vao + vbo to store the mesh */
  /* Create the vbo to store all the information for the grid and the height */

  /* setup the scene ready for rendering */
  glViewport(0, 0, 800, 600);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  /* main loop */
  frame = 0;
  last_update_time = glfwGetTime();

  while (!glfwWindowShouldClose(window))
  {
    ++frame;
    /* render the next frame */
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_LINES, 2 * hm.numLines(), GL_UNSIGNED_INT, 0);

    /* display and process events through callbacks */
    glfwSwapBuffers(window);
    glfwPollEvents();
    /* Check the frame rate and update the heightmap if needed */
    dt = glfwGetTime();
    if ((dt - last_update_time) > 0.001)
    {
      /* generate the next iteration of the heightmap */
      hm.update_map(10);
      hm.update_mesh();
      last_update_time = dt;
      frame = 0;
    }
  }

  glfwTerminate();
  return 0;
}

