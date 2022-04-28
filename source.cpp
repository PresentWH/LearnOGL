#include <glad/glad.h>	//使用GLAD获取OpenGL函数引用,引用了gl.h须在最开始引用
#include <GLFW/glfw3.h>//使用GLFW创建OpenGL上下文
#include <iostream>

const char* vertexShaderSource = //顶点着色器源代码
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);//用户需要调整窗口大小时的回调函数
void processInput(GLFWwindow* window);//处理用户输入的函数


int main()
{
	float vertices[] = { //定义三角形顶点坐标
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

//初始化Opengl#############################################################
	glfwInit(); //初始化opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置主版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置次版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//设置opengl为核心模式
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//苹果电脑加上这个
#endif  __APPLE__

	

//绘制窗口并设定在当前窗口设定OGL上下文########################################
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

//初始化着色器设置###########################################################
	unsigned int VBO; //定义保存顶点缓冲对象的ID的变量
	unsigned int VAO; //定义保存顶点数组对象的变量
	unsigned int EBO; //定义索引缓冲数组
	unsigned int VBO2;
	unsigned int VAO2;
	unsigned int EBO2;
	unsigned int vertexShader;//定义顶点着色器ID
	unsigned int fragmentShader;//绑定编译片段着色器
	unsigned int fragmentShader2;
	unsigned int shaderProgram;//创建着色器程序对象
	unsigned int shaderProgram2;
	int success;//表示过程是否成功
	char infoLog[512];//若失败了用这个变量存放失败日志
	//配置顶点着色器和片段着色器---------------------------------------------
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//将着色器源码附加到着色器对象上
	glCompileShader(vertexShader);//编译着色器源码
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//检查是否编译成功
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);//获取错误信息
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
	shaderProgram = glCreateProgram();//附加并链接着色器对象
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
	glDeleteShader(vertexShader);//删除无用的着色器对象
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader2);
	//----------------------------------------------------------
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);//生成顶点缓冲对象VBO
	glGenVertexArrays(1, &VAO);//创建VAO
	glGenBuffers(1, &EBO2);
	glGenBuffers(1, &VBO2);
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO);//绑定VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//把新建的缓冲绑定到GL_ARRAY_BUFFER目标上
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定EBO缓存
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//复制顶点索引数据到缓存中
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//解释顶点属性
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

//循环####################################################################
	while (!glfwWindowShouldClose(window))//渲染循环
	{
		//处理输入*********************
		processInput(window);

		//处理渲染*********************
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //设置清空屏幕的颜色
		glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//检查并调用时间，交换缓冲*******
		glfwSwapBuffers(window);//交换颜色缓冲(存储窗口中像素颜色值)，用来绘制
		glfwPollEvents();//检查是否有事件发生
	}
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();//结束绘制并释放所有资源
	return 0;
}
//用户调整窗口回调函数定义########################################################
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//处理用户输入函数定义############################################################
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}