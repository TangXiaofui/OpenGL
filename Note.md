#OpenGL 学习总结

##1 环境搭建
###运行环境  
**Host** : MacOS 10.12  
**IDE** : Xcode 8.3       
**Compile tool**: cMake-3.8.1    
**Dependence**s: glfw-3.2.1, glew-2.0.0, glm-0.9.7.1

###资源下载地址   
**CMake**  [here](https://cmake.org/files/v3.8/cmake-3.8.1-Darwin-x86_64.dmg).   
**glfw-3.2.1** [github](https://github.com/glfw/glfw.git).   
**glew-2.0.0** [github](https://github.com/nigels-com/glew.git).   
**glm-0.9.7.1** [github](https://github.com/g-truc/glm.git).

###资源说明及安装.  
####1. CMake.     
* CMake是一个比Make更高级的编译配置工具，它可以根据不同平台、不同的编译器，生成相应的Makefile或者vcproj项目。
* 安装步骤。    
	1.点击CMake下载链接地址，下载`cmake-3.8.1-Darwin-x86_64.dmg`。     
	2.双击`cmake-3.8.1-Darwin-x86_64.dmg`。如下图所示，将`CMake`图标拉到`Application`.即可完成安装。
	![](http://or9mg8tf6.bkt.clouddn.com/cMake-setup.png)
		
####2.GLFW.  
* GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文，定义**窗口**参数以及处理用户**输入**。
* 安装步骤     
	1. 在终端下进入你要放置源代码的位置，然后使用`git`，下载GLFW源代码，命令如下。

   		 	git clone https://github.com/glfw/glfw.git      
	2. 打开CMake,设置GLFW源代码路径以及GLFW编译完后的路径。如下图所示。     
![](http://or9mg8tf6.bkt.clouddn.com/cMake-compile.png)     
	3. 选择GLFW默认配置，点击`Configure`。使用原生`Unix Makefiles`编译器生成GLFW工程。     
![](http://or9mg8tf6.bkt.clouddn.com/cMake-Generator.png)
	4. 选择完编译器后，若界面还出现红色，则再次点击`Configure`。然后点击`Generate`生成工程。        
	5. 终端进入源代码所在路径，使用make进行编译，安装相应文件到系统目录下。命令如下:   
			
			make     
			make install
*注意：make install可能需要超级用户的权限，这时候可以使用如下命令进行安装。*
		
			sudo make install
	6. 若在系统目录`/usr/local/include`和`/usr/local/lib`下生成如下文件，则表示GLFW库安装成功。          
 ![](http://or9mg8tf6.bkt.clouddn.com/glfw-include.png)       
 ![](http://or9mg8tf6.bkt.clouddn.com/glfw-lib.png)          
 
####3.GLEW.    
* GLEW是OpenGL Extension Wrangler Library的缩写,用于帮助C/C++开发者初始化扩展（OpenGL扩展功能）并书写可移植的应用程序。GLEW当前支持各种各样的操作系统，包含Windows，Linux，Darwin，Irix与Solaris。
* 安装步骤        
	GLEW前几步的安装参考GLFW的1-5安装，若GLFW安装成功，则在系统目录`/usr/local/include`和`/usr/local/lib`下生成如下文件。  
	![](http://or9mg8tf6.bkt.clouddn.com/glew-include.png)
	![](http://or9mg8tf6.bkt.clouddn.com/glew-lib.png)    

####4.GLM
* GLM是OpenGL Mathematics的缩写，它是一个只有头文件的库，也就是说我们只需包含对应的头文件就行了，不用链接和编译。这是一个用于图形计算的C++库，它是基于OpenGL着色器语言开发的。它提供的类,函数的设计以及实现都跟GLSL同名的类和函数一样。任何人懂GLSL的，都可以用C++很好的使用GLM。
* 安装步骤    
	将glm源代码git clone到相应目录下即可。
	
###Xcode配置
* 打开Xcode，创建一个`Command Line Tool`工程。   
![](http://or9mg8tf6.bkt.clouddn.com/xCode-createProject.png)
* 配置工程，将刚才编译生成的GLFW,GLEW,GLM配置到工程配置中，如下图所示.    
![](http://or9mg8tf6.bkt.clouddn.com/xcode-config.png)
![](http://or9mg8tf6.bkt.clouddn.com/xCode-config2.png)
* 绘制第一个窗口，测试配置是否成功。    
	1.建立一个.cpp文件，然后在该文件内添加OpenGL头文件。    
			
		#include <GL/glew.h>
		#include <GLFW/glfw3.h>     
		//注意：请确认在包含GLFW的头文件之前包含了GLEW的头文件。在包含glew.h头文件时会引入许多OpenGL必要的头文件（例如GL/gl.h），所以你需要在包含其它依赖于OpenGL的头文件之前先包含GLEW。    
	2.接下来我们创建main函数，在这个函数中我们将会实例化GLFW窗口。
	
		int main()
		{
			//初始化GLFW
    		glfwInit();
    		//使用glfwWindowHint函数来配置GLFW
    		//glfwWindowHint函数的第一个参数代表选项的名称，我们可以从很多以GLFW_开头的枚举值中选择；第二个参数接受一个整形，用来设置这个选项的值。
    		//我们需要告诉GLFW我们要使用的OpenGL版本是3.3，这样GLFW会在创建OpenGL上下文时做出适当的调整
    		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    		//我们同样明确告诉GLFW我们使用的是核心模式(Core-profile)  
    		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    		//并且不允许用户调整窗口的大小
    		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    		//使用Mac OS X系统，需要加下面这行代码到你的初始化代码中这些配置才能起作用
    		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

   			return 0;
		}
	3.接下来我们创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据，而且会被GLFW的其他函数频繁地用到。
		
		//窗口的宽和高作为它的前两个参数；第三个参数表示这个窗口的名称,最后两个参数我们暂时忽略，先设置为空指针就行
		GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
		if (window == nullptr)
		{
    		std::cout << "Failed to create GLFW window" << std::endl;
    		glfwTerminate();
    		return -1;
		}
		//创建完窗口我们就可以通知GLFW将我们窗口的上下文设置为当前线程的主上下文
		glfwMakeContextCurrent(window);
		
   4.由于GLEW是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLEW。     
   
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
    		return -1;
		}    
   5.我们希望程序在我们明确地关闭它之前不断绘制图像并能够接受用户输入。因此，我们需要在程序中添加一个while循环，它能在我们让GLFW退出前一直保持运行。    
   
		//函数在我们每次循环的开始前检查一次GLFW是否被要求退出
		while(!glfwWindowShouldClose(window))
		{
			//函数检查有没有触发什么事件（比如键盘输入、鼠标移动等），然后调用对应的回调函数（可以通过回调方法手动设置）
    		glfwPollEvents();
    		//我们应用双缓冲渲染窗口应用程序。前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制。当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲，这样图像就立即呈显出来
    		glfwSwapBuffers(window);
		}
		
   6.当循环结束后我们需要正确释放/删除之前的分配的所有资源。 
   
		glfwTerminate();
		return 0;
   7.编译运行程序，如果工程配置成功，并且程序没有错误的话应该显示如下输出。    
   ![](http://or9mg8tf6.bkt.clouddn.com/xCode-window.png)


##2 预备知识
* OpenGL（全写Open Graphics Library）是指定义了一个**跨编程语言**、**跨平台**的编程接口规格的专业的**图形程序接口**。它用于**三维图像(二维的亦可)**，是一个功能强大，调用方便的底层图形库。    
  
* OpenGL自身是一个巨大的**状态机(State Machine)**：一系列的变量描述OpenGL此刻应当如何运行。OpenGL的状态通常被称为**OpenGL上下文(Context)**。我们通常使用如下途径去更改OpenGL状态：**设置选项**，**操作缓冲**。最后，我们使用当前OpenGL上下文来渲染。    
假设当我们想告诉OpenGL去画线段而不是三角形的时候，我们通过改变一些上下文变量来改变OpenGL状态，从而告诉OpenGL如何去绘图。一旦我们改变了OpenGL的状态为绘制线段，下一个绘制命令就会画出线段而不是三角形。

* 当OpenGL设置完选项，操作缓冲后，在绘制图像时，则由OpenGL的**图形渲染管线**(即一堆原始图形数据途经一个输送管道，期间经过各种变化处理最终出现在屏幕的过程)管理实现的。

* **图形渲染管线**接受一组**3D坐标**，然后把它们转变为你屏幕上的**有色2D像素输出**。图形渲染管线可以被划分为几个阶段，每个阶段将会把前一个阶段的输出作为输入。所有这些阶段都是高度专门化的（它们都有一个特定的函数），并且很容易并行执行。正是由于它们具有并行执行的特性，当今大多数显卡都有成千上万的小处理核心，它们在GPU上为每一个(渲染管线)阶段运行各自的小程序，从而在图形渲染管线中快速处理你的数据。这些小程序叫做**着色器(Shader)**。

* 有些着色器允许开发者自己配置，这就允许我们用自己写的着色器来替换默认的。这样我们就可以更细致地控制图形渲染管线中的特定部分了，而且因为它们运行在GPU上，所以它们可以给我们节约宝贵的CPU时间。    
	下图是图形渲染管线的每个阶段的抽象展示。要注意蓝色部分代表的是我们可以注入**自定义**的着色器的部分。    
	![](http://or9mg8tf6.bkt.clouddn.com/shader-pipeline.png)
	如你所见，图形渲染管线包含很多部分，每个部分都将在转换顶点数据到最终像素这一过程中处理各自特定的阶段。    
	
	首先，我们以数组的形式传递3个3D坐标作为图形渲染管线的输入，用来表示一个三角形，这个数组叫做**顶点数据(Vertex Data)**；顶点数据是一系列顶点的集合。一个顶点(Vertex)是一个3D坐标的数据的集合。而顶点数据是用**顶点属性(Vertex Attribute)**表示的，它可以包含任何我们想用的数据，但是简单起见，我们还是假定每个顶点只由一个3D位置组成的吧。    
	
	图形渲染管线的第一个部分是**顶点着色器(Vertex Shader)**，它把一个单独的顶点作为输入。顶点着色器主要的目的是把3D坐标转为另一种3D坐标(后面会解释)，同时顶点着色器允许我们对顶点属性进行一些基本处理。  
	  
	**图元装配(Primitive Assembly)**阶段将顶点着色器输出的所有顶点作为输入，将所有的点装配成指定图元的形状。    
	
	图元装配阶段的输出会传递给**几何着色器(Geometry Shader)**。几何着色器把图元形式的一系列顶点的集合作为输入，通过产生**新顶点**构造出新的（或是其它的）图元来生成**其他形状**。    
	
	几何着色器的输出会被传入**光栅化阶段(Rasterization Stage)**，这里它会把图元映射为最终屏幕上相应的像素，生成供**片段着色器(Fragment Shader)**使用的片段(Fragment)。在片段着色器运行之前会执行**裁切(Clipping)**。裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。    
	
	**片段着色器**的主要目的是计算一个像素的最终颜色，这也是所有OpenGL**高级效果**产生的地方。通常，片段着色器包含3D场景的数据（比如光照、阴影、光的颜色等等），这些数据可以被用来计算最终像素的颜色。    
	
	在现代OpenGL中，我们**必须**定义至少一个顶点着色器和一个片段着色器（因为GPU中没有默认的顶点/片段着色器）。出于这个原因，刚开始学习现代OpenGL的时候可能会非常困难，因为在你能够渲染自己的第一个三角形之前已经需要了解一大堆知识了。
	
##3 绘制第一个三角形
在写第一个绘制图形的程序之前，我们先对程序的流程进行一下说明。    
**流程如下**：    
	1.准备三角形的顶点数据。   
	2.向OpenGL申请用于存储顶点数据的缓存。    
	3.将顶点数据传入申请的缓存中。	
  	4.使用GLSL编写顶点着色器以及片段着色器程序。    
	5.使用OpenGL内置编译器编译着色器程序。	    
	6.配置传入顶点数据的属性。 	
	7.设置缓存上下文，将其发送给着色器，然后使用绘制图形的函数进行绘制。

###使用OpenGL绘制三角形
####1）顶点数据
* OpenGL是一个3D图形库，所以我们在OpenGL中指定的所有坐标都是3D坐标（x、y和z）。OpenGL不是简单地把所有的3D坐标变换为屏幕上的2D像素；OpenGL仅当3D坐标在3个轴（x、y和z）上都为-1.0到1.0的范围内时才处理它。所有在所谓的标准化设备坐标(Normalized Device Coordinates)范围内的坐标才会最终呈现在屏幕上。下图NDC坐标。   
<div align=center>
![](http://or9mg8tf6.bkt.clouddn.com/ndc.png)
</div>
* 设置三角形顶点位置坐标.   
	
		//由于我们希望渲染一个三角形，我们一共要指定三个顶点，每个顶点都有一个3D位置
		//由于OpenGL是在3D空间中工作的，而我们渲染的是一个2D三角形，我们将它顶点的z坐标设置为0.0
		GLfloat vertices[] = {
    		-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
    		 0.0f,  0.5f, 0.0f
		};

####2) 缓存对象	
* 定义顶点数据后，我们需要向OpenGL申请**顶点缓冲对象(Vertex Buffer Objects, VBO数据）**，然后使用它往GPU内存(通常被称为显存)中发送大量顶点数据。当数据发送至显卡的内存中后，顶点着色器几乎能立即访问顶点，这是个非常快的过程。
		
		//glGenBuffers函数和一个缓冲ID生成一个VBO对象
		GLuint VBO;
		glGenBuffers(1, &VBO);  
	OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是`GL_ARRAY_BUFFER`。
	
		//我们使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
		glBindBuffer(GL_ARRAY_BUFFER, VBO);  
	从这一刻起，我们使用的任何(在`GL_ARRAY_BUFFER`目标上的)缓冲调用都会用来配置当前绑定的缓冲(VBO)。
	
		//调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	`glBufferData`是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。    
	第一个参数是目标缓冲的类型: 顶点缓冲对象当前绑定到`GL_ARRAY_BUFFER`目标上。    
	第二个参数指定传输数据的大小(以字节为单位): 用一个简单的sizeof计算出顶点数据大小就行。     
	第三个参数是我们希望发送的实际数据。    
   第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：    
`GL_STATIC_DRAW` ：数据不会或几乎不会改变。    
`GL_DYNAMIC_DRAW`：数据会被改变很多。    
`GL_STREAM_DRAW` ：数据每次绘制时都会改变。

####3) 着色器程序    
我们已经把顶点数据储存在显卡的内存中，用VBO这个顶点缓冲对象管理。接下来我们创建一个顶点和片段着色器来处理这些数据。    

#####顶点着色器对象
* 我们使用**着色器语言GLSL(OpenGL Shading Language)**编写**顶点着色器**，然后编译这个着色器，这样我们就可以在程序中使用它了。下面是一个非常基础的顶点着色器的源代码：
	
		//我们同样明确表示我们会使用核心模式
		#version 330 core
		//使用in关键字，在顶点着色器中声明输入顶点属性(Input Vertex Attribute)
		//现在我们只关心位置(Position)数据，所以我们只需要一个顶点属性
		//通过layout (location = 0)设定了输入变量的位置值(Location)
		layout (location = 0) in vec3 position;
		void main()
		{
			//为了设置顶点着色器的输出，我们必须把位置数据赋值给预定义的gl_Position变量，它在幕后是vec4类型的
    		gl_Position = vec4(position.x, position.y, position.z, 1.0);
		}
我们对输入数据什么都没有处理就把它传到着色器的输出了。在真实的程序里输入数据通常都不是标准化设备坐标，所以我们首先必须先把它们转换至OpenGL的可视区域内。    

* 我们已经写了一个顶点着色器源码（储存在一个C语言的字符串中），为了让OpenGL使用它，我们必须在**运行时动态编译**它的源码。
	
		//我们首先要做的是创建一个着色器对象，注意还是用ID来引用的。
		GLuint vertexShader;
		//因为我们正在创建一个顶点着色器，所以传递的参数是GL_VERTEX_SHADER。
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//接着我们把这个着色器源码附加到着色器对象上，然后编译它
		//glShaderSource函数把要编译的着色器对象作为第一个参数。
		//第二参数指定了传递的源码字符串数量，这里只有一个。
		//第三个参数是顶点着色器真正的源码，
		//第四个参数我们先设置为NULL
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
	你可能会希望检测在调用`glCompileShader`后编译是否成功了，如果没成功的话，你还会希望知道错误是什么，这样你才能修复它们。检测编译时错误可以通过以下代码来实现：
		
		//定义一个整型变量来表示是否成功编译
		GLint success;
		//定义了一个储存错误消息（如果有的话）的容器
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			//如果编译失败，我们会用glGetShaderInfoLog获取错误消息，然后打印它
    		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		
#####片段着色器对象  
* 我们继续使用**着色器语言GLSL(OpenGL Shading Language)**编写用于渲染三角形的**片段着色器**。
    
    	#version 330 core
		//片段着色器只需要一个输出变量，这个变量是一个4分量向量，它表示的是最终的输出颜色，我们应该自己将其计算出来。我们可以用out关键字声明输出变量，这里我们命名为color。
		out vec4 color;

		void main()
		{
			//颜色被表示为有4个元素的数组：红色、绿色、蓝色和alpha(透明度)分量，通常缩写为RGBA,颜色每个分量的强度设置在0.0到1.0之间,将一个alpha值为1.0(1.0代表完全不透明)的橘黄色的vec4赋值给颜色输出
    		color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
		
* 同样为了OpenGL能够使用该片段着色器，我们需要编译它。编译片段着色器的过程与顶点着色器类似，只不过我们使用`GL_FRAGMENT_SHADER`常量作为着色器。

		GLuint fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
					
#####着色器程序对象
**着色器程序对象(Shader Program Object)**是多个着色器合并之后并最终链接完成的版本。如果要使用刚才编译的着色器我们必须把它们链接为一个着色器程序对象，然后在渲染对象的时候**激活**这个着色器程序。已激活着色器程序将在我们发送渲染调用的时候被使用。创建着色器程序对象如下：     

		GLuint shaderProgram;
		//创建一个程序，并返回新创建程序对象的ID引用
		shaderProgram = glCreateProgram();
		
		//把之前编译的着色器附加到程序对象上
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		//用glLinkProgram链接
		glLinkProgram(shaderProgram);

就像着色器的编译一样，我们也可以检测链接着色器程序是否失败，并获取相应的日志。与上面不同，我们不会调用`glGetShaderiv`和`glGetShaderInfoLog`，现在我们使用：
		
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if(!success) {
    		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			...
		}
在把着色器对象链接到程序对象以后，记得删除着色器对象，我们不再需要它们了：
		
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		
接下来，我们可以调用`glUseProgram`函数，用刚创建的着色器程序对象作为它的参数，以激活这个着色器程序对象：

		glUseProgram(shaderProgram);

####4) 链接顶点属性    
顶点着色器允许我们指定**任何**以顶点属性为形式的输入。这使其具有很强的灵活性的同时，它还的确意味着我们必须**手动指定**输入数据的哪一个部分**对应**顶点着色器的哪一个顶点属性。所以，我们必须在渲染前指定OpenGL该如何解释顶点数据。我们的顶点缓冲数据会被解析为下面这样子：
![](http://or9mg8tf6.bkt.clouddn.com/vertex_attribute_pointer.png)
   
* 位置数据被储存为32-bit（4字节）浮点值
* 每个位置包含3个这样的值
* 在这3个值之间没有空隙（或其他值）。这几个值在数组中**紧密排列**
* 数据中第一个值在缓冲开始的位置    

有了这些信息我们就可以使用`glVertexAttribPointer`函数告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）。   

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		
* 第一个参数指定我们要配置的顶点属性。它可以把顶点属性的位置值设置为0，这里的0对应顶点着色器中`layout（location = 0）`。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
* 第二个参数指定顶点属性的大小。顶点属性是一个`vec3`，它由3个值组成，所以大小是3。
* 第三个参数指定数据的类型，这里是GL_FLOAT。 
* 第四个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为`GL_TRUE`，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为`GL_FALSE`。
* 第五个参数叫做步长(Stride)，它告诉我们在连续的**顶点属性**之间的间隔。
* 最后一个参数的类型是`GLvoid*`，它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。   

现在我们已经定义了OpenGL该如何解释顶点数据，我们现在应该使用`glEnableVertexAttribArray`，以顶点属性位置值作为参数，启用顶点属性。

*注意：每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用`glVetexAttribPointer`时绑定到`GL_ARRAY_BUFFER`的VBO决定的。*

现在，我们的代码会像这样:
	
		// 0. 复制顶点数组到缓冲中供OpenGL使用
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 1. 设置顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// 2. 当我们渲染一个物体时要使用着色器程序
		glUseProgram(shaderProgram);
		// 3. 绘制物体
		someOpenGLFunctionThatDrawsOurTriangle();
		
每当我们绘制一个物体的时候都必须重复这一过程。这看起来可能不多，但是如果有超过5个顶点属性，上百个不同物体呢。绑定正确的缓冲对象，为每个物体配置所有顶点属性很快就变成一件麻烦事。有没有一些方法可以使我们把所有这些状态配置储存在一个对象中，并且可以通过绑定这个对象来恢复状态呢？

####5）顶点数组对象    
**顶点数组对象(Vertex Array Object, VAO)**可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会**储存**在这个VAO中。这样的好处就是，当配置顶点属性指针时，你只需要将那些调用执行一次，之后再绘制物体的时候只需要**绑定相应的VAO**就行了。这使在不同顶点数据和属性配置之间切换变得非常简单，只需要绑定不同的VAO就行了。刚刚设置的所有状态都将存储在VAO中。    

一个顶点数组对象会储存以下这些内容:      

* 通过`glVertexAttribPointer`设置的**顶点属性配置**。    
* 通过`glVertexAttribPointer`调用与顶点属性关联的**顶点缓冲对象(VBO)**。
![](http://or9mg8tf6.bkt.clouddn.com/vertex_array_objects.png)

使用顶点数组对象如下：

		GLuint VAO;
		glGenVertexArrays(1, &VAO); 
		
		//  初始化代码(只运行一次, 除非你的物体频繁改变)
		// 1. 绑定VAO
		glBindVertexArray(VAO);
    	// 2. 把顶点数组复制到缓冲中供OpenGL使用
    	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    	// 3. 设置顶点属性指针
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    	glEnableVertexAttribArray(0);
		//4. 解绑VAO
		glBindVertexArray(0);

		[...]

		// 5. 绘制物体
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		someOpenGLFunctionThatDrawsOurTriangle();
		//通常情况下当我们配置好OpenGL对象以后要解绑它们，这样我们才不会在其它地方错误地配置它们。
		glBindVertexArray(0);


####6）绘制三角形
要想绘制我们想要的物体，OpenGL给我们提供了`glDrawArrays`函数，它使用当前激活的着色器，之前定义的顶点属性配置，和VBO的顶点数据（通过VAO间接绑定）来绘制图元。

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//第一个参数是我们打算绘制的OpenGL图元的类型
		//第二个参数指定了顶点数组的起始索引
		//最后一个参数指定我们打算绘制多少个顶点
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);   

如果编译通过，应该有如下显示：
![](http://or9mg8tf6.bkt.clouddn.com/Triangle.png)    

[参考代码](#Reference-code-block)
##4 深入学习着色器
前面我们只是简要地触及了一点着色器的皮毛，并了解了如何恰当地使用它们。现在我们会用一种更加广泛的形式详细解释着色器，特别是OpenGL着色器语言(GLSL)。
###GLSL
着色器是使用一种叫GLSL的类C语言写成的。GLSL是为图形计算量身定制的，它包含一些针对向量和矩阵操作的有用特性。

着色器的开头总是要声明版本，接着是输入和输出变量、uniform和main函数。每个着色器的入口点都是main函数，在这个函数中我们处理所有的输入变量，并将结果输出到输出变量中。

一个典型的着色器有下面的结构：

		#version version_number

		in type in_variable_name;
		in type in_variable_name;

		out type out_variable_name;

		uniform type uniform_name;

		int main()
		{
		// 处理输入并进行一些图形操作
			...
		// 输出处理过的结果到输出变量
			out_variable_name = weird_stuff_we_processed;
		}

接下来我们针对这个着色器的结构来对GLSL进行说明。    
####数据类型
GLSL中包含C等其它语言大部分的默认基础数据类型：int、float、double、uint和bool。    
GLSL也有两种容器类型，分别是**向量(Vector)**和**矩阵(Matrix)**，其中矩阵我们会在之后的教程里再讨论。    
#####向量
 类型    |   含义
--------| ---------------------------
`vecn`  | 包含`n`个`float`分量的默认向量
`bvecn` |	包含`n`个`bool`分量的向量
`ivecn` |	包含`n`个`int`分量的向量
`uvecn` |	包含`n`个`unsigned int`分量的向量
`dvecn` |	包含`n`个`double`分量的向量	    
大多数时候我们使用vecn，因为float足够满足大多数要求了。    

一个向量的分量可以通过vec.x这种方式获取，这里x是指这个向量的第一个分量。你可以分别使用.x、.y、.z和.w来获取它们的第1、2、3、4个分量。GLSL也允许你对颜色使用rgba，或是对纹理坐标使用stpq访问相同的分量。

####输入与输出
虽然着色器是各自独立的小程序，但是它们都是一个整体的一部分，出于这样的原因，我们希望每个着色器都有输入和输出，这样才能进行数据交流和传递。GLSL定义了`in`和`out`关键字专门来实现这个目的。每个着色器使用这两个关键字设定输入和输出，只要一个输出变量与下一个着色器阶段的**输入匹配**，它就会传递下去。    

接下来我们修改一下绘制三角形的顶点着色器和片段着色器，实现顶点着色器往片段着色器传递数据。

顶点着色器代码

		#version 330 core
		layout (location = 0) in vec3 position; // position变量的属性位置值为0
		out vec4 vertexColor; // 为片段着色器指定一个颜色输出
		void main()
		{
    		gl_Position = vec4(position, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
    		vertexColor = vec4(0.5f, 0.5f, 0.5f, 1.0f); // 把输出变量设置为灰色
		}
		
片段着色器代码    
	
		#version 330 core
		in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
		out vec4 color; // 片段着色器输出的变量名可以任意命名，类型必须是vec
		void main()
		{
    		color = vertexColor;
		}
结果如下图所示    
![](http://or9mg8tf6.bkt.clouddn.com/Triangle-shader.png)    

####Uniform	
Uniform是一种从**CPU中的应用**向**GPU中的着色器**发送数据的方式，但uniform和顶点属性有些不同。首先，uniform是**全局的(Global)**。全局意味着uniform变量必须在每个着色器程序对象中都是独一无二的，而且它可以被**着色器程序**的任意着色器在任意阶段访问。第二，无论你把uniform值设置成什么，uniform会**一直**保存它们的数据，直到它们被重置或更新。    

接下来我们修改一下应用程序和片段着色器相关代码，实现应用向着色器传递发送数据。

片段着色器代码

		#version 330 core
		out vec4 color;
		uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量
		void main()
		{
    		color = ourColor;
		} 

应用程序

		//获取运行的秒数
		GLfloat timeValue = glfwGetTime();
		//使用sin函数让颜色在0.0到1.0之间改变
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		//查询uniform ourColor的位置值
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//激活的着色器程序
		glUseProgram(shaderProgram);
		//在当前激活的着色器程序中设置uniform
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

结果如下图所示,中间绿色三角形的颜色会随时间进行变化。      
![](http://or9mg8tf6.bkt.clouddn.com/Triangle-green.png)     

[参考代码](#Reference-code-block)

##5 纹理
我们已经了解到，我们可以为每个顶点添加颜色来增加图形的细节，从而创建出有趣的图像。但是，如果想让图形看起来更真实，我们就必须有足够多的顶点，从而指定足够多的颜色。这将会产生很多额外开销。  

一般程序员会使用纹理。纹理是一个2D图片（甚至也有1D和3D的纹理），它可以用来添加物体的细节；你可以想象纹理是一张绘有砖块的纸，无缝折叠贴合到你的3D的房子上，这样你的房子看起来就像有砖墙外表了。    

###准备
使用纹理之前要做的第一件事是把它们加载到我们的应用中。但是，纹理图像可能被储存为各种各样的格式，每种都有自己的数据结构和排列，我们不可能为每个支持的格式写加载器。因此，为了简化开发流程，我们使用一个支持多种流行格式的图像加载库，来帮我们完成图像加载过程。   
####SOIL
SOIL是简易OpenGL图像库(Simple OpenGL Image Library)的缩写，它支持大多数流行的图像格式，使用起来也很简单。你可以从他们的[主页](http://www.lonesock.net/soil.html)查看相关信息以及下载相应源码进行编译和安装到相关目录。安装过程参考GLFW的安装过程。    

安装成功有如下文件:
![](http://or9mg8tf6.bkt.clouddn.com/SOIL.png)
![](http://or9mg8tf6.bkt.clouddn.com/SOIL-lib.png)

然后还需要在Xcode工程下进行配置。
   
![](http://or9mg8tf6.bkt.clouddn.com/Xcode-soil-include.png)
![](http://or9mg8tf6.bkt.clouddn.com/Xcode-soil-link.png)     


####程序使用纹理流程如下    
1.准备顶点的纹理坐标数据。    
2.使用SOIL加载纹理数据。   
3.向OpenGL申请用于存储纹理数据的缓存。    
4.将纹理数据传入申请的缓存中。	  
5.配置传入顶点数据的属性，激活纹理坐标数据。 	
6.设置缓存上下文，通过uniform sampler往片段着色器传递纹理数据。


###生成纹理    
####1）纹理坐标
我们在原来的顶点数据中加入纹理数据，这样一行就代表一个顶点的属性。

	GLfloat vertices[] = {
        //vertex            //texcoords
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 左下角
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 右下角
         0.0f,  0.5f, 0.0f, 0.5f, 1.0f  // 上中
    };
    
####2）纹理数据
要使用SOIL库，我们需要加上头文件
	
		#include <SOIL.h>
然后我们就可以使用SOIL提供的函数加载纹理数据。

		int width, height;
		unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
函数首先需要输入图片文件的路径。然后需要两个int指针作为第二个和第三个参数，SOIL会分别返回图片的宽度和高度到其中。后面我们在生成纹理的时候会用图像的宽度和高度。第四个参数指定图片的通道(Channel)数量，但是这里我们只需留为0。最后一个参数告诉SOIL如何来加载图片：我们只关注图片的RGB值。结果会储存为一个很大的`char/byte`数组。


####3）纹理缓存对象
类似VBO,纹理也是使用ID引用。

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		//纹理已经绑定了，我们可以使用前面载入的图片数据生成一个纹理了
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
glTexImage2D参数说明：    

* 第一个参数指定了纹理目标(Target)。设置为`GL_TEXTURE_2D`意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到`GL_TEXTURE_1D`和`GL_TEXTURE_3D`的纹理不会受到影响）。
* 第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
* 第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
* 第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
* 下个参数应该总是被设为0（历史遗留问题）。
* 第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为`char(byte)`数组，我们将会传入对应值。
* 最后一个参数是真正的图像数据。

生成了纹理和相应的多级渐远纹理后，释放图像的内存并解绑纹理对象是一个很好的习惯。

		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	
####4）配置顶点属性指针
	
	 	//由于三角形坐标数据已经在location = 0了，因此我们将纹理坐标放在location = 1中
	 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	 	//激活顶点属性
    	glEnableVertexAttribArray(1);
    
####5）编写顶点着色器和片段着色器
顶点着色器，加入纹理坐标属性，并设置输出变量，将纹理坐标输出到片段着色器

		#version 330 core
		layout (location = 0) in vec3 position;
		layout (location = 1) in vec2 texCoord;
		out vec2 TexCoord;
		void main()
		{
    		gl_Position = vec4(position.x, position.y, position.z, 1.0);
    		TexCoord = texCoord;
		}	
 
片段着色器,设置输入变量，获取纹理坐标。同时定义一个`uniform sampler2D`变量用于获取纹理数据

		#version 330 core
		out vec4 color;
		in vec2 TexCoord;
		uniform sampler2D ourTexture;
		void main()
		{
			//GLSL内建的texture函数来采样纹理的颜色
    		color = texture(ourTexture, TexCoord);
		}
	
####6) 使用纹理绘制三角形
绘制三角形之前，我们要先激活着色器程序中设置uniform，并向其传入纹理数据，然后才开始绘制图形。

		//在当前激活的着色器程序中设置uniform
    	glActiveTexture(GL_TEXTURE0);
    	glBindTexture(GL_TEXTURE_2D, texture);
    	glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
        
    	glBindVertexArray(VAO);

	   glDrawArrays(GL_TRIANGLES, 0, 3);
    	glBindVertexArray(0);
    	glfwSwapBuffers(window);
    
####7）图形显示
若编译没有错误，运行应该有如下现象。
![](http://or9mg8tf6.bkt.clouddn.com/Triangle-wall.png)

###<a name="Reference-code-block">参考代码</a>

	#include <iostream>
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
	#include <math.h>
	#include <SOIL/SOIL.h>
	using namespace std;

	const GLuint WIDTH = 1024;
	const GLuint HEIGHT = 768;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	const GLchar * vertex = "#version 330 core\n\
	layout (location = 0) in vec3 position;\n\
	layout (location = 1) in vec2 texCoord;\n\
	out vec2 TexCoord;\n\
	void main()\n\
	{\n\
    	gl_Position = vec4(position.x, position.y, position.z, 1.0);\n\
    	TexCoord = texCoord;\n\
	}";

	const GLchar *fragment ="#version 330 core\n\
	out vec4 color;\n\
	in vec2 TexCoord;\n\
	uniform sampler2D ourTexture;\n\
	void main()\n\
	{\n\
    	color = texture(ourTexture, TexCoord);\n\
	}";

	int main(int argc, const char * argv[]) {
    
    	glfwInit();
    	glfwWindowHint(GLFW_SAMPLES, 4);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
    	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Windows", NULL, NULL);
    
    	if (!window) {
        	cerr << "create windows failed" << endl;
        	glfwTerminate();
        	return -1;
    	}
    	glfwMakeContextCurrent(window);
    	glfwSetKeyCallback(window, key_callback);
    
    	glewExperimental = GL_TRUE;
    	if (glewInit() != GLEW_OK)
    	{
        	std::cout << "Failed to initialize GLEW" << std::endl;
        	return -1;
    	}
    
    	GLuint vertexShader;
    	vertexShader = glCreateShader(GL_VERTEX_SHADER);
    	glShaderSource(vertexShader, 1, &vertex, NULL);
    	glCompileShader(vertexShader);
    	GLint success;
    	GLchar infoLog[512];
    	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    	if(!success)
    	{
        	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    	}
    
    	GLuint fragmentShader;
    	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    	glShaderSource(fragmentShader, 1, &fragment, NULL);
    	glCompileShader(fragmentShader);
    	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    	if(!success)
    	{
        	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    	}
    
    	GLuint shaderProgram;
    	shaderProgram = glCreateProgram();
    
    	glAttachShader(shaderProgram, vertexShader);
    	glAttachShader(shaderProgram, fragmentShader);
    	glLinkProgram(shaderProgram);
    
    	glDeleteShader(vertexShader);
    	glDeleteShader(fragmentShader);

    	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    	if(!success) {
        	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    	}
    
    
    	GLfloat vertices[] = {
        	//vertex            //texcoords
        	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 左下角
        	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 右下角
        	 0.0f,  0.5f, 0.0f,  0.5f, 1.0f // 上中
    	};
    	GLuint VAO, VBO;
    	glGenVertexArrays(1, &VAO);
    	glGenBuffers(1, &VBO);
    	glBindVertexArray(VAO);

    	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    	glEnableVertexAttribArray(0);
    	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    	glEnableVertexAttribArray(1);
    
    	int width, height;
    	unsigned char* image = SOIL_load_image("wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    
    	GLuint texture;
    	glGenTextures(1, &texture);
    	glBindTexture(GL_TEXTURE_2D, texture);
    
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    	glGenerateMipmap(GL_TEXTURE_2D);
    
    	SOIL_free_image_data(image);
    	glBindTexture(GL_TEXTURE_2D, 0);
    
    	glBindVertexArray(0);
    
    	while (!glfwWindowShouldClose(window)) {
        	glClear(GL_COLOR_BUFFER_BIT);
        	glfwPollEvents();
        
        	glUseProgram(shaderProgram);
        	glActiveTexture(GL_TEXTURE0);
        	glBindTexture(GL_TEXTURE_2D, texture);
        	glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
        

        	glBindVertexArray(VAO);

        	glDrawArrays(GL_TRIANGLES, 0, 3);
        	glBindVertexArray(0);
        	glfwSwapBuffers(window);
    	}	
    
    	glfwTerminate();
    
    	return 0;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
    	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, GL_TRUE);
	}



##6 变换
尽管我们现在已经知道了如何创建一个物体、着色、加入纹理，给它们一些细节的表现，但因为它们都还是静态的物体，仍是不够有趣。我们可以尝试着在每一帧改变物体的顶点并且重配置缓冲区从而使它们移动，但这太繁琐了，而且会消耗很多的处理时间。我们现在有一个更好的解决方案，使用（多个）**矩阵(Matrix)对象**可以更好的**变换(Transform)**一个物体。    

为了快速上手，我们省略掉变换背后的数学理论，有兴趣的读者可以点击[这里](https://learnopengl-cn.github.io/01%20Getting%20started/07%20Transformations/)。我们直接使用GLM库来实现各种变换。

####1）配置工程，并加入如下头文件

	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtc/type_ptr.hpp>
####2) 位移
我们使用`glm::translate`变换把一个向量`(1, 0, 0)`位移`(1, 1, 0)`个单位。     
我们把单位矩阵和一个位移向量传递给`glm::translate`函数来完成这个工作,然后用给定的矩阵乘以位移矩阵就能获得最后需要的矩阵。
	
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;
	//输出 2 1 0
*注意：我们把向量定义为一个glm::vec4类型的值，齐次坐标设定为1.0。齐次坐标为1.0允许我们在3D向量上进行位移，如果一个向量的齐次坐标是0，这个坐标就是方向向量(Direction Vector)，因为w坐标是0，这个向量就不能位移。*。  

####3) 旋转
我们使用`glm::rotate`变换把一个向量`(1, 0, 0)`绕`z`轴逆时针旋转`45`度。
我们把单位矩阵和一个旋转角度，以及要绕哪个轴旋转传递给`glm::rotate`函数来完成旋转操作。然后用给定的矩阵乘以位移矩阵就能获得最后需要的矩阵。

	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);    
	glm::mat4 trans;
	//该GLM版本接收的是弧度而不是角度，这种情况下我们用glm::radians(45.0f)将角度转换为弧度
	trans = glm::rotate(trans,glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	vec =  trans * vec ;
	std::cout << vec.x << " " << vec.y << " "<< vec.z << std::endl;
	//输出 0.707107 0.707107 0

####4) 缩放
我们使用`glm::scale`变换把一个向量`(1, 1, 1)`每个轴都缩小0.5倍。
我们把单位矩阵和每个轴要缩放的分量传递给`glm::scale`函数来完成缩放操作。然后用给定的矩阵乘以位移矩阵就能获得最后需要的矩阵。

	glm::vec4 vec(1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::scale(trans, vec3(0.5f,0.5f,0.5f)); 
	vec =  trans * vec ;
	std::cout << vec.x << " " << vec.y << " "<< vec.z << std::endl;
	//输出 0.5 0.5 0.5

##7 坐标系统

OpenGL希望在每次顶点着色器运行后，我们可见的所有顶点都为**标准化设备坐标(Normalized Device Coordinate, NDC)**。也就是说，每个顶点的x，y，z坐标都应该在`-1.0`到`1.0`之间，超出这个坐标范围的顶点都将不可见。我们通常会自己设定一个坐标的范围，之后再在顶点着色器中将这些坐标变换为标准化设备坐标。然后将这些标准化设备坐标传入光栅器(Rasterizer)，将它们变换为屏幕上的二维坐标或像素。

将坐标变换为标准化设备坐标，接着再转化为屏幕坐标的过程通常是**分步**进行的，也就是类似于流水线那样子。在流水线中，物体的顶点在最终转化为屏幕坐标之前还会被变换到多个坐标系统(Coordinate System)。将物体的坐标变换到几个**过渡坐标系(Intermediate Coordinate System)**的优点在于，在这些特定的坐标系统中，一些操作或运算更加方便和容易，这一点很快就会变得很明显。对我们来说比较重要的总共有5个不同的坐标系统：

* 局部空间(Local Space，或者称为物体空间(Object Space))
* 世界空间(World Space)
* 观察空间(View Space，或者称为视觉空间(Eye Space))
* 裁剪空间(Clip Space)
* 屏幕空间(Screen Space)
这就是一个顶点在最终被转化为片段之前需要经历的所有不同状态。

###预备知识
为了将坐标从一个坐标系变换到另一个坐标系，我们需要用到几个变换矩阵，最重要的几个分别是**模型(Model)**、**观察(View)**、**投影(Projection)**三个矩阵。我们的顶点坐标起始于**局部空间(Local Space)**，在这里它称为**局部坐标(Local Coordinate)**，它在之后会变为**世界坐标(World Coordinate)**，**观察坐标(View Coordinate)**，**裁剪坐标(Clip Coordinate)**，并最后以**屏幕坐标(Screen Coordinate)**的形式结束。下面的这张图展示了整个流程以及各个变换过程做了什么：    
![](http://or9mg8tf6.bkt.clouddn.com/coordinate_systems.png)    
1. 局部坐标是对象相对于**局部原点**的坐标，也是物体起始的坐标。    
2. 下一步是将局部坐标变换为世界空间坐标，世界空间坐标是处于一个更大的空间范围的。这些坐标相对于世界的**全局原点**，它们会和其它物体一起**相对于世界的原点**进行摆放。    
3. 接下来我们将世界坐标变换为观察空间坐标，使得每个坐标都是从**摄像机或者说观察者**的角度进行观察的。     
4. 坐标到达观察空间之后，我们需要将其投影到裁剪坐标。**裁剪坐标会被处理至-1.0到1.0的范围内**，并判断哪些顶点将会出现在屏幕上。     
5. 最后，我们将裁剪坐标变换为屏幕坐标，我们将使用一个叫做视口变换(Viewport Transform)的过程。视口变换将位于`-1.0`到`1.0`范围的坐标变换到由`glViewport`函数所定义的坐标范围内。最后变换出来的坐标将会送到光栅器，将其转化为片段。   

####局部空间    
局部空间是指物体所在的坐标空间，即对象最开始所在的地方。我们一直使用的那个三角形的顶点是被设定在`-0.5`到`0.5`的坐标范围中，`(0, 0)`是它的原点。这些都是局部坐标。
####世界坐标   
如果我们将我们所有的物体导入到程序当中，它们有可能会全挤在世界的原点`(0, 0, 0)`上，这并不是我们想要的结果。我们想为每一个物体定义一个位置，从而能在更大的世界当中放置它们。世界空间中的坐标正如其名：是指顶点相对于世界的坐标。如果你希望将物体分散在世界上摆放，这就是你希望物体变换到的空间。物体的坐标将会从局部变换到世界空间；该变换是由**模型矩阵(Model Matrix)**实现的。
模型矩阵是一种变换矩阵，它能通过对物体进行`位移、缩放、旋转`来将它置于它本应该在的位置或朝向。
####观察空间    
观察空间经常被人们称之OpenGL的**摄像机(Camera)**（所以有时也称为**摄像机空间(Camera Space)或视觉空间(Eye Space)**）。观察空间是将世界空间坐标转化为**用户视野前方**的坐标而产生的结果。因此观察空间就是从摄像机的视角所观察到的空间。而这通常是由一系列的`位移和旋转`的组合来完成，平移和旋场景从而使得特定的对象被**变换到摄像机的前方**。这些组合在一起的变换通常存储在一个**观察矩阵(View Matrix)**里，它被用来将世界坐标变换到观察空间。
####裁剪空间
在一个顶点着色器运行的最后，OpenGL期望所有的坐标都能落在一个特定的范围内，且任何在这个范围之外的点都应该被裁**剪掉(Clipped)**。被裁剪掉的坐标就会被忽略，所以剩下的坐标就将变为屏幕上可见的片段。这也就是**裁剪空间(Clip Space)**名字的由来。    

因为将所有可见的坐标都指定在`-1.0`到`1.0`的范围内不是很直观，所以我们会指定自己的**坐标集(Coordinate Set)**并将它变换回标准化设备坐标系。   

为了将顶点坐标从观察变换到裁剪空间，我们需要定义一个**投影矩阵(Projection Matrix)**，它指定了一个范围的坐标，比如在每个维度上的`-1000`到`1000`。投影矩阵接着会将在这个指定的范围内的坐标变换为标准化设备坐标的范围`(-1.0, 1.0)`。   
 
由投影矩阵创建的**观察箱(Viewing Box)**被称为**平截头体(Frustum)**，每个出现在平截头体范围内的坐标都会最终出现在用户的屏幕上。将特定范围内的坐标转化到**标准化设备坐标系**的过程（而且它很容易被映射到2D观察空间坐标）被称之为**投影(Projection)**，因为使用投影矩阵能将3D坐标投影(Project)到很容易映射到2D的标准化设备坐标系中。  
  
一旦所有顶点被变换到裁剪空间，最终的操作——**透视除法(Perspective Division)**将会执行，在这个过程中我们将位置向量的`x，y，z`分量分别除以向量的齐次`w`分量；透视除法是将`4D裁剪空间坐标`变换为`3D标准化设备坐标`的过程。这一步会在每一个顶点着色器运行的最后被自动执行。

在这一阶段之后，最终的坐标将会被映射到**屏幕空间**中（使用`glViewport`中的设定），并被变换成片段。

将观察坐标变换为裁剪坐标的投影矩阵可以为两种不同的形式，每种形式都定义了不同的平截头体。我们可以选择创建一个**正射投影矩阵(Orthographic Projection Matrix)**或一个**透视投影矩阵(Perspective Projection Matrix)**。    

####正射投影
正射投影矩阵定义了一个类似立方体的平截头箱，它定义了一个裁剪空间，在这空间之外的顶点都会被裁剪掉。创建一个正射投影矩阵需要指定可见平截头体的宽、高和长度。在使用正射投影矩阵变换至裁剪空间之后处于这个平截头体内的所有坐标将不会被裁剪掉。它的平截头体看起来像一个容器：
<div align=center>
![](http://or9mg8tf6.bkt.clouddn.com/orthographic_frustum.png)    
</div>
上面的平截头体定义了可见的坐标，它由由宽、高、近(Near)平面和远(Far)平面所指定。任何出现在近平面之前或远平面之后的坐标都会被裁剪掉。正射平截头体直接将平截头体内部的所有坐标映射为标准化设备坐标，因为每个向量的w分量都没有进行改变；如果w分量等于1.0，透视除法则不会改变这个坐标。

要创建一个正射投影矩阵，我们可以使用GLM的内置函数glm::ortho：

	//前两个参数指定了平截头体的左右坐标
	//第三和第四参数指定了平截头体的底部和顶部
	//通过这四个参数我们定义了近平面和远平面的大小
	//然后第五和第六个参数则定义了近平面和远平面的距离。
	//这个投影矩阵会将处于这些x，y，z值范围内的坐标变换为标准化设备坐标。
	glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	
####透视投影
如果你曾经体验过实际生活给你带来的景象，你就会注意到离你越远的东西看起来更小。这个奇怪的效果称之为**透视(Perspective)**。透视的效果在我们看一条无限长的高速公路或铁路时尤其明显，正如下面图片显示的那样：     
<div align=center>    
![](http://or9mg8tf6.bkt.clouddn.com/perspective.png)    
</div>  
正如你看到的那样，由于透视，这两条线在很远的地方看起来会相交。这正是透视投影想要模仿的效果，它是使用**透视投影矩阵**来完成的。这个投影矩阵将给定的平截头体范围映射到裁剪空间，除此之外还修改了每个顶点坐标的`w`值，从而使得离观察者**越远**的顶点坐标**`w`分量越大**。顶点坐标的每个分量都会**除以**它的`w`分量，距离观察者越远顶点坐标就会越小。这是也是`w`分量非常重要的另一个原因，它能够帮助我们进行透视投影。 
   
下面是一张透视平截头体的图片：
<div align=center>    
![](http://or9mg8tf6.bkt.clouddn.com/perspective_frustum.png) 
</div>        
在GLM中可以这样创建一个透视投影矩阵：    

	//第一个参数定义了fov的值，它表示的是视野(Field of View)，并且设置了观察空间的大小
	//第二个参数设置了宽高比，由视口的宽除以高所得
	//第三和第四个参数设置了平截头体的近和远平面。我们通常设置近距离为0.1f，而远距离设为100.0f。
	glm::mat4 proj = glm::perspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
	
我们为上述的每一个步骤都创建了一个变换矩阵：模型矩阵、观察矩阵和投影矩阵。一个顶点坐标将会根据以下过程被变换到裁剪坐标：
<math display="block">
    <msubsup><mi>V</mi> <mi>clip</mi> <mi></mi></msubsup>
    <mo>=</mo>
    <msubsup><mi>M</mi> <mi>projection</mi><mi></mi></msubsup>
    <mo>·</mo>
    <msubsup><mi>M</mi> <mi>view</mi> <mi></mi></msubsup>
    <mo>·</mo>
    <msubsup><mi>M</mi> <mi>model</mi> <mi></mi></msubsup>
    <mo>·</mo>
    <msubsup><mi>V</mi> <mi>local</mi> <mi></mi></msubsup>
</math>
注意矩阵运算的顺序是相反的（记住我们需要**从右往左**阅读矩阵的乘法）。最后的顶点应该被赋值到顶点着色器中的`gl_Position`，OpenGL将会自动进行透视除法和裁剪。

###进入3D
既然我们知道了如何将3D坐标变换为2D坐标，我们可以开始绘制3D场景。
简单起见，我们变换一下我们的三角形，使它看起来就像是一个3D的平面，静止在一个虚构的地板上。

####1）设置模型矩阵（Model Matrix）
我们首先创建一个模型矩阵。这个模型矩阵包含了位移、缩放与旋转操作，它们会被应用到所有物体的顶点上，以变换它们到全局的世界空间。让我们变换一下我们的平面，将其绕着x轴旋转，使它看起来像放在地上一样。这个模型矩阵看起来是这样的：

	glm::mat4 model;
	model = glm::rotate(model, glm::radians(-70.0f) , glm::vec3(1.0f, 0.0f, 0.0f));
通过将顶点坐标乘以这个模型矩阵，我们将该顶点坐标变换到世界坐标。我们的平面看起来就是在地板上，代表全局世界里的平面。

####2）设置观察矩阵（View Matrix）
我们想要在场景里面稍微往后移动，以使得物体变成可见的（当在世界空间时，我们位于原点`(0,0,0)`)。而将摄像机向后移动，和将整个场景向前移动是一样的。我们以**相反**于摄像机移动的方向移动整个场景。这里我们将整个场景向前移动，并且由于OpenGL是一个**右手坐标系(Right-handed System)**，所以我们会通过将场景沿着`z`轴负方向平移来实现。它会给我们一种我们在往后移动的感觉。因此，观察矩阵是这样的：

	glm::mat4 view;
	// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
	
*右手坐标系：*
<div align=center>    
![](http://or9mg8tf6.bkt.clouddn.com/coordinate_systems_right_handed.png) 
</div>  

####3）设置投影矩阵（Projection Matrix）
我们希望在场景中使用透视投影，所以像这样声明一个投影矩阵：

    glm::mat4 projection;
    //注意这里的glm::radians
    projection = glm::perspective(glm::radians(45.0f), (GLfloat)800 /(GLfloat) 600, 0.1f, 100.0f);
    
####4）修改顶点着色器
我们在顶点着色器中声明uniform变换矩阵然后将它乘以顶点坐标：

	...
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
	...
	// 注意从右向左读
	gl_Position = projection * view * model * vec4(position, 1.0f);
	...
	
####5）传递变换矩阵，绘制场景
我们将创建的变换矩阵传入着色器，并且在每次的渲染迭代中进行，因为变换矩阵会经常变动：

	 ...
	GLint modelLoc = glGetUniformLocation(shaderProgram, "model"); 
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");   
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    ...
    while(...)
    {
    	...
    	glUseProgram(shaderProgram);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        //往顶点着色器传入model,view,projection矩阵
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
  
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        ...
    }
    
####6) 显示
我们的顶点坐标已经使用模型、观察和投影矩阵进行变换了，最终的物体应该会：    

* 稍微向后倾斜至地板方向。
* 离我们有一些距离。
* 有透视效果（顶点越远，变得越小。     
    
若编译没问题，应该有如下显示：    
<div align=center>    
![](http://or9mg8tf6.bkt.clouddn.com/triangle-3D.png) 
</div> 

###参考源码

	#include <iostream>
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
	#include <math.h>
	#include <SOIL/SOIL.h>
	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtc/type_ptr.hpp>
	using namespace glm;
	using namespace std;

	const GLuint WIDTH = 1024;
	const GLuint HEIGHT = 768;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	const GLchar * vertex = "#version 330 core\n\
	layout (location = 0) in vec3 position;\n\
	layout (location = 1) in vec2 texCoord;\n\
	uniform mat4 model;\n\
	uniform mat4 view;\n\
	uniform mat4 projection;\n\
	out vec2 TexCoord;\n\
	void main()\n\
	{\n\
	    	gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);\n\
    		TexCoord = texCoord;\n\
	}";

	const GLchar *fragment ="#version 330 core\n\
	out vec4 color;\n\
	in vec2 TexCoord;\n\
	uniform sampler2D ourTexture;\n\
	void main()\n\
	{\n\
    	color = texture(ourTexture, TexCoord);\n\
	}";

	int main(int argc, const char * argv[]) {
    
    	//设置窗口属性
    	glfwInit();
    	glfwWindowHint(GLFW_SAMPLES, 4);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
    	//创建窗口
    	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Windows", NULL, NULL);
    
    	if (!window) {
        	cerr << "create windows failed" << endl;
        	glfwTerminate();
        	return -1;
    	}
    
    	//设置该window为opengl上下文对象
    	glfwMakeContextCurrent(window);
    	//设置按键回调函数
    	glfwSetKeyCallback(window, key_callback);
    
    	//初始化glew
    	glewExperimental = GL_TRUE;
    	if (glewInit() != GLEW_OK)
    	{
        	std::cout << "Failed to initialize GLEW" << std::endl;
        	return -1;
    	}
    
    	//编译顶点着色器
    	GLuint vertexShader;
    	vertexShader = glCreateShader(GL_VERTEX_SHADER);
    	glShaderSource(vertexShader, 1, &vertex, NULL);
    	glCompileShader(vertexShader);
    	GLint success;
    	GLchar infoLog[512];
    	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    	if(!success)
    	{
        	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    	}
    
    	//编译片段着色器
    	GLuint fragmentShader;
    	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    	glShaderSource(fragmentShader, 1, &fragment, NULL);
    	glCompileShader(fragmentShader);
    	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    	if(!success)
    	{
        	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    	}
    
    	//链接顶点着色器和片段着色器，创建着色器对象
    	GLuint shaderProgram;
    	shaderProgram = glCreateProgram();
    	glAttachShader(shaderProgram, vertexShader);
    	glAttachShader(shaderProgram, fragmentShader);
    	glLinkProgram(shaderProgram);
    	glDeleteShader(vertexShader);
    	glDeleteShader(fragmentShader);
    	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    	if(!success) {
        	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    	}
    
    	//三角形顶点属性，包括三角形顶点坐标以及纹理坐标
    	GLfloat vertices[] = {
        	//vertex            //texcoords
        	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 左下角
        	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 右下角
        	0.0f,  0.5f, 0.0f,  0.5f, 1.0f // 上中
    	};
    
    	GLuint VAO, VBO;
    	glGenVertexArrays(1, &VAO);
    	glGenBuffers(1, &VBO);
    	//绑定vao对象
    	glBindVertexArray(VAO);

    	//填充vbo缓存
    	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    	//设置顶点属性
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    	glEnableVertexAttribArray(0);
    	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    	glEnableVertexAttribArray(1);
    
    	//加载纹理数据
    	int width, height;
    	unsigned char* image = SOIL_load_image("/Users/zj-db0860/LearnOpenGL/common/resources/textures/wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    
    	GLuint texture;
    	//创建纹理缓存
    	glGenTextures(1, &texture);
    	//绑定纹理缓存
    	glBindTexture(GL_TEXTURE_2D, texture);
    
    	//填充纹理缓存
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    	glGenerateMipmap(GL_TEXTURE_2D);
    	SOIL_free_image_data(image);
    	glBindTexture(GL_TEXTURE_2D, 0);
    
    
    	//设置模型矩阵
    	glm::mat4 model = glm::rotate(model, glm::radians(-70.0f) , glm::vec3(1.0f, 0.0f, 0.0f));
    	//设置观察矩阵
    	glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    	//设置投影矩阵
    	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH /(GLfloat) HEIGHT, 0.1f, 100.0f);
    
    	//获取着色器对象内相应变换矩阵的uniformID
    	GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    	GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    	GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
   
    	glBindVertexArray(0);
    
    	while (!glfwWindowShouldClose(window)) {
        	glClear(GL_COLOR_BUFFER_BIT);
        	glfwPollEvents();
        
        	//激活着色器对象
        	glUseProgram(shaderProgram);
        	//激活纹理对象
        	glActiveTexture(GL_TEXTURE0);
        	glBindTexture(GL_TEXTURE_2D, texture);
        
        	//传入矩阵
        	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        	//传入纹理数据
        	glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
        
        	//绑定vao
        	glBindVertexArray(VAO);
        	//绘制图形
        	glDrawArrays(GL_TRIANGLES, 0, 3);
        	glBindVertexArray(0);
        	glfwSwapBuffers(window);
    	}
    
    	glfwTerminate();
    
    	return 0;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
    
    	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
	}


##参考
[learnopengl](https://learnopengl-cn.github.io/intro/)