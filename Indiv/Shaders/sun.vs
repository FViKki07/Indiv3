#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textPosition;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;



uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() 
{
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0f); 
    TexCoord = vec2(textPosition.x, 1.0 - textPosition.y);

     FragPos = vec3(model * vec4(vertexPosition, 1.0));
    Normal = mat3(transpose(inverse(model))) * normals;  
}