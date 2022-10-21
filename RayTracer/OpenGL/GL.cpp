#include "OpenGL/GL.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace GL {

	const float QUAD_VERTS[] = {
		-1.0f, -1.0f,		0.0f, 0.0f,
		 1.0f, -1.0f,		1.0f, 0.0f,
		 1.0f,	1.0f,		1.0f, 1.0f,
		-1.0f, -1.0f,		0.0f, 0.0f,
		 1.0f,  1.0f,		1.0f, 1.0f,
		-1.0f,  1.0f,		0.0f, 1.0f
	};

	GLFWwindow* CreateWindow(int width, int height, std::string title) {

		if (!glfwInit()) {
			std::cerr << "Could not load glfw!\n";
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
		}
		glfwSwapInterval(0);

		return window;
	}

	unsigned int InitQuadVba() {

		unsigned int vbaID, vboID;
		glEnable(GL_TEXTURE_2D);

		// Initialize vertex array
		glCreateVertexArrays(1, &vbaID);
		glBindVertexArray(vbaID);

		// Initialize vertex buffer
		glCreateBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD_VERTS), QUAD_VERTS, GL_STATIC_DRAW);

		// Setup vertex array attributes
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexArrayAttrib(vbaID, 0);
		glEnableVertexArrayAttrib(vbaID, 1);

		// Unbind vertex array
		glBindVertexArray(0);

		return vbaID;
	}

	void DrawImage(unsigned int vbaID, unsigned int shaderID, unsigned char* image, int width, int height) {

		// Create texture.
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Draw texture.
		glUseProgram(shaderID);
		glBindVertexArray(vbaID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	/*
		@brief Compile and bind vertex and fragment shader while logging errors.
		@return Shader program id.
	*/
	unsigned int InitShader(std::string vertexPath, std::string fragmentPath) {

		std::string vertexString = GL::LoadShaderString(vertexPath);
		std::string fragString = GL::LoadShaderString(fragmentPath);
		const char* vertexChar = vertexString.c_str();
		const char* fragChar = fragString.c_str();

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexChar, 0);
		glCompileShader(vertexShader);

		int success = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(vertexShader);
			std::cerr << errorLog.data();
		}

		unsigned int fragShader;
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragChar, 0);
		glCompileShader(fragShader);

		success = 0;
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(fragShader, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(fragShader);
			std::cerr << errorLog.data();
		}

		GLuint shaderID = glCreateProgram();
		glAttachShader(shaderID, vertexShader);
		glAttachShader(shaderID, fragShader);

		glLinkProgram(shaderID);

		GLint isLinked = 0;
		glGetProgramiv(shaderID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(shaderID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragShader);

			std::cerr << infoLog.data();
		}

		glDetachShader(shaderID, vertexShader);
		glDetachShader(shaderID, fragShader);

		return shaderID;
	}

	std::string LoadShaderString(const std::string& filePath)
	{
		std::ifstream shaderSource(filePath);
		if (!shaderSource.is_open()) {
			std::cerr << "Failed to read file: " << filePath << "\n";
		}
		std::stringstream ss;

		ss << shaderSource.rdbuf();

		shaderSource.close();
		return ss.str();
	}
}