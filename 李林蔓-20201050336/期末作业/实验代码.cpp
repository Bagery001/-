#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat planes[]= {-1.0, 0.0, 1.0, 0.0};
GLfloat planet[]= {0.0, -1.0,  0.0, 1.0};

	GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

	GLfloat colors[][4] = {{0.0,0.0,0.0,0.5},{1.0,0.0,0.0,0.5},
	{1.0,1.0,0.0,0.5}, {0.0,1.0,0.0,0.5}, {0.0,0.0,1.0,0.5},
	{1.0,0.0,1.0,0.5}, {1.0,1.0,1.0,0.5}, {0.0,1.0,1.0,0.5}};


typedef struct lightStruct
{
	GLfloat position[4];
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightStruct;//定义光源数据结构

lightStruct light=
{
	{10.0,1.0,0.0,1.0}, //灯光位置
	{0.0,0.0,0.0,1.0}, //环境光
	{3.0,2.0,0.0,1.0}, //漫反射光
	{0.0,0.0,0.0,1.0}, //镜面光
};

void setLight()
{
	glLightfv(GL_LIGHT0, GL_POSITION, light.position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void polygon(int a, int b, int c , int d)
{



 	glBegin(GL_POLYGON);
	/*	glColor4fv(colors[a]);*/
	/*	glTexCoord2f(0.0,0.0); */
		glVertex3fv(vertices[a]);
	/*	glColor4fv(colors[b]); */
	/*	glTexCoord2f(0.0,1.0); */
		glVertex3fv(vertices[b]);
	/*	glColor4fv(colors[c]); */
	/*	glTexCoord2f(1.0,1.0); */
		glVertex3fv(vertices[c]);
	/*	glColor4fv(colors[d]); */
	/*	glTexCoord2f(1.0,0.0); */
		glVertex3fv(vertices[d]);
	glEnd();
																										}

void colorcube(void)
{

/* map vertices to faces */

	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(0,4,7,3);
	polygon(1,2,6,5);
	polygon(4,5,6,7);
	polygon(0,1,5,4);
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;

void display(void)
{



	//清除显存
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	setLight();
	//以下代码用来控制旋转的方向
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

 /* colorcube();*/
	//以下代码用来控制茶壶大小
	glutSolidTeapot(1.0);
	//交换缓冲区
	glutSwapBuffers();
}

void spinCube()
{



	//控制旋转的角度和速度
	theta[axis] += 0.1;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	/* display(); */
	glutPostRedisplay();
}


//用来捕获鼠标点击的情况并给相应的角度控制变量赋值
void mouse(int btn, int state, int x, int y)
{



	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}



void myReshape(int w, int h)
{
	//控制显示图像在窗口中的大小
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}


//响应键盘点击事件，改变茶壶旋转方向
void key(char k, int x, int y)
{

	if(k == '1') axis = 0;
	if(k == '2') axis = 1;
	if(k == '3') axis = 2;

}

int main(int argc, char **argv)
{

   GLubyte image[64][64][3];
   int i, j, r, c;
   for(i=0;i<64;i++)
   {
     for(j=0;j<64;j++)
     {
       c = ((((i&0x8)==0)^((j&0x8))==0))*255;
       image[i][j][0]= (GLubyte) c;
       image[i][j][1]= (GLubyte) c;
       image[i][j][2]= (GLubyte) c;
     }
   }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("计算机科学与技术 李林蔓 20201050336");



   glutReshapeFunc(myReshape);
   glutDisplayFunc(display);
   glutIdleFunc(spinCube);
   glutMouseFunc(mouse);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_TEXTURE_2D);
   /*glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
   glTexGenfv(GL_S, GL_OBJECT_PLANE, planes);
   glEnable(GL_TEXTURE_GEN_S);
   glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
   glTexGenfv(GL_T, GL_OBJECT_PLANE, planet);
   glEnable(GL_TEXTURE_GEN_T);*/

   /* glPixelStorei(GL_UNPACK_ALIGNMENT,1); */
/*
 GlTexImage2D(Glenum target,Glint level,Glint internalformat,Glsizei width,Glsizei height,Glint border,Glenum format,Glenum type,const Glvoid *pixels)
targe 必须是GL_TEXTURE_2D。
level: 系统自动生成纹理 (MipMap:1,2)，当设置为0时，单分辨率纹理图像，设置为1时候，分辨率为原大小的1/2,必须大于等于0
internalformat:有效取值范围为 GL_ALPHA,GL_RGB,GL_RGBA,GL_LUMINANCE,GL_LUMINANCE_ALPHA. 这个值和format参数必须是一样的。
GL_ALPHA            (0, 0, 0, A)
GL_LUMINANCE            (1, 1, 1, 1)
GL_LUMINANCE_ALPHA        (1, 1, 1, A)
GL_RGB                (R, G, B, 1)
GL_RGBA                (R, G, B, A)
Width和Height必须是2的整数幂，如果有边界，则必须是2的整数幂+2。
Border为0代表无边框,1代表纹理有边框
format和internalformat一样。
Type: 此参数决定了pixel中的一个像素的比特组成，GL_UNSIGNED_BYTE为1位。此位通常为元像素(r+g+b)/3得出:
*/
   //此处显示的是马赛克的贴图

   glTexImage2D(GL_TEXTURE_2D,0,3,64,64,0,GL_RGB,GL_UNSIGNED_BYTE, image);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
 /*  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);*/
 /*  gluBuild2DMipmaps(GL_TEXTURE_2D,3,64,64,GL_RGB,GL_UNSIGNED_BYTE, image);*/
 /*  glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/



	//glutKeyboardFunc(key);
	glClearColor(1.0,0.5,1.0,1.0);
    glutMainLoop();

    return 0;
}
