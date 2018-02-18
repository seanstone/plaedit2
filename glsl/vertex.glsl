#version 300 es

uniform ivec2 WindowSize;
uniform ivec2 TextureSize;
uniform float TileZoom;

in mediump vec2 QuadPos;

in lowp vec2 PlaData;
in lowp float PlaLifeData;

out mediump vec2 TexCoord;

vec2 Tile = vec2(0);

const vec2 BiomeBaseTile[] = vec2[8]
(
    vec2(7, 14),    // No Biome
    vec2(5, 14),    // Arctic
    vec2(12, 4),    // Boreal
    vec2(14, 4),    // Desert
    vec2(9, 4),     // Grasslands
    vec2(10, 4),    // Forests
    vec2(11, 4),    // Jungle
    vec2(8, 4)      // Swamp
);

const vec2 CityBaseTile[] = vec2[13]
(
    vec2(0, 1),     // Stone Age
    vec2(0, 2),     // Bronze Age
    vec2(0, 3),     // Iron Age
    vec2(0, 4),     // Industrial Age
    vec2(0, 5),     // Atomic Age
    vec2(0, 6),     // Information Age
    vec2(0, 8),     // Nanotech Age
    vec2(0, 0),
    vec2(0, 0),
    vec2(0, 0),
    vec2(0, 0),
    vec2(0, 0),
    vec2(0, 0)
);

const vec2 LifeBaseTile[] = vec2[16]
(
    vec2(40, 16),   // Prokaryotes
    vec2(41, 17),   // Eukaryotes
    vec2(41, 18),   // Radiates
    vec2(41, 12),   // Arthropods
    vec2(41, 14),   // Mollusks
    vec2(41, 11),   // Fish
    vec2(42, 1),    // Cetaceans
    vec2(41, 13),   // Trichordates
    vec2(41, 15),   // Insects
    vec2(41, 9),    // Amphibians
    vec2(41, 3),    // Reptiles
    vec2(41, 5),    // Dinosaurs
    vec2(41, 4),    // Avians
    vec2(41, 2),    // Mammals
    vec2(41, 20),   // Carniferns
    vec2(41, 19)    // Robots
);

vec2 Pixel2Screen (vec2 pixelPos)
{
    return pixelPos / (0.5 * vec2(WindowSize)) + vec2(-1.0);
}

void main() {
    int rows = 64;
    vec2 VertexPos = Pixel2Screen((vec2(gl_InstanceID / rows, gl_InstanceID % rows) + QuadPos) * TileZoom);
    gl_Position = vec4(VertexPos.x, -VertexPos.y, 0.0, 1.0);

    Tile = BiomeBaseTile[int(PlaData.x) >> 5];

    if (int(PlaLifeData) > 0x00)
        Tile = LifeBaseTile[int(PlaLifeData) >> 4] + vec2(int(PlaLifeData) & 0xF, 0);

    if ((int(PlaData.y) & 0x3F) > 0x03)
        Tile = CityBaseTile[((int(PlaData.y) & 0x3F) - 0x03) >> 2];

    TexCoord = (16.0 * QuadPos + 19.0 * Tile + vec2(3.0)) / vec2(TextureSize);
}
