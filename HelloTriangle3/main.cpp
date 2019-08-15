// ʹ��������ͬ��VAO��VBOΪ�����ݴ�����ͬ��2��������
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

void create_VBO1()
{
	float vertices[] = {
		-1.0f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// �������ݸ��Ƶ��������ڴ��еĺ���
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void create_VBO2()
{
	float vertices[] = {
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


unsigned int  VAO,VAO2;
unsigned int vertexShader;
unsigned int shaderProgram;
unsigned int shaderProgramGreen;


bool before_render()
{
	create_VBO1();
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	/*
	���Ե��������Ҳ���Բ����á���Ϊ����Ḳ��
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	*/

	create_VBO2();
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ����󶨵�VBO��VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	// ����һ����ɫ�������ٴ���ID����
	const auto vertexShader = create_vertex_shader_from_source(vertexShaderSource);
	if (!(vertexShader))
	{
		return false;
	}

	// ����Ƭ����ɫ��	
	const auto fragmentShader = create_fragment_shader_from_source(fragmentShaderSource);

	// ����Ƭ����ɫ�� - ��ɫ	
	const auto fragmentShaderGreen = create_fragment_shader_from_source(fragmentShaderSourceGreen);

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
	glBindVertexArray(VAO2);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	return true;
}
