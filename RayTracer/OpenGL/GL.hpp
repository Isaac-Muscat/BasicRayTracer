#pragma once

#include <string>
#include <memory>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


namespace GL {
	GLFWwindow* CreateWindow(int width, int height, std::string title);
	unsigned int InitShader(std::string vertexPath, std::string fragmentPath);
	std::string LoadShaderString(const std::string& filePath);
	unsigned int InitQuadVba();
	void DrawImage(unsigned int vbaID, unsigned int shaderID, unsigned char* image, int width, int height);
}