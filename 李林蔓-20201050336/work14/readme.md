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
