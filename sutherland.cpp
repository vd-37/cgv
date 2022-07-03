#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#define outcode int
GLfloat xmin, ymin, xmax, ymax;
GLfloat xvmin, yvmin, xvmax, yvmax;
GLfloat x0, y0, x1, y1;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;
outcode ComputeOutCode(double x, double y);
void CohenSutherlandLineClipAndDraw()
{
    outcode outcode0, outcode1, outcodeOut;
    bool accept = false, done = false;
    outcode0 = ComputeOutCode(x0, y0);
    outcode1 = ComputeOutCode(x1, y1);
    do
    {
        if (!(outcode0 | outcode1))
        {
            accept = true;
            done = true;
        }
        else if (outcode0 & outcode1)
            done = true;
        else
        {

            double x, y;
            outcodeOut = outcode0 ? outcode0 : outcode1;

            if (outcodeOut & TOP)
            {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            }
            else if (outcodeOut & BOTTOM)
            {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            }
            else if (outcodeOut & RIGHT)
            {
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            }
            else
            {
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }
            if (outcodeOut == outcode0)
            {
                x0 = x;
                y0 = y;
                outcode0 = ComputeOutCode(x0, y0);
            }
            else
            {
                x1 = x;
                y1 = y;
                outcode1 = ComputeOutCode(x1, y1);
            }
        }
    } while (!done);
    if (accept)
    {
        double sx = (xvmax - xvmin) / (xmax - xmin);
        double sy = (yvmax - yvmin) / (ymax - ymin);
        double vx0 = xvmin + (x0 - xmin) * sx;
        double vy0 = yvmin + (y0 - ymin) * sy;
        double vx1 = xvmin + (x1 - xmin) * sx;
        double vy1 = yvmin + (y1 - ymin) * sy;
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin, yvmin);
        glVertex2f(xvmax, yvmin);
        glVertex2f(xvmax, yvmax);
        glVertex2f(xvmin, yvmax);
        glEnd();
        glFlush();
        glColor3f(0.0, 1.0, 0.0) glBegin(GL_LINES);
        glVertex2d(vx0, vy0);
        glVertex2d(vx1, vy1);
        glEnd();
        glFlush();
    }
}

outcode ComputeOutCode(double x, double y)
{
    outcode code = 0;
    if (y > ymax)
        code |= TOP;
    else if (y < ymin)
        code |= BOTTOM;
    if (x > xmax)
        code |= RIGHT;
    else if (x < xmin)
        code |= LEFT;
    return code;
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x0, y0);
    glVertex2d(x1, y1);
    glEnd();
    glFlush();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
    glFlush();
    CohenSutherlandLineClipAndDraw();
}
void myinit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1000.0, 1000.0, -1000.0, 1000.0);
}
int main(int argc, char **argv)
{
    printf("Enter xmin, ymin, xmax, ymax for the clipping window\n");
    scanf("%f%f%f%f", &xmin, &ymin, &xmax, &ymax);
    printf("Enter xmin, ymin, xmax, ymax for the viewport for the output display\n");
    scanf("%f%f%f%f", &xvmin, &yvmin, &xvmax, &yvmax);
    printf("Enter the points for the line\n");
    scanf("%f%f%f%f", &x0, &y0, &x1, &y1);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cohen Suderland Line Clipping Algorithm");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}