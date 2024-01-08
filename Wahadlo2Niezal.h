#ifndef WAHADLO2NIEZAL_H
#define WAHADLO2NIEZAL_H

#include "GL/glut.h"

#include <math.h>

#define PI 3.14

GLenum rgb, doubleBuffer=1, windType;
GLint windW, windH;

//#include "tkmap.c"

GLenum mode=0;

float point[2] = { 1.0, 1.0 };
float point2[2] = { 1.0, 1.0 };


double omega,teta,omega2,teta2,dt,g,r,r2,t;


static void Init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.4);

    glBlendFunc(GL_SRC_ALPHA, GL_ZERO);

    mode = GL_FALSE;


    /* Stałe */

    dt=0.001f;
    g=9.8f;
    r=0.9;
    r2=0.5;

/* Warunki początkowe rozwiązania numerycznego */

    t=0;
    omega=0.0f;
    teta=4.0f;					 // x

    omega2=0.0f;
    teta2=2.0f;				 // y



}

static void Reshape(int width, int height)
{

    windW = (GLint)width;
    windH = (GLint)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}


#define MOVEY 0.5


void RysujWektor(double x1, double y1, double x2, double y2, double scale)
{
    double kx,ky,kprimx,kprimy,vsize,ksize;

    // Wylicz długość wektora v i ustal długość wektora k

    vsize=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    ksize=vsize*scale/4.f;


    // Rysuj podstawę strzałki


    glBegin(GL_LINE_STRIP);

    //	glVertex2f(x1,y1);
    //	glVertex2f(((x2-x1)/vecsize),((y2-y1)/vecsize));

    glVertex2f(x1,y1);
    glVertex2f(x1+(x2-x1)*scale,y1+(y2-y1)*scale);

    glEnd();


    // wyznacz wektor jednostkowy skierowany naprzeciwko v

    kx=-(x2-x1)/vsize;
    ky=-(y2-y1)/vsize;

    // obróć k o 30 stopni

    kprimx=kx*cos(35*PI/180.f)+ky*sin(35*PI/180.f);
    kprimy=-kx*sin(35*PI/180.f)+ky*cos(35*PI/180.f);

    // wymnóż przez jego długość

    kprimx*=ksize;
    kprimy*=ksize;

    // rysuj kprim

    glBegin(GL_LINE_STRIP);

    glVertex2f(x1+(x2-x1)*scale,y1+(y2-y1)*scale);
    glVertex2f(x1+(x2-x1)*scale+kprimx,y1+(y2-y1)*scale+kprimy);

    glEnd();

    // obróć k o -30 stopni

    kprimx=kx*cos(-35*PI/180.f)+ky*sin(-35*PI/180.f);
    kprimy=-kx*sin(-35*PI/180.f)+ky*cos(-35*PI/180.f);

    // wymnóż przez jego długość

    kprimx*=ksize;
    kprimy*=ksize;

    // rysuj kprim

    glBegin(GL_LINE_STRIP);

    glVertex2f(x1+(x2-x1)*scale,y1+(y2-y1)*scale);
    glVertex2f(x1+(x2-x1)*scale+kprimx,y1+(y2-y1)*scale+kprimy);

    glEnd();

}



static void Draw(void)
{


    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);


    glColor3f(1.0,1.0,1.0);
    glLineWidth(1);


    glPointSize(14);

    glBegin(GL_POINTS);
    glVertex2f(point[0], point[1]+MOVEY);
    glEnd();

    glBegin(GL_POINTS);
    glVertex2f(point2[0], point2[1]+MOVEY);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0 + MOVEY);
    glVertex2f(point[0], point[1]+MOVEY);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0 + MOVEY);
    glVertex2f(point2[0], point2[1]+MOVEY);
    glEnd();


    glLineWidth(3);
    glColor3f(0.6,0.6,0.5);

    // vs
    RysujWektor(point[0],point[1]+MOVEY,r*sin(teta+omega*dt),r*cos(teta+omega*dt)+MOVEY,95.5f);
    RysujWektor(point2[0],point2[1]+MOVEY,r2*sin(teta2+omega2*dt),r2*cos(teta2+omega2*dt)+MOVEY,95.5f);

    glLineWidth(3);
    glColor3f(0.4,0.6,0.8);


    // g

    RysujWektor(point[0],point[1]+MOVEY,point[0],point[1]+MOVEY-0.3,1);
    RysujWektor(point2[0],point2[1]+MOVEY,point2[0],point2[1]+MOVEY-0.3,1);



    glFlush();

    if (doubleBuffer) {
        glutSwapBuffers();
    }
}


static GLenum Args(int argc, char **argv)
{
    rgb = GL_TRUE;
    doubleBuffer = GL_TRUE;

    return GL_TRUE;
}


void idle(void)
{
    t=t+dt;

    // m=1

    //   printf("%f     %f       %f      %f\n",t,((omega*omega)*(r*r)/2.f)*10,(9.8 + g*point[1])*10,( (omega*omega)*(r*r)/2.f + 9.8 + g*point[1])*10);


    //	printf("%f %f\n",teta,teta2);

    omega = omega + (g/r)*sin(teta)*dt;
    teta  = teta + omega * dt;

    omega2 = omega2 + (g/r2)*sin(teta2)*dt;
    teta2  = teta2 + omega2 * dt;

    point[0] = r*sin(teta);
    point[1] = r*cos(teta);

    point2[0] = r2*sin(teta2);
    point2[1] = r2*cos(teta2);


    glutPostRedisplay();
}


#endif // WAHADLO2NIEZAL_H
