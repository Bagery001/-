实验七
1、实验内容：
1）教材P458，GLUT鼠标函数
2）使用opengl，实现任一反走样技术。

2、实验目的：
1）调用鼠标函数完成相应功能，2-3个程序。
2）使用opengl，实现任一反走样技术。

结果：
GLUT鼠标函数
画直线（由鼠标起点，左鼠标终点）
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work7/%E5%AE%9E%E9%AA%8C7.1.1.jpg)

画点
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work7/%E5%AE%9E%E9%AA%8C7.1.2.jpg)

反走样
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work7/%E5%AE%9E%E9%AA%8C7.2.jpg)

关键代码：
GLUT鼠标函数：
if (button_kind == 0)	//左键点击
	{
		//画一个蓝色的点
		glPointSize(20);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(hit_pos_x, hit_pos_y);
		glEnd();
	}
	else if (button_kind == 2)	//右键点击
	{
		//画一个绿色的点
		glPointSize(20);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(hit_pos_x, hit_pos_y);
		glEnd();
	}
	else if (button_kind == 3)	//鼠标拖动
	{
		//沿拖动轨迹画一条红色的线
		glLineWidth(5);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(hit_pos_x, hit_pos_y);
		glVertex2f(move_pos_x, move_pos_y);
		glEnd();
	}
  
  反走样：
  void Displayw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);  //用当前背景色填充窗口
	glEnable(GL_LINE_SMOOTH);      //使用反走样
	glEnable (GL_BLEND);             //启用混合函数
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //指定混合函数
   	glCallList(lineList); //函数执行显示列表
    glFlush();            //强制刷新缓冲，保证绘图命令将被执行

}

总结：
GLUT提供鼠标动作检测能力。有两种GLUT处理的motion：active motion和passive motion。

  Active motion是指鼠标移动并且有一个鼠标键被按下。
  Passive motion是指当鼠标移动时，并有没鼠标键按下。
  如果一个程序正在追踪鼠标，那么鼠标移动期间，每一帧将产生一个结果。
  和以前一样，必须注册将处理鼠标事件的函数（定义函数）。GLUT让我们可以指定两个不同的函数，一个追踪passive motion，另一个追踪active motion。
