#include "scene.h"

Scene::Scene(Camera camera)
{
    this->camera = camera;
    scene1();
}

void Scene::scene1()
{
    player.position = {0, 0.01, -1};
    player.rotation = {0, 180, 0};
    lightPosition = {0, 6, 0};
    LColor = {1, 1, 0.8};

    glm::vec3 p = {1.5, 2, -5}; // bear
    glm::vec3 r = {0, 0, 0};
    glm::vec3 s = {1, 1, 1};
    auto obj = std::make_unique<staticObjects>(p, r, s, 1);
    objects.push_back(move(obj));

    for (int i = 0; i < 50; i++)
    { // trees
        glm::vec3 p = {0, 0, 0};
        glm::vec3 r = {0, 0, 0};
        glm::vec3 s = {1, 1, 1};
        auto tree = std::make_unique<staticObjects>(p, r, s, 0);
        bool collided = true;
        while (collided)
        {
            collided = false;
            float x = glm::linearRand(-30.f, 30.f);
            ;
            float z = glm::linearRand(-60.f, 60.f);
            tree->position = {x, 2, z};
            tree->updateCollider();
            for (auto &obj : objects)
            { // check for some collision with another objects
                if (obj.get()->collision(tree->collider))
                {
                    collided = true;
                    break;
                }
            }
        }
        objects.push_back(move(tree));
    }

    p = lightPosition; // sun
    r = {0, 0, 0};
    s = {10, 10, 10};
    auto sun = std::make_unique<staticObjects>(p, r, s, 3);
    objects.push_back(move(sun));

    p = {0, -0.5, -30}; // ground
    r = {0, 0, 0};
    s = {40, 1, 60};
    auto ground = std::make_unique<staticObjects>(p, r, s, 4);
    objects.push_back(move(ground));
}

bool Scene::update(float dTime)
{
    std::cout<< lightColor.x << " " << lightColor.y << " " << lightColor.z<<std::endl;

    camera.update(*this, dTime);
    player.update(*this, dTime);
    auto i = std::begin(objects);
    while (i != std::end(objects))
    {
        auto obj = i->get();
        if (!obj->update(*this, dTime))
            i = objects.erase(i);
        else
            ++i;
    }

    return true;
}

void Scene::render()
{
    player.render(*this);

    for (auto &obj : objects)
        obj->render(*this);
}