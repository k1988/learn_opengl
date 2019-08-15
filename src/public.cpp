#include "public.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

GLFWwindow* window = nullptr;

bool init_glcontext()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return true;
}

unsigned int create_vertex_shader_from_source(const char* vertexShaderSource)
{
	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 将着色器源代码附加到着色器对象并编译着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 调用后检查编译是否成功 glCompileShader如果没有，发现了什么错误，所以你可以修复它们。检查编译时错误的完成如下：
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		glDeleteShader(vertexShader);
		return 0;
	}
	return vertexShader;
}

unsigned mk_link_program(const std::initializer_list<unsigned> shaders)
{
	int success;
	char infoLog[512];
	const unsigned int shaderProgram = glCreateProgram();

	// 将先前编译的着色器附加到程序对象，然后将它们链接起来
	for (auto it : shaders)
	{
		glAttachShader(shaderProgram, it);
	}

	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		glDeleteProgram(shaderProgram);
		return 0;
	}
	return shaderProgram;
}


int main()
{
	if (!init_glcontext())
	{
		return -1;
	}

	if (!before_render())
	{
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		render();
		
		// check and call events and swap the buffers
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}
