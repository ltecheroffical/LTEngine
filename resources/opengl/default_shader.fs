#version 330 core

out vec4 finalColor;

in vec4 fragColor;
in vec2 texCoord;

void main() {
    finalColor = fragColor;
}