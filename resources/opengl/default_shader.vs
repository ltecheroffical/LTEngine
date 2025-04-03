#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vTexCoord;

out vec2 fragPosition;
out vec4 fragColor;
out vec2 texCoord;

void main() {
    gl_Position = vec4(vPosition, 1.f);
    fragPosition.x = gl_Position.x;
    fragPosition.y = gl_Position.y;

    fragColor = vColor;
    texCoord = vTexCoord;
}