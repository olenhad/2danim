#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#define PI 3.14159265
using namespace std;
float alpha = 0.0, k=0.4;
float tx = 0.0, ty=0.0;


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
double toRad(double t)
{
  return t/180*PI;
}
double toDeg(double t)
{
  return t/PI*180;
}

double getDistance(Point x1,Point x2)
{
  return sqrt((x1.x-x2.x)*(x1.x-x2.x)+(x1.y-x2.y)*(x1.y-x2.y));
}

void drawCircle(double radius, double ox, double oy,GLfloat color[3])
{
  int a;
  //glPushMatrix();
  glTranslatef(ox,oy,0);
  glBegin(GL_POLYGON);
  glColor3f(color[0],color[1],color[2]);
  for(a = 0; a < 360 ; a++)
    {
      glVertex2f(radius*(cos(a)),radius*(sin(a)));
    }
  glEnd();
  //glPopMatrix();
}

class Planet {
public:
  Point orbitCenter;
  Point position;
  double radius;
  double orbitRadius;
  GLfloat color[3];
  double angularV;
  double angle;
  Planet* orbitPlanet;
  int moon;
  Planet(double tx,double ty, double tr)
  {
    position.x = tx;
    position.y = ty;
    radius = tr;
  }
  Planet(double tx,double ty, double tr,double orx,double ory,double dW,GLfloat r,GLfloat g, GLfloat b)
  {
    position.x = tx;
    position.y = ty;
    radius = tr;
    orbitCenter.x = orx;
    orbitCenter.y = ory;
    orbitRadius = getDistance(position,orbitCenter);
    angularV = toRad(dW);
    angle = 0;
    color[0] = r;
    color[1] = g;
    color[2] = b;
    orbitPlanet = NULL;
    moon = 0;
  }
  Planet(double orbitR,double tr, Planet* planetO,double dW,GLfloat r,GLfloat g, GLfloat b)
  {
    orbitRadius = orbitR;
    radius = tr;
    orbitPlanet = planetO;
    angularV = toRad(dW);
    moon = 1;
    angle = 0;
    color[0] = r;
    color[1] = g;
    color[2] = b;
    
  }
  
 
  void path()
  {
    Point t;
    if(moon==1){
      orbitCenter = orbitPlanet->position;
      angle = angle + angularV;
      position.x = orbitPlanet->position.x+orbitRadius*(cos(angle));
      position.y = orbitPlanet->position.y+orbitRadius*(sin(angle));
    }
    else {
      angle = angle+angularV;
      t.x = orbitCenter.x+orbitRadius*(cos(angle));
      t.y = orbitCenter.y+orbitRadius*(sin(angle));
      position = t;
      
    }
    //cout<<position.x<< " "<<position.y<<endl;
   
  }
  double currentW(){
    Point t = position.sub(orbitCenter);
    return atan2(t.y,t.x);
    
  }
  void drawPlanet(){
    drawCircle(radius,position.x,position.y,color);
  }
};
class Star {
public:
  Point position;
  double radius;
  GLfloat color[3];
  Star()
  {
    position.x = (rand()%100)-50;
    position.y = (rand()%100)-50;
    radius = (1.0*(rand()%1000))/5000;
    color[0] = (1.0*(rand()%255))/255;
    color[1] = (1.0*(rand()%255))/255;
    color[2] = (1.0*(rand()%255))/255;
  }
  void drawStar()
  {
    drawCircle(radius, position.x, position.y,color);
  }
  void updateStar()
  {
    color[0] = 1- color[0];
    color[1] = 1- color[1];
    color[2] = 1- color[2];
    
  }
};
class System {
public:
  vector<Planet> planets;
  vector<Star> stars;
  System()
  {
    //Sun
    Planet Sun (0,0,2,0,0,0.5,1,1,0);
    planets.push_back(Sun);
    //first -red
    planets.push_back(Planet(10,10,1.2,0,0,0.5,1,0,0));
    //planets.push_back(Planet(11,0.9,&planets[0],0.5,1,0,0));
    //first moon -redish blue
    planets.push_back(Planet(2,0.5,&planets[1],0.9,0,0,1));
    //second - green
    planets.push_back(Planet(9,0.8,&Sun,0.6,0,1,0));
    //second moon greenish blue
    planets.push_back(Planet(3,0.3,&Sun,0.9,0.3,0.9,0.5));
    planets.push_back(Planet(4,0.6,&planets[1],0.6,0,0.3,0.7));
    int i= 0;
    for(i=0;i<50;i++)
      {
      	stars.push_back(Star());
      }
  }
  void drawSystem()
  {
    int i =0;
    for(i = 0;i < planets.size();i++)
      {
	planets[i].drawPlanet();
      }
    for(i=0; i < stars.size();i++)
      {
	stars[i].drawStar();
      }
  }
  void updatePlanets()
  {
    int i = 0;
    for(i=0;i<planets.size();i++)
      {
	planets[i].path();
      }
    for(i=0;i<stars.size();i++)
      {
	stars[i].updateStar();
      }
  }
};
void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-10, 10, -10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Planet test (5,5,1,0,0,0.5);
//Planet test1 (0,0,1,10,5,0.5);
  Star testS;  
System solarSystem;
void keyboard (unsigned char key, int x, int y)
{
    //keys to control scaling - k
    //keys to control rotation - alpha
    //keys to control translation - tx, ty
    switch (key) {

	    case 'a':
		    alpha+=10;
		    glutPostRedisplay();
	    break;

	    case 'd':
		    alpha-=10;
		    glutPostRedisplay();
	    break;

	    case 'q':
		    k+=0.1;
		    glutPostRedisplay();
	    break;

	    case 'e':
		    if(k>0.1)
			    k-=0.1;
		    glutPostRedisplay();
	    break;

	    case 'z':
		    tx-=0.1;
		    glutPostRedisplay();
		    break;

	    case 'c':
		    tx+=0.1;
		    glutPostRedisplay();
	    break;

	    case 's':
		    ty-=0.1;
		    glutPostRedisplay();
	    break;

	    case 'w':
		    ty+=0.1;
		    glutPostRedisplay();
	    break;

	    default:
	    break;
    }
}

void display(){

  
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0,0,0,1);
    
    glLoadIdentity();
    glPushMatrix();
    glScalef(k,k,k);
    glTranslatef(tx,ty,0);
    glRotatef(alpha,0,0,1);
    
    //test.drawPlanet();
    //test1.drawPlanet();
    solarSystem.drawSystem();
    testS.drawStar();
    glPopMatrix();
    glFlush();
}
void idle()
{
  //test.path();
  //test1.path();
  testS.updateStar();
  solarSystem.updatePlanets();
  glutPostRedisplay();
  
}
int main(int argc, char* args[] )
{
      cout<<"CS3241 Lab 2\n\n";
    cout<<"+++++CONTROL BUTTONS+++++++\n\n";
    cout<<"Scale Up/Down: Q/E\n";
    cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
    cout<<"Move Up/Down: W/S\n";
    cout<<"Move Left/Right: Z/C\n";

    srand ( time(NULL) );

    glutInit(&argc,args);
    glutInitWindowSize (600, 600);
    
    glutInitWindowPosition (100, 100);
    
    glutCreateWindow("bla");
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
}
