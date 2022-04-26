#include <glad/glad.h>	//ʹ��GLAD��ȡOpenGL��������,������gl.h�����ʼ����
#include <GLFW/glfw3.h>//ʹ��GLFW����OpenGL������
#include <iostream>

using std::cout;
using std::endl;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);//�û���Ҫ�������ڴ�Сʱ�Ļص�����

int main()
{
	glfwInit(); //��ʼ��opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//�������汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//���ôΰ汾
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����openglΪ����ģʽ
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);ƻ�����Լ������

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

	while (!glfwWindowShouldClose(window))//��Ⱦѭ��
	{
		glfwSwapBuffers(window);//������ɫ����(�洢������������ɫֵ)����������
		glfwPollEvents();//����Ƿ����¼�����
	}
	glfwTerminate();//�������Ʋ��ͷ�������Դ
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
