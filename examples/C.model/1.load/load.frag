#version 330 core
in vec2 TexCoords;

out vec4 color;

#define MAX_TEXTURE_NUM 1
struct Texture {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normals;
    sampler2D height;
};
uniform Texture textures[MAX_TEXTURE_NUM];

uniform int select;

void main()
{
    int s = select % 5;
    if (s == 0) color = texture(textures[0].ambient, TexCoords);
    if (s == 1) color = texture(textures[0].diffuse, TexCoords);
    if (s == 2) color = texture(textures[0].specular, TexCoords);
    if (s == 3) color = texture(textures[0].normals, TexCoords);
    if (s == 4) color = texture(textures[0].height, TexCoords);
}
