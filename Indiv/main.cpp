#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Shader.h"
#include "Mesh.h"
#include "SceneObject.h"
#include "Scene.h"


//bool firstMouse = true;
bool isCamActive = false;
//bool isCamTouched = false;
glm::vec2 mousePos;
glm::vec2 mouseDelta;

int main()
{
    sf::Window window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Lab13", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    glewInit();
    glClearColor(0.65, 0.8, 0.92, 1.0);
    glEnable(GL_DEPTH_TEST);

    Shader shader = Shader("Shaders\\sun.vs", "Shaders\\sun.frag", "simple");
    Shader santaShader = Shader("Shaders\\sun.vs", "Shaders\\sun.frag", "santa");

    Mesh mesh_ground = Mesh("meshes\\box.obj", "meshes\\snow.jpg");
    SceneObject ground = SceneObject(&mesh_ground, &shader);
    ground.scale = ground.scale * 1.2f;
    ground.position.y -= 100;
    ground.position.z -= 30;


    Mesh mesh_tree = Mesh("meshes\\tree.obj", "meshes\\tree.png");
    SceneObject tree = SceneObject(&mesh_tree, &shader);
    tree.scale = ground.scale * 0.02f;
    tree.position.y -= 10; 

    Mesh mesh_santa = Mesh("meshes\\santa.obj", "meshes\\santa.jpg");
    SceneObject santa = SceneObject(&mesh_santa, &santaShader);
    santa.position.y += 30;
    santa.position.x -= 30;
    santa.rotation.y += 30;
    santa.scale *= 0.1;

    Scene mainScene = Scene();
    mainScene.AddSceneObject(ground);
    mainScene.AddSceneObject(tree);
    mainScene.AddSceneObject(santa);
    mainScene.AddShaderProgram(shader);
    mainScene.AddShaderProgram(santaShader);

    sf::Time elapsedTime;
    sf::Clock clock;
    bool running = true;

    GLfloat move_x = 0;
    GLfloat move_y = 0;
    GLfloat move_z = 0;
    
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // Изменён размер окна, надо поменять и размер области Opengl отрисовки
                glViewport(0, 0, event.size.width, event.size.height);
            }
            else if (event.type == sf::Event::MouseWheelMoved)
            {
                mainScene.camera.ProcessMouseScroll(event.mouseWheel.delta);
            }
            else if (event.type == sf::Event::MouseButtonPressed) {

                switch (event.mouseButton.button)
                {
                case sf::Mouse::Right:
                    isCamActive = true;
                    break;
                default:
                    break;
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                auto newMousePos = glm::vec2(event.mouseMove.x, event.mouseMove.y);
                mouseDelta = newMousePos - mousePos;
                mousePos = newMousePos;
                if (isCamActive)
                    mainScene.camera.OnMouseMove(mouseDelta);
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Right:
                    isCamActive = false;
                    break;
                default:
                    break;
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                //player.OnKeyPress(event.key.code, mainScene.getDeltaTime());
                switch (event.key.code)
                {
                case (sf::Keyboard::W): santa.position.z -= 10 ; break;
                case (sf::Keyboard::S): santa.position.z += 10; break;
                case (sf::Keyboard::A): santa.position.x -= 10;  break;
                case (sf::Keyboard::D): santa.position.x += 10; break;
                case (sf::Keyboard::Z): santa.position.y -= 10; break;
                case (sf::Keyboard::X): santa.position.y += 10;; break;
                case (sf::Keyboard::J): mainScene.camera.ProcessKeyboard(LROTATION, mainScene.getDeltaTime()); break;
                case (sf::Keyboard::L): mainScene.camera.ProcessKeyboard(RROTATION, mainScene.getDeltaTime()); break;
                case (sf::Keyboard::I): mainScene.camera.ProcessKeyboard(UPROTATION, mainScene.getDeltaTime() * 2); break;
                case (sf::Keyboard::K): mainScene.camera.ProcessKeyboard(DOWNROTATION, mainScene.getDeltaTime() * 2); break;
                case (sf::Keyboard::R): mainScene.camera.ProcessKeyboard(UP, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::F): mainScene.camera.ProcessKeyboard(DOWN, elapsedTime.asSeconds()); break;
                default: break;
                }
            }
        }
        elapsedTime = clock.getElapsedTime();
        if (elapsedTime > sf::milliseconds(5))
        {
            elapsedTime = clock.restart();
        }
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainScene.Draw(move_x, move_y, move_z);

        window.display();



    }
    window.close();
    return 0;
}
