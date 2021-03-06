#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture samplers
uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    // Linearly interpolate between both textures (second texture is only slightly combined)
    color = mix(texture2D(tex1, TexCoord), texture2D(tex2, TexCoord), 0.5);
}
