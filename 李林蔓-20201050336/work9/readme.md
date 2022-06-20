实验九

1、实验内容：
 教材P222，三维图形旋转、缩放变换、平移变换、错切变换、对称变换等任意变换。

2、实验目的：
 调用函数完成三维图形几何变换。

结果：
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work9/%E5%AE%9E%E9%AA%8C9.1.jpg)
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work9/%E5%AE%9E%E9%AA%8C9.2.jpg)
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work9/%E5%AE%9E%E9%AA%8C9.3.jpg)
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work9/%E5%AE%9E%E9%AA%8C9.4.jpg)

关键代码：
void Keyboard (unsigned char key, int x, int y)
{
    switch (key) {
       case 'd' : d[0] += 0.1; std::cout<<"sağ"<<std::endl; break;
       case 'w' : d[1] += 0.1; std::cout<<"yukarı"<<std::endl;  break;
       case 'e' : d[2] += 0.1; std::cout<<"yakınlaş"<<std::endl; break;
       case 's' : d[1] -= 0.1; std::cout<<"aşağı"<<std::endl; break;
       case 'a' : d[0] -= 0.1;  std::cout<<"sol"<<std::endl;break;
       case 'z' : d[2] -= 0.1; std::cout<<"uzaklaş"<<std::endl; break; break;

       case 'k' : xAngle += 5;  std::cout<<"X ekseninde döndür"<<std::endl; break; break;break;
       case 'l' : yAngle += 5; std::cout<<"Y ekseninde döndür"<<std::endl; break; break; break;
       case 'm' : zAngle += 5;  std::cout<<"Z ekseninde döndür"<<std::endl; break; break;break;
    }
    glutPostRedisplay();
}

void Triad (void)
{
    glColor3f (1.0, 1.0, 1.0);
    glBegin (GL_LINES);
       glVertex3fv (ORG); glVertex3fv (XUP);
       glVertex3fv (ORG); glVertex3fv (YUP);
       glVertex3fv (ORG); glVertex3fv (ZUP);
    glEnd ();
}

总结：
  三维图形变换分为：几何变换和投影变换。
    基本几何变换都是相对于坐标原点、坐标轴和坐标平面，包括：平移、缩放、旋转、对称和错切。
    三维空间中点的变换可以表示成点的齐次坐标与四阶的变换矩阵相乘。
    
