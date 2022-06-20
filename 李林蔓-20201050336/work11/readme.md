实验十一

1、实验内容：
 1）使用opengl，完成鼠标、键盘交互操作
 2）OPENGL画茶壶并旋转 
2、实验目的：
 1）熟悉鼠标、键盘交互
 2）opengl的函数功能，使用opengl库函数对3D图像的坐标位置进行定位，使用相关函数进行旋转。
 设置输入输出语句，配合scanf人机交互，由用户对旋转轴和角度进行指定。填充图定位在固定点，旋转线框图来进行对照。
 
 结果：
 ![Image text]()
 ![Image text]()
 ![Image text]()
 
 关键代码：
 void displayWirePolyhedra(float x,float y,float z,float thera){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);
	gluLookAt(5.0,5.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
	glScalef(1.0,1.0,1.0);
	glTranslatef(1.0,2.0,0.0);//下一个图形坐标
	glutSolidTeapot(1.5);
	//glutWireTeapot(1.5);//放大倍数
	glScalef(1.0,1.0,1.0);//缩放比
	glTranslatef(-1.0,-5.0,0.0);//下一个图形坐标

	glRotatef(thera,x,y,z);
	glutWireTeapot(1.5);
	//glutSolidTeapot(2.0);
	glFlush();
}

总结：
