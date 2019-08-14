#ifndef __public_
#define __public_ 1

#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// ��Ҫ�������Ŀʵ��
bool before_render();
bool render();

extern GLFWwindow* window;

#endif // end of __public_
	