#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <cmath>

/* Define the variables */
GLfloat theta[4] = {0.0, 0.0, 0.0, 0.0};
GLboolean circular = GL_FALSE; //switch circular motion
GLboolean swim = GL_TRUE;      //switch swim animation
GLboolean rotate = GL_FALSE;   //switch rotate animation
GLboolean sun = GL_FALSE;      //switch of the sun light
GLboolean spot = GL_FALSE;     //switch of the spot light
GLboolean spot1_on = GL_FALSE; //switch of the shpere
GLboolean spot2_on = GL_FALSE; //switch of the shpere
GLboolean both = GL_FALSE;     //switch of the both light
GLint u_direction = 1;
GLint l_direction = 1;
GLint h_direction = 1;
GLint menu_id = 0;
GLint menu2_id = 0;
GLint colorflag = 0;
GLint lightflag = 0;
GLint lightcolor = 0;
GLint button= 0;       // 0 is light open state
GLUquadricObj *p;   // pointer to quadric object


/* Define some type of materials */
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

materialStruct brassMaterials = {
   {0.33, 0.22, 0.03, 1.0},
   {0.78, 0.57, 0.11, 1.0},
   {0.99, 0.91, 0.81, 1.0},
   27.8
};

materialStruct redPlasticMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {0.6, 0.0, 0.0, 1.0},
   {0.8, 0.6, 0.6, 1.0},
   32.0
};

materialStruct whiteShinyMaterials = {
   {1.0, 1.0, 1.0, 1.0},
   {1.0, 1.0, 1.0, 1.0},
   {1.0, 1.0, 1.0, 1.0},
   100.0
};

materialStruct violetMaterials = {
   {0.83, 0.58, 0.97, 1.0},
   {0.95, 0.39, 0.95, 1.0},
   {0.33, 0.33, 0.52, 1.0},
   50.0
};

materialStruct lightyellowMaterials = {
   {0.33, 0.22, 0.03, 1.0},
   {0.97, 0.96, 0.58, 1.0},
   {0.99, 0.91, 0.81, 1.0},
   70.0
};

materialStruct obsidianMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {0.18, 0.17, 0.22, 0.82},
   {0.8, 0.6, 0.6, 1.0},
   85.0
};

materialStruct orangeMaterials = {
   {0.33, 0.22, 0.03, 1.0},
   {0.95, 0.47, 0.15, 1.0},
   {0.99, 0.91, 0.81, 1.0},
   85.0
};

materialStruct redorangeMaterials = {
   {0.33, 0.22, 0.03, 1.0},
   {0.967, 0.10, 0.02, 1.0},
   {0.99, 0.91, 0.81, 1.0},
   32.0
};

materialStruct brorangeMaterials = {
   {0.33, 0.22, 0.03, 1.0},
   {0.56, 0.15, 0.02, 1.0},
   {0.99, 0.91, 0.81, 1.0},
   22.0
};

materialStruct blueMaterials = {
   {0.83, 0.58, 0.97, 1.0},
   {0.05, 0.05, 0.84, 1.0},
   {0.33, 0.33, 0.52, 1.0},
   50.0
};

materialStruct pinkMaterials = {
   {0.175, 0.0118, 0.0118, 0.55},
   {0.95, 0.56, 0.67, 0.55},
   {0.728, 0.627, 0.627, 0.55},
    76.8
};

materialStruct redMaterials = {
   {0.175, 0.0118, 0.0118, 0.55},
   {0.9, 0.05, 0.26, 0.55},
   {0.728, 0.627, 0.627, 0.55},
    76.8
};

materialStruct rubyMaterials = {
   {0.175, 0.0118, 0.0118, 0.55},
   {0.814, 0.021, 0.21, 0.55},
   {0.728, 0.627, 0.627, 0.55},
   76.8
};

materialStruct meatMaterials = {
   {0.175, 0.0118, 0.0118, 0.55},
   {1.0, 0.34, 0.34, 0.55},
   {0.728, 0.627, 0.627, 0.55},
   76.8
};

materialStruct whitepinkMaterials = {
   {0.175, 0.0118, 0.0118, 0.55},
   {0.98, 0.62, 0.796, 0.55},
   {0.728, 0.627, 0.627, 0.55},
   76.8
};

materialStruct deepredMaterials = {
   {0.175, 0.0118, 0.0118, 0.55},
   {1.0, 0.0, 0.13, 0.55},
   {0.728, 0.627, 0.627, 0.55},
   76.8
};

