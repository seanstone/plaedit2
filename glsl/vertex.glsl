#version 300 es

in mediump vec3 aPos;
in mediump vec3 aColor;
in mediump vec2 aTexCoord;

out mediump vec3 ourColor;
out mediump vec2 TexCoord;

uniform vec2 WindowSize;

void main() {
    gl_Position = vec4((aPos.x * 100.0) / WindowSize.x, -aPos.y * 100.0 / WindowSize.y, 0.0, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
