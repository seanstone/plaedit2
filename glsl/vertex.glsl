#define in attribute
#define out varying

in vec3 aPos;
in vec3 aColor;
in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform vec2 WindowSize;

void main() {
    gl_Position = vec4((aPos.x * 100.0) / WindowSize.x, -aPos.y * 100.0 / WindowSize.y, 0.0, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
