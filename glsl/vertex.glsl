#version 300 es

uniform vec2 WindowSize;
uniform vec2 TextureSize;
uniform float TileZoom;

in mediump vec2 QuadPos;
out mediump vec2 TexCoord;

vec2 Tile = vec2(0.0, 3.0);

vec2 Pixel2Screen (vec2 pixelPos)
{
    return pixelPos / (0.5 * WindowSize) + vec2(-1.0);
}

void main() {
    int columns = int(WindowSize.x / TileZoom) + 1;
    vec2 VertexPos = Pixel2Screen((vec2(gl_InstanceID % columns, gl_InstanceID / columns) + QuadPos) * TileZoom);
    gl_Position = vec4(VertexPos.x, -VertexPos.y, 0.0, 1.0);
    TexCoord = (16.0 * QuadPos + 19.0 * Tile + vec2(3.0)) / TextureSize;
}
