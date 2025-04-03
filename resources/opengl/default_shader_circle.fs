#version 330 core

uniform float radius;

vec4 fragment(vec2 fragPosition, vec4 fragColor, vec2 texCoord) {
    float dist = length(gl_FragCoord.xy - fragPosition);

    if (dist > radius) {
        discard;
    }

    return fragColor;
}