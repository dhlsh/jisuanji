#include <GL/glut.h>
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
