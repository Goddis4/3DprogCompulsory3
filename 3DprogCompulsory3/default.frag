#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;

in vec2 texCoord;


uniform sampler2D tex0;

struct Material {
    vec3 diffuse; 
};
void main()
{
    Material mat; 
    mat.diffuse = vec3(texture(tex0, texCoord));
    vec3 finalColor = mat.diffuse * color; 
    FragColor = vec4(finalColor, 1.0f);
	//FragColor = vec4(color, 1.0f);
	
}