materialStruct wineMaterials = {
   {0.175, 0.0118, 0.0118, 0.55},
   {0.47, 0.035, 0.35, 0.55},
   {0.728, 0.627, 0.627, 0.55},
   76.8
};

materialStruct wpinkMaterials = {
   {0.175, 0.0118, 0.0118, 0.55},
   {1.0, 0.34, 0.34, 0.55},
   {0.728, 0.627, 0.627, 0.55},
   76.8
};

materialStruct deepOrangeMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {1.0, 0.443, 0.047, 1.0},
   {0.8, 0.6, 0.6, 1.0},
   32.0
};

materialStruct deepYellowMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {0.96, 0.95, 0.047, 0.067},
   {0.8, 0.6, 0.6, 1.0},
   32.0
};

materialStruct bluishMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {0.584, 0.314, 0.99, 0.067},
   {0.8, 0.6, 0.6, 1.0},
   85.0
};

materialStruct purplishbuleMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {0.086, 0.24,0.73},
   {0.8, 0.6, 0.6, 1.0},
   85.0
};

materialStruct purplishMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {0.14, 0.33,0.957},
   {0.8, 0.6, 0.6, 1.0},
   85.0
};

materialStruct babyyellowMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {1.0, 1.0,0.337},
   {0.8, 0.6, 0.6, 1.0},
   85.0
};

materialStruct babyblueMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {0.8, 0.976,0.976},
   {0.8, 0.6, 0.6, 1.0},
   85.0
};

materialStruct deepblueMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {0.14, 0.149,0.176},
   {0.8, 0.6, 0.6, 1.0},
   85.0
};

materialStruct byellowMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {0.98, 0.98,0.075},
   {0.8, 0.6, 0.6, 1.0},
   85.0
};

materialStruct fblueMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {0.11, 0.05,0.64},
   {0.8, 0.6, 0.6, 1.0},
   85.0
};

materialStruct tyellowMaterials = {
   {0.3, 0.0, 0.0, 1.0},
   {1.0, 1.0,0.0},
   {0.8, 0.6, 0.6, 1.0},
   85.0
};
/* define some type of light */
typedef struct lightingStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
} lightingStruct;

lightingStruct whiteLighting = {
   {0.0, 0.0, 0.0, 1.0},
   {1.0, 1.0, 1.0, 1.0},
   {1.0, 1.0, 1.0, 1.0}
};

lightingStruct coloredLighting = {
   {0.0, 0.0, 0.0, 1.0},
   {1.0, 1.0, 1.0, 1.0},
   {0.0, 0.0, 0.0, 1.0}
};

lightingStruct greenLighting = {
   {0.0, 0.0, 0.0, 1.0},
   {0.0, 1.0, 0.0, 1.0},
   {0.0, 1.0, 0.0, 1.0}
};

lightingStruct magentaLighting = {
   {0.0, 0.0, 0.0, 1.0},
   {1.0, 0.0, 1.0, 1.0},
   {1.0, 0.0, 1.0, 1.0}
};

/* The pointer of the material and light to every part of fish */
materialStruct *bodyMaterials;
lightingStruct *bodyLighting;
materialStruct *headMaterials;
lightingStruct *headLighting;
materialStruct *eyeMaterials;
lightingStruct *eyeLighting;
materialStruct *eyeballMaterials;
lightingStruct *eyeballLighting;
materialStruct *wingMaterials;
lightingStruct *wingLighting;
materialStruct *tailMaterials;
lightingStruct *tailLighting;
materialStruct *mouthMaterials;
lightingStruct *sunLighting;
lightingStruct *spotLighting;

/* Draw the body of red rose fish */
void redbody()
{
  headMaterials = &pinkMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,headMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, headMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, headMaterials-> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &headMaterials -> shininess);

   glPushMatrix();
   glColor3ub(241,184,242);
   glRotatef (-90.0, 1.0, 0.0, 0.0);
   gluSphere (p, 1.5, 15, 15);
   glPopMatrix();

   bodyMaterials = &redMaterials;
   glMaterialfv(GL_FRONT, GL_AMBIENT,bodyMaterials -> ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyMaterials -> diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, bodyMaterials -> specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &bodyMaterials -> shininess);

   glPushMatrix();
   glColor3ub(235,147,237);
   glRotatef (-90.0, 1.0, 0.0, 0.0);
   glTranslatef(0.0,0.4,0.0);
   gluSphere (p, 1.7, 15, 15);
   glPopMatrix();

    bodyMaterials = &rubyMaterials;
   glMaterialfv(GL_FRONT, GL_AMBIENT,bodyMaterials -> ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyMaterials -> diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, bodyMaterials -> specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &bodyMaterials -> shininess);
   glPushMatrix();
   glColor3ub(211,70,214);
   glRotatef (-90.0, 1.0, 0.0, 0.0);
   glTranslatef(0.0,0.8,0.0);
   gluSphere (p, 1.8, 15, 15);
   glPopMatrix();


}
/* Draw the mouth of red rose fish */
void redmouth()
{
   mouthMaterials = &meatMaterials;
   glMaterialfv(GL_FRONT, GL_AMBIENT,bodyMaterials -> ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyMaterials -> diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, bodyMaterials -> specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, &bodyMaterials -> shininess);
  glPushMatrix();
  glColor3ub(255,170,170);
  glTranslatef(0,0,1.5);
  glScalef(1.0,0.9,0.0);
  gluDisk(p,0.1,0.35,15,15);
  glPopMatrix();
}
/* Draw the eye of red rose fish in one side */
void redeye()
{
  eyeMaterials = &whitepinkMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeMaterials -> shininess);

  eyeLighting = &whiteLighting;
  glLightfv(GL_LIGHT0, GL_AMBIENT, eyeLighting -> ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, eyeLighting -> diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, eyeLighting -> specular);

  glPushMatrix();
  glColor3ub(242,232,142);
  glTranslatef(1.0,0.6,0.6);
  glScalef(0.8, 1.0, 0.8);
  gluSphere(p,0.5,15,15);
  glPopMatrix();

  eyeballMaterials = &obsidianMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeballMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeballMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeballMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeballMaterials -> shininess);

  glPushMatrix();
  glTranslatef(1.25,0.7,0.6);
  glScalef(0.3, 0.4, 0.3);
  glColor3f (0.0, 0.0, 0.0);
  gluSphere(p,0.7,15,15);
  glPopMatrix();

}
/* Draw the eye of red rose fish in another side*/
void redeye2()
{
  eyeMaterials = &whitepinkMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeMaterials -> shininess);

  glPushMatrix();
  glColor3ub(242,232,142);
  glTranslatef(-1.0,0.6,0.6);
  glScalef(0.8, 1.0, 0.8);
  gluSphere(p,0.5,15,15);
  glPopMatrix();

  eyeballMaterials = &obsidianMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeballMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeballMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeballMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeballMaterials -> shininess);


  glPushMatrix();
  glTranslatef(-1.25,0.7,0.6);
  glScalef(0.3, 0.4, 0.3);
  glColor3f (0.0, 0.0, 0.0);
  gluSphere(p,0.7,15,15);
  glPopMatrix();
}
/* Draw the tail of red rose fish */
void redtail()
{
  tailMaterials = &deepredMaterials;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,tailMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tailMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tailMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &tailMaterials -> shininess);

  glPushMatrix();
  glColor3ub(211,70,214);
  glTranslatef(0.0,0.0,-1.0);
  glScalef(0.8,0.8,0.8);
  glRotatef(180, 0.0, 1.0, 0.0);
  glRotatef(theta[1],0.0,1.0,0.0);
  gluCylinder(p,0.8,1.6,3.2,15,15);
  glPopMatrix();
 }
