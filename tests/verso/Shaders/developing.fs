#version 330
#define pi 3.141592

uniform vec2 resolution;
out vec4 fragColor;

void main(void)
{
    vec2 uv = gl_FragCoord.xy/resolution;
    float e = sin(uv.x*pi*15);
    float r = e;
    float g = abs(e);
    float b = 0;

    fragColor = vec4(r,g,b,1.0);
}
