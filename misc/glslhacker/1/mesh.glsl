[Vertex_Shader]
#version 150    

in vec4 gxl3d_Position;
in vec4 gxl3d_Color;
uniform mat4 gxl3d_ModelViewProjectionMatrix;
out vec4 Vertex_Color;
void main()
{
  gl_Position = gxl3d_ModelViewProjectionMatrix * gxl3d_Position;		
  Vertex_Color = gxl3d_Color;
}

[Pixel_Shader]
#version 150
precision highp float;

in vec4 Vertex_Color;
out vec4 FragColor;
void main (void)
{
  FragColor = Vertex_Color;
}
