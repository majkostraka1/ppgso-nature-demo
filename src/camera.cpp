#include "camera.h"
#include "scene.h"

Camera::Camera(float fov, float ratio, float near, float far)
{
    projectionMatrix = glm::perspective(glm::radians(fov), ratio, near, far);
}

void Camera::handleCursor(Cursor cursor)
{
    glm::vec3 front;
    float yaw = cursor.yaw;
    float pitch = cursor.pitch;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    this->back = -glm::normalize(front);
}

void Camera::update(Scene &scene, float dTime)
{
    handleCursor(scene.cursor);

    position += back * 5.0f;
    viewMatrix = lookAt(position, position - back, up);
}
