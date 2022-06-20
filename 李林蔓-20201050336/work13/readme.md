实验十三

1、实验内容：
 生成多面体线框图，P300、P307
2、实验目的：
 熟悉三维线框图相关内容
 
 结果：
 ![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work13/%E5%AE%9E%E9%AA%8C13.1.jpg)
 ![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/work13/%E5%AE%9E%E9%AA%8C13.2.jpg)
 
 关键代码：
 课本P300页代码实现：线框多面体
 void displayWirPloyhedra(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    gluLookAt(5.0,5.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
    glScalef(1.5,2.0,1.0);
    glutWireCube(1.0);

    glScalef(0.8,0.5,0.8);
    glTranslatef(-6.0,-5.0,0.0);
    glutWireDodecahedron();

    glTranslatef(8.6,8.6,2.0);
    glutWireTetrahedron();

    glTranslatef(-3.0,-1.0,0.0);
    glutWireOctahedron();

    glScalef(0.8,0.8,1.0);
    glTranslatef(4.3,-2.0,0.5);
    glutWireIcosahedron();

    glFlush();
}
void winReshapeFcn(GLint newWidth,GLint newHeight)
{
    glViewport(0,0,newWidth,newHeight);
    glMatrixMode(GL_PROJECTION);
    glFrustum(-1.0,1.0,-1.0,1.0,2.0,20.0);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
}

课本P307页代码实现：线框二次曲面
void wireQuadSurfs(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);

    gluLookAt(2.0,2.0,2.0,0.0,0.0,0.0,0.0,0.0,1.0);

    glPushMatrix();
    glTranslatef(1.0,1.0,0.0);
    glutWireSphere(0.75,8,6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0,-0.5,0.5);
    glutWireCone(0.7,2.0,7,6);
    glPopMatrix();

    GLUquadricObj*cylinder;
    glPushMatrix();
    glTranslatef(0.0,1.2,0.8);
    cylinder=gluNewQuadric();
    gluQuadricDrawStyle(cylinder,GLU_LINE);
    gluCylinder(cylinder,0.6,0.6,1.5,6,4);
    glPopMatrix();

    glFlush();
}

void winReshapeFcn(GLint newWidth,GLint newHeight)
{
    glViewport(0,0,newWidth,newHeight);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-2.0,2.0,-2.0,2.0,0.0,5.0);

    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT);
}

总结：
幸运的是，某些标准的形体–五种规则多面体–由GLUT库中的子程序预先定义。这些多面体也称为柏拉图式实体，由它的每一面是一个单位规则多边形来标识。
GLUT中总共有10个函数用来生成这些实体
    glutWireTetrahedron();//规则三棱锥线框图
    glutSolidTetrahedron();//规则三棱锥实体图
    glutWireCube(1.0);//规则立方体线框图
    glutSolidCube(1.0);
    glutWireOctahedron();//规则八面体线框图
    glutSolidOctahedron();
    glutWireDodecahedron();//规则十二面体线框图
    glutSolidOctahedron();
    glutWireIcosahedron();//规则二十面体线框图
    glutSolidIcosahedron();
