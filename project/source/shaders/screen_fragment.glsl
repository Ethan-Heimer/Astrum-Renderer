#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0/300.0;

struct Kernal{
    mat3 matrix;
};

uniform vec4 ColorOffset;
uniform vec4 ChannelMultiplyer;

#define MAX_KERNAL 8
uniform int kernal_count;
uniform Kernal[MAX_KERNAL] kernal;

void main()
{
    if(kernal_count == 0){
        FragColor = (vec4(texture(screenTexture, TexCoords)) + ColorOffset) * ChannelMultiplyer;
        return;
    }

    vec2 offsets[9] = vec2[](
        vec2(-offset, offset), // top-left
        vec2( 0.0f, offset), // top-center
        vec2( offset, offset), // top-right
        vec2(-offset, 0.0f), // center-left
        vec2( 0.0f, 0.0f), // center-center
        vec2( offset, 0.0f), // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f, -offset), // bottom-center
        vec2( offset, -offset) // bottom-right
    );

    vec4 sampleTex[9];
    for(int i = 0; i < 9; i++){
        sampleTex[i] = vec4(texture(screenTexture, TexCoords.st + offsets[i]));
    }

    vec4 color = vec4(0.0);
    int i = 0;

    for(int k = 0; k < kernal_count; k++){
        i = 0;
        for(int x = 0; x < 3; x++){
            for(int y = 0; y < 3; y++){
                color += sampleTex[i] * kernal[k].matrix[x][y];
                i++;
            }
        }
    }
    
    FragColor = (vec4(color) + ColorOffset) * ChannelMultiplyer;
}
