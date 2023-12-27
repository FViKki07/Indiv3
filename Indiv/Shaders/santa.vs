#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textPosition;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float x_move;
uniform float y_move;
uniform float z_move;

void main() 
{
	//vec3 position = vec3(vertexPosition) + vec3(x_move, y_move, z_move);
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0f); 
    TexCoord = vec2(textPosition.x, 1.0 - textPosition.y);
}