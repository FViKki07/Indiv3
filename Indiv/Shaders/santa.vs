#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textPosition;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 scale;
uniform float x_move;
uniform float y_move;
uniform float z_move;

void main() 
{
   /* mat4 new_pos = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x_move, y_move, z_move ,1);*/
   //vec4 transformedPosition = new_pos * vec4(vertexPosition, 1.0);
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0); 
    TexCoord = vec2(textPosition.x, 1.0 - textPosition.y);
}