#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

GLint xi, yi, xk, yk;
void plotpoint(GLint x, GLint y)
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void BresenhamlineDrawing()
{
	GLint pk;
	GLint dy = yk - yi;
	GLint dx = xk - xi;
	plotpoint(xi, yi);
	float m;
	if (xi != xk && yi != yk)
	{
		printf("nextpk\tnextxi\tnextyi\n");
		m = (float)dy / (float)dx;
		if (m > 0)
		{
			plotpoint(xi, yi);
			if (abs(m) <= 1)
			{
				pk = 2 * dy - dx;
				while (xi < xk)
				{
					if (pk <= 0)
					{
						pk = pk + 2 * dy;
						xi++;
						printf("%2d\t\t %2d\t\t %2d\n", pk, xi, yi);
						plotpoint(xi, yi);
					}
					if (pk > 0)
					{
						pk = pk + 2 * (dy - dx);
						xi++;
						yi++;
						printf("%2d\t\t %2d\t\t %2d\n", pk, xi, yi);
						plotpoint(xi, yi);
					}
				}
			}
			if (abs(m) > 1)
			{
				pk = dy - 2 * dx;
				while (yi < yk)
				{
					if (pk <= 0)
					{
						pk = pk + 2 * (dy - dx);
						xi++;
						yi++;
						printf("%3d\t%3d\t%3d\n", pk, xi, yi);
						plotpoint(xi, yi);
					}
					if (pk > 0)
					{
						pk = pk - 2 * dx;
						yi++;
						printf("%3d\t%3d\t%3d\n", pk, xi, yi);
						plotpoint(xi, yi);
					}
				}
			}
		}
		else if (m < 0)
		{
			plotpoint(xk, yk);
			if (abs(m) <= 1)
			{
				pk = -2 * dy - dx;
				while (xk > xi)
				{
					if (pk <= 0)
					{
						pk = pk + (-2 * dy);
						xk--;
						printf("%2d\t%2d\t%2d\n", pk, xk, yk);
						plotpoint(xk, yk);
					}
					if (pk > 0)
					{
						pk = pk + 2 * (-dy - dx);
						xk--;
						yk++;
						printf("%2d\t%2d\t%2d\n", pk, xk, yk);
						plotpoint(xk, yk);
					}
				}
			}
			if (abs(m) > 1)
			{
				pk = -dy - 2 * dx;
				while (yk < yi)
				{
					if (pk <= 0)
					{
						pk = pk + 2 * (-dy - dx);
						xk--;
						yk++;
						printf("%3d\t%3d\t%3d\n", pk, xk, yk);
						plotpoint(xk, yk);
					}
					if (pk > 0)
					{
						pk = pk + (-2 * dx);
						yk++;
						printf("%3d\t%3d\t%3d\n", pk, xk, yk);
						plotpoint(xk, yk);
					}
				}
			}
		}
	}
	else if (xi == xk)
	{
		while (yi < yk)
		{
			yi++;
			printf("nextxi\tnextyi\n");
			printf("%3d\t%3d\n", xi, yi);
			plotpoint(xi, yi);
		}
	}
	else if (yi == yk)
	{
		while (xi < xk)
		{
			xi++;
			printf("nextxi\tnextyi\n");
			printf("%3d\t%3d\n", xi, yi);
			plotpoint(xi, yi);
		}
	}
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	BresenhamlineDrawing();
	glFlush();
}
int main(int argc, char** argv)
{
	printf("Enter the values of x0,y0 and x1,y1\n");
	scanf("%d%d%d%d", &xi, &yi, &xk, &yk);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Bresenham Line Drawing Algorithm");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}