实验十

1、实验内容：
1） 使用opengl，片元着色器着色，P523
2）使用opengl，教材P541，颜色编码建模显示
2、实验目的：
1）验证片元着色器算法，获得着色结果。 
2）调用函数完成颜色编码建模实验。

结果：
片元着色器（课本代码，运行错误）
![Image text]([https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work10/%E5%AE%9E%E9%AA%8C10-2%E5%BB%BA%E6%A8%A1%E5%AE%9E%E9%AA%8C.jpg](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work10/%E5%AE%9E%E9%AA%8C10-1%E7%89%87%E5%85%83%E7%9D%80%E8%89%B2%E5%99%A8%E7%9D%80%E8%89%B2%E9%94%99%E8%AF%AF%E8%BF%90%E8%A1%8C.jpg))

建模实验（书中代码）
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work10/%E5%AE%9E%E9%AA%8C10-2%E5%BB%BA%E6%A8%A1%E5%AE%9E%E9%AA%8C.jpg)

关键代码：
片元着色器：
vec3 modNormal(vec2 point)
{
    vec2 d0=vec2(0, 0.001);
    vec2 d1=vec2(-0.000866,-0.0005);
    vec2 d2=vec2(0.000866,-0.0005);

    vec2 p0=point +d0;
    vec2 p1=point +d1;
    vec2 p3=point +d2;

    float h0=height(vec3(texture2D(textureID,p0)));
    float h1=height(vec3(texture2D(textureID,p1)));
    float h2=height(vec3(texture2D(textureID,p2)));

    vec3 v0=vec3(d0,h0);
    vec3 v1=vec3(d1,h0);
    vec3 v2=vec3(d2,h0);

    return normalize(vec3(cross(v1-v0,v2-v0)));
}

建模实验：
class complexNum
{
public:
    GLfloat x, y;
};
struct color
{
    GLfloat r, g, b;
};

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
void plotpoint(complexNum z)
{
    glBegin(GL_POINTS);
    glVertex2f(z.x, z.y);
    glEnd();
}
complexNum complexSquare(complexNum z)
{
    complexNum zSquare;

    zSquare.x = z.x * z.x - z.y * z.y;
    zSquare.y = 2 * z.x * z.y;
    return zSquare;
}
GLint mandelSqTransf(complexNum z0, GLint maxIter)
{
    complexNum z = z0;
    GLint count = 0;
    while ((z.x * z.x + z.y * z.y <= 4.0) && (count < maxIter))
    {
        z = complexSquare(z);
        z.x += z0.x;
        z.y += z0.y;
        count++;
    }
    return count;
}
void mandelbrot(GLint nx, GLint ny, GLint maxIter)
{

    complexNum z, zIncr;
    color ptColor;
    GLint iterCount;
    zIncr.x = complexWidth / GLfloat(nx);
    zIncr.y = complexHeight / GLfloat(ny);
    for (z.x = xComplexMin; z.x < xComplexMax; z.x += zIncr.x)
        for (z.y = yComplexMin; z.y < yComplexMax; z.y += zIncr.y)
        {
            iterCount = mandelSqTransf(z, maxIter);
            if (iterCount >= maxIter)
                ptColor.r = ptColor.g = ptColor.b = 0.0;
            else if (iterCount > (maxIter / 10))
            {
                ptColor.r = 1.0;
                ptColor.g = 0.5;
                ptColor.b = 0.0;
            }
            else if (iterCount > (maxIter / 10))
            {
                ptColor.r = 1.0;
                ptColor.g = ptColor.b = 0.0;
            }
            else if (iterCount > (maxIter / 20))
            {
                ptColor.b = 0.5;
                ptColor.r = ptColor.g = 0.0;
            }
            else if (iterCount > (maxIter / 100))
            {
                ptColor.r = ptColor.b = 0.0;
                ptColor.g = 0.3;
            }
            else
            {
                ptColor.r = 0.0;
                ptColor.g = ptColor.b = 1.0;
            }
            glColor3f(ptColor.r, ptColor.g, ptColor.b);
            plotpoint(z);
        }
}

总结：
● 片元着色器的作用是处理由光栅化阶段生成的每个片元，最终计算出每个像素的最终颜色。
● 和编写顶点着色器的过程相似。片段着色器只需要一个输出变量，这个变量是一个 4 分量向量，它表示的是最终的输出颜色
