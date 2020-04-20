//Bresenham�㷨
#include <gl/glut.h>
void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	gluOrtho2D(0.0, 10.0, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}
void Bresenhamline(int x0, int y0, int x1, int y1)
{
	int x, y, dx, dy, i;
	float k, e;
	dx = x1 - x0, dy = y1 - y0;
	e = -dx;
	x = x0, y = y0;
	glColor3f(0.1f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
	glVertex2f(x, y);
	for (i = 0; i <= dx; i++)
	{
		glVertex2f(x, y);
		x = x + 1;
		e = e + 2 * dy;
		if (e >= 0)
		{
			y++;
			e = e - 2 * dx;
		}
	}
	glEnd();
	glFlush();
}
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	Bresenhamline(1, 0, 10, 4);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("��������Bresenham�㷨");
	glutDisplayFunc(display);
	Init();
	glutMainLoop();

}

//�е㻭���㷨
#include <gl/glut.h>
void Init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0.0, 10.0, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}
void zhongdian(int x0, int y0, int x1, int y1)
{
	int a, b, d1, d2, d0, x, y, d;
	a = y1 - y0;
	b = x1 - x0;
	d0 = 2 * a + b;
	d1 = 2 * a;
	d2 = 2 * a + 2 * b;
	x = x0;
	y = y0;
	glColor3f(0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
	glVertex2f(x, y);
	while (x < x1)
	{
		if (d0 < 0)
		{
			x++;
			y--;
			d0 += d2;
		}
		else
		{
			x++;
			d0 += d1;
		}
		glVertex2f(x, y);
	}
	glEnd();
	glFlush();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	zhongdian(0, 5, 9, 0);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("���������е㻭���㷨");
	glutDisplayFunc(display);
	Init();
	glutMainLoop();
}


//DDA�����㷨
#include <gl/glut.h>
void  init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glOrtho(-10.0, 10.0, -10.0, 10.0, 0.1, -0.1);
}
void DDA(int x0, int y0, int x1, int y1)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int dx, dy, s, i;
	double x2, y2, x3, y3;
	dx = x1 - x0;
	dy = y1 - y0;
	x2 = x0;
	y2 = y0;
	glColor3f(0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
	glVertex2f(x2, y2 + 0.5);
	if (abs(dx) > abs(dy))
		s = abs(dx);
	else
		s = abs(dy);
	x3 = (double)dx / (double)s;
	y3 = (double)dy / (double)s;
	for (i = 0; i <= s; i++)
	{
		glVertex2f(x2, y2 + 0.5);
		x2 += x3;
		y2 += y3;
	}
	glEnd();
	glFlush();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	DDA(0, 5, 9, 0);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(300, 300);
	glutCreateWindow("������,DDA���߷�");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}




#include<gl\glut.h>
#include<iostream>
#include<cmath>
using namespace std;

/*void init(void)
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
}
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

void DDAshuzhi_Circle(int x0, int y0, int r)//DDA��Բ����ֵ΢�ַ���
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
}
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
}*/




#include <gl/glut.h>
#include<iostream>
#include<cmath>
using namespace std;

/* �е��߻�����Բ�㷨                                                     */
/************************************************************************/
using namespace std;
float wid = 400;         //���ô��ڵĴ�С,Լ�����ڱ���Ϊ������
float height = wid;      //���ô��ڵĴ�С
int numbers = 20;       //���û��ֵ�����ĸ���
float t = wid / numbers; //ģ�������µĵ�λ1
int index_y;                 //��¼��б��Ϊ-1ʱ��y��λ��
/*
 ��������˵����
 ��Ӧ��ȷ��������Χ��-400��400.��Ϊ������
 ����ʹ�õ���ģ�����أ�Ӧ��������Ϊ��λģ������ֵ�ı�����
 */
