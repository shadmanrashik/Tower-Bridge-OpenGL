#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"
#include "text3d.h"


using namespace std;
int flag = 0;

double hAngle = 0.0;
double vAngle = 0.0;
double view_x = 0.0;
double view_z = 0.0;
bool day = true;
bool fog = false;


GLuint loadTexture(Image* image) {
	GLuint textureId;

	//The first argument is the number of textures we need, and the second is an array where OpenGL will store the id's of the textures.
	glGenTextures(1, &textureId); //Make room for our texture
	// to assign the texture id to our image data.
//	We call glBindTexture(GL_TEXTURE_2D, textureId) to let OpenGL know
// that we want to work with the texture we just created. Then, we call glTexImage2D to load the image into OpenGL.
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}
GLuint _textureIdGrass;
GLuint _textureIdWater;
GLuint _textureIdBridgeBase;
GLuint _textureIdBridgePiller;
GLuint _textureIdMiddlePyramid;
GLuint _textureIdWindow;
GLuint _textureIdWindowSide;
GLuint _textureIdRoad;
GLuint _textureIdSkyDay;
GLuint _textureIdSkyNight;
GLuint _textureIdCorridor;


void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	//Take a look at imageloader.h. This gives us the basic idea of what loadBMP does.
	//(The actual code for loadBMP is in imageloader.cpp.) Given a filename, it returns an Image object,
	//which contains the width and height of the image, as well as the array pixels,
	//which stores the pixels' colors in the format we want.
	Image* image = loadBMP("vtr1.bmp");

	//Once we've got the image, we have to send it to OpenGL. We do this in a function we write called loadTexture.
	_textureIdGrass = loadTexture(image);
	//Note that we should only use images whose widths and heights are 64, 128, or 256, since computers like powers of 2.
//	Other sizes of images might not work properly.
	delete image;

	image = loadBMP("water2.bmp");
	_textureIdWater = loadTexture(image);
	delete image;

	image = loadBMP("window.bmp");
	_textureIdWindow = loadTexture(image);
	delete image;

	image = loadBMP("bridge_base.bmp");
	_textureIdBridgeBase = loadTexture(image);
	delete image;

	image = loadBMP("road.bmp");
	_textureIdRoad = loadTexture(image);
	delete image;

	image = loadBMP("day.bmp");
	_textureIdSkyDay = loadTexture(image);
	delete image;

	image = loadBMP("night.bmp");
	_textureIdSkyNight = loadTexture(image);
	delete image;

	image = loadBMP("window_side.bmp");
	_textureIdWindowSide = loadTexture(image);
	delete image;

	image = loadBMP("bridge_piller.bmp");
	_textureIdBridgePiller = loadTexture(image);
	delete image;

	image = loadBMP("middle_pyramid.bmp");
	_textureIdMiddlePyramid = loadTexture(image);
	delete image;

	image = loadBMP("corridor.bmp");
	_textureIdCorridor = loadTexture(image);
	delete image;
}

void drawBase() {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdGrass);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    glPushMatrix();
	glBegin(GL_QUADS);

    //left base
    //top
    glColor3f(1, 1, 1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5000, -8.0, 5000);
    glTexCoord2f(50.0f, 0.0f);
    glVertex3f(-30, -8.0, 5000);
    glTexCoord2f(50.0f, 50.0f);
    glVertex3f(-30, -8.0, -5000);
    glTexCoord2f(0.0f,50.0f);
    glVertex3f(-5000,-8.0,-5000);
    //bottom
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5000, -10.0, 5000);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-30, -10.0, 5000);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-30, -10.0, -5000);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-5000,-10.0,-5000);
    //right
    glColor3f(0.2,0.2,0.2);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-30, -8.0, -5000);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-30, -8.0, 5000);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-30, -10.0, 5000);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-30, -10.0, -5000);

    //right base
    glColor3f(1,1,1);
    //top
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5000, -8.0, 5000);
    glTexCoord2f(50.0f, 0.0f);
    glVertex3f(30, -8.0, 5000);
    glTexCoord2f(50.0f, 50.0f);
    glVertex3f(30, -8.0, -5000);
    glTexCoord2f(0.0f,50.0f);
    glVertex3f(5000,-8.0,-5000);
    //bottom
    glColor3f(0.2,0.2,0.2);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5000, -10.0, 5000);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(30, -10.0, 5000);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(30, -10.0, -5000);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(5000,-10.0,-5000);
    //left
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(30, -8.0, -5000);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(30, -8.0, 5000);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(30, -10.0, 5000);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(30, -10.0, -5000);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //glDisable(GL_TEXTURE_2D);
}

