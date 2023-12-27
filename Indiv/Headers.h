#pragma once

#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include <ctime>  
#include <SOIL/SOIL.h> 
#include "direct_light.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

const float YAW = -90.0f;
const float PITCH = -25.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    LROTATION,
    RROTATION,
    UPROTATION,
    DOWNROTATION
};

struct Texture
{
    GLuint id;
    std::string type;
    sf::Texture texture;
};