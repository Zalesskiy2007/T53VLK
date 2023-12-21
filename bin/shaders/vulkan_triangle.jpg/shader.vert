#version 450

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNorm;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNorm;
layout(location = 3) in vec4 inColor;

layout(binding = 0) uniform UniformBufferObject
{
  mat4 model;
} ubo;

void main() {
    gl_Position = ubo.model * vec4(inPos, 1.0);
    fragColor = inColor.xyz;
    fragTexCoord = inTexCoord;
    fragNorm = inNorm;
}