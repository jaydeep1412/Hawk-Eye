//if #include <glut.h> does not work then replace it with #include <GL/glut.h>


#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

GLint FPS = 0;

void fps(void) {
  static GLint frameCounter = 0;         // frames averaged over 1000mS
  static GLuint currentClock;             // [milliSeconds]
  static GLuint previousClock = 0; // [milliSeconds]
  static GLuint nextClock = 0;     // [milliSeconds]

  ++frameCounter;
  currentClock = glutGet(GLUT_ELAPSED_TIME); //has limited resolution, so average over 1000mS
  if ( currentClock < nextClock ) return;

  FPS = frameCounter/1; // store the averaged number of frames per second

  previousClock = currentClock;
  nextClock = currentClock+1000; // set the next clock to aim for as 1 second in the future (1000 ms)
  frameCounter=0;
}

void pitch()
{
 glPushMatrix();
   glColor3f(1,1,1); glTranslated(0,-3,0); glScaled(12,1,9); glutSolidCube(1);
   glColor3f(0,0,0); glutWireCube(1);
   glPopMatrix();
}
void wickets()
{
    glPushMatrix();

    //wickets on right side
   glColor3f(0,0,1); glTranslated(5.8,-2.5,0); glScaled(0.1,1.3,9); glutSolidCube(1);
   glColor3f(0,0,0); glutWireCube(1);
   glPopMatrix();
   glPushMatrix();

   //wickets on left side

   glColor3f(0,0,1); glTranslated(-5.8,-2.5,0); glScaled(0.1,1.3,9); glutSolidCube(1);
   glColor3f(0,0,0); glutWireCube(1);
   glPopMatrix();
}

void boundary()
{
 glPushMatrix();
   glColor3f(1,1,1); glTranslated(0,3.5,0); glScaled(20,0.5,9); glutSolidCube(1);
   glColor3f(0,0,0); glutWireCube(1);
   glPopMatrix();
}


void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat r, GLfloat g, GLfloat b){
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	GLfloat twicePi = 6.29;
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
        glEnd();
}

void animateBall(GLfloat v, GLfloat r, GLfloat g, GLfloat b)
{
    GLfloat startY = -1.0;
    GLfloat startX = -5.8;
    GLfloat endX = 5.8;
    GLfloat endY = -3.0;
    GLfloat radius = 0.1;
    GLfloat x = -5.8;
    GLfloat y = -1.0;
    GLfloat t = 0;

    while(y > endY && x < endX){
        x = startX + v*t;
        y = startY - 0.5*10*t*t;
        drawFilledCircle(x,y,radius, r, g, b);
        t += 0.005;
        glutPostRedisplay();
        glutSwapBuffers();
    }
    GLfloat tMid = t;
    GLfloat vy = 20*g*t;
    while(x < endX){
        x = startX + v*t;
        y = endY + vy*(t - tMid) - 0.5*10*(t - tMid)*(t - tMid);
        drawFilledCircle(x,y,radius,r,g,b);
        t += 0.005;
        glutPostRedisplay();
        glutSwapBuffers();
    }
}


void background()
{
    glColor3f(0,1,0.372549);glRecti(-3,-2,3,1); //ground
  	glColor3f(0.22,0.69,0.87);glRecti(-3,1,3,2); //sky
  glPushMatrix();
   glTranslated(0,0,0);glScaled(0.3,0.3,0.1);pitch(); wickets(); boundary();
   drawFilledCircle(-5.8,-1.0,0.1, 1, 0.34, 0.2);

   animateBall(10.0, 1, 0.34, 0.2);animateBall(7.2,0.45, 0.77, 0.71);
   animateBall(12.0,0.35, 0.84, 0.55);animateBall(15, 0.65, 0.41, 0.74);
   animateBall(15.7, 0.09, 0.12, 0.16);animateBall(9.0, 0.95, 0.61, 0.07);

  glPopMatrix();

}

void idle() {
  static GLuint previousClock=glutGet(GLUT_ELAPSED_TIME);
  static GLuint currentClock=glutGet(GLUT_ELAPSED_TIME);
  static GLfloat deltaT;

  currentClock = glutGet(GLUT_ELAPSED_TIME);
  deltaT=currentClock-previousClock;
  if (deltaT < 35) {return;} else {previousClock=currentClock;}

  // put your idle code here, and it will run at the designated fps (or as close as the machine can get

  printf(".");
  //end your idle code here

  fps(); //only call once per frame loop

  glutPostRedisplay();
}

void renderScene (void)
{
   glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
   glOrtho (-3,3,-2,2,-4,4);  background();

}

int main(int argc,char** argv) {
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition (10,10);
glutInitWindowSize (1200,600);
glutCreateWindow("Cricket Pitch");
glutIdleFunc(idle);
glutDisplayFunc(renderScene);
glClearColor(1,1,1,1);
glutMainLoop();
return 0;
}
