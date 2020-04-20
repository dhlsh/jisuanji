
#include<gl\glut.h>
#include<iostream>
#include<cmath>
using namespace std;

void init(void)
{
	glClearColor(0.0, 0.0, 1.0, 1.0);  // 设置窗口为白色
}
void Ellipse_Bresenham(int a, int b, int xL, int yL)
{
	glPushMatrix();
	int x, y;
	float d1, d2, aa, bb;
	aa =(float)a * a;
	bb =(float) b * b;
	d1 = bb + aa * (-b + 0.25);
	glTranslatef((GLfloat)xL, (GLfloat)yL, 0.0f);
	glTranslatef((GLfloat)xL, (GLfloat)yL, 0.0f);
	x = 0;
	y = b;
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glVertex2i(-x, y);
	glVertex2i(-x, -y);
	glVertex2i(x, -y);
	while (bb * (x + 1) < aa * (y - 0.5))
	{
		if (d1 <= -0.000001)
		{
			d1 += bb * ((x << 1) + 3);

		}
		else
		{
			d1 += bb * ((x << 1) + 3) + aa * (2 - (y << 1));
			--y;
		}
		++x;
		glVertex2i(x, y);
		glVertex2i(-x, y);
		glVertex2i(-x, -y);
		glVertex2i(x, -y);
	}
	d2= bb* (0.25 * x) + aa* (1 - (y<< 1));
	while(y> 0)
	{
		if(d2<= -0.000001)
		{
			++x;
			d2+= bb* ((x+ 1) << 1) + aa* (3 - (y<< 1));
		}
		else
		{
			d2+= aa* (3 - (y<< 1));
		}
		--y;
		glVertex2i(x, y);
		glVertex2i(-x, y);
		glVertex2i(-x, -y);
		glVertex2i(x, -y);
	}
	glEnd();
	glPushMatrix();
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<= h)
	{
		gluOrtho2D(-600.0, 600.0, -600.0 * (GLfloat)h/ (GLfloat)w, 600.0 * (GLfloat)h/ (GLfloat)w);
	}
    else
    {
          gluOrtho2D(-600.0 * (GLfloat)w/ (GLfloat)h, 600.0 * (GLfloat)w/ (GLfloat)h, -600.0, 600.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display(void)
{
	// 用当前背景色填充窗口，如果不写这句会残留之前的图像
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	Ellipse_Bresenham(200, 300, 50, 50);
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(400, 400);
	glutCreateWindow("代亨兰，Bresenham椭圆");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
	return 0;
}