/* Draw the fins of red rose fish */
void redfins()
{
   wingMaterials = &wineMaterials;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,wingMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wingMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wingMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &wingMaterials -> shininess);

  glPushMatrix();
  glColor3ub(239,221,62);
  glTranslatef(0.0,0.0,-2.0);
  glScalef(0.8,0.8,0.8);
  glRotatef(270, 0.0, 1.0, 0.0);
  gluPartialDisk(p,0.0,3.5,15,15,0,180);
  glPopMatrix();
}
/* Draw the wing of red rose fish in one side */
void redwing1()
{
  wingMaterials = &wpinkMaterials;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,wingMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wingMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wingMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &wingMaterials -> shininess);

   glPushMatrix();
   glColor3ub(247,139,71);
   glTranslatef(1.0,0.6,-0.6);
   glScalef(0.8,0.8,0.8);
   glRotatef(0.0, 0.0, 0.0, 1.0);
   glRotatef(theta[1],0.0,1.0,0.0);
   gluPartialDisk(p,0.0,2.0,15,15,60,70);
   glPopMatrix();
}
/* Draw the wing of red rose fish in another side*/
void redwing2()
{
 wingMaterials = &wpinkMaterials;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,wingMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wingMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wingMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &wingMaterials -> shininess);

   glPushMatrix();
   glColor3ub(247,139,71);
   glTranslatef(1.0,0.6,-0.6);
   glScalef(0.8,0.8,0.8);
   glRotatef(0.0, 0.0, 0.0, 1.0);
   glRotatef(-theta[1],0.0,1.0,0.0);
   gluPartialDisk(p,0.0,2.0,15,15,60,70);
   glPopMatrix();
}
/* Draw the body of clownfish */
void clownbody()
{
  headMaterials = &deepOrangeMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,headMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, headMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, headMaterials-> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &headMaterials -> shininess);

   glPushMatrix();
   glColor3ub(241,184,242);
   glRotatef (-90.0, 1.0, 0.0, 0.0);
   gluSphere (p, 1.5, 15, 15);
   glPopMatrix();

   bodyMaterials = &obsidianMaterials;
   glMaterialfv(GL_FRONT, GL_AMBIENT,bodyMaterials -> ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyMaterials -> diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, bodyMaterials -> specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &bodyMaterials -> shininess);

   glPushMatrix();
   glColor3ub(235,147,237);
   glRotatef (-90.0, 1.0, 0.0, 0.0);
   glTranslatef(0.0,0.4,0.0);
   gluSphere (p, 1.7, 15, 15);
   glPopMatrix();


   bodyMaterials = &deepOrangeMaterials;
   glMaterialfv(GL_FRONT, GL_AMBIENT,bodyMaterials -> ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyMaterials -> diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, bodyMaterials -> specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &bodyMaterials -> shininess);

   glPushMatrix();
   glColor3ub(211,70,214);
   glRotatef (-90.0, 1.0, 0.0, 0.0);
   glTranslatef(0.0,0.8,0.0);
   gluSphere (p, 1.8, 15, 15);
   glPopMatrix();
}
/* Draw the mouth of clownfish */
void clownmouth()
{
   mouthMaterials = &redPlasticMaterials;
   glMaterialfv(GL_FRONT, GL_AMBIENT,bodyMaterials -> ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyMaterials -> diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, bodyMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &bodyMaterials -> shininess);
  glPushMatrix();
  glColor3ub(255,170,170);
  glTranslatef(0.0,0.0,1.5);
  glScalef(1.0,0.9,0.0);
  gluCylinder(p,0.1,0.35,0.5,15,15);
  glPopMatrix();
}
/* Draw the eye of clownfish in one side*/
void clowneye()
{
  eyeMaterials = &lightyellowMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeMaterials -> shininess);

  glPushMatrix();
  glColor3ub(242,232,142);
  glTranslatef(1.0,0.6,0.6);
  glScalef(0.8, 1.0, 0.8);
  gluSphere(p,0.5,15,15);
  glPopMatrix();

  eyeballMaterials = &obsidianMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeballMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeballMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeballMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeballMaterials -> shininess);


  glPushMatrix();
  glTranslatef(1.25,0.7,0.6);
  glScalef(0.3, 0.4, 0.3);
  glColor3f (0.0, 0.0, 0.0);
  gluSphere(p,0.7,15,15);
  glPopMatrix();

}
/* Draw the eye of clownfish in another fish */
void clowneye2()
{
  eyeMaterials = &lightyellowMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeMaterials -> shininess);

  glPushMatrix();
  glColor3ub(242,232,142);
  glTranslatef(-1.0,0.6,0.6);
  glScalef(0.8, 1.0, 0.8);
  gluSphere(p,0.5,15,15);
  glPopMatrix();

  eyeballMaterials = &obsidianMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeballMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeballMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeballMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeballMaterials -> shininess);

  glPushMatrix();
  glTranslatef(-1.25,0.7,0.6);
  glScalef(0.3, 0.4, 0.3);
  glColor3f (0.0, 0.0, 0.0);
  gluSphere(p,0.7,15,15);
  glPopMatrix();
}
/* Draw the tail of clownfish */
void clowntail()
{
  tailMaterials = &brorangeMaterials;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,tailMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tailMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tailMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &tailMaterials -> shininess);

  glPushMatrix();
  glColor3ub(211,70,214);
  glTranslatef(0.0,0.0,-1.0);
  glScalef(0.8,0.8,0.8);
  glRotatef(180, 0.0, 1.0, 0.0);
  glRotatef(theta[1],0.0,1.0,0.0);
  gluCylinder(p,0.8,1.6,3.2,15,15);
  glPopMatrix();
 }
