#include<stdio.h>
#include<GL/glut.h>

typedef float point[3];

point v[4]={   {0.0, 0.0, 10.0},  {0.0, 10.0, -10.0},  {-10.0, -10.0, -10.0}, {10.0, -10.0, -10.0}   };
int n;

void triangle( point a, point b, point c) // display one triangle
{
            glBegin(GL_POLYGON);
                        glVertex3fv(a);
                        glVertex3fv(b);
                        glVertex3fv(c);
            glEnd();
}

void divide_triangle(point a, point b, point c, int m)   // triangle subdivision
{
            point p1, p2, p3;
            int i;
            if(m>0)
            {
                        for(i=0; i<3;i++)
                        {
                                    p1[i]=(a[i]+b[i])/2;
                                    p2[i]=(a[i]+c[i])/2;
                                    p3[i]=(b[i]+c[i])/2;
                        }
                        divide_triangle(a, p1, p2, m-1);
                        divide_triangle(c, p2, p3, m-1);
                        divide_triangle(b, p3, p1, m-1);
            }
            else
triangle(a,b,c);            
}

void tetrahedron( int m)       
{

            glColor3f(1.0,0.0,0.0);
            divide_triangle(v[0], v[1], v[2], m);
            glColor3f(0.0,1.0,0.0);
            divide_triangle(v[3], v[2], v[1], m);
            glColor3f(0.0,0.0,1.0);
            divide_triangle(v[0], v[3], v[1], m);
            glColor3f(0.0,0.0,0.0);
            divide_triangle(v[0], v[2], v[3], m);
}

void display()
{
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            tetrahedron(n);
            glFlush();
}

void myReshape(int w, int h)
{
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            if (w <= h)
            glOrtho(-12.0, 12.0, -12.0 * (GLfloat) h / (GLfloat) w, 12.0 * (GLfloat) h / (GLfloat) w, -12.0, 12.0);
            else
            glOrtho(-12.0 * (GLfloat) w / (GLfloat) h, 12.0 * (GLfloat) w / (GLfloat) h, -12.0, 12.0, -12.0, 12.0);
            glMatrixMode(GL_MODELVIEW);
            glutPostRedisplay();
}
 
void main(int argc, char **argv)
{
            printf(" No. of Divisions ? ");
            scanf("%d",&n);
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);  //  to view the behind triangle
            glutInitWindowSize(500, 500);
            glutCreateWindow("3D Gasket");
            glClearColor (1.0, 1.0, 1.0, 1.0);
            glutReshapeFunc(myReshape);
            glutDisplayFunc(display);
            glEnable(GL_DEPTH_TEST);
            glutMainLoop();
}
