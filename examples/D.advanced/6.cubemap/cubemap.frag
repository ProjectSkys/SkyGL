#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 cameraPos;
uniform int effect;
uniform samplerCube skybox;

uniform sampler2D texture_ambient0;
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_height0;

void main()
{
    vec3 I = normalize(Position - cameraPos);
    int e = effect % 3;
    if (e == 0) {
        color = texture(texture_diffuse0, TexCoords);
    } else {
        vec3 R;
        if (e == 1) {
            R = reflect(I, normalize(Normal));
        } else {
            float ratio = 1.00 / 1.52;
            R = refract(I, normalize(Normal), ratio);
        }
        color = texture(skybox, R);
    }
}
