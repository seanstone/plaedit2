#version 300 es

uniform ivec2 WindowSize;
uniform ivec2 TextureSize;
uniform float TileZoom;

in mediump vec2 QuadPos;

in lowp vec2 PlaData;
in lowp float PlaLifeData;

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

    switch (int(PlaData.x) >> 4)
    {
        case 0x0: case 0x1: // No Biome
            Tile = vec2(7, 14);
        break;
        case 0x2: case 0x3: // Arctic
            Tile = vec2(5, 14);
        break;
        case 0x4: case 0x5: // Boreal
            Tile = vec2(12, 4);
        break;
        case 0x6: case 0x7: // Desert
            Tile = vec2(14, 4);
        break;
        case 0x8: case 0x9: // Grasslands
            Tile = vec2(9, 4);
        break;
        case 0xA: case 0xB: // Forests
            Tile = vec2(10, 4);
        break;
        case 0xC: case 0xD: // Jungle
            Tile = vec2(11, 4);
        break;
        case 0xE: case 0xF: // Swamp
            Tile = vec2(8, 4);
        break;
    }

    switch (int(PlaLifeData) >> 4)
    {
        case 0x0: // Prokaryotes
        if ((int(PlaLifeData) & 0xF) > 0) Tile = vec2(41 + (int(PlaLifeData) & 0xF) - 1, 16);
        break;
        case 0x1: // Eukaryotes
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 17);
        break;
        case 0x2: // Radiates
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 18);
        break;
        case 0x3: // Arthropods
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 12);
        break;
        case 0x4: // Mollusks
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 14);
        break;
        case 0x5: // Fish
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 11);
        break;
        case 0x6: // Cetaceans
        Tile = vec2(1 + 41 + (int(PlaLifeData) & 0xF), 1);
        break;
        case 0x7: // Trichordates
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 13);
        break;
        case 0x8: // Insects
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 15);
        break;
        case 0x9: // Amphibians
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 9);
        break;
        case 0xA: // Reptiles
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 3);
        break;
        case 0xB: // Dinosaurs
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 5);
        break;
        case 0xC: // Avians
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 4);
        break;
        case 0xD: // Mammals
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 2);
        break;
        case 0xE: // Carniferns
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 20);
        break;
        case 0xF: // Robots
        Tile = vec2(41 + (int(PlaLifeData) & 0xF), 19);
        break;
    }

    switch (int(PlaData.y) & 0x3F)
    {
        case 0x04: case 0x05: case 0x06: case 0x07:
            Tile = vec2(0, 1);
        break;
        case 0x08: case 0x09: case 0x0A: case 0x0B:
            Tile = vec2(0, 2);
        break;
        case 0x0C: case 0x0D: case 0x0E: case 0x0F:
            Tile = vec2(0, 3);
        break;
        case 0x10: case 0x11: case 0x12: case 0x13:
            Tile = vec2(0, 4);
        break;
        case 0x14: case 0x15: case 0x16: case 0x17:
            Tile = vec2(0, 5);
        break;
        case 0x18: case 0x19: case 0x1A: case 0x1B:
            Tile = vec2(0, 6);
        break;
        case 0x1C: case 0x1D: case 0x1E: case 0x1F:
            Tile = vec2(0, 8);
        break;
    }

    TexCoord = (16.0 * QuadPos + 19.0 * Tile + vec2(3.0)) / vec2(TextureSize);
}
