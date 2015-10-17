#version 410

in vec3 normal;
in vec4 eye;
in vec4 color;
in vec2 texCord;
uniform mat4 viewMatrix;
uniform sampler2D mytex;
out vec4 frag_color;
uniform int texFlag;

void main () 
{
    vec4 diffuse = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 specular = vec4(0.2, 0.2, 0.2, 1.0);
    float shininess = 50.0;
    vec4 spec = vec4(0.0);

    vec4 lightPos = vec4(4, 4, -4, 0.0);
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
    vec4 colorNew;
    if (texFlag == 1)
    {
        vec4 tex_color = 2*texture(mytex, texCord);
        vec4 colorNew = max((intensity*diffuse   + spec)*tex_color, ambient);
    }
    else
    { 
        colorNew = max((intensity*diffuse   + spec)*color, ambient);
    }
    frag_color = colorNew;
    if (texFlag ==1)
    { 
        frag_color = 2*texture(mytex, texCord);
    }    
}
