#version 410


in vec4 vPosition;
in vec4 vColor;
in vec4 vNormal;

out vec3 normal;
out vec4 eye;
out vec4 color;

uniform mat4 uModelViewMatrix;
uniform mat4 normalMatrix;
uniform mat4 viewMatrix;
void main (void)
{
  gl_Position = uModelViewMatrix * vPosition;
  vec4 normal2 = (normalMatrix * normalize(vNormal));
  normal = vec3(normal2[0],normal2[1],normal2[2]);
  eye = - (uModelViewMatrix * gl_Position);
  color = vColor;
}   