int x = 0;
int y = 0;
int a = 300;
int b = 200;
void draw_point(float x, float y, float x1, float y1);
float translater(int x);
void real_circle();
int decision_fxy(int x, int y) {
	/*
	 ����˵�����ú���Ϊ���ߺ�����ÿ���ж���һ���ο��е����Բ�ڻ���԰��
	 �����Բ����ô����0�������԰����ôѡ��1��
	 ����˵������������㡣����int�ж�ֵ��
	 */
	float d = (x + t) * (x + t) / (a * a) + (y - 0.5 * t) * (y - 0.5 * t) / (b * b) - 1;
	if ((d) >= 0)
		return 1;
	else
		return 0;
}
int decision_fxy2(int x, int y) {
	/*
	 ����˵�����ú���Ϊ���ߺ���2��ÿ���ж���һ���ο��е����Բ�ڻ���԰��
	 �����Բ����ô����0�������԰����ôѡ��1��
	 ����˵������������㡣����int�ж�ֵ��
	 */
	float d = (y + t) * (y + t) / (b * b) + (x - 0.5 * t) * (x - 0.5 * t) / (a * a) - 1;
	if ((d) >= 0)
		return 1;
	else
		return 0;
}
void bresenham_oval(float r_x, float r_y) {
	/*
	 ����˵����bresenham����Բ�㷨����s
	 ����˵��������Բ����������㣨openGL�����£��Ͱ뾶���ȡ�Ϊ�˱���ģ�����ص��ʵ�����ص�Ķ�Ӧ���
	 ���ǽ�ԭ���ĵ�λ1��Ϊһ���������ӡ���������= wid / numbers��
	 */
	int x, y;
	float h;
	x = 0;
	y = int(b);
	//��ʵ�ϼ����޷�����ʹ�ø�������
	draw_point(translater(x), translater(y), r_x, r_y); //�Ȼ������
	while (y > 0) {
		float k = -b * b * x / (a * a * y);
		cout << "б�ʣ� " << k << endl;
		if (k <= -1) {
			//���б���ڵ���-1�������
			index_y = y;
			cout << "br4eak " << endl;
			break;
		}
		//��Ϊ����ѡȡ����45�ȡ�90�Ȳ������Ա�׼Ϊx<y;
		if (decision_fxy(x, y) == 1) {
			//˵������Ϊ��һ���е���Բ�⣬ѡ���²�ĵ㡣
			y -= t;
			//��Ȼ����ͬ��a��b�����Ի���
		}
		else {
			//˵������һ���е���Բ�ڣ�˵��Ӧ��ѡ���Ϸ��ĵ㡣
		}
		x += t;
		//�������Ƶ�
		draw_point(translater(x), translater(y), r_x, r_y);
	}
	y = 0;
	x = a;
	cout << "б�ʣ��������� -1" << endl;
	draw_point(translater(x), translater(y), r_x, r_y);
	while (y < index_y) {
		if (decision_fxy2(x, y) == 1) {
			x -= t;
			//��Ȼ����ͬ��a��b�����Ի���
		}
		y += t;
		draw_point(translater(x), translater(y), r_x, r_y);
		//�������Ƶ�
	}

}
float translater(int x) {
	/*
	 ����˵���������������µ�����ת��ΪopenGL����
	 ����˵�����������������-wid-wid������-1��1����
	 */
	return  x / wid;
}
void draw_point(float x, float y, float x1, float y1) {
	/*
	 ����˵�����������صĵ㣬���ｫ��Ĵ�С����Ϊ7��
	 ��ɫ������ɫ������Բ�˸����ֵ������Ӧ��ϵ���л�ͼ��
	 ��x1��y1��Ϊ�˽���Բ��ƽ��
	 ����˵����������x��y��openGl����ϵ��
	 */
	glPointSize(14);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3f(x + x1, y + y1, 0.0);
	glVertex3f(-x + x1, y + y1, 0.0);              //����y��Գ�
	glVertex3f(x + x1, -y + y1, 0.0);              //����x��Գ�
	glVertex3f(-x + x1, -y + y1, 0.0);            //����ԭ��Գ�
	glEnd();
	glFlush();
}
void grid() {
	/*
	 ����˵������������Ϊ�˱��ڽ���ʵ������pixelת��Ϊ����ģ�������
	 */
	glClearColor(0, 0, 0, 0);//�������ñ���ɫ,����Ҫ��glclear֮ǰ����
	glClear(GL_COLOR_BUFFER_BIT);
	int hei_number = numbers;
	float delta_hei = height / hei_number;
	glColor3f(1.0, 1.0, 0);
	for (int i = 1; i < 40; i++) { //����ѭ����������
		glBegin(GL_LINES);
		glVertex2f(-1 + i * delta_hei / height, -1);
		glVertex2f(-1 + i * delta_hei / height, 1);
		glVertex2f(-1, -1 + i * delta_hei / height);
		glVertex2f(1, -1 + i * delta_hei / height);
		glEnd();
		glFlush();
	}
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINES);          //��������ϵ�����ڹ۲�
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(0, -1);
	glVertex2f(0, 1);
	glEnd();
	glFlush();
	//Ϊ�˱��ڱȽ�����ͬʱʹ�õ���������openGL����Բ��
	real_circle();
	//ˢ�»��壬��֤��ͼ�����ܱ�ִ��
	bresenham_oval(translater(x), translater(y));//����bresenham�㷨
}
const int n = 120;
const GLfloat Pi = 3.1415926536f;
void real_circle()
{
	/*
	 ����˵����ʹ�õ������л�Բ��������N�����ơ�
	 */
	glBegin(GL_TRIANGLE_FAN);
	int i;
	float P = 3.1415926;
	for (i = 1; i <= n; i++)
		glVertex2f(translater(a) * cos(2 * P / i * n), translater(b) * sin(2 * P / i * n));
	glEnd();
	glFlush();
}
int main(int argc, char* argv[]) {
	//��ʼ��GLUT library
	glutInit(&argc, argv);
	//�Դ��ڵĴ�С���г�ʼ��
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(300, 200);
	// ���ô��ڳ��ֵ�λ��
	//glutInitWindowPosition(int x, int y);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("class16_hw1_oval");
	glutDisplayFunc(&grid);
	glutMainLoop();
	return 0;
}
