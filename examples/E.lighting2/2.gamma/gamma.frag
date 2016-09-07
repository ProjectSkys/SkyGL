#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

out vec4 FragColor;

struct Material {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define MAX_LIGHT_NUM 4

uniform vec3 viewPos;
uniform Material material;
uniform int lightNum;
uniform Light lights[MAX_LIGHT_NUM];
uniform bool blinn;
uniform bool gamma;

vec3 BlinnPhong(Material material, Light light) {
    // Ambient
    vec3 ambient = light.ambient * texture(material.ambient, fs_in.TexCoords).rgb;

    // Diffuse
    vec3 lightDir = normalize(light.position - fs_in.FragPos);
    vec3 normal = normalize(fs_in.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, fs_in.TexCoords).rgb;

    // Specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    float spec = 0.0;
    if (blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 4 * material.shininess);
    } else {
        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }
    vec3 specular = light.specular * spec * texture(material.specular, fs_in.TexCoords).rgb;

    // Simple attenuation
    float max_distance = 1.5;
    float distance = length(light.position - fs_in.FragPos);
    float attenuation = 1.0 / (gamma ? distance * distance : distance);

    vec3 result = ambient + diffuse + specular;
    result *= attenuation;

    return result;
}

void main() {
    vec3 color = vec3(0.0);
    for (int i = 0; i < lightNum; ++i) {
        color += BlinnPhong(material, lights[i]);
    }
    if (gamma) color = pow(color, vec3(1.0/2.2));
    FragColor = vec4(color, 1.0f);
}
