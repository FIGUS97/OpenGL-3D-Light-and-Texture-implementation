#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinate;
layout (location = 2) in vec3 normalsPosition;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragmentPosition;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	
	FragmentPosition = (model * vec4(position, 1.0)).xyz; 
	
	Normal = mat3(transpose(inverse(model))) * normalsPosition;
	
	TexCoord = textureCoordinate;
}