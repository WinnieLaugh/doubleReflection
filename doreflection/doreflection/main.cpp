#define h0 0.001

#include <GL/glut.h> 
#include "vector.h"
#include "doureflection.h"

static GLfloat centerX = 0.0, centerY = 0.0, centerZ = 0.0;

void init(void)

{

	glClearColor(0.0, 0.0, 0.0, 0.0);//设置背景颜色为黑色
	glShadeModel(GL_SMOOTH);//设置为光滑明暗模式

}

vector X(int i){
	vector X;
	X.x = 10 * (0.6 + 0.3 * cos(7 * i*h0)) * cos(2 * i*h0);
	X.y = 10 * (0.6 + 0.3*cos(7 * i*h0))*sin(2 * i*h0);
	X.z = 10 * 0.3*sin(7 * i*h0);

	return X;
}

vector T(int i){
	vector t;
	t.x = -0.6 * cos(7 * i*h0) * sin(2 * i*h0) - 2.1 * sin(7 * i*h0) * cos(2 * i*h0) - 1.2*sin(2*i*h0);
	t.y = 1.2*cos(2*i*h0) + 0.6 * cos(7 * i*h0) * cos(2 * i*h0) - 2.1*sin(7 * i*h0)*sin(2 * i*h0);
	t.z = 2.1 * cos(7 * i*h0);

	return t;
}

void myDisplay(void)
{
	vector xii;
	vector ri, ti, si;
	vector Xi, Xi1, v1, riL, tiL, ti1, v2, ri1, si1;
	double c1, c2;

	Xi = X(0);
	ti = T(0);
	xii.x = -15.9 * cos(7 * 0 * h0) *cos(2 * 0 * h0) + 8.4 * sin(7 * 0 * h0) * sin(2 * 0 * h0) - 2.4 * cos(2 * 0 * h0);
	xii.y = -15.9 * cos(7 * 0 * h0) * sin(2 * 0 * h0) - 8.4 * sin(7 * 0 * h0) * cos(2 * 0 * h0) - 2.4* sin(2 * 0 * h0);
	xii.z = -14.7 * sin(7 * 0 * h0);

	si = ti * xii;
	si = si.nomalize();

	ti = ti.nomalize();
	ri = si * ti;

	ri = ri.nomalize();
	glClear(GL_COLOR_BUFFER_BIT);// 将缓存清除为预先的设置值,即黑色

	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < 2000; i++){


		Xi1 = X(i + 1);
		ti1 = T(i + 1);

		glBegin(GL_LINES);
		glLineWidth(3.0);
		glVertex3f(Xi.x, Xi.y, Xi.z);
		glVertex3f(Xi1.x, Xi1.y, Xi1.z);
		glEnd();

		if (i % 20 == 0){
			glBegin(GL_LINES);
			glLineWidth(2.0);
			glVertex3f(Xi.x, Xi.y, Xi.z);
			glVertex3f(Xi.x + (ri.x)/10, Xi.y + (ri.y)/10, Xi.x + (ri.z/10));
			glEnd();
		}
		
		v1 = Xi1 - Xi;
		c1 = v1.dot(v1);

		riL = ri - v1 * (2 / c1) * (v1.dot(ri));
		tiL = ti - v1 * (2 / c1) * (v1.dot(ri));
		v2 = ti1 - tiL;
		c2 = v2.dot(v2);
		ri1 = riL - v2 * (2 / c2) * (v2.dot(riL));
		si1 = ti1 * ri1;

		ti = ti1.nomalize();
		Xi = Xi1;
		ri = ri1.nomalize();
		si = si1;	

	}

	glutSwapBuffers();
	glFlush();//强制OpenGL函数在有限时间内运行

}

static double lookatx = 0.0, lookatz = 20.0, lookaty = 0.0;
static int scrw, scrh;

void passiveMotionFunc(int x, int y) {

	lookatx = -50.0 + (double)x / scrw * 100.0;
	lookatz = sqrt(2500 - lookatx * lookatx);

	lookaty = -50.0 + (double)y / scrh * 100;

	glLoadIdentity();
	gluLookAt(lookatx, lookaty, lookatz, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
	glutPostRedisplay();
}


void myReshape(GLsizei w, GLsizei h)
{
	scrw = (int)w;
	scrh = (int)h;
	glViewport(0, 0, w, h);//设置视口
	glMatrixMode(GL_PROJECTION);//指明当前矩阵为GL_PROJECTION
	glLoadIdentity();//将当前矩阵置换为单位阵

	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);//定义二维正视投影矩阵

	glMatrixMode(GL_MODELVIEW);//指明当前矩阵为GL_MODELVIEW
	
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 50.0, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
}


int main(int argc, char ** argv)

{
	/*初始化*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Demo");//窗口标题
	init();

	/*绘制与显示*/
	glutReshapeFunc(myReshape);//窗口大小发生改变时采取的行为
	glutDisplayFunc(myDisplay);//显示绘制图形
	glutPassiveMotionFunc(passiveMotionFunc);
	glutMainLoop();//循环
	return(0);

}
