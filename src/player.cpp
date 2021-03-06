#include "player.h"
#include "scene.h"

std::unique_ptr<ppgso::Mesh> Player::mesh;
std::unique_ptr<ppgso::Texture> Player::texture;
std::unique_ptr<ppgso::Shader> Player::shader;

Player::Player()
{
    if (!shader)
        shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture)
        texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("rat.bmp"));
    if (!mesh)
        mesh = std::make_unique<ppgso::Mesh>("rat.obj");

    scale = {0.05f, 0.05f, 0.05f};
    position.y = 0.01f;
}

glm::vec3 Player::handleKeys(bool keys[5], glm::vec3 back, float dTime)
{
    glm::vec3 direction = -back;

    direction.y = 0;
    direction = glm::normalize(direction);

    glm::vec3 side = {direction.z, 0, -direction.x};

    const float speed = 8.0f * dTime;
    glm::vec3 dPos = {0, 0, 0};

    if (keys[1])
        dPos += speed * direction;

    if (keys[2])
        dPos -= speed * direction;

    if (keys[3])
        dPos += side * speed;

    if (keys[4])
        dPos -= side * speed;

    return dPos;
}

bool Player::update(Scene &scene, float dTime)
{
    glm::vec3 deltaPosition = handleKeys(scene.keys, scene.camera.back, dTime);

    if (deltaPosition.x != 0 || deltaPosition.z != 0)
        rotation.y = -scene.cursor.yaw;

    animationTime += dTime;

    /*if (currKeyframe >= 3 || deltaPosition.x == 0 && deltaPosition.z == 0)
    {
        animationTime = 0;
        currKeyframe = 0;
    }*/

    glm::vec3 lastPosition = position;
    position += deltaPosition;

    updateCollider();

    for (auto &obj : scene.objects)
    {
        if (obj.get() == this)
            continue;

        if (obj.get()->collision(collider))
        {
            position = lastPosition;
            updateCollider();
            break;
        }
    }

    scene.camera.position = position;

    generateModelMatrix();

    return true;
}

void Player::render(Scene &scene)
{
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera.projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera.viewMatrix);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("LightPosition", scene.lightPosition);
    shader->setUniform("LightDirection", scene.lightDirection);
    shader->setUniform("LightColor", scene.lightColor);
    shader->setUniform("CameraPosition", scene.camera.position);

    mesh->render();
}