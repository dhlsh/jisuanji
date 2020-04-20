#include<gl\glut.h>
#include<iostream>
#include<cmath>
using namespace std;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);  // ���ô���Ϊ��ɫ
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 10.0, 0.0, 10.0);
}
void setPixel(int x, int y)//����
{
	glColor3f(0.0, 0.0, 1.0);       // ��ɫ
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}
void Cirpot(int x0, int y0, int x, int y)//8·�Գ�
{
	setPixel((x0 + x), (y0 + y));//1
	setPixel((x0 + y), (y0 + x));//2
	setPixel((x0 + y), (y0 - x));//3
	setPixel((x0 + x), (y0 - y));//4
	setPixel((x0 - x), (y0 - y));//5
	setPixel((x0 - y), (y0 - x));//6
	setPixel((x0 - y), (y0 + x));//7
	setPixel((x0 - x), (y0 + y));//8
}

/*void MidPoint_Circle(int x0, int y0, int r)//�е㻭Բ�㷨
{
	int x = 0;
	int y = r;
	int d = 1 - r;      // d = 1.25-r��ȡ���Ľ��
	Cirpot(x0, y0, x, y);
	while (x < y)
	{
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
		Cirpot(x0, y0, x, y);
	}
}
void Bresenham_Circle(int x0, int y0, int r)//Bresenham��Բ�㷨
{
	int x = 0;
	int y = r;
	int d = 3 - 2 * r;
	Cirpot(x0, y0, x, y);
	while (x <= y)
	{
		if (d < 0)
		{
			d += 4 * x + 6;
		}
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}	
		x++;
		Cirpot(x0, y0, x, y);
	}
}
void PN_Circle(int x0, int y0, int r)//������Բ��
{
	int x = 0;
	int y = r;
	int f = 0;
	Cirpot(x0, y0, x, y);
	while (x <= y)
	{
		if (f <= 0)
		{
			f = f + 2 * x + 1;
			x++;
		}
		else
		{
			f = f - 2 * y + 1;
			y--;
		}
		Cirpot(x0, y0, x, y);
	}
}*/
void DDA_Circle(int x0, int y0, int r)//�Ƕ�DDA��Բ�㷨
{
	double k = 1 / (double)r;
	double x = r;
	double y = 0;
	int x_round, y_round;
	double pi = 3.1415927;
	double i;
	for (i = 0; i <= pi / 4;i+=k)
	{
		x_round = (int)(x + 0.5);
		y_round = (int)(y + 0.5);
		Cirpot(x0, y0, x, y);
		x += -sin(i);
		y += cos(i);
		Cirpot(x0, y0, x, y);
	}
}

/*void DDAshuzhi_Circle(int x0, int y0, int r)//DDA��Բ����ֵ΢�ַ���
{
	int x = 0;
	int y = r;
	int d = r;
	double x1 = (double)r;
	double z = 1.0 / x1;
	double a = x;
	double b = y;
	double tmp;
	while (d > 0)
	{
		Cirpot(x0, y0, x, y);
		tmp = a;
		a -= b * z;
		b += tmp * z;
		x = (int)a;
		y = (int)b;
		d--;
	}
	if(x==y)
		Cirpot(x0, y0, x, y);
}*/
// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{

	if (h == 0)     h = 1;// ���������ߴ�
	glViewport(0, 0, w, h);// ��������ϵͳ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();// �����޼��ռ�ķ�Χ
	if (w <= h)
		glOrtho(0.0f, 250.0f, 0.0f, 250.0f * h / w, 1.0, -1.0);
	else
		glOrtho(0.0f, 250.0f * w / h, 0.0f, 250.0f, 1.0, -1.0);

}
void display(void)
{
	// �õ�ǰ����ɫ��䴰�ڣ������д�������֮ǰ��ͼ��
	glClear(GL_COLOR_BUFFER_BIT);
	int x0 =100, y0 =100, r = 50;
	//MidPoint_Circle(x0, y0, r);
	//Bresenham_Circle(x0, y0, r);
	//PN_Circle(x0, y0, r);
	DDA_Circle(x0, y0, r);
	//DDAshuzhi_Circle(x0, y0, r);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	//glutCreateWindow("������, MidCircle�е㻭Բ��");
	//glutCreateWindow("������, Bresenham��Բ��");
	//glutCreateWindow("������,������Բ��");
	glutCreateWindow("������,�Ƕ�DDA�㷨");
	//glutCreateWindow("������,DDA΢����ֵ��Բ�㷨");
	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	init();
	glutMainLoop();
	return 0;
}

