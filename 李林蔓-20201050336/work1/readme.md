实验一
1、实验内容：
熟悉OPENGL，通过示例程序生成直线段

2、实验目的：
安装OPENGL，能编写代码运行，参考课本代码。
    
实验重点：
关键代码
void lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.4,0.2);
    glBegin(GL_LINES);
      glVertex2i(180,15);
      glVertex2i(10,145);
    glEnd();
    glFlush();
}
描述图形的函数lineSegment称为一个显示回调函数( display allback function)。 该函数由glutDisplayFunc作为在显示窗口需要重新显示时引人的函数来“注册”。例如，显示窗口移动时会出现这种情况。在后面几章中，我们将看到其他类型的回调函数及辅助的对它们注册的GLUT函数。图3.3由示例程序生成的显示窗口和线段 一般情况下，OpenGL程序组织成一组在一定行为发生时的回调函数的集合。

结果：
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work1/%E5%AE%9E%E9%AA%8C1.jpg)

总结：学习了利用OpenGL画出图形，虽然画出的图形比较简单和粗糙，之后希望可以更精致。
