#version 300 es

uniform ivec2 WindowSize;
uniform ivec2 TextureSize;
uniform float TileZoom;

in mediump vec2 QuadPos;
in lowp vec2 PlaData;

out mediump vec2 TexCoord;

vec2 Tile = vec2(0);

vec2 Pixel2Screen (vec2 pixelPos)
{
    return pixelPos / (0.5 * vec2(WindowSize)) + vec2(-1.0);
}

void main() {
    int rows = 64;
    vec2 VertexPos = Pixel2Screen((vec2(gl_InstanceID / rows, gl_InstanceID % rows) + QuadPos) * TileZoom);
    gl_Position = vec4(VertexPos.x, -VertexPos.y, 0.0, 1.0);

    switch (int(PlaData[0]) >> 4)
    {
        case 0x0: // No Biome
        case 0x1:
            Tile = vec2(7, 14);
            break;
        case 0x2: // Arctic
        case 0x3:
            Tile = vec2(13, 4);
            break;
        case 0x4: // Boreal
        case 0x5:
            Tile = vec2(12, 4);
            break;
        case 0x6: // Desert
        case 0x7:
            Tile = vec2(14, 4);
            break;
        case 0x8: // Grasslands
        case 0x9:
            Tile = vec2(9, 4);
            break;
        case 0xA: // Forests
        case 0xB:
            Tile = vec2(10, 4);
            break;
        case 0xC: // Jungle
        case 0xD:
            Tile = vec2(11, 4);
            break;
        case 0xE: // Swamp
        case 0xF:
            Tile = vec2(8, 4);
            break;
    }
    TexCoord = (16.0 * QuadPos + 19.0 * Tile + vec2(3.0)) / vec2(TextureSize);
}
