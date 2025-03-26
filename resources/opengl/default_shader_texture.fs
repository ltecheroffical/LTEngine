#version 330 core

out vec4 finalColor;

in vec4 fragColor;
in vec2 texCoord;

uniform sampler2D myTexture;

void main() {
    finalColor = texture(myTexture, texCoord) * fragColor;
}