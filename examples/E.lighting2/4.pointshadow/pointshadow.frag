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

uniform Material material;
uniform Light light;

uniform samplerCube depthMap;
uniform vec3 viewPos;
uniform float far_plane;

uniform bool shadows;
uniform bool debug;

float averageClosestDepthForDebug = 0;

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[] (
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(vec3 fragPos, Light light)
{
    // Get vector between fragment position and light position
    vec3 fragToLight = fragPos - light.position;
    // Now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
#define METHOD 3
#if (METHOD == 1)
    // Use the fragment to light vector to sample from the depth map
    float closestDepth = texture(depthMap, fragToLight).r;
    // It is currently in linear range between [0,1]. Let's re-transform it back to original depth value
    closestDepth *= far_plane;
    // Now test for shadows
    float bias = 0.05; // We use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;
    if (debug) {
        averageClosestDepthForDebug = closestDepth;
    }
#endif
#if (METHOD == 2)
    // PCF
    float shadow = 0.0;
    float bias = 0.05;
    float samples = 4.0;
    float offset = 0.1;
    for(float x = -offset; x < offset; x += offset / (samples * 0.5)) {
        for(float y = -offset; y < offset; y += offset / (samples * 0.5)) {
            for(float z = -offset; z < offset; z += offset / (samples * 0.5)) {
                float closestDepth = texture(depthMap, fragToLight + vec3(x, y, z)).r; // Use lightdir to lookup cubemap
                closestDepth *= far_plane;   // Undo mapping [0;1]
                if(currentDepth - bias > closestDepth)
                    shadow += 1.0;
                if (debug) {
                    averageClosestDepthForDebug += closestDepth / (samples * samples * samples);
                }
            }
        }
    }
    shadow /= (samples * samples * samples);
#endif
#if (METHOD == 3)
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i) {
        float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // Undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
        if (debug) {
            averageClosestDepthForDebug += closestDepth / samples;
        }
    }
    shadow /= float(samples);
#endif
    return shadow;
}

vec3 BlinnPhong(Material material, Light light)
{
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
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 4 * material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, fs_in.TexCoords).rgb;

    // Shadow
    float shadow = shadows ? ShadowCalculation(fs_in.FragPos, light) : 0.0;

    vec3 result = ambient + (1.0 - shadow) * (diffuse + specular);

    return result;
}

void main()
{
    vec3 color = vec3(0.0);
    color += BlinnPhong(material, light);
    if (debug) {
        color = vec3(averageClosestDepthForDebug / far_plane);
    }
    FragColor = vec4(color, 1.0f);
}
