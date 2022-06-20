实验十四

1、实验内容：
 生成曲线或者曲面，P323

2、实验目的：
熟悉Bezier、样条等相关内容

结果：
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work14/%E5%AE%9E%E9%AA%8C14.jpg)

关键代码：
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glMapGrid1f(100,0.0,1.0);//生成均匀分布的参数值，从0开始经过100步到1.0
    glEvalMesh1(GL_LINE, 0, 100);//从0到100个参数绘制Bezier曲线
    glFlush();
}

void Reshape(GLint newWidth, GLint newHeight)
{
    glViewport(0,0,newWidth,newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0,100.0,-100.0,100.0);
}

总结：
在OpenGL中，可以使用下面函数便捷地实现曲线和曲面的绘制：

（1）Bezier曲线绘制:

Void glMap1{fd}(Glenum target, TYPE t1, TYPE t2, Glint stride, Glint order, const TYPE *points);
             for（k=0;k<=50;k++）

                glEvalCoord1f(Glfloat(k)/100.0)

       glEnd();
生成一组均匀分布的参数值：

glMapGrid1{fd}(Glint n, TYPE t1, TYPE t2);//指定曲线步长

glEvalMesh1(Glenum mode,Glint n1,Glint n2);//绘制曲线

（2）Bezier曲面绘制:

Void glMap2{fd}(Glenum target, TYPE u1, TYPE u2, Glint ustride, Glint uorder, TYPE v1, TYPE v2, Glint vstride, Glint vorder, const TYPE *points); //求值函数

glEvalCoord2{fd}(TYPE u, TYPE v); //绘制曲面

生成曲面上的均匀间隔参数：

glMapGrid2{fd}(Glint nu, TYPE u1, TYPE u2, Glint nv, TYPE v1, TYPE v2);

glEvalMesh2(Glenum mode, Glint nu1,Glint nu2, Glint nv1,Glint nv2);