/* Draw the fins of clownfish */
void clownfins()
{
   wingMaterials = &deepYellowMaterials ;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,wingMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wingMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wingMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &wingMaterials -> shininess);

  glPushMatrix();
  glColor3ub(239,221,62);
  glTranslatef(0.0,0.0,-2.0);
  glScalef(0.8,0.8,0.8);
  glRotatef(270, 0.0, 1.0, 0.0);
  gluPartialDisk(p,0.0,3.5,15,15,0,180);
  glPopMatrix();
}
/* Draw the wing of clownfish in one side */
void clownwing1()
{
  wingMaterials = &redorangeMaterials;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,wingMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wingMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wingMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &wingMaterials -> shininess);

   glPushMatrix();
   glColor3ub(247,139,71);
   glTranslatef(1.0,0.6,-0.6);
   glScalef(0.8,0.8,0.8);
   glRotatef(0.0, 0.0, 0.0, 1.0);
   glRotatef(theta[1],0.0,1.0,0.0);
   gluPartialDisk(p,0.0,2.0,15,15,60,70);
   glPopMatrix();
}
/* Draw the wing of clownfish in another side*/
void clownwing2()
{
 wingMaterials = &redorangeMaterials;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,wingMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wingMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wingMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &wingMaterials -> shininess);

   glPushMatrix();
   glColor3ub(247,139,71);
   glTranslatef(1.0,0.6,-0.6);
   glScalef(0.8,0.8,0.8);
   glRotatef(0.0, 0.0, 0.0, 1.0);
   glRotatef(-theta[1],0.0,1.0,0.0);
   gluPartialDisk(p,0.0,2.0,15,15,60,70);
   glPopMatrix();
}
/* Draw the body of blue crane fish */
void bluebody()
{
  headMaterials = &bluishMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,headMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, headMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, headMaterials-> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &headMaterials -> shininess);


   glPushMatrix();
   glColor3ub(241,184,242);
   glRotatef (-90.0, 1.0, 0.0, 0.0);
   gluSphere (p, 1.5, 15, 15);
   glPopMatrix();

   bodyMaterials = &purplishbuleMaterials;
   glMaterialfv(GL_FRONT, GL_AMBIENT,bodyMaterials -> ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyMaterials -> diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, bodyMaterials -> specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &bodyMaterials -> shininess);

   glPushMatrix();
   glColor3ub(235,147,237);
   glRotatef (-90.0, 1.0, 0.0, 0.0);
   glTranslatef(0.0,0.4,0.0);
   gluSphere (p, 1.7, 15, 15);
   glPopMatrix();


   bodyMaterials = &purplishMaterials;
   glMaterialfv(GL_FRONT, GL_AMBIENT,bodyMaterials -> ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyMaterials -> diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, bodyMaterials -> specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &bodyMaterials -> shininess);

   glPushMatrix();
   glColor3ub(211,70,214);
   glRotatef (-90.0, 1.0, 0.0, 0.0);
   glTranslatef(0.0,0.8,0.0);
   gluSphere (p, 1.8, 15, 15);
   glPopMatrix();
}
/* Draw the mouth of blue crane fish */
void bluemouth()
{
   mouthMaterials = &babyyellowMaterials;
   glMaterialfv(GL_FRONT, GL_AMBIENT,bodyMaterials -> ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyMaterials -> diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, bodyMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &bodyMaterials -> shininess);
  glPushMatrix();
  glColor3ub(255,170,170);
  glTranslatef(0.0,0.0,1.5);
  glScalef(1.0,0.9,0.0);
  gluCylinder(p,0.1,0.35,0.5,15,15);
  glPopMatrix();
}
/* Draw the eye of blue crane fish in one side*/
void blueeye()
{
  eyeMaterials = &babyblueMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeMaterials -> shininess);

  glPushMatrix();
  glColor3ub(242,232,142);
  glTranslatef(1.0,0.6,0.6);
  glScalef(0.8, 1.0, 0.8);
  gluSphere(p,0.5,15,15);
  glPopMatrix();

  eyeballMaterials = &deepblueMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeballMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeballMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeballMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeballMaterials -> shininess);


  glPushMatrix();
  glTranslatef(1.25,0.7,0.6);
  glScalef(0.3, 0.4, 0.3);
  glColor3f (0.0, 0.0, 0.0);
  gluSphere(p,0.7,15,15);
  glPopMatrix();

}
/* Draw the eye of blue crane fish in another side */
void blueeye2()
{
  eyeMaterials = &babyblueMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeMaterials -> shininess);


  glPushMatrix();
  glColor3ub(242,232,142);
  glTranslatef(-1.0,0.6,0.6);
  glScalef(0.8, 1.0, 0.8);
  gluSphere(p,0.5,15,15);
  glPopMatrix();

  eyeballMaterials = &deepblueMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,eyeballMaterials -> ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeballMaterials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeballMaterials -> specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &eyeballMaterials -> shininess);

  glPushMatrix();
  glTranslatef(-1.25,0.7,0.6);
  glScalef(0.3, 0.4, 0.3);
  glColor3f (0.0, 0.0, 0.0);
  gluSphere(p,0.7,15,15);
  glPopMatrix();
}
/* Draw the tail of blue crane fish */
void bluetail()
{
  tailMaterials = &byellowMaterials;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,tailMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tailMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tailMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &tailMaterials -> shininess);

  glPushMatrix();
  glColor3ub(211,70,214);
  glTranslatef(0.0,0.0,-1.0);
  glScalef(0.8,0.8,0.8);
  glRotatef(180, 0.0, 1.0, 0.0);
  glRotatef(theta[1],0.0,1.0,0.0);
  gluCylinder(p,0.8,1.6,3.2,15,15);
  glPopMatrix();
 }
