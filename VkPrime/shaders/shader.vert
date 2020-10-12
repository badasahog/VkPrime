#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) readonly buffer UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout (std430, set = 0, binding = 6) restrict readonly buffer sso_positions
{
    float positions[];
};
layout (std430, set = 0, binding = 7) restrict readonly buffer sso_normals
{
    float normals[];
};
layout (std430, set = 0, binding = 8) restrict readonly buffer sso_UVs
{
    float UVs[];
};

layout (std430, set = 0, binding = 9) restrict readonly buffer sso_indices
{
    uint indices[];
};
//layout(location = 0) in vec3 inPosition;
//layout(location = 1) in vec3 inColor;
//layout(location = 2) in vec2 inTexCoord;
//layout(location = 3) in uint  inTexIndex;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out uint  outTexIndex;

void main() {
    int k = gl_VertexIndex*3;
    gl_Position = ubo.proj * ubo.view * ubo.model * 
    vec4(

    positions[indices[k+0]*3+0],
    positions[indices[k+0]*3+1],
    positions[indices[k+0]*3+2],

    1.0);
    fragColor = vec3(1.0,1.0,1.0);
    fragTexCoord = vec2(UVs[indices[k+2]*2],UVs[indices[k+2]*2+1]);
    outTexIndex = 0;
}