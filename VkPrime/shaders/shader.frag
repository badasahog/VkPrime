#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSamplers[35];

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in flat uint inTexIndex;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = gl_FragCoord.z * texture(texSamplers[inTexIndex], fragTexCoord);
    //outColor = vec4(gl_FragCoord.z/gl_FragCoord.w, 1.0, 1.0, 1.0);
}