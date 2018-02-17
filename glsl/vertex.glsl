#version 300 es

in mediump vec2 QuadPos;
out mediump vec2 TexCoord;
uniform vec2 WindowSize;
uniform float TileSize;

void main() {
    int columns = int(WindowSize.x / TileSize) + 1;

    vec2 IndexPos = QuadPos + vec2(gl_InstanceID % columns, gl_InstanceID / columns);
    vec2 TilePos = IndexPos * TileSize / (0.5 * WindowSize) + vec2(-1.0);
    gl_Position = vec4(TilePos.x, -TilePos.y, 0.0, 1.0);

    vec2 TextureUnit = vec2(1.0) / vec2(1200.0, 720.0);
    vec2 Tile = vec2(0.0, 3.0);
    TexCoord = TextureUnit * (16.0 * QuadPos + 19.0 * Tile + vec2(3.0));
}
