#include <windows.h>
#include <GL/glut.h>

void initial(void)
{

    glClearColor (1.0, 1.0, 1.0, 0.0);
    glLineWidth(4.0);
GLfloat ControlP[4][3]={{-80.0,-40.0,0.0},{-10.0,90.0,0.0},
                     {10.0,-90.0,0.0},{80.0,40.0,0.0}};
    glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,*ControlP);//绘制Bezier曲线函数
    glEnable(GL_MAP1_VERTEX_3);//激活控制点的三维坐标

}

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

int main(void)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Bezier曲线");
    initial();
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}
