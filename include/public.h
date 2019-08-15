#ifndef __public_
#define __public_ 1

#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

/** 在窗口大小发生变化后回调此函数，改变viewport
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/** 处理按键消息，如果是Esc键，则退出render循环
*/
void processInput(GLFWwindow *window);

/** 创建一个program，并且将参数中的多个shader都attach进去
@return 返回新建的program，如果创建成功或附加失败，则返回nullptr
*/
unsigned int mk_link_program(const std::initializer_list<unsigned int> shaders);

//////// 以下函数，需要具体的项目实现 //////////////////////

/** render循环之前代码
*/
bool before_render();

/** render循环中的代码
*/
bool render();

extern GLFWwindow* window;

#endif // end of __public_
	