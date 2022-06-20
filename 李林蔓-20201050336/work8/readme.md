实验八

1、实验内容：
 使用opengl，用Cohen-Sutherland线段裁剪算法对直线段进行裁剪
 
2、实验目的：
 验证Cohen-Sutherland裁剪算法，从键盘输入任意的直线段，用指定的裁剪窗口裁剪直线段。
 
 结果：
 ![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work8/%E5%AE%9E%E9%AA%8C8.jpg)
 
 关键代码：
 //画点函数
void draw_a_point(int x, int y)
{
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

//判断位置
void chopLine(Point& p, unsigned char code, double dely, double delx) {
	if (code & 1) { //0001 左方，位与运算，结果不为0时证明在窗口左方有交点
		p.y += (myWindow.l - p.x) * dely / delx;
		p.x = myWindow.l;
	}
	else if (code & 2) { //0010 右方
		p.y += (myWindow.r - p.x) * dely / delx;
		p.x = myWindow.r;
	}
	else if (code & 4) { //0100 下方
		p.x += (myWindow.b - p.y) * delx / dely;
		p.y = myWindow.b;
	}
	else { //1000 上方
		p.x += (myWindow.t - p.y) * delx / dely;
		p.y = myWindow.t;
	}
}

//按位或，生成编号（根据二进制转十进制）
void generateCode(Point& p, unsigned char& code) {
	if (p.x < myWindow.l)	code |= 1;
	if (p.y > myWindow.t)	code |= 8;
	if (p.x > myWindow.r)	code |= 2;
	if (p.y < myWindow.b)	code |= 4;
}

//裁剪
int cut(pair<Point, Point>& tmp) {
	unsigned char code1;
	unsigned char code2;
	int k = 0;
	do {
		code1 = 0;
		code2 = 0;
		generateCode(tmp.first, code1);
		generateCode(tmp.second, code2);
		if ((code1 | code2) == 0) {  //完全在窗口里面（0000|0000）
			return 1;
		}
		else if ((code1 & code2) != 0) { //在某条边界同侧，即完全在窗口外面
			return 0;
		}
		if (code1 != 0) {
			chopLine(tmp.first, code1, tmp.second.y - tmp.first.y, tmp.second.x - tmp.first.x);
		}
		if (code2 != 0) {
			chopLine(tmp.second, code2, tmp.second.y - tmp.first.y, tmp.second.x - tmp.first.x);
		}
		k++;
	} while (1);
}

总结
以下分析Cohen-Sutherland和Sutherland-Hodgman两个算法，其中Cohen-Sutherland算法的基本思想通过编码的方法快速实现对直线段的裁剪；Sutherland-Hodgman算法基本思想是用窗口的四条边所在的直线依次来裁剪多边形。
Cohen-Sutherland算法
该算法的基本思想是：对于每条待裁剪的线段P1,P2分三种情况处理：
若P1P2完全在窗口内，则显示该线段。
若P1P2完全在窗口外，则丢弃该线段。
若线段既不满足“取”的条件，也不满足“舍”的条件，则求线段与窗口边界的交点，在交点处把线段分为两段。
编码原则
具体编码过程为将延长线窗口的四条边线(yT、yB、xR、xL)，将二维平面分成九个区域，全为0的区域是裁剪窗口，其中各位编码的定义如下：
按照如上定义。

裁剪算法：
依据上面的编码原则，可以总结出对一条线段的可见性进行测试：
若线段两个端点的四位二进制编码全为0000，即两端点编码逻辑或运算为0，那么该线段完全位于窗口内，可直接保留。
对端点的四位二进制编码进行逻辑与运算，若结果不为零，那么整条线段必位于窗口外，可直接舍弃。
否则，这条线段既不能保留也不能舍弃，它可能与窗口相交。此时，需要对窗口进行再分割，并对分割后的线段按照一定顺序进行检查，决定保留、舍弃或再分割。重复这过程，直到全部线段均被舍弃或保留为止。
Sutherland-Hodgman算法
算法的基本思想是利用窗口的四条边所在的直线依次来裁剪多边形。多边形的每条边与裁剪线的位置关系有4种情况
