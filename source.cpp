#include <glad/glad.h>	//使用GLAD获取OpenGL函数引用,引用了gl.h须在最开始引用
#include <GLFW/glfw3.h>//使用GLFW创建OpenGL上下文
#include <iostream>

using std::cout;
using std::endl;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);//用户需要调整窗口大小时的回调函数

int main()
{
	glfwInit(); //初始化opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置主版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置次版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//设置opengl为核心模式
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);苹果电脑加上这个

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//创建窗口对象
	if (window == NULL)//窗口初始化失败则终止程序
	{
		cout << "初始化窗口失败" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//设置window为当前Opengl上下文

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//初始化GLAD
	{
		cout << "Fail to initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);//设置Viewport

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册用户改变窗口大小的回调函数

	while (!glfwWindowShouldClose(window))//渲染循环
	{
		glfwSwapBuffers(window);//交换颜色缓冲(存储窗口中像素颜色值)，用来绘制
		glfwPollEvents();//检查是否有事件发生
	}
	glfwTerminate();//结束绘制并释放所有资源
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
