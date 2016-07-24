#include <GL/glut.h> 

void init(void)

{

	glClearColor(0.0, 0.0, 0.0, 0.0);//设置背景颜色为黑色
	glShadeModel(GL_SMOOTH);//设置为光滑明暗模式

}


void myDisplay(void)

{

	glClear(GL_COLOR_BUFFER_BIT);// 将缓存清除为预先的设置值,即黑色

	glBegin(GL_TRIANGLES);//开始画三角形

	glColor3f(1.0, 0.0, 0.0);//设置第一个顶点为红色
	glVertex2f(-1.0, -1.0);//设置第一个顶点的坐标


	glColor3f(0.0, 1.0, 0.0);//设置第二个顶点为绿色
	glVertex2f(0.0, -1.0);//设置第二个顶点的坐标


	glColor3f(0.0, 0.0, 1.0);//设置第三个顶点为蓝色
	glVertex2f(-0.5, 1.0);//设置第三个顶点的坐标


	glEnd();//三角形结束

	glFlush();//强制OpenGL函数在有限时间内运行

}


void myReshape(GLsizei w, GLsizei h)

{

	glViewport(0, 0, w, h);//设置视口
	glMatrixMode(GL_PROJECTION);//指明当前矩阵为GL_PROJECTION
	glLoadIdentity();//将当前矩阵置换为单位阵

	if (w <= h)
		gluOrtho2D(-10, 15, -15, 15 * (GLfloat)h / (GLfloat)w);//定义二维正视投影矩阵
	else
		gluOrtho2D(-10, 15 * (GLfloat)w / (GLfloat)h, -15, 15);

	glMatrixMode(GL_MODELVIEW);//指明当前矩阵为GL_MODELVIEW

}


int main(int argc, char ** argv)

{

	/*初始化*/

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//单缓冲、RGB模式

	glutInitWindowSize(400, 400);

	glutInitWindowPosition(200, 200);

	glutCreateWindow("Demo");//窗口标题

	init();

	/*绘制与显示*/

	glutReshapeFunc(myReshape);//窗口大小发生改变时采取的行为

	glutDisplayFunc(myDisplay);//显示绘制图形

	glutMainLoop();//循环

	return(0);

}
