#include<gl\glut.h>
#include<iostream>
#include<cmath>
using namespace std;
// 中点线绘制椭圆算法                                                     
/***********************************************************************/
void  init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glOrtho(-10.0, 10.0, -10.0, 10.0, 0.1, -0.1);
}
void EllipsePoints(int CenterX, int CenterY, int x, int y)
{
    glVertex2i(x + CenterX, y + CenterY);
    glVertex2i(-x + CenterX, y + CenterY);
    glVertex2i(x + CenterX, -y + CenterY);
    glVertex2i(-x + CenterX, -y + CenterY);

}
void MidpointEllipse(int CenterX, int CenterY, int a, int b)
{
    double d2, d1 = pow(b, 2) - (pow(a, 2) * b) + 0.25 * pow(a, 2);
    double x = 0, y = b;
    EllipsePoints(CenterX, CenterY, x, y);
    //梯度检测
    while (pow(a, 2) * (y - 0.5) > pow(b, 2) * (x + 1))
    {
        //在区域一
        if (d1 < 0) //选择E点
        {
            d1 += pow(b, 2) * (2 * x + 3);
        }
        else          //选择SE点
        {
            d1 += pow(b, 2) * (2 * x + 3) + pow(a, 2) * (-2 * y + 2);
            y--;
        }
        x++;
        EllipsePoints(CenterX, CenterY, x, y);

    }
    d2 = pow(b, 2) * pow(x + 0.5, 2) + pow(a, 2) * pow(y - 1, 2) - pow(a * b, 2);
    while (y > 0)       //区域二
    {
        if (d2 < 0)       //选择SE点
        {
            d2 += pow(b, 2) * (2 * x + 2) + pow(a, 2) * (-2 * y + 3);
            x++;
        }
        else
        {
            d2 += pow(a, 2) * (-2 * y + 3);
        }
        y--;
        EllipsePoints(CenterX, CenterY, x, y);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    MidpointEllipse(0, 0, 6, 6);
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(300, 300);
    glutCreateWindow("代亨兰,椭圆画法");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}