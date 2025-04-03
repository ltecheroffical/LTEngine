#version 330 core

out vec4 finalColor;

in vec2 fragPosition;
in vec4 fragColor;
in vec2 texCoord;

vec4 fragment(vec2 fragPosition, vec4 fragColor, vec2 texCoord);

void main() {
    finalColor = fragment(fragPosition, fragColor, texCoord);
}