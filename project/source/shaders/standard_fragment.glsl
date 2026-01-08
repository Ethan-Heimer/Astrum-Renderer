#version 330 core

in vec2 UV;

out vec4 Color;

uniform bool useTexture;

uniform vec4 color;
uniform sampler2D Texture;

void main(){
    if(useTexture){
        Color = texture(Texture, UV) * color;
    }
    else{
        Color = color;
    }
}
