#version 410

in vec3 normal;
in vec4 eye;
in vec4 color;
in vec2 texCord;
uniform mat4 viewMatrix;
uniform sampler2D mytex;
out vec4 frag_color;
uniform int texFlag;
uniform int l1Flag;
uniform int l2Flag;
uniform int l3Flag;

void main () 
{
    vec4 diffuse = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 diffuse2 = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 specular = vec4(0.2, 0.2, 0.2, 1.0);
    vec4 specular2 = vec4(0.2, 0.2, 0.2, 1.0);
    float shininess = 50.0;
    vec4 spec = vec4(0.0);
    vec4 spec2 = vec4(0.0);

    vec4 lightPos = vec4(-10, 5, 6, 1.0);
    vec3 lightDir =  vec3(viewMatrix*lightPos);
    lightDir =  vec3(lightDir);

    vec3 e = vec3(eye);
    vec3 h = normalize(lightDir + e );
    vec3 n = normalize(vec3(normal));
    float dotProduct = dot(n, h);
    float intensity =  max( dotProduct, 0.0);
    if(intensity > 0.0)
    {
        float intSpec = max(dot(h,n), 0.0);
        spec = specular * pow(intSpec, shininess);
    }

    vec4 lightPos2 = vec4(-5, 5, -5, 1.0);
    vec3 lightDir2 =  vec3(viewMatrix*lightPos2);
    lightDir2 = normalize( vec3(lightDir2));

    vec3 e2 = normalize(vec3(eye));
    vec3 h2 = normalize(lightDir2 + e2 );
    vec3 n2 = normalize(vec3(normal));
    float dotProduct2 = dot(n2, h2);
    float intensity2 =  max( dotProduct2, 0.0);
    if(intensity2 > 0.0)
    {
        float intSpec2 = max(dot(h2,n2), 0.0);
        spec2 = specular2 * pow(intSpec2, shininess);
    }

    vec4 colorNew;
    colorNew = texture(mytex, texCord);

    vec4 l1 = max(intensity*diffuse +spec,ambient);
    vec4 l2 = max(intensity2*diffuse2 +spec2,ambient);
    vec4 l3 = vec4(0,0,0,0);
    if (l1Flag == 0)
    {
        l1 = vec4(0,0,0,0);
    }

    if (l2Flag == 0)
    {
        l2 = vec4(0,0,0,0);
    }

    vec4 l = l1+l2+l3;
    float a = (l1Flag+l2Flag+l3Flag)/3.0;
    if (texFlag == 1)
    {
        colorNew = l*colorNew;
    }
    else if (texFlag == 2)
    { 
        colorNew = vec4(a,a,a,1)*texture(mytex, texCord);
    }
    else
    { 
        colorNew = l*color;
    }    
    frag_color = colorNew;
}
