#include <iostream>
#include <fstream>
#include <vector>

#include "glad/glad.h"

#include "OpenGL/GL.hpp"
#include "Utilities.hpp"
#include "Core/Integrator.hpp"
#include "Core/Scene.hpp"
#include "Core/Random.hpp"

int main() {

    const int WIDTH = 800;
    const int HEIGHT = 600;
    unsigned char* image = new unsigned char[3 * WIDTH * HEIGHT];

    // Setup OpenGL windows, shaders, and buffers.
    GLFWwindow* window = GL::CreateWindow (WIDTH, HEIGHT, "Ray Tracing");
    GLuint shaderID = GL::InitShader("OpenGL/Image.vert", "OpenGL/Image.frag");
    unsigned int vbaid = GL::InitQuadVba();

    // Create integrator object to compute pixel colors.
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(0, 0, -0.5), glm::vec3(0, 0, -1), glm::vec2(WIDTH, HEIGHT));
    Scene scene;
    Integrator integrator(camera, 50);

    int numSamples = 500;
    int numFrameUpdates = 10;
    // Draw to scene incrementally to the window.
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH * 3; i+=3) {
            glm::vec3 color(0);
            for (int k = 0; k < numSamples; k++) {

                float u = (double(i / 3) + RandomUnitFloat()) / (WIDTH - 1);
                float v = (double(j) + RandomUnitFloat()) / (HEIGHT - 1);
                color += integrator.GetPixelColor(u, v, scene);

                /*color.r = float(i) / (WIDTH * 3);
                color.g = float(j) / HEIGHT;
                color.b = 0;*/

            }
            color /= numSamples;

            unsigned char ir = static_cast<unsigned char>(255 * color.r);
            unsigned char ig = static_cast<unsigned char>(255 * color.g);
            unsigned char ib = static_cast<unsigned char>(255 * color.b);

            image[(HEIGHT - j - 1) * WIDTH * 3 + i + 0] = ir;
            image[(HEIGHT - j - 1) * WIDTH * 3 + i + 1] = ig;
            image[(HEIGHT - j - 1) * WIDTH * 3 + i + 2] = ib;
        }

        if (j % (HEIGHT / numFrameUpdates) == 0) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            GL::DrawImage(vbaid, shaderID, image, WIDTH, HEIGHT);
            glfwSwapBuffers(window);
        }
    }

    // One last refresh and wait until window is closed.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GL::DrawImage(vbaid, shaderID, image, WIDTH, HEIGHT);
    glfwSwapBuffers(window);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    glfwDestroyWindow(window);

    // Output file.
    //SavePPMFile(WIDTH, HEIGHT, image, "renders/render");

    delete[] image;
    return 0;
}