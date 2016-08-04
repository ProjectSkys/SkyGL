#version 330 core
in vec4 Color;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    color = mix(texture2D(tex1, TexCoord), texture2D(tex2, TexCoord), 0.5);
    color = mix(color, Color, 0.5);
}
