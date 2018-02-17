#version 300 es

in mediump vec2 QuadPos;
out mediump vec2 TexCoord;
uniform vec2 WindowSize;
uniform float TileSize;

void main() {
    int columns = int(WindowSize.x / TileSize) + 1;

    vec2 IndexPos = QuadPos + vec2(float(gl_InstanceID % columns), float(gl_InstanceID / columns));
    vec2 TilePos = IndexPos * TileSize / (0.5 * WindowSize) + vec2(-1.0);
    gl_Position = vec4(TilePos.x, -TilePos.y, 0.0, 1.0);
    TexCoord = QuadPos;
}
