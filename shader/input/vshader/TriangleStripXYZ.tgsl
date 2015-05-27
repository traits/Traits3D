uniform mat4 $proj_matrix;
uniform mat4 $mv_matrix;
in float x;
in float y;
in float z;
in vec4 $v_in_color;
out vec4 $v_out_color;
void main()
{
   gl_Position = $proj_matrix * $mv_matrix * vec4(x, y, z, 1.0);
   $v_out_color = $v_in_color;
}