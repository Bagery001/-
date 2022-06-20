//平移、比例、旋转
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

float deltax, deltay;
float intervalx, intervaly;
float _angle;
struct Point {
	int x;
	int y;
};
/*采用行向量矩阵，把P'=M*P的变换矩阵M和列向量P转置，CT=(AB)T=BT*AT,得到的结果也是行向量*/
void MultiplyMatrixAB(int a[3][3], float b[3][3], float c[3][3], int row) {
	int i, j, k, sum;
	for (i = 0; i < row; i++) {
		for (k = 0; k < 3; k++) {
			sum = 0;
			for (j = 0; j < 3; j++)
				sum += a[i][j] * b[j][k];
			c[i][k] = sum;
		}
	}
}
void Scaling2D(Point shape[], int n, Point Rshape[]) {
	/*这里是左边P乘以右边S，左边是仅有一行，相当于是把计算设计时的P'=S*P的P转置后放在左边。
	右边S也是相当于转置过的矩阵，在这无法体现。旋转变化时，rotate[0][1]就取正sin，rotate[1][0]=-sin
	用列向量的公式是第一行第二列取-sin，第二行第一列取sin。只要正确转置就行。*/
	float scale[3][3] = { 1,0,0,0,1,0,0,0,1 };
	scale[0][0] = deltax;
	scale[1][1] = deltay;
	int pnt[1][3] = { 0,0,1 };
	int i;
	float result[1][3] = { 0 };
	for (i = 0; i < n; i++) {//有n个点要变换，循环n次
		pnt[0][0] = shape[i].x;//shape存储了变形前的坐标，每个点依次变换
		pnt[0][1] = shape[i].y;
		MultiplyMatrixAB(pnt, scale, result, 1);//数组的值存在堆中，数组传递给函数的变量是一个指针，被调函数内通过指针直接改变存储的值
		Rshape[i].x = result[0][0];//Rshape存储了变形后的坐标
		Rshape[i].y = result[0][1];
	}
}
void Translation2D(Point shape[], int n, int deltax, int deltay, Point Rshape[]) {
	float trans[3][3] = { 1,0,0,0,1,0,0,0,1 };
	trans[2][0] = deltax;//同样，相比于笔记的公式，转个置。
	trans[2][1] = deltay;
	int pnt[1][3] = { 0,0,1 };
	int i;
	float result[1][3] = { 0 };
	for (i = 0; i < n; i++) {
		pnt[0][0] = shape[i].x;
		pnt[0][1] = shape[i].y;
		MultiplyMatrixAB(pnt, trans, result, 1);
		Rshape[i].x = result[0][0];
		Rshape[i].y = result[0][1];
	}
}
void Rotation2D(Point shape[], int n, float angle, Point Rshape[]) {
	angle *= 3.14 / 180;
	float rotate[3][3] = { 0,0,0,0,0,0,0,0,1 };
	rotate[0][0] = rotate[1][1] = cos(angle);
	rotate[0][1] = sin(angle);
	rotate[1][0] = -rotate[0][1];//取负肯定比再sin一次快。
	int pnt[1][3] = { 0,0,1 };
	int i;
	float result[1][3] = { 0 };
	for (i = 0; i < n; i++) {
		pnt[0][0] = shape[i].x;
		pnt[0][1] = shape[i].y;
		MultiplyMatrixAB(pnt, rotate, result, 1);
		Rshape[i].x = result[0][0];
		Rshape[i].y = result[0][1];
	}
}
/*Bresenham画线法*/
#pragma region Line
void drawOrdinayLine(int x0, int y0, int x1, int y1, int flag) {
	int i;
	int x, y, dx, dy, e;
	dx = x1 - x0;
	dy = y1 - y0;
	e = -dx;
	x = x0; y = y0;
	for (i = 0; i <= dx; i++) {
		switch (flag) {
		case 0:
			glVertex2i(x,y);   break;
		case 1:
			glVertex2i(x, 2 * y0 - y); break;//增量为(y-y0)则，实际增量应取相反方向为y0-（y-y0）=2y0-y
		case 2:
			glVertex2i(y, x); break;//这里也要交换
		case 3:
			glVertex2i(2 * y0 - y, x); break;
		}
		x++;
		e = e + 2 * dy;
		if (e >= 0) {
			y++;
			e = e - 2 * dx;
		}
	}
}
void Swap(int *a, int *b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
void BresenhamLine(int x0, int y0, int x1, int y1) {
	int i;
	if (x0 > x1) {//总是从左端开始
		Swap(&x0, &x1);
		Swap(&y0, &y1);
	}
	if (x0 == x1) {
		if (y0 > y1) {//从y0开始“往上”画，所以不允许y1更低;
			Swap(&y0, &y1);
		}
		for (i = y0; i < y1; i++) {
			glVertex2i(x0, i);
		}
		return;
	}
	float k = (1.0*(y1 - y0)) / (x1 - x0);//根据斜率调整取点
	if (0 <= k && k <= 1) {  //直接画
		drawOrdinayLine(x0, y0, x1, y1, 0);
	} else if (-1 <= k && k < 0) {//以y=y0作B点的对称点
		drawOrdinayLine(x0, y0, x1, y1 + 2 * (y0 - y1), 1);
	} else if (k > 1) {//交换x,y的坐标值。
		Swap(&x0, &y0);//可以直接交换传入函数的参数，这为了直观。
		Swap(&x1, &y1);
		drawOrdinayLine(x0, y0, x1, y1, 2);
	} else if (k < -1) {
		//交换xy
		Swap(&x0, &y0);
		Swap(&x1, &y1);
		//交换两个点
		Swap(&x0, &x1);
		Swap(&y0, &y1);
		drawOrdinayLine(x0, y0, x1, y1 + 2 * (y0 - y1), 3);
	}
}
#pragma endregion
void Transform2DSegment() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	//绘制带小箭头的坐标系
	BresenhamLine(10, 200, 400, 200);
	BresenhamLine(395, 195, 400, 200);
	BresenhamLine(400, 200, 395, 205);
	BresenhamLine(200, 400, 200, 10);
	BresenhamLine(200, 400, 205, 395);
	BresenhamLine(200, 400, 195, 395);
	//试验
	/*
	Point a, b, c, d, e;
	a.x = 60 - 20 * sin(36 * 3.14 / 180); a.y = 60 - 20 * cos(36 * 3.14 / 180);
	b.x = 60; b.y = 80;
	c.x = 60 + 20 * sin(36 * 3.14 / 180); c.y = 60 - 20 * cos(36 * 3.14 / 180);
	d.x = 60 - 20 * cos(18 * 3.14 / 180); d.y = 60 + 20 * sin(18 * 3.14 / 180);
	e.x = 60 + 20 * cos(18 * 3.14 / 180); e.y = 60 + 20 * sin(18 * 3.14 / 180);

	Point shape[5] = { a,b,c,d,e };
	Point Rshape[5] = { 0 };
	Scaling2D(shape, 5, Rshape);
	Translation2D(Rshape, 5, intervalx, intervaly, Rshape);
	Rotation2D(Rshape, 5, _angle, Rshape);
	//到第一象限显示
	for (int i = 0; i < 5; i++) {
		shape[i].x = 200 + shape[i].x;
		Rshape[i].x = 200 + Rshape[i].x;
		shape[i].y = 200 + shape[i].y;
		Rshape[i].y = 200 + Rshape[i].y;
	}
	//输出结果
	for (int i = 0; i < 4; i++) {
		BresenhamLine(shape[i].x, shape[i].y, shape[i + 1].x, shape[i + 1].y);
		BresenhamLine(Rshape[i].x, Rshape[i].y, Rshape[i + 1].x, Rshape[i + 1].y);
	}
	BresenhamLine(shape[0].x, shape[0].y, shape[4].x, shape[4].y);
	BresenhamLine(Rshape[0].x, Rshape[0].y, Rshape[4].x, Rshape[4].y);
	glEnd();
	glFlush();
	*/
	Point a, b, c, d;
	a.x = 60 - 20 * sin(36 * 3.14 / 180); a.y = 60 - 20 * cos(36 * 3.14 / 180);
	b.x = 60; b.y = 80;
	c.x = 60 + 20 * sin(36 * 3.14 / 180); c.y = 60 - 20 * cos(36 * 3.14 / 180);
	d.x = 60 - 20 * cos(18 * 3.14 / 180); d.y = 60 + 20 * sin(18 * 3.14 / 180);

	Point shape[4] = { a,b,c,d };
	Point Rshape[4] = { 0 };
	Scaling2D(shape, 4, Rshape);
	Translation2D(Rshape, 4, intervalx, intervaly, Rshape);
	Rotation2D(Rshape, 4, _angle, Rshape);
	//到第一象限显示
	for (int i = 0; i < 4; i++) {
		shape[i].x = 200 + shape[i].x;
		Rshape[i].x = 200 + Rshape[i].x;
		shape[i].y = 200 + shape[i].y;
		Rshape[i].y = 200 + Rshape[i].y;
	}
	//输出结果
	for (int i = 0; i < 3; i++) {
		BresenhamLine(shape[i].x, shape[i].y, shape[i + 1].x, shape[i + 1].y);
		BresenhamLine(Rshape[i].x, Rshape[i].y, Rshape[i + 1].x, Rshape[i + 1].y);
	}
	BresenhamLine(shape[0].x, shape[0].y, shape[3].x, shape[3].y);
	BresenhamLine(Rshape[0].x, Rshape[0].y, Rshape[3].x, Rshape[3].y);
	glEnd();
	glFlush();
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	cout << "输入X轴与Y轴的缩放因子" << endl;
	cin >> deltax >> deltay;
	cout << "输入X轴与Y轴的坐标平移量" << endl;
	cin >> intervalx >> intervalx;
	cout << "输入旋转角度-360~360" << endl;
	cin >> _angle;

	glutInitWindowPosition(50, 100);
	glutInitWindowSize(500, 400);
	glutCreateWindow("二维几何变换算法");
	glClearColor(0.1, 0.5, 0.5, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutDisplayFunc(Transform2DSegment);
	glutMainLoop();
	return 0;
}
