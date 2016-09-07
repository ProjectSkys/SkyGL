#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 cameraPos;
uniform int effect;
uniform samplerCube skybox;

#define MAX_TEXTURE_NUM 1
struct Texture {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normals;
    sampler2D height;
};
uniform Texture textures[MAX_TEXTURE_NUM];

void main()
{
    vec3 I = normalize(Position - cameraPos);
    int e = effect % 3;
    if (e == 0) {
        // Diffuse
        vec4 diffuse_color = texture(textures[0].diffuse, TexCoords);
        // Reflection
        vec3 I = normalize(Position - cameraPos);
        vec3 R = reflect(I, normalize(Normal));
        float reflect_intensity = texture(textures[0].ambient, TexCoords).r;
        vec4 reflect_color = vec4(0.0);
        if(reflect_intensity > 0.1) // Only sample reflections when above a certain treshold
            reflect_color = texture(skybox, R) * reflect_intensity;
        // Combine them
        color = diffuse_color + reflect_color;
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
