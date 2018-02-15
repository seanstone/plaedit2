precision mediump float;

#define in varying
#define texture texture2D

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
   gl_FragColor = texture(ourTexture, TexCoord);
}
