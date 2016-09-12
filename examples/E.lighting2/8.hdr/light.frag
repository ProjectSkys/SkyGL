#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 color;
};

uniform int lightNum;
uniform Light lights[16];
uniform vec3 viewPos;
uniform sampler2D texture_diffuse;

void main()
{
    vec3 color = texture(texture_diffuse, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    // Ambient
    vec3 ambient = 0.0 * color;
    // Lighting
    vec3 lighting = vec3(0.0f);
    for (int i = 0; i < lightNum; i++) {
        // Diffuse
        vec3 lightDir = normalize(lights[i].position - fs_in.FragPos);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = lights[i].color * diff * color;
        vec3 result = diffuse;
        // Attenuation (use quadratic as we have gamma correction)
        float distance = length(fs_in.FragPos - lights[i].position);
        result *= 1.0 / (distance * distance);
        lighting += result;
    }
    FragColor = vec4(ambient + lighting, 1.0f);
}
