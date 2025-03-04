#VertexBegin
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    FragPos = vec3(model * vec4(aPos, 1.0)); // 顶点在世界空间中的位置
    Normal = mat3(transpose(inverse(model))) * aNormal; // 法线变换到世界空间
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
#VertexEnd

#FragmentBegin

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightCol;      // 光的颜色
uniform vec3 lightDir;      // 光的方向（平行光）
uniform vec3 viewPos;       // 相机位置

void main()
{
    // 环境光
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightCol;

    // 漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDirNorm = normalize(-lightDir); // 平行光方向需要取反
    float diff = max(dot(norm, lightDirNorm), 0.0);
    vec3 diffuse = diff * lightCol;

    // 镜面反射光（Blinn-Phong）
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDirNorm + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightCol;

    // 最终颜色
    vec3 result = (ambient + diffuse + specular)+0.5;
    FragColor = vec4(result, 1.0);
}

#FragmentEnd