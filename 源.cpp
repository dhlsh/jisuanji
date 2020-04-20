#include <GL/glut.h>
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
