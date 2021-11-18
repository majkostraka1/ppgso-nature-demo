#ifndef player_H
#define player_H

#include "camera.h"
#include "object.h"
#include <ppgso/ppgso.h>

class Scene;

class Player final : public Object
{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    float animationTime = 0;
    int currKeyframe = 0;

    glm::vec3 handleKeys(bool keys[5], glm::vec3 back, float dTime);

public:
    Player();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

#endif
