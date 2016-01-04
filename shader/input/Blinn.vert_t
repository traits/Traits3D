uniform mat4 $proj_matrix;
uniform mat4 $mv_matrix;
uniform mat3 $normal_matrix;
uniform vec3 $light_position;

layout (location = 0) in vec3 $v_coordinates;
in vec3 $v_normals;
in vec4 $v_in_color;

out vec4 $v_out_color;
out vec3 N;
out vec3 V;
out vec3 L;

void main()
{    
    N = normalize($normal_matrix*$v_normals);
    V = vec3($mv_matrix * vec4($v_coordinates, 1.0));
	  L = $light_position - V;
    $v_out_color = $v_in_color;
    gl_Position = $proj_matrix * $mv_matrix * vec4($v_coordinates, 1.0);
}

