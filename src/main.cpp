#include "scene.h"

/*
 * iba 24 bit, Blender, low poly
 * Spraviť krajinu + dieru
 * Myš
 * Listnatý strom
 * Ihličnatý strom ?
 * Medveď
 * Orech ?
 * List ?
 * Jedlo
 * Kameň ?
 * Hora
 * Oblaky
*/

const unsigned int WIDTH = 1920, HEIGHT = 1080;

class OriginWindow : public ppgso::Window
{
private:
    std::unique_ptr<Scene> scene;
    float time;
    float lastX;
    float lastY;
    bool firstTime = true;

public:
    OriginWindow() : Window{"nature_demo", WIDTH, HEIGHT}
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glEnable(GL_COLOR_MATERIAL); // new
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        auto camera = Camera(90.0f, (float)width / (float)height, 1.0f, 400.0f);
        scene = std::make_unique<Scene>(camera);
    }

    void onCursorPos(double cursorX, double cursorY) override
    {
        if (firstTime)
        {
            lastX = cursorX;
            lastY = cursorY;
            firstTime = false;
        }

        float xoffset = cursorX - lastX;
        float yoffset = lastY - cursorY;

        lastX = cursorX;
        lastY = cursorY;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        scene->cursor.yaw += xoffset;
        scene->cursor.pitch += yoffset;

        if (scene->cursor.pitch > 89.0f)
            scene->cursor.pitch = 89.0f;

        if (scene->cursor.pitch < -89.0f)
            scene->cursor.pitch = -89.0f;
    }

    void onKey(int key, int scanCode, int action, int mods) override
    {
        // released - 0, pressed - 1, hold - 2

        switch (key)
        {
        case GLFW_KEY_F:
            scene->keys[0] = action == 1;
            break;
        case GLFW_KEY_W:
            scene->keys[1] = action > 0;
            break;
        case GLFW_KEY_S:
            scene->keys[2] = action > 0;
            break;
        case GLFW_KEY_A:
            scene->keys[3] = action > 0;
            break;
        case GLFW_KEY_D:
            scene->keys[4] = action > 0;
            break;
        }
    }

    void onIdle()
    {
        glClearColor(0.1f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float dTime = (float)glfwGetTime() - time;
        time = (float)glfwGetTime();

        if (!scene->update(dTime))
            exit(EXIT_SUCCESS);

        scene->render();
    }
};

int main()
{
    auto window = OriginWindow{};

    while (window.pollEvents())
    {
    }

    return EXIT_SUCCESS;
}
