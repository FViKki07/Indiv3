
#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    float specular;
    float shininess;
}; 

struct DirectionalLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;


uniform Material material;
uniform DirectionalLight directionalLight;
uniform vec3 viewPos;

uniform float TIME;
uniform float Stripes = 5.0;


vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular);
}



void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    result += CalculateDirectionalLight(directionalLight, norm, viewDir);
    FragColor = vec4(result, 1.0);

}
