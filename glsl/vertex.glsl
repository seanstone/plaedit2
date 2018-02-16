#version 300 es

in mediump vec2 aPos;
out mediump vec2 TexCoord;
uniform vec2 WindowSize;

void main() {
    gl_Position = vec4((aPos.x * 100.0 + float(gl_InstanceID) * 200.0) / WindowSize.x, -aPos.y * 100.0 / WindowSize.y, 0.0, 1.0);
    TexCoord = aPos;
}
