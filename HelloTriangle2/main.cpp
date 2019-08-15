// ʹ������Ƭ����ɫ����ʹ��ͬһ����������(6��)�еĲ�ͬ����(ǰ3�ͺ�3)����������ɫ��ͬ��������
//

#include "public.h"


auto vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

auto fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
)";

auto fragmentShaderSourceGreen = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
} 
)";

void create_VBO()
{
	// ����3���ͣ�6������
	float vertices[] = {
		-1.0f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,

		0.0f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		1.0f, -0.5f, 0.0f,
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// �������ݸ��Ƶ��������ڴ��еĺ���
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

unsigned int  VAO;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
unsigned int shaderProgramGreen;

bool before_render()
{
	create_VBO();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	// ��glVertexAttribPointer ֮��Ϳ����Ƚ������
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
   // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// ����һ����ɫ�������ٴ���ID����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// ����ɫ��Դ���븽�ӵ���ɫ�����󲢱�����ɫ��
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// ���ú�������Ƿ�ɹ� glCompileShader���û�У�������ʲô��������������޸����ǡ�������ʱ�����������£�
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	// ����Ƭ����ɫ��	
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// ����Ƭ����ɫ�� - ��ɫ	
	auto fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderGreen, 1, &fragmentShaderSourceGreen, NULL);
	glCompileShader(fragmentShaderGreen);

	// �������ֳ���
	shaderProgram = mk_link_program({ fragmentShader, vertexShader });
	shaderProgramGreen = mk_link_program({ fragmentShaderGreen, vertexShader });

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShaderGreen);
	return true;
}

bool render()
{
	// rendering commands here
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);


	glUseProgram(shaderProgramGreen);
	glDrawArrays(GL_TRIANGLES, 3, 3);
	return true;
}
