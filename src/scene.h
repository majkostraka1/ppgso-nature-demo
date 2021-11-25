#ifndef scene_H
#define scene_H

#include <list>
#include <memory>

#include "camera.h"
#include "object.h"
#include "player.h"
#include "staticObjects.h"

class Scene
{
private:
    glm::vec3 LColor = {1,1,1};
public:
    Camera camera;

    Player player;

    glm::vec3 lightPosition;

    glm::vec3 lightColor = {1.2f, 1, .8f};

    std::list<std::unique_ptr<Object>> objects;

    bool keys[5] = {0};

    Cursor cursor;

    Scene(Camera camera);

    void scene1();

    bool update(float dTime);

    void render();
};

#endif