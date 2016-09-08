#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
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

uniform Material material;
uniform Light light;

uniform sampler2D shadowMap;
uniform vec3 viewPos;
uniform bool blinn;
uniform bool gamma;
uniform bool shadows;

float ShadowCalculation(vec4 fragPosLightSpace, Light light) {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(light.position - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // Check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if (projCoords.z > 1.0) shadow = 0.0;

    return shadow;
}

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
    distance = max(distance, max_distance);
    float attenuation = 1.0 / (gamma ? distance * distance : distance);

    // Shadow
    float shadow = shadows ? ShadowCalculation(fs_in.FragPosLightSpace, light) : 0.0;

    vec3 result = ambient + (1.0 - shadow) * (diffuse + specular);
    result *= attenuation;

    return result;
}

void main() {
    vec3 color = vec3(0.0);
    color += BlinnPhong(material, light);
    if (gamma) color = pow(color, vec3(1.0/2.2));
    FragColor = vec4(color, 1.0f);
}