void drawRiver() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdWater);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPushMatrix();
    glColor3f(1,1,1);

    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(30,-10.0,-5000);
    glTexCoord2f(100.0f,0.0f);
    glVertex3f(-30,-10.0,-5000);
    glTexCoord2f(100.0f,100.0f);
    glVertex3f(-30,-10.0,5000);
    glTexCoord2f(0.0f,100.0f);
    glVertex3f(30,-10.0,5000);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawBridge() {
    glColor3f(1,1,1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdBridgeBase);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPushMatrix();
    glBegin(GL_QUADS);

    //right base of bridge
    //base
    glVertex3f(4, -9.9, -5);
    glVertex3f(11, -9.9, -5);
    glVertex3f(11, -9.9, 5);
    glVertex3f(4, -9.9, 5);
    //top
    glTexCoord2f(1.0,1.0);
    glVertex3f(4, -8, -5);
    glTexCoord2f(0.0,1.0);
    glVertex3f(11, -8, -5);
    glTexCoord2f(0.0,0.0);
    glVertex3f(11, -8, 5);
    glTexCoord2f(1.0,0.0);
    glVertex3f(4, -8, 5);
    //right
    glTexCoord2f(1.0,1.0);
    glVertex3f(11, -8, -5);
    glTexCoord2f(0.0,1.0);
    glVertex3f(11, -8, 5);
    glTexCoord2f(0.0,0.0);
    glVertex3f(11, -9.9, 5);
    glTexCoord2f(1.0,0.0);
    glVertex3f(11, -9.9, -5);
    //left
    glTexCoord2f(1.0,1.0);
    glVertex3f(4, -8, -5);
    glTexCoord2f(0.0,1.0);
    glVertex3f(4, -8, 5);
    glTexCoord2f(0.0,0.0);
    glVertex3f(4, -9.9, 5);
    glTexCoord2f(1.0,0.0);
    glVertex3f(4, -9.9, -5);
    //front
    glTexCoord2f(1.0,1.0);
    glVertex3f(11, -8, 5);
    glTexCoord2f(0.0,1.0);
    glVertex3f(4, -8, 5);
    glTexCoord2f(0.0,0.0);
    glVertex3f(4, -9.9, 5);
    glTexCoord2f(1.0,0.0);
    glVertex3f(11, -9.9, 5);
    //back
    glTexCoord2f(1.0,1.0);
    glVertex3f(11, -8, -5);
    glTexCoord2f(0.0,1.0);
    glVertex3f(4, -8, -5);
    glTexCoord2f(0.0,0.0);
    glVertex3f(4, -9.9, -5);
    glTexCoord2f(1.0,0.0);
    glVertex3f(11, -9.9, -5);
    glEnd();

    glPushMatrix();
    glTranslatef(-15,0,0);
    glBegin(GL_QUADS);
    //left base of bridge
    //base
    glVertex3f(4, -9.9, -5);
    glVertex3f(11, -9.9, -5);
    glVertex3f(11, -9.9, 5);
    glVertex3f(4, -9.9, 5);
    //top
    glTexCoord2f(1.0,1.0);
    glVertex3f(4, -8, -5);
    glTexCoord2f(0.0,1.0);
    glVertex3f(11, -8, -5);
    glTexCoord2f(0.0,0.0);
    glVertex3f(11, -8, 5);
    glTexCoord2f(1.0,0.0);
    glVertex3f(4, -8, 5);
    //right
    glTexCoord2f(1.0,1.0);
    glVertex3f(11, -8, -5);
    glTexCoord2f(0.0,1.0);
    glVertex3f(11, -8, 5);
    glTexCoord2f(0.0,0.0);
    glVertex3f(11, -9.9, 5);
    glTexCoord2f(1.0,0.0);
    glVertex3f(11, -9.9, -5);
    //left
    glTexCoord2f(1.0,1.0);
    glVertex3f(4, -8, -5);
    glTexCoord2f(0.0,1.0);
    glVertex3f(4, -8, 5);
    glTexCoord2f(0.0,0.0);
    glVertex3f(4, -9.9, 5);
    glTexCoord2f(1.0,0.0);
    glVertex3f(4, -9.9, -5);
    //front
    glTexCoord2f(1.0,1.0);
    glVertex3f(11, -8, 5);
    glTexCoord2f(0.0,1.0);
    glVertex3f(4, -8, 5);
    glTexCoord2f(0.0,0.0);
    glVertex3f(4, -9.9, 5);
    glTexCoord2f(1.0,0.0);
    glVertex3f(11, -9.9, 5);
    //back
    glTexCoord2f(1.0,1.0);
    glVertex3f(11, -8, -5);
    glTexCoord2f(0.0,1.0);
    glVertex3f(4, -8, -5);
    glTexCoord2f(0.0,0.0);
    glVertex3f(4, -9.9, -5);
    glTexCoord2f(1.0,0.0);
    glVertex3f(11, -9.9, -5);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdWindow);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //right side
    //front piller
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,1.0);
    glVertex3f(10, 1, 2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(5, 1, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(5, -8, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(10, -8, 2);
    //back piller
    glTexCoord2f(1.0,1.0);
    glVertex3f(10, 1, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(5, 1, -2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(5, -8, -2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(10, -8, -2);
    glEnd();

    //left side
    glPushMatrix();
    glTranslatef(-15,0,0);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,1.0);
    glVertex3f(10, 1, 2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(5, 1, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(5, -8, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(10, -8, 2);
    //back piller
    glTexCoord2f(1.0,1.0);
    glVertex3f(10, 1, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(5, 1, -2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(5, -8, -2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(10, -8, -2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdWindowSide);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //right piller
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,1.0);
    glVertex3f(10, 1, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(10, 1, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(10, -5, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(10, -5, -2);
    //left piller
    glTexCoord2f(1.0,1.0);
    glVertex3f(5, 1, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(5, 1, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(5, -5, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(5, -5, -2);

    glEnd();

    glPushMatrix();
    glTranslatef(-15,0,0);
    //right piller
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,1.0);
    glVertex3f(10, 1, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(10, 1, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(10, -5, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(10, -5, -2);
    //left piller
    glTexCoord2f(1.0,1.0);
    glVertex3f(5, 1, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(5, 1, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(5, -5, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(5, -5, -2);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdBridgePiller);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    //smallRactangle_Front_left_one
    //front
    glNormal3f(0,0,1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,2.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,2.5);
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,1.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,1.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,1.5);

    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(4.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(4.5, -8,1.5);

    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(5.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,1.5);

    //smallRactangle_Back_left_one
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,-2.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,-2.5);
    //front
    //glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,-1.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,-1.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,-1.5);
    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(4.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(4.5, -8,-1.5);
    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(5.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,-1.5);


    //smallRactangle_front_right_one
    //front
    glNormal3f(0,0,1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,2.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,2.5);
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,1.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,1.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,1.5);
    //left
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(9.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(9.5, -8,1.5);
        //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(10.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(10.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,1.5);

    //smallRactangle_Back_Right_one
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,-2.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,-2.5);
    //front
    //glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,-1.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,-1.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,-1.5);
    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(9.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(9.5, -8,-1.5);
    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(10.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(10.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,-1.5);

    //right middle top cover
    glNormal3f(0,1,0);
    glVertex3f(10, 1, -2);
    glVertex3f(5, 1, -2);
    glVertex3f(5, 1, 2);
    glVertex3f(10, 1, 2);

    glEnd();

    //left side
    glPushMatrix();
    glTranslatef(-15,0,0);
    glBegin(GL_QUADS);

//smallRactangle_Front_left_one
    //front
    glNormal3f(0,0,1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,2.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,2.5);
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,1.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,1.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,1.5);

    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(4.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(4.5, -8,1.5);

    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(5.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,1.5);

    //smallRactangle_Back_left_one
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,-2.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,-2.5);
    //front
    //glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,-1.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,-1.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,-1.5);
    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(4.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(4.5, -8,-1.5);
    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(5.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(5.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -8,-1.5);



    //smallRactangle_front_right_one
    //front
    glNormal3f(0,0,1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,2.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,2.5);
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,1.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,1.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,1.5);
    //left
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(9.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(9.5, -8,1.5);
        //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(10.5, 1.3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(10.5, -8,2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,1.5);

    //smallRactangle_Back_Right_one
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,-2.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,-2.5);
    //front
    //glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,-1.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,-1.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,-1.5);
    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(9.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(9.5, -8,-1.5);
    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(10.5, 1.3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(10.5, 1.3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(10.5, -8,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -8,-1.5);


    //right middle top cover
    glNormal3f(0,1,0);
    glVertex3f(10, 1, -2);
    glVertex3f(5, 1, -2);
    glVertex3f(5, 1, 2);
    glVertex3f(10, 1, 2);
    glEnd();
    glPopMatrix();



    //middle pyramid
    glBegin(GL_TRIANGLES);
    //front
    glNormal3f(0,0,1);
    glVertex3f(5,.7,2);
    glVertex3f(10,.7,2);
    glVertex3f(7.5,6,1);
    //back
    glNormal3f(0,0,1);
    glVertex3f(5,.7,-2);
    glVertex3f(10,.7,-2);
    glVertex3f(7.5,6,-1);
    glEnd();

    glPushMatrix();
    glTranslatef(-15,0,0);
    glBegin(GL_TRIANGLES);
    //front
    glNormal3f(0,0,1);
    glVertex3f(5,.7,2);
    glVertex3f(10,.7,2);
    glVertex3f(7.5,6,1);
    //back
    glNormal3f(0,0,1);
    glVertex3f(5,.7,-2);
    glVertex3f(10,.7,-2);
    glVertex3f(7.5,6,-1);
    glEnd();
    glPopMatrix();


    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdMiddlePyramid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    glTexCoord2f(1,1);
    glVertex3f(7.5, 6, -1);
    glTexCoord2f(0,1);
    glVertex3f(7.5, 6, 1);
    glTexCoord2f(0,0);
    glVertex3f(5, 0.7, 2);
    glTexCoord2f(1,0);
    glVertex3f(5, 0.7, -2);

    glTexCoord2f(1,1);
    glVertex3f(7.5, 6, -1);
    glTexCoord2f(0,1);
    glVertex3f(7.5, 6, 1);
    glTexCoord2f(0,0);
    glVertex3f(10, 0.7, 2);
    glTexCoord2f(1,0);
    glVertex3f(10, 0.7, -2);
    glEnd();

    glPushMatrix();
    glTranslatef(-15,0,0);
    glBegin(GL_QUADS);
    glTexCoord2f(1,1);
    glVertex3f(7.5, 6, -1);
    glTexCoord2f(0,1);
    glVertex3f(7.5, 6, 1);
    glTexCoord2f(0,0);
    glVertex3f(5, 0.7, 2);
    glTexCoord2f(1,0);
    glVertex3f(5, 0.7, -2);

    //glTexCoord2f(1,1);
    glVertex3f(7.5, 6, -1);
    glTexCoord2f(0,1);
    glVertex3f(7.5, 6, 1);
    glTexCoord2f(0,0);
    glVertex3f(10, 0.7, 2);
    glTexCoord2f(1,0);
    glVertex3f(10, 0.7, -2);
    glEnd();

    glPopMatrix();
    glBegin(GL_TRIANGLES);
    //small pyramids
    //front left
    //front
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(5, 4, 2);
    //back
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //left
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //right
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    glEnd();

    glPushMatrix();
    glTranslatef(5,0,0);
    glBegin(GL_TRIANGLES);
    //front
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(5, 4, 2);
    //back
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //left
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //right
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-4);
    glBegin(GL_TRIANGLES);
    //right back small
    //front
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(5, 4, 2);
    //back
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //left
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //right
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,-4);
    glBegin(GL_TRIANGLES);
    //right back small
    //front
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(5, 4, 2);
    //back
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //left
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //right
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,0,0);
    glBegin(GL_TRIANGLES);
    //right back small
    //front
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(5, 4, 2);
    //back
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //left
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //right
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,0);
    glBegin(GL_TRIANGLES);
    //right back small
    //front
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(5, 4, 2);
    //back
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //left
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //right
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,0,-4);
    glBegin(GL_TRIANGLES);
    //right back small
    //front
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(5, 4, 2);
    //back
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //left
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //right
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,-4);
    glBegin(GL_TRIANGLES);
    //right back small
    //front
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(5, 4, 2);
    //back
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //left
    glVertex3f(4.5, 1.3,2.5);
    glVertex3f(4.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    //right
    glVertex3f(5.5, 1.3,2.5);
    glVertex3f(5.5, 1.3,1.5);
    glVertex3f(5, 4, 2);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdCorridor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    //glColor3f(0.0,1,0.0);
    //front
    /*glTexCoord2f(0,0);
    glVertex3f(5.5, 1.3,2);
    glTexCoord2f(1,0);
    glVertex3f(-5.5, 1.3,2);
    glTexCoord2f(1,1);
    glVertex3f(-5.5, 0 ,2.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, 0,2.5);*/

    glTexCoord2f(0,0);
    glVertex3f(5.5, 1.3,2);
    glTexCoord2f(1,0);
    glVertex3f(-5.5, 1.3,2);
    glTexCoord2f(1,1);
    glVertex3f(-5.5, 0 ,2.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, 0,2.5);
    //back
    glTexCoord2f(0,0);
    glVertex3f(5.5, 1.3,1.75);
    glTexCoord2f(1,0);
    glVertex3f(-5.5, 1.3,1.75);
    glTexCoord2f(1,1);
    glVertex3f(-5.5, 0 ,1.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, 0,1.5);
    //bottom
    glVertex3f(5.5, 0,2.5);
    glVertex3f(-5.5, 0,2.5);
    glVertex3f(-5.5, 0,1.5);
    glVertex3f(5.5, 0,1.5);
    //top
    glVertex3f(5.5, 1.3,2);
    glVertex3f(-5.5, 1.3,2);
    glVertex3f(-5.5, 1.3,1.75);
    glVertex3f(5.5, 1.3,1.75);
    glEnd();

    glPushMatrix();
    glTranslatef(0,0,-4);
    //glEnd();
    glBegin(GL_QUADS);
    //glColor3f(0.0,1,0.0);
    //front
    /*glTexCoord2f(0,0);
    glVertex3f(5.5, 1.3,2);
    glTexCoord2f(1,0);
    glVertex3f(-5.5, 1.3,2);
    glTexCoord2f(1,1);
    glVertex3f(-5.5, 0 ,2.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, 0,2.5);*/

    glTexCoord2f(0,0);
    glVertex3f(5.5, 1.3,2);
    glTexCoord2f(1,0);
    glVertex3f(-5.5, 1.3,2);
    glTexCoord2f(1,1);
    glVertex3f(-5.5, 0 ,2.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, 0,2.5);


    //back
    glTexCoord2f(0,0);
    glVertex3f(5.5, 1.3,1.75);
    glTexCoord2f(1,0);
    glVertex3f(-5.5, 1.3,1.75);
    glTexCoord2f(1,1);
    glVertex3f(-5.5, 0 ,1.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, 0,1.5);
    //bottom
    glVertex3f(5.5, 0,2.5);
    glVertex3f(-5.5, 0,2.5);
    glVertex3f(-5.5, 0,1.5);
    glVertex3f(5.5, 0,1.5);
    //top
    glVertex3f(5.5, 1.3,2);
    glVertex3f(-5.5, 1.3,2);
    glVertex3f(-5.5, 1.3,1.75);
    glVertex3f(5.5, 1.3,1.75);
    glEnd();
    glPopMatrix();


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void drawGroundBase() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdWindow);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //right side
    //front piller
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glTexCoord2f(1.0,1.0);
    glVertex3f(35, -3, 2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(30, -3, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(30, -8, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(35, -8, 2);
    //back wall
    glTexCoord2f(1.0,1.0);
    glVertex3f(35, -3, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(30, -3, -2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(30, -8, -2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(35, -8, -2);
    glEnd();

    //left side front wall
    glPushMatrix();
    glTranslatef(-65,0,0);
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glTexCoord2f(1.0,1.0);
    glVertex3f(35, -3, 2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(30, -3, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(30, -8, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(35, -8, 2);
    //back wall
    glTexCoord2f(1.0,1.0);
    glVertex3f(35, -3, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(30, -3, -2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(30, -8, -2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(35, -8, -2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdWindowSide);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //right wall
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,1.0);
    glVertex3f(35, -3, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(35, -3, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(35, -5, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(35, -5, -2);
    //left wall
    glTexCoord2f(1.0,1.0);
    glVertex3f(30, -3, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(30, -3, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(30, -5, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(30, -5, -2);

    glEnd();

    glPushMatrix();
    glTranslatef(-65,0,0);
    //left side
    //right wall
    glBegin(GL_QUADS);
    glTexCoord2f(1.0,1.0);
    glVertex3f(35, -3, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(35, -3, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(35, -5, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(35, -5, -2);
    //left wall
    glTexCoord2f(1.0,1.0);
    glVertex3f(30, -3, -2);
    glTexCoord2f(0.0,1.0);
    glVertex3f(30, -3, 2);
    glTexCoord2f(0.0,0.0);
    glVertex3f(30, -5, 2);
    glTexCoord2f(1.0,0.0);
    glVertex3f(30, -5, -2);

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdBridgePiller);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPushMatrix();
    glTranslatef(25,0,0);
    glBegin(GL_QUADS);

    //small Ractangle_Front_left_one
    //front
    glNormal3f(0,0,1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,2.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,2.5);
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,1.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,1.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,1.5);

    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(4.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(4.5, -15,1.5);

    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(5.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,1.5);

    //smallRactangle_Back_left_one
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,-2.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,-2.5);
    //front
    //glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,-1.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,-1.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,-1.5);
    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(4.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(4.5, -15,-1.5);
    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(5.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,-1.5);


    //smallRactangle_front_right_one
    //front
    glNormal3f(0,0,1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,2.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,2.5);
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,1.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,1.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,1.5);
    //left
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(9.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(9.5, -15,1.5);
        //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(10.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(10.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,1.5);

    //smallRactangle_Back_Right_one
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,-2.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,-2.5);
    //front
    //glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,-1.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,-1.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,-1.5);
    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(9.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(9.5, -15,-1.5);
    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(10.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(10.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,-1.5);

    //right middle top cover
    glNormal3f(0,1,0);
    glVertex3f(10, -3, -2);
    glVertex3f(5, -3, -2);
    glVertex3f(5, -3, 2);
    glVertex3f(10, -3, 2);

    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40,0,0);
    glBegin(GL_QUADS);

    //smallRactangle_Front_left_one
    //front
    glNormal3f(0,0,1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,2.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,2.5);
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,1.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,1.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,1.5);

    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(4.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(4.5, -15,1.5);

    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(5.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,1.5);

    //smallRactangle_Back_left_one
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,-2.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,-2.5);
    //front
    //glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,-1.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,-1.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,-1.5);
    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(4.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(4.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(4.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(4.5, -15,-1.5);
    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(5.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(5.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(5.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(5.5, -15,-1.5);



    //smallRactangle_front_right_one
    //front
    glNormal3f(0,0,1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,2.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,2.5);
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,1.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,1.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,1.5);
    //left
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(9.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(9.5, -15,1.5);
        //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,1.5);
    glTexCoord2f(0,1);
    glVertex3f(10.5, -3,2.5);
    glTexCoord2f(0,0);
    glVertex3f(10.5, -15,2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,1.5);

    //smallRactangle_Back_Right_one
    //back
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,-2.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,-2.5);
    //front
    //glNormal3f(0,0,-1);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,-1.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,-1.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,-1.5);
    //left
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(9.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(9.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(9.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(9.5, -15,-1.5);
    //right
    glNormal3f(1,0,0);
    glTexCoord2f(1,1);
    glVertex3f(10.5, -3,-1.5);
    glTexCoord2f(0,1);
    glVertex3f(10.5, -3,-2.5);
    glTexCoord2f(0,0);
    glVertex3f(10.5, -15,-2.5);
    glTexCoord2f(1,0);
    glVertex3f(10.5, -15,-1.5);

    //right middle top cover
    glNormal3f(0,1,0);
    glVertex3f(10, -3, -2);
    glVertex3f(5, -3, -2);
    glVertex3f(5, -3, 2);
    glVertex3f(10, -3, 2);

    glEnd();
    glPopMatrix();

    glBegin(GL_QUADS);
    glEnd();

}
void drawRoad() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdRoad);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glTexCoord2f(1,1);
    glVertex3f(-5, -7.99, -2);
    glTexCoord2f(0,1);
    glVertex3f(-50, -7.99, -2);
    glTexCoord2f(0,0);
    glVertex3f(-50, -7.99, 2);
    glTexCoord2f(1,0);
    glVertex3f(-5, -7.99, 2);

    glTexCoord2f(1,1);
    glVertex3f(5, -7.99, -2);
    glTexCoord2f(0,1);
    glVertex3f(50, -7.99, -2);
    glTexCoord2f(0,0);
    glVertex3f(50, -7.99, 2);
    glTexCoord2f(1,0);
    glVertex3f(5, -7.99, 2);

    glTexCoord2f(1,1);
    glVertex3f(5, -7.99, -2);
    glTexCoord2f(0,1);
    glVertex3f(-5, -7.99, -2);
    glTexCoord2f(0,0);
    glVertex3f(-5, -7.99, 2);
    glTexCoord2f(1,0);
    glVertex3f(5, -7.99, 2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawBackground() {
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    if(day == true)
        glBindTexture(GL_TEXTURE_2D, _textureIdSkyDay);
    else
        glBindTexture(GL_TEXTURE_2D, _textureIdSkyNight);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    //back
    glBegin(GL_QUADS);
    glTexCoord2f(3.0,3.0);
    glVertex3f(-500, 500, -100);
    glTexCoord2f(0.0,3.0);
    glVertex3f(500, 500, -100);
    glTexCoord2f(0.0,0.0);
    glVertex3f(500, -15, -100);
    glTexCoord2f(3.0,0.0);
    glVertex3f(-500, -15, -100);
    //front
    glTexCoord2f(3.0,3.0);
    glVertex3f(-500, 500, 100);
    glTexCoord2f(0.0,3.0);
    glVertex3f(500, 500, 100);
    glTexCoord2f(0.0,0.0);
    glVertex3f(500, -15, 100);
    glTexCoord2f(3.0,0.0);
    glVertex3f(-500, -15, 100);
    //left
    glTexCoord2f(3.0,3.0);
    glVertex3f(-100, 500, -500);
    glTexCoord2f(0.0,3.0);
    glVertex3f(-100, 500, 500);
    glTexCoord2f(0.0,0.0);
    glVertex3f(-100, -15, 500);
    glTexCoord2f(3.0,0.0);
    glVertex3f(-100, -15, -500);
    //right
    glTexCoord2f(3.0,3.0);
    glVertex3f(100, 500, -500);
    glTexCoord2f(0.0,3.0);
    glVertex3f(100, 500, 500);
    glTexCoord2f(0.0,0.0);
    glVertex3f(100, -15, 500);
    glTexCoord2f(3.0,0.0);
    glVertex3f(100, -15, -500);





    glEnd();
    glDisable(GL_TEXTURE_2D);

}
void drawRope() {
    glLineWidth(4);
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_LINE_STRIP);
    glVertex3f (10 , -2.2, 2);
    glVertex3f (11 , -2.8, 2.00);
    glVertex3f (12 , -3.4, 2.01);
    glVertex3f (13 , -4, 2.02);
    glVertex3f (14 , -4.5, 2.03);
    glVertex3f (15 , -5.0, 2.04);
    glVertex3f (16 , -5.5, 2.05);
    glVertex3f (17 , -6, 2.06);
    glVertex3f (18 , -6.5, 2.07);
    glVertex3f (19 , -7.0, 2.08);
    glVertex3f (20 , -7.5, 2.09);
    glVertex3f (21 , -7.7, 2.1);
    glVertex3f (22 , -7.7, 2.09);
    glVertex3f (23 , -7.7, 2.08);
    glVertex3f (24 , -7.5, 2.07);
    glVertex3f (25 , -7, 2.06);
    glVertex3f (26 , -6.4, 2.05);
    glVertex3f (27 , -5.8, 2.04);
    glVertex3f (28 , -5.3, 2.03);
    glVertex3f (29 , -4.8, 2.02);
    glVertex3f (30 , -4.2, 2.01);
    glVertex3f (30 , -3.6, 2.00);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex3f (10 , -2.2, 2.00);
    glVertex3f (11 , -2.8, 1.99);
    glVertex3f (12 , -3.4, 1.98);
    glVertex3f (13 , -4, 1.97);
    glVertex3f (14 , -4.5, 1.96);
    glVertex3f (15 , -5.0, 1.95);
    glVertex3f (16 , -5.5, 1.94);
    glVertex3f (17 , -6, 1.95);
    glVertex3f (18 , -6.5, 1.94);
    glVertex3f (19 , -7.0, 1.93);
    glVertex3f (20 , -7.5, 1.92);
    glVertex3f (21 , -7.7, 1.91);
    glVertex3f (22 , -7.7, 1.9);
    glVertex3f (23 , -7.7, 1.91);
    glVertex3f (24 , -7.5, 1.92);
    glVertex3f (25 , -7, 1.93);
    glVertex3f (26 , -6.4, 1.94);
    glVertex3f (27 , -5.8, 1.95);
    glVertex3f (28 , -5.3, 1.96);
    glVertex3f (29 , -4.8, 1.97);
    glVertex3f (30 , -4.2, 1.98);
    glVertex3f (30 , -3.6, 1.99);
    glEnd();

    glPushMatrix();
    glTranslatef(0,0,-4);
    glBegin(GL_LINE_STRIP);
    glVertex3f (10 , -2.2, 2.00);
    glVertex3f (11 , -2.8, 1.99);
    glVertex3f (12 , -3.4, 1.98);
    glVertex3f (13 , -4, 1.97);
    glVertex3f (14 , -4.5, 1.96);
    glVertex3f (15 , -5.0, 1.95);
    glVertex3f (16 , -5.5, 1.94);
    glVertex3f (17 , -6, 1.95);
    glVertex3f (18 , -6.5, 1.94);
    glVertex3f (19 , -7.0, 1.93);
    glVertex3f (20 , -7.5, 1.92);
    glVertex3f (21 , -7.7, 1.91);
    glVertex3f (22 , -7.7, 1.9);
    glVertex3f (23 , -7.7, 1.91);
    glVertex3f (24 , -7.5, 1.92);
    glVertex3f (25 , -7, 1.93);
    glVertex3f (26 , -6.4, 1.94);
    glVertex3f (27 , -5.8, 1.95);
    glVertex3f (28 , -5.3, 1.96);
    glVertex3f (29 , -4.8, 1.97);
    glVertex3f (30 , -4.2, 1.98);
    glEnd();

    glPopMatrix();

    glBegin(GL_LINES);
    glVertex3f (12 , -3.4, 1.98);
    glVertex3f (12, -8, 1.98);

    glVertex3f (14 , -4.5, 1.96);
    glVertex3f (14 , -8, 1.96);

    glVertex3f (16 , -5.5, 1.94);
    glVertex3f (16 , -8, 1.94);

    glVertex3f (18 , -6.5, 1.94);
    glVertex3f (18 , -8, 1.94);

    glVertex3f (20 , -7.5, 1.92);
    glVertex3f (20 , -8, 1.92);

    glVertex3f (24 , -7.5, 1.92);
    glVertex3f (24 , -8, 1.92);

    glVertex3f (26 , -6.4, 1.94);
    glVertex3f (26 , -8, 1.94);

    glVertex3f (28 , -5.3, 1.96);
    glVertex3f (28 , -8, 1.96);

	glEnd();

    glPushMatrix();
    glTranslatef(0,0,-4);
    glBegin(GL_LINES);
    glVertex3f (12 , -3.4, 1.98);
    glVertex3f (12, -8, 1.98);

    glVertex3f (14 , -4.5, 1.96);
    glVertex3f (14 , -8, 1.96);

    glVertex3f (16 , -5.5, 1.94);
    glVertex3f (16 , -8, 1.94);

    glVertex3f (18 , -6.5, 1.94);
    glVertex3f (18 , -8, 1.94);

    glVertex3f (20 , -7.5, 1.92);
    glVertex3f (20 , -8, 1.92);

    glVertex3f (24 , -7.5, 1.92);
    glVertex3f (24 , -8, 1.92);

    glVertex3f (26 , -6.4, 1.94);
    glVertex3f (26 , -8, 1.94);

    glVertex3f (28 , -5.3, 1.96);
    glVertex3f (28 , -8, 1.96);

    glEnd();
    glPopMatrix();

    glBegin(GL_LINE_STRIP);
    glVertex3f (-30 , -3.6, 2.00);
    glVertex3f (-29 , -4.2, 1.99);
    glVertex3f (-28 , -4.8, 1.98);
    glVertex3f (-27 , -5.3, 1.97);
    glVertex3f (-26 , -5.8, 1.96);
    glVertex3f (-25 , -6.4, 1.95);
    glVertex3f (-24 , -7, 1.94);
    glVertex3f (-23 , -7.5, 1.95);
    glVertex3f (-22 , -7.7, 1.94);
    glVertex3f (-21 , -7.7, 1.93);
    glVertex3f (-20 , -7.7, 1.92);
    glVertex3f (-19 , -7.5, 1.91);
    glVertex3f (-18 , -7.0, 1.9);
    glVertex3f (-17 , -6.5, 1.91);
    glVertex3f (-16 , -6.0, 1.92);
    glVertex3f (-15 , -5.5, 1.93);
    glVertex3f (-14 , -5.0, 1.94);
    glVertex3f (-13 , -4.5, 1.95);
    glVertex3f (-12 , -4.0, 1.96);
    glVertex3f (-11 , -3.4, 1.97);
    glVertex3f (-10 , -2.8, 1.98);
    glEnd();

    glPushMatrix();
    glTranslatef(0,0,-4);
    glBegin(GL_LINE_STRIP);
    glVertex3f (-30 , -3.6, 2.00);
    glVertex3f (-29 , -4.2, 1.99);
    glVertex3f (-28 , -4.8, 1.98);
    glVertex3f (-27 , -5.3, 1.97);
    glVertex3f (-26 , -5.8, 1.96);
    glVertex3f (-25 , -6.4, 1.95);
    glVertex3f (-24 , -7, 1.94);
    glVertex3f (-23 , -7.5, 1.95);
    glVertex3f (-22 , -7.7, 1.94);
    glVertex3f (-21 , -7.7, 1.93);
    glVertex3f (-20 , -7.7, 1.92);
    glVertex3f (-19 , -7.5, 1.91);
    glVertex3f (-18 , -7.0, 1.9);
    glVertex3f (-17 , -6.5, 1.91);
    glVertex3f (-16 , -6.0, 1.92);
    glVertex3f (-15 , -5.5, 1.93);
    glVertex3f (-14 , -5.0, 1.94);
    glVertex3f (-13 , -4.5, 1.95);
    glVertex3f (-12 , -4.0, 1.96);
    glVertex3f (-11 , -3.4, 1.97);
    glVertex3f (-10 , -2.8, 1.98);
    glEnd();
    glPopMatrix();

    glBegin(GL_LINES);
    glVertex3f (-12 , -4, 1.98);
    glVertex3f (-12, -8, 1.98);

    glVertex3f (-14 , -5, 1.96);
    glVertex3f (-14 , -8, 1.96);

    glVertex3f (-16 , -6, 1.94);
    glVertex3f (-16 , -8, 1.94);

    glVertex3f (-18 , -7, 1.94);
    glVertex3f (-18 , -8, 1.94);

    glVertex3f (-20 , -7.7, 1.92);
    glVertex3f (-20 , -8, 1.92);

    glVertex3f (-24 , -7, 1.92);
    glVertex3f (-24 , -8, 1.92);

    glVertex3f (-26 , -5.8, 1.94);
    glVertex3f (-26 , -8, 1.94);

    glVertex3f (-28 , -4.8, 1.96);
    glVertex3f (-28 , -8, 1.96);

    glEnd();

    glPushMatrix();
    glTranslatef(0,0,-4);
    glBegin(GL_LINES);
    glVertex3f (-12 , -4, 1.98);
    glVertex3f (-12, -8, 1.98);

    glVertex3f (-14 , -5, 1.96);
    glVertex3f (-14 , -8, 1.96);

    glVertex3f (-16 , -6, 1.94);
    glVertex3f (-16 , -8, 1.94);

    glVertex3f (-18 , -7, 1.94);
    glVertex3f (-18 , -8, 1.94);

    glVertex3f (-20 , -7.7, 1.92);
    glVertex3f (-20 , -8, 1.92);

    glVertex3f (-24 , -7, 1.92);
    glVertex3f (-24 , -8, 1.92);

    glVertex3f (-26 , -5.8, 1.94);
    glVertex3f (-26 , -8, 1.94);

    glVertex3f (-28 , -4.8, 1.96);
    glVertex3f (-28 , -8, 1.96);
    glEnd();
    glPopMatrix();
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glTranslatef(0.0f, 1.0f, -50.0f);

	GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 2.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	//On to drawScene. We start by calling glEnable(GL_TEXTURE_2D) to enable applying textures
//	and glBindTexture(GL_TEXTURE_2D, _textureId) to tell OpenGL that we want to use the texture with id _textureId.

	//Bottom

	//The first call tells OpenGL to use the blocky mapping (GL_NEAREST)
//	when the texture is far away from us, and the second call tells it to use blocky mapping when the texture is close.
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// blurry mapping, we'd pass GL_LINEAR as the third parameter of these two functions.

	//Now, in addition to a normal vector, each vertex has a texture coordinate.
	//The texture coordinates indicates to what point on the image each vertex maps.
	//The texture coordinate (a + b, c + d), where a and c are integers,
//	indicates the spot that is the fractional amount b above the bottom of the texture
// and the fractional amount d right of the left of the texture.
// To specify the texture coordinates of a vertex, we simply call glTexCoord2f with the texture coordinates we want before calling glVertex3f for the vertex.

	//will multiply the red of pixel by 1, blue by .2 and g reen by .2

    glTranslatef(view_x,0,view_z);
	glRotatef(vAngle, 0.0, 1.0, 0.0);
	glRotatef(hAngle, 1.0, 0.0, 0.0);
    drawBackground();
    drawBase();
    drawGroundBase();
    drawBridge();
    drawRiver();
    drawRoad();
    drawRope();

    if(fog==true)
    {
        GLfloat fogcolour[4]= {1.0,1.0,1.0,1.0};

        glFogfv(GL_FOG_COLOR,fogcolour);              /* Define the fog colour */
        glFogf(GL_FOG_DENSITY,0.009);                   /* How dense */
        glFogi(GL_FOG_MODE,GL_EXP);                   /* exponential decay */
        glFogf(GL_FOG_START,3.0);                   /* Where wwe start fogging */
        glFogf(GL_FOG_END,150.0);                       /* end */
        glHint(GL_FOG_HINT, GL_FASTEST);              /* compute per vertex */
        glEnable(GL_FOG);/* ENABLE */
    }
    else {
        glDisable(GL_FOG);
    }

	glutSwapBuffers();
}


void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
        case 'l':
            flag = 0;
            //glutPostRedisplay();
            break;
        case 'e':
        case 'E':
            vAngle -= 2.5f;
            if (vAngle < 360)
            {
                vAngle += 360;
            }
            break;
        case 'r':
        case 'R':
            vAngle += 2.5f;
            if (vAngle > 360)
            {
                vAngle -= 360;
            }
            break;
        case 'D':
        case 'd':
            hAngle -= 5;
            if(hAngle < 360)
                hAngle += 360;
            break;
        case 'u':
        case 'U':
            hAngle += 5;
            if(hAngle>360)
                hAngle -= 360;
            break;
        case 'T':
        case 't':
            if(day == true) {
                day = false;
                glDisable(GL_LIGHTING);
            }
            else
                day = true;
            break;
        case 'f':
        case 'F':
            if (fog == false)
                fog = true;
            else
                fog = false;
    }
	glutPostRedisplay();
}
void special_key(int key,int x,int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT :
        view_x += .3;
        break;
    case GLUT_KEY_RIGHT:
        view_x -= .3;
        break;
    case GLUT_KEY_UP   :
        view_z += .3;
        break;
    case GLUT_KEY_DOWN :
        view_z -= .3;
        break;
    }
    glutPostRedisplay();
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (float)w / (float)h, 1.0, 200.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1500, 750);

	glutCreateWindow("Textures - videotutorialsrock.com");
	initRendering();

    glClearColor(1,1,1,.5);
    //glClearColor (0.529, 0.808, 0.922, 0.0);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(special_key);
	glutReshapeFunc(handleResize);

	glutMainLoop();
	return 0;
}

