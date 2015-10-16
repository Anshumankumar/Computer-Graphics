#version 410


in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;
in vec2 vTex;

out vec3 normal;
out vec4 eye;
out vec4 color;
out vec2 texCord;

uniform mat4 uModelViewMatrix;
uniform mat4 normalMatrix;
uniform mat4 viewMatrix;
void main (void)
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = mat3(normalMatrix) * normalize(vNormal);
  eye = - (uModelViewMatrix * gl_Position);
  color = vColor;
  texCord = vTex;
}   
