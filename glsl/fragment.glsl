#version 300 es

in mediump vec3 ourColor;
in mediump vec2 TexCoord;

uniform sampler2D ourTexture;

out mediump vec4 FragColor;

void main() {
   FragColor = texture(ourTexture, TexCoord);
}