/* Draw the fins of blue crane fish */
void bluefins()
{
   wingMaterials = &fblueMaterials ;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,wingMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wingMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wingMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &wingMaterials -> shininess);

  glPushMatrix();
  glColor3ub(239,221,62);
  glTranslatef(0.0,0.0,-2.0);
  glScalef(0.8,0.8,0.8);
  glRotatef(270, 0.0, 1.0, 0.0);
  gluPartialDisk(p,0.0,3.5,15,15,0,180);
  glPopMatrix();
}
/* Draw the wing of blue crane fish in one side*/
void bluewing1()
{
  wingMaterials = &tyellowMaterials;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,wingMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wingMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wingMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &wingMaterials -> shininess);

   glPushMatrix();
   glColor3ub(247,139,71);
   glTranslatef(1.0,0.6,-0.6);
   glScalef(0.8,0.8,0.8);
   glRotatef(0.0, 0.0, 0.0, 1.0);
   glRotatef(theta[1],0.0,1.0,0.0);
   gluPartialDisk(p,0.0,2.0,15,15,60,70);
   glPopMatrix();
}
/* Draw the wing of blue crane fish in another side */
void bluewing2()
{
 wingMaterials = &tyellowMaterials;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,wingMaterials -> ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wingMaterials -> diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wingMaterials -> specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &wingMaterials -> shininess);

   glPushMatrix();
   glColor3ub(247,139,71);
   glTranslatef(1.0,0.6,-0.6);
   glScalef(0.8,0.8,0.8);
   glRotatef(0.0, 0.0, 0.0, 1.0);
   glRotatef(-theta[1],0.0,1.0,0.0);
   gluPartialDisk(p,0.0,2.0,15,15,60,70);
   glPopMatrix();
}

