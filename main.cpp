#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#define PI 3.14159265

class Point {
public:
  double x;
  double y;
  Point()
  {
    x = 0;
    y = 0;
  }
  Point(double tx, double ty)
  {
    x = tx;
    y = ty;
  }
  Point add(Point p)
  {
    Point t (x+p.x,y+p.y);
    return t;
  }
  Point sub(Point p)
  {
    Point t (x-p.x,y-p.y);
    return t;
  }
};

class Planet {
public:
  Point orbitCenter;
  Point position;
  double radius;
  double orbitRadius;
  Planet(double tx,double ty, double tr)
  {
    position.x = tx;
    position.y = ty;
    radius = tr;
  }
  Planet(double tx,double ty, double tr,double orx,double ory)
  {
    position.x = tx;
    position.y = ty;
    radius = tr;
    orbitCenter.x = orx;
    orbitCenter.y = ory;
  }
  
  void path(double deltaW)
  {
    Point t;
    t.x = orbitRadius*(cos(currentW()+deltaW));
    t.y = orbitRadius*(sin(currentW()+deltaW));
    position = t;
    
  }
  double currentW(){
    Point t = position.sub(orbitCenter);
    return atan2(t.y,t.x);
    
  }
};
class System {
  //vector<Planet> planets;
}; 
double toRad(double t)
{
  return t/180*PI;
}
double toDeg(double t)
{
  return t/PI*180;
}
void drawCircle(double radius, double ox, double oy)
{
  int a;
  glBegin(GL_POLYGON);
  for(a = 0; a < 360 ; a++)
    {
      glVertex2f(radius*(ox+cos(a)),radius*(oy+sin(a)));
    }
  glEnd();
}

void myDisplay(){

  Planet test (0,0,0.5);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0,0,0,1);
    
    glLoadIdentity();
    drawCircle(test.radius,test.position.x,test.position.y);
    glFlush();
}

int main(int argc, char* args[] )
{
    glutInit(&argc,args);
    glutInitWindowSize (600, 600);
    glutCreateWindow("bla");
    
    glutDisplayFunc(myDisplay);
    glutMainLoop();
}
