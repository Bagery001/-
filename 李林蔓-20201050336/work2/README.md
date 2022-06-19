实验二

1、实验内容：
熟悉OPENGL，通过DDA、中点算法生成直线段

2、实验目的：
安装OPENGL，能编写代码运行，参考课本代码。

关键代码：
void DDA_Line(int x1, int y1, int x2, int y2) {
	double dx, dy, e, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	dx /= e;
	dy /= e;
	x = x1;
	y = y1;
	for (int i = 0; i < e; i++) {
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex2i(int(x + 0.5), int(y + 0.5));
		glEnd();
		glFlush();
		x += dx;
		y += dy;
	}
}

结果：
  ![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work2/%E5%AE%9E%E9%AA%8C2.jpg)

总结：
计算机中，直线并不是连续的，二是离散的点，这是光珊化的本质决定的。
两点确定一条直线，假设如果给出了起点和终点分别是(x1，y1)，(x2，y2)，假设这条直线为 y = mx + b，那么斜率m就是：
m = dy / dx = (y2 - y1) / (x2 - x1)
b = (x2y1 - x1y2) / (x2 - x1)
有限差分近似解是：
x(i+1) = x(i) + ∆x
y(i+1) = y(i) + ∆y = y(i) + ((y1 - y1) / (x2 - x1)) * ∆x
考虑到不能让直线出现中断的情况，
斜率|m|<1时，要以x轴为步进的主方向，∆y每次比较小。
斜率|m|>1时，要以y轴为步进的主方向，∆x每次比较小。
经过上述知识点描述，DDA算法的实现思路如下：
  声明double类的变量dx，dy，e，x，y，其中dx和dy作为步进长度，e作为循环次数，x和y记录每次画点的坐标；
  dx=x2-x1，dy=y2-y1，计算斜率，如果斜率小于1则选择x为主步进方向，反之y为主步进方向。
  循环e次，每次循环画一个点，这里我选择x每次增大0.5，同时要将变化后的点从浮点类型转换为整型，同时更新下一次的x和y值。