/* Draw red rose fish completely */
void redrose()
{
  redbody();
  redfins();
  redeye();
  redeye2();
  redmouth();
  redwing1();
  glPushMatrix();
  glRotatef(180,0.0,1.0, 0.0);
  glTranslatef(-0.1,0.0,1.0);
  redwing2();
  glPopMatrix();
  glPushMatrix();
  redtail();
  glPopMatrix();
}
/* Draw the clownfish completely */
void clownfish()
{

  clownbody();
  clownmouth();
  clowneye();
  clowneye2();
  clowntail();
  clownfins();
  clownwing1();
  glPushMatrix();
  glRotatef(180,0.0,1.0, 0.0);
  glTranslatef(-0.1,0.0,1.0);
  clownwing2();
  glPopMatrix();
}
/* Draw the blue crane fish completely */
void bluecrane()
{
  bluebody();
  bluefins();
  blueeye();
  blueeye2();
  bluemouth();
  bluewing1();
  glPushMatrix();
  glRotatef(180,0.0,1.0, 0.0);
  glTranslatef(-0.1,0.0,1.0);
  bluewing2();
  glPopMatrix();
  glPushMatrix();
  bluetail();
  glPopMatrix();
}
/*Define the sun light */
void  sunlight()
{
   GLfloat light0_position[]={0.0,1.0,0.0,0.0};     // Define the position of sun light
   glLightfv(GL_LIGHT0,GL_POSITION,light0_position); // Set the sunlight in that position
   sunLighting = &whiteLighting;                     // The light is white light
   glLightfv(GL_LIGHT0, GL_AMBIENT,sunLighting-> ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,sunLighting -> diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, sunLighting -> specular);
}
/*Define the spot light */
void Spotlight()
{
   GLfloat light1_position[]={0.0,5.0,5.0,1.0};    // Define the position of spot light
   glLightfv(GL_LIGHT1,GL_POSITION,light1_position);// Set the spot light in that position
   GLfloat spot_direction[]={0.0,-1.0,-1.0};       // Define the direction of spot light
   glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,spot_direction); // Set the direction of spot light
   glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,6.0);		  // Set attenuation of spot light
}
/* Set up three different light properties for the spotlight:
 * white, green and magenta.
 * For each colour, also choose a different cutoff angle.*/
void key(unsigned char k, int x, int y){
	switch(k){
		case'w': //'w' to choose white
		glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,40.0);
		spotLighting = &whiteLighting;
	    glLightfv(GL_LIGHT1, GL_AMBIENT,spotLighting-> ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,spotLighting -> diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spotLighting -> specular);
        lightcolor=1;
		  break;
		case'g': //'g' to choose green,
		glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30.0);
		spotLighting = &greenLighting;
		glLightfv(GL_LIGHT1, GL_AMBIENT,spotLighting-> ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,spotLighting -> diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spotLighting -> specular);
        lightcolor=2;
		  break;
		case'm': //'m' to choose magenta.
		glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,20.0);
	    spotLighting = &magentaLighting;
	    glLightfv(GL_LIGHT1, GL_AMBIENT,spotLighting-> ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,spotLighting -> diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spotLighting -> specular);
        lightcolor=3;
	      break;
	  case NULL:
		  spotLighting = &coloredLighting;
		  glLightfv(GL_LIGHT1, GL_AMBIENT,spotLighting-> ambient);
          glLightfv(GL_LIGHT1, GL_DIFFUSE,spotLighting -> diffuse);
          glLightfv(GL_LIGHT1, GL_SPECULAR, spotLighting -> specular);
		  break;
   }
}
/* Create a menu attached to the right button of the mouse
 * that shows the following three options: Sun, Spotlight and Both */
