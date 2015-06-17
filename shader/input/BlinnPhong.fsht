in vec3 normal_out;
in vec3 vert_out;
in vec4 $v_out_color;
in vec3 $light_position;
in vec3 $light_position2;
out vec4 $f_out_color;

vec3 diffuseColor = vec3($v_out_color);
const vec3 ambientColor = vec3(0.2, 0.0, 0.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

// -1 for x<0; 1 else
float strictSign(float x)
{
	return step(0, x)*2 - 1;
}

void main() 
{
  vec3 normal = normalize(normal_out);
  vec3 lightDir = -normalize($light_position2 - vert_out);
 
  float lambertian = dot(lightDir,normal);
  float s = strictSign(lambertian);
  lambertian = s * lambertian;
  normal = s * normal;

  float specular = 0.0;
  vec3 viewDir = normalize(-vert_out);

  // this is blinn phong
  vec3 halfDir = normalize(lightDir + viewDir);
  float specAngle = max(dot(halfDir, normal), 0.0);
  specular = pow(specAngle, 16.0);

  $f_out_color = vec4(ambientColor +
                    lambertian*diffuseColor +
                    specular*specColor, 1.0);
  //$f_out_color = vec4(diffuseColor, 1.0);
}
