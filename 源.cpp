//Bresenham算法
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
	glutCreateWindow("代亨兰，Bresenham算法");
	glutDisplayFunc(display);
	Init();
	glutMainLoop();

}

//中点画线算法
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
	glutCreateWindow("代亨兰，中点画线算法");
	glutDisplayFunc(display);
	Init();
	glutMainLoop();
}


//DDA画线算法
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
	glutCreateWindow("代亨兰,DDA画线法");
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
	glClearColor(0.0, 0.0, 0.0, 0.0);  // 设置窗口为黑色
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 10.0, 0.0, 10.0);
}
void setPixel(int x, int y)//画点
{
	glColor3f(0.0, 0.0, 1.0);       // 蓝色
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}
void Cirpot(int x0, int y0, int x, int y)//8路对称
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

/*void MidPoint_Circle(int x0, int y0, int r)//中点画圆算法
{
	int x = 0;
	int y = r;
	int d = 1 - r;      // d = 1.25-r的取整的结果
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
void Bresenham_Circle(int x0, int y0, int r)//Bresenham画圆算法
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
void PN_Circle(int x0, int y0, int r)//正负画圆法
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
void DDA_Circle(int x0, int y0, int r)//角度DDA画圆算法
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

void DDAshuzhi_Circle(int x0, int y0, int r)//DDA画圆（数值微分法）
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
// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{

	if (h == 0)     h = 1;// 设置视区尺寸
	glViewport(0, 0, w, h);// 重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();// 建立修剪空间的范围
	if (w <= h)
		glOrtho(0.0f, 250.0f, 0.0f, 250.0f * h / w, 1.0, -1.0);
	else
		glOrtho(0.0f, 250.0f * w / h, 0.0f, 250.0f, 1.0, -1.0);

}
void display(void)
{
	// 用当前背景色填充窗口，如果不写这句会残留之前的图像
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
	//glutCreateWindow("代亨兰, MidCircle中点画圆法");
	//glutCreateWindow("代亨兰, Bresenham画圆法");
	//glutCreateWindow("代亨兰,正负画圆法");
	glutCreateWindow("代亨兰,角度DDA算法");
	//glutCreateWindow("代亨兰,DDA微分中值画圆算法");
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

/* 中点线绘制椭圆算法                                                     */
/************************************************************************/
using namespace std;
float wid = 400;         //设置窗口的大小,约定窗口必须为正方形
float height = wid;      //设置窗口的大小
int numbers = 20;       //设置划分的网格的个数
float t = wid / numbers; //模拟像素下的单位1
int index_y;                 //记录下斜率为-1时的y的位置
/*
 参数设置说明：
 您应当确保参数范围在-400～400.且为整数。
 由于使用的是模拟像素，应保持数据为单位模拟像素值的倍数。
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
	 函数说明：该函数为决策函数，每次判断下一个参考中点点在圆内还是园外
	 如果在圆内那么返回0，如果是园外那么选择1；
	 参数说明：传入坐标点。返回int判断值。
	 */
	float d = (x + t) * (x + t) / (a * a) + (y - 0.5 * t) * (y - 0.5 * t) / (b * b) - 1;
	if ((d) >= 0)
		return 1;
	else
		return 0;
}
int decision_fxy2(int x, int y) {
	/*
	 函数说明：该函数为决策函数2，每次判断下一个参考中点点在圆内还是园外
	 如果在圆内那么返回0，如果是园外那么选择1；
	 参数说明：传入坐标点。返回int判断值。
	 */
	float d = (y + t) * (y + t) / (b * b) + (x - 0.5 * t) * (x - 0.5 * t) / (a * a) - 1;
	if ((d) >= 0)
		return 1;
	else
		return 0;
}
void bresenham_oval(float r_x, float r_y) {
	/*
	 函数说明：bresenham画椭圆算法部分s
	 参数说明：传入圆的中心坐标点（openGL坐标下）和半径长度。为了保障模拟像素点和实际像素点的对应情况
	 我们将原来的单位1变为一个比例因子。比例因子= wid / numbers；
	 */
	int x, y;
	float h;
	x = 0;
	y = int(b);
	//事实上几乎无法避免使用浮点运算
	draw_point(translater(x), translater(y), r_x, r_y); //先绘制起点
	while (y > 0) {
		float k = -b * b * x / (a * a * y);
		cout << "斜率： " << k << endl;
		if (k <= -1) {
			//如果斜率在到达-1的情况：
			index_y = y;
			cout << "br4eak " << endl;
			break;
		}
		//因为我们选取的是45度～90度部分所以标准为x<y;
		if (decision_fxy(x, y) == 1) {
			//说明，因为下一个中点在圆外，选择下侧的点。
			y -= t;
			//当然两边同乘a方b方可以化简
		}
		else {
			//说明，下一个中点在圆内，说明应该选择上方的点。
		}
		x += t;
		//继续绘制点
		draw_point(translater(x), translater(y), r_x, r_y);
	}
	y = 0;
	x = a;
	cout << "斜率：：：：： -1" << endl;
	draw_point(translater(x), translater(y), r_x, r_y);
	while (y < index_y) {
		if (decision_fxy2(x, y) == 1) {
			x -= t;
			//当然两边同乘a方b方可以化简
		}
		y += t;
		draw_point(translater(x), translater(y), r_x, r_y);
		//继续绘制点
	}

}
float translater(int x) {
	/*
	 函数说明：将像素坐标下的坐标转化为openGL坐标
	 参数说明：传入点像素坐标-wid-wid，返回-1～1坐标
	 */
	return  x / wid;
}
void draw_point(float x, float y, float x1, float y1) {
	/*
	 函数说明：绘制像素的点，这里将点的大小设置为7。
	 颜色采用蓝色。利用圆八个部分的坐标对应关系进行绘图。
	 加x1与y1是为了进行圆的平移
	 参数说明：浮点数x，y是openGl坐标系。
	 */
	glPointSize(14);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3f(x + x1, y + y1, 0.0);
	glVertex3f(-x + x1, y + y1, 0.0);              //关于y轴对称
	glVertex3f(x + x1, -y + y1, 0.0);              //关于x轴对称
	glVertex3f(-x + x1, -y + y1, 0.0);            //关于原点对称
	glEnd();
	glFlush();
}
void grid() {
	/*
	 函数说明：绘制网格为了便于将真实的像素pixel转化为我们模拟的像素
	 */
	glClearColor(0, 0, 0, 0);//这是设置背景色,必须要在glclear之前调用
	glClear(GL_COLOR_BUFFER_BIT);
	int hei_number = numbers;
	float delta_hei = height / hei_number;
	glColor3f(1.0, 1.0, 0);
	for (int i = 1; i < 40; i++) { //利用循环绘制网格
		glBegin(GL_LINES);
		glVertex2f(-1 + i * delta_hei / height, -1);
		glVertex2f(-1 + i * delta_hei / height, 1);
		glVertex2f(-1, -1 + i * delta_hei / height);
		glVertex2f(1, -1 + i * delta_hei / height);
		glEnd();
		glFlush();
	}
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINES);          //绘制坐标系，便于观察
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(0, -1);
	glVertex2f(0, 1);
	glEnd();
	glFlush();
	//为了便于比较我们同时使用迭代法进行openGL绘制圆。
	real_circle();
	//刷新缓冲，保证绘图命令能被执行
	bresenham_oval(translater(x), translater(y));//进入bresenham算法
}
const int n = 120;
const GLfloat Pi = 3.1415926536f;
void real_circle()
{
	/*
	 函数说明：使用迭代进行画圆，精度用N来控制。
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
	//初始化GLUT library
	glutInit(&argc, argv);
	//对窗口的大小进行初始化
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(300, 200);
	// 设置窗口出现的位置
	//glutInitWindowPosition(int x, int y);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("class16_hw1_oval");
	glutDisplayFunc(&grid);
	glutMainLoop();
	return 0;
}
