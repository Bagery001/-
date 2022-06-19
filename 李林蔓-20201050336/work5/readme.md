实验5

1、实验内容：
圆扫描转换
种子点填充算法

2、实验目的：
输入多边形，种子点位置，填充多边形
输入圆的半径，画出圆。

圆扫描转换
结果:
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work5/%E5%AE%9E%E9%AA%8C5.1.jpg)

关键代码：
void BresenhamCircle(void)
{
    float d, x, y;
    glClear(GL_COLOR_BUFFER_BIT);
    x = 0;
    y = r;
    d = 1 - r;
    while (x <= y)
    {
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);//线的颜色为红色
        glVertex3f( x,  y, 0);
        glVertex3f( -x,  -y, 0);
        glVertex3f( -x,  y, 0);
        glVertex3f( x,  -y, 0);
        glVertex3f( y,  -x, 0);
        glVertex3f( -y,  -x, 0);
        glVertex3f( -y,  x, 0);
        glVertex3f( y,  x, 0);
        glEnd();
        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        glFlush();
    }
}

种子填充算法

结果：
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work5/%E5%AE%9E%E9%AA%8C5.2.jpg)

关键代码：
void setpixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}
//比较颜色是否相等
int compareColor(Color color1, Color color2) {
    if (color1[0] != color2[0] || color1[1] != color2[1] || color1[2] != color2[2]) { return 0; }
    else { return 1; }
}
void boundaryFill4(int x, int y, Color fillColor, Color boarderColor) {
    Color interiorColor;
    getpixel(x, y, interiorColor);
    if (compareColor(interiorColor, fillColor) == 0 && compareColor(interiorColor, boarderColor) == 0) {
        setpixel(x, y);
        boundaryFill4(x,y+1, fillColor, boarderColor);
        boundaryFill4(x,y-1, fillColor, boarderColor);
        boundaryFill4(x-1,y, fillColor, boarderColor);
        boundaryFill4(x+1,y, fillColor, boarderColor);
    }

}

