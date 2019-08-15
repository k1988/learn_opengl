#ifndef __public_
#define __public_ 1

#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

/** �ڴ��ڴ�С�����仯��ص��˺������ı�viewport
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/** ��������Ϣ�������Esc�������˳�renderѭ��
*/
void processInput(GLFWwindow *window);

/** ���ַ���������shader�д���һ��������ɫ��(GL_VERTEX_SHADER)
*/
unsigned int create_vertex_shader_from_source(const char* vertexShaderSource);

/** ���ַ���������shader�д���һ��Ƭ����ɫ��(GL_FRAGMENT_SHADER)
*/
unsigned int create_fragment_shader_from_source(const char* fragmentShaderSource);

/** ����һ��program�����ҽ������еĶ��shader��attach��ȥ
@return �����½���program����������ɹ��򸽼�ʧ�ܣ��򷵻�nullptr
*/
unsigned int mk_link_program(const std::initializer_list<unsigned int> shaders);

//////// ���º�������Ҫ�������Ŀʵ�� //////////////////////

/** renderѭ��֮ǰ����
*/
bool before_render();

/** renderѭ���еĴ���
*/
bool render();

extern GLFWwindow* window;

#endif // end of __public_
	