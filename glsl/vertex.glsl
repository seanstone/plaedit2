#version 300 es

in mediump vec2 QuadPos;
out mediump vec2 TexCoord;
uniform vec2 WindowSize;

void main() {
    float TILE_SIZE = 100.0;
    int columns = int(WindowSize.x / TILE_SIZE) + 1;

    vec2 IndexPos = vec2(QuadPos.x + float(gl_InstanceID % columns), QuadPos.y + float(gl_InstanceID / columns));
    vec2 TilePos = vec2(-1.0) + IndexPos * TILE_SIZE * 2.0 / WindowSize;
    gl_Position = vec4(TilePos.x, -TilePos.y, 0.0, 1.0);
    TexCoord = QuadPos;
}
