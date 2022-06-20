实验6
实验目的和实验内容：
验证二维几何变换，熟悉变换矩阵；（平移、比例、旋转、对称）

结果：
![Image text]()

关键代码：
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

总结：
设有一三角形ABC,其中三个顶点为A(5,10),B(1,2),C(8,5)，求对于直线-2x+3y+3=0的对称变换后的图形结果。

%-2x+3y+3=0

clear;

clc;

X1=[-1 10];

Y1=[-5/3 17/3];

plot(X1,Y1);

hold on;

x=atan(2/3);

X2=[5 1 8  5];

Y2=[10 2 5 10];

plot(X2,Y2,'b');

%用鼠标标出DABC

gtext('A(5,10)');

gtext('B(1,2)');

gtext('C(8,5)');

P=[5   10 1

   1   2  1

   8   5  1];

T=[cos(2*x)            sin(2*x)       0

   sin(2*x)            -cos(2*x)      0

   -(cos(2*x)-1)*3/2   -sin(2*x)*3/2  1];

 P1=P*T;

X3=[P1(1,1),P1(2,1),P1(3,1),P1(1,1)];

Y3=[P1(1,2),P1(2,2),P1(3,2),P1(1,2)];

plot(X3,Y3,'r');

%画X及Y轴

X4=[-2,14];

Y4=[0,0];

plot(X4,Y4,'m');

X4=[0,0];

Y4=[-2,12];

plot(X4,Y4,'m');

%用鼠标标志有关点

gtext('0(0,0)');

xlabel('X-轴');

ylabel('Y-轴');

gtext('A1(12.1,-0.6)');

gtext('B1(3.2,-1.2)');

gtext('C1(8.6,4.1)');

gtext('X');

gtext('Y');

gtext('-2x+3y+3=0');

axis equal;

T1=[1     0   0

    0     1   0

    -3/2  0   1];

T2=[cos(x)   -sin(x)   0
    sin(x)    cos(x)   
    0         0        1];
T3=[1   0   0
    0  -1   0
    0   0  1];
T4=[cos(x)    sin(x)    0
    -sin(x)    cos(x)   0
    0            0      1];
T5=[1     0   0
    0     1  0
    3/2   0  1];
T=T1*T2*T3*T4*T5;
P1=P*T;  
