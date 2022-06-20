实验十二

1、实验内容：
 1）使用opengl，完成投影变换等实验
 2）P 264  

2、实验目的：
 熟悉三维观察相关内容
 
 结果：
 ![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work12/%E5%AE%9E%E9%AA%8C12.jpg)
 
 关键代码：
 void displayFcn(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	/*Set parameters for a square fi11 area. */
	glColor3f(0.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	glEnd();
	glFlush();
}
void reshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
}

总结：
计算机显示器是一个 2D 表面。OpenGL 渲染的 3D 场景必须作为 2D 图像投影到计算机屏幕上。
1、定义投影矩阵，指定了一个范围的坐标，以此来模拟相机的可视范围
2、投影矩阵接着会将在这个指定的范围内的坐标变换为标准化设备坐标的范围(-1.0, 1.0)。所有在范围外的坐标不会被映射到在-1.0到1.0的范围之间，所以会被裁剪掉。以此模拟相机的可视范围。
2、裁剪完后，进行透视除法，将4D裁剪空间坐标变换为3D标准化设备坐标
