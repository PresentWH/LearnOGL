#include <glad/glad.h>	//ʹ��GLAD��ȡOpenGL��������,������gl.h�����ʼ����
#include <GLFW/glfw3.h>//ʹ��GLFW����OpenGL������
#include <iostream>

const char* vertexShaderSource = //������ɫ��Դ����
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
	"}\0";

const char* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
	"}\n";

const char* fragmentShaderSource2 =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f,1.0f,0.0f,1.0f);\n"
	"}\n";

using std::cout;
using std::endl;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);//�û���Ҫ�������ڴ�Сʱ�Ļص�����
void processInput(GLFWwindow* window);//�����û�����ĺ���


int main()
{
	float vertices[] = { //���������ζ�������
		0.5f,0.5f,0.0f,
		0.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,
	};

	float vertices2[] = {
		-0.5f,0.5f,0.0f,
		0.0f,0.0f,0.0f,
		-0.5f,-0.5f,0.0f
	};

	unsigned int indices[] = {
		0,1,2
	};

//��ʼ��Opengl#############################################################
	glfwInit(); //��ʼ��opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//�������汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//���ôΰ汾
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����openglΪ����ģʽ
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//ƻ�����Լ������
#endif  __APPLE__

	

//���ƴ��ڲ��趨�ڵ�ǰ�����趨OGL������########################################
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//�������ڶ���
	if (window == NULL)//���ڳ�ʼ��ʧ������ֹ����
	{
		cout << "��ʼ������ʧ��" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//����windowΪ��ǰOpengl������
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//��ʼ��GLAD
	{
		cout << "Fail to initialize GLAD" << endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);//����Viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//ע���û��ı䴰�ڴ�С�Ļص�����

//��ʼ����ɫ������###########################################################
	unsigned int VBO; //���屣�涥�㻺������ID�ı���
	unsigned int VAO; //���屣�涥���������ı���
	unsigned int EBO; //����������������
	unsigned int VBO2;
	unsigned int VAO2;
	unsigned int EBO2;
	unsigned int vertexShader;//���嶥����ɫ��ID
	unsigned int fragmentShader;//�󶨱���Ƭ����ɫ��
	unsigned int fragmentShader2;
	unsigned int shaderProgram;//������ɫ���������
	unsigned int shaderProgram2;
	int success;//��ʾ�����Ƿ�ɹ�
	char infoLog[512];//��ʧ����������������ʧ����־
	//���ö�����ɫ����Ƭ����ɫ��---------------------------------------------
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//����������ɫ��
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//����ɫ��Դ�븽�ӵ���ɫ��������
	glCompileShader(vertexShader);//������ɫ��Դ��
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//����Ƿ����ɹ�
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);//��ȡ������Ϣ
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT2::COMPILATION_FAILED\n" << infoLog << endl;
	}
	shaderProgram = glCreateProgram();//���Ӳ�������ɫ������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << endl;
	}
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER2::LINK_FAILED\n" << infoLog << endl;
	}
	glDeleteShader(vertexShader);//ɾ�����õ���ɫ������
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader2);
	//----------------------------------------------------------
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);//���ɶ��㻺�����VBO
	glGenVertexArrays(1, &VAO);//����VAO
	glGenBuffers(1, &EBO2);
	glGenBuffers(1, &VBO2);
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO);//��VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//���½��Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//��EBO����
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//���ƶ����������ݵ�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//���Ͷ�������
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//unbind
	glBindVertexArray(0);
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO2);

//ѭ��####################################################################
	while (!glfwWindowShouldClose(window))//��Ⱦѭ��
	{
		//��������*********************
		processInput(window);

		//������Ⱦ*********************
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //���������Ļ����ɫ
		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ����
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//��鲢����ʱ�䣬��������*******
		glfwSwapBuffers(window);//������ɫ����(�洢������������ɫֵ)����������
		glfwPollEvents();//����Ƿ����¼�����
	}
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();//�������Ʋ��ͷ�������Դ
	return 0;
}
//�û��������ڻص���������########################################################
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//�����û����뺯������############################################################
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}