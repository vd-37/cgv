#include<stdio.h>
#include<gl/glut.h>

int x, y;
int vFlag = 0;
float th = 0.0, trX = 0.0, trY = 0.0;

void draw_pixel(float x1, float y1) {
	glColor3f(0, 0, 1);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
}

void triangle() {
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(250, 400);
	glVertex2f(400, 100);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	if (vFlag == 1) {
		trX = 0.0;
		trY = 0.0;
		th += 0.1;
		draw_pixel(0.0, 0.0);
	}
	if(vFlag == 2) {
		trX = x;
		trY = y;
		th += 0.1;
		draw_pixel(x, y);
	}
	glTranslatef(trX, trY, 0.0);
	glRotatef(th, 0, 0, 1);
	glTranslatef(-trX, -trY, 0);

	triangle();
	glutPostRedisplay();
	glutSwapBuffers();
}

void rotateMenu(int op) {
	if (op == 1) vFlag = 1;
	if (op == 2) vFlag = 2;
	if (op == 3) vFlag = 3;
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -500, 500);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char** argv) {
	printf("Enter x and y: ");
	scanf_s("%d%d", &x, &y);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("rotate triangle");
	myInit();
	glutDisplayFunc(display);
	glutCreateMenu(rotateMenu);
	glutAddMenuEntry("ROTATE AT ORIGIN", 1);
	glutAddMenuEntry("ROTATE AT FIXED POINT", 2);
	glutAddMenuEntry("STOP", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}