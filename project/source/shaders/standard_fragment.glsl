#version 330 core

in vec2 UV;
in vec3 Normal;
in vec3 FragPos;

out vec4 Color;

uniform bool useTexture;

uniform vec4 color;
uniform sampler2D Texture;

// Lighting

uniform vec3 l_ambient;
uniform vec3 l_position;
uniform vec3 l_color;

uniform vec3 viewPos;

void main(){
    float specularStrength = 0.5;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(l_position - FragPos);

    float diff = max(dot(norm, l_position), 0.0);
    vec3 diffuse = diff * l_color;


    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * l_color;

    vec3 lightResult = (l_ambient + diffuse * specular) * vec3(color);

    vec4 finalColor = color * vec4(l_ambient, 1.0) * vec4(lightResult, 1.0);

    if(useTexture){
        Color = texture(Texture, UV) * finalColor;
    }
    else{
        Color = finalColor;
    }
}
