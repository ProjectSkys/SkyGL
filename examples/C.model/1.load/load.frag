#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_ambient0;
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_height0;
uniform int select;

void main()
{
    int s = select % 5;
    if (s == 0) color = texture(texture_ambient0, TexCoords);
    if (s == 1) color = texture(texture_diffuse0, TexCoords);
    if (s == 2) color = texture(texture_specular0, TexCoords);
    if (s == 3) color = texture(texture_normal0, TexCoords);
    if (s == 4) color = texture(texture_height0, TexCoords);
}