void mymenu2(int id ){
 //Select sun light
 if(id==1){
  sun =! sun;
  spot=GL_FALSE;
  both=GL_FALSE;
  // The switch of the sun light
  if(sun){
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);
	}
  else{
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT0);
   }
  lightflag=1;
}
   //Select spot light
  if(id==2){
  sun=GL_FALSE;
  both=GL_FALSE;
  spot =! spot;
  // The switch of the spot light
  if(spot){
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	spot1_on= GL_TRUE;
	}
  else{
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT0);
	spot1_on= GL_FALSE;
   }
  lightflag=2;
 }
 //Select two light
  if(id==3){
  sun=GL_FALSE;
  both =! both;
  spot=GL_FALSE;
  // The switch of two light
  if(both){
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	spot2_on= GL_TRUE;
	}
  	else{
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT0);
	spot2_on= GL_FALSE;
   }
  lightflag=3;
}
}
/* Dispaly the fish which is selected with the light chose */
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotatef(45, 0.0, -1.0, 0.0);
  glTranslatef(0.0,0.0,-3.0); //Ensure the fish swimming inside the window
  glTranslatef(0.0,0.0,theta[3]); //Make the fish moving from one side of the window to the other
  glTranslatef(2.5*cos(theta[0]/180*3.14),0.0,2.5*sin(theta[0]/180*3.14)); //The fish follow a circular trajectory
  glRotatef(theta[0], 0.0, -1.0, 0.0); // Make sure the head of fish follow the circular trajectory
  // Head rotate when reach the side of window
   if(h_direction<0)
   glRotatef(180, 0.0, 1.0, 0.0);
   //Select the type of material
   if((colorflag==1)||(colorflag==0)){
   clownfish();
    }
   if(colorflag==2){
	bluecrane();
	}
   if(colorflag==3){
	redrose();
	}
    glLoadIdentity();
    GLfloat mat_emission1[] = {1.0f, 1.0f, 1.0f, 1.0f};//White emission
    GLfloat mat_emission2[] = {0.0f, 1.0f, 0.0f, 1.0f};//Green emission
    GLfloat mat_emission3[] = {1.0f, 0.0f, 1.0f, 1.0f};//Magenta emission
    //Define a material of the sphere
    GLfloat mat_ambient[] = {0.5,0.5,0.5,1.0};
    GLfloat mat_diffuse[] = {1.0,1.0,1.0,1.0};
    GLfloat mat_specular[] = {0.5,0.5,0.5,1.0};
    GLfloat low_shininess = 5.0;
    //Select the type of light
	switch(lightflag)
	{
	  // Choose the sun light
	  case 1:
		sunlight();
	    break;
	  // Choose the spot light
	  case 2:
	    Spotlight();
	    if(spot1_on){

		glPushMatrix();
        glTranslatef(0.0f,5.0f,5.0f);

        glPushAttrib(GL_ALL_ATTRIB_BITS);
        switch(lightcolor){
		case 1:
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
		break;
		case 2:
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission2);
		break;
		case 3:
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission3);
		break;
	    }
	    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
		 gluSphere(p, 1.0f, 16, 16);
		 glPopAttrib();

         glPopMatrix();
		}
	    break;
	  // Choose the both type of light
	  case 3:
	    sunlight();
	    Spotlight();

	    if(spot2_on){
	  	glPushMatrix();
        glTranslatef(0.0f, 5.0f, 5.0f);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        switch(lightcolor){
		case 1:
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
		break;
		case 2:
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission2);
		break;
		case 3:
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission3);
		break;
	    }
	    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
		 gluSphere(p, 1.0f, 16, 16);
		 glPopAttrib();
         glPopMatrix();
		}
	    break;
	  default:
		glDisable(GL_LIGHT1);
	    glEnable(GL_LIGHT0);
		sunlight();
	    break;
     }
  glutSwapBuffers();
}

void init()
{
  p = gluNewQuadric();
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Make light affects the two sides
  glClearColor(0.557f, 0.949f, 0.949f, 0.8f); // Set the background color
}

void reshape(int w, int h)
{
  glViewport (0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-7.0, 7.0, -7.0, 7.0, -10.0, 10.0);
}


void idle()
{
  // Define the angle of circular motion
  if (circular) {
    theta[0] += 0.1;
    if (theta[0] > 360) theta[0] -= 360;
  }
  // Define the angle of swimming animation for every part of fish
  if (swim) {
    if (l_direction > 0) {
       theta[1] += 0.1;
       if (theta[1] > 15) {
          l_direction = -1;
          theta[1] -= 0.02;
       }
    }
    else {
       theta[1] -= 0.1;
       if (theta[1] < -15) {
          l_direction = 1;
          theta[1] += 0.02;
       }
    }

      if(h_direction > 0){
    theta[3] += 0.002;
     if(theta[3]>6.5){
		 h_direction = -1;

       }
	}

	 else {
       theta[3] -= 0.003;
       if (theta[3] < 0) {
          h_direction = 1;
          }
      }

}
  // Define the angle of rotate animation
  if (rotate) {
       theta[2] += 0.02;
 }
  glutPostRedisplay();
}

void mymouse(int btn, int state, int x, int y)
{
 if (btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
   swim = !swim;
}

/* Select the type of material used to render */
void mymenu(int id){
  if(id==1)
  colorflag=1;
  if(id==2)
  colorflag=2;
  if(id==3)
  colorflag=3;

}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(650, 650);
  glutCreateWindow("swimming fish");

  glTranslatef(8.0,8.0,8.0);
  glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
  glutKeyboardFunc(key);

  menu_id = glutCreateMenu(mymenu);
  glutAddMenuEntry("clownfish",1);
  glutAddMenuEntry("blue crane" , 2);
  glutAddMenuEntry("red rose" , 3);
  glutAttachMenu(GLUT_LEFT_BUTTON);

  menu2_id = glutCreateMenu(mymenu2);
  glutAddMenuEntry("Sun",1);
  glutAddMenuEntry("Spotlight" , 2);
  glutAddMenuEntry("Both" , 3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  init();
  glutMainLoop();
}
