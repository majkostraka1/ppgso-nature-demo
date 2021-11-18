#ifndef camera_H
#define camera_H

#include <glm/gtc/matrix_transform.hpp>

class Scene;

struct Cursor
{
    float yaw = -90.0f; // rotation around y
    float pitch = 0.0f; // rotation around x
};

class Camera
{
private:
    float diff = 0;

    void handleCursor(Cursor cursor);

public:
    glm::vec3 up{0, 1, 0};
    glm::vec3 position{5, 2, 5};
    glm::vec3 back{0, 0, 1};
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    Camera(float fov = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 10.0f);

    void update(Scene &scene, float dTime);
};

#endif