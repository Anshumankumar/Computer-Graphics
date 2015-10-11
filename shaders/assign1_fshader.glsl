#version 410

in vec3 normal;
in vec4 eye;
in vec4 color;
uniform mat4 viewMatrix;
out vec4 frag_color;

void main () 
{
    vec4 diffuse = vec4(1.0, 0.823, 0.0, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 specular = vec4(0.2, 0.2, 0.2, 1.0);
    float shininess = 50.0;
    vec4 spec = vec4(0.0);

    vec4 lightPos = vec4(2, 2, 2, 0.0);
    vec3 lightDir = vec3(viewMatrix * lightPos);  // Transforms with camera
    lightDir = normalize( vec3(lightDir));

    vec3 e = normalize(vec3(eye));
    vec3 h = normalize(lightDir + e );
    vec3 n = normalize(vec3(normal));
    float dotProduct = dot(n, h);
    float intensity =  max( dotProduct, 0.0);
    if(intensity > 0.0)
    {
        float intSpec = max(dot(h,n), 0.0);
        spec = specular * pow(intSpec, shininess);
    }
    vec4 colorNew = max((intensity*diffuse   + spec)*color, ambient); // All
   frag_color =  colorNew;
}
