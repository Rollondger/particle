#ifndef _particle_h
#define _particle_h
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>			// used for some calculations
#include <iostream>
#include <fstream>			// used in the stats debugger file IO.
#include <ctime>

#define PARTICLECOUNT	40000		// number of particles, not counting stars or planets, 9000 works well.
#define lifeset			1000		// lifetime of particles, unused atm.
#define slowdown		4000		// particle speed controler, 4000 is a good base. this is used as a gravity multiplyer atm.
#define friction		.9			// my attempt at forcing orbit decay, unused atm.
#define gravity			-10			// gravity consant, must be a negitive number! defualt is -10
#define spawndist		20			// dist each box is from one another, defualt is 60
#define spawnrad		40			// spawn modelus, used to set height and width of spawn box, defualt 50
#define neardist		10			// used to limit particle - particle interactions, particles farther away than this rfom source will not be tested
#define logpath			"log.txt"

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application
GLUquadricObj *quadratic;
//ULONGLONG timer;			// used as a timer with GetTickCount64();  this is millisecond prescise. used for debug.

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
bool	test;				// I use this in alot of loops for vaule testing at odd times, best to declare once I say.

int i;			// I'll let you guess what this is used for.
int loop;		// kind of like i, but for loops inside of i loops... yea...
double dist;	// used to find distance from object to gravity source.  found like right triangle hyp (A^2 + B^2 = C^2 ) (C=dist)
int fps;		// mean frames per second, used to help with debugging
long int cycles;		// find clock cycles and find diffrence from last cycle, used for debugging help
long int ticks;
double loginfo;
int quad;		// this is here for the ammount of quadrent selection statements needed for the complex math.
double diffx, diffy; // quad diff math in non-refranced system -- TEMPORARY will be replaced with proper math after i know it works!
GLfloat zoom;


typedef struct 			// Creating struct for particles so I can place each in an array and call on each attribute as much as I want.
{
	bool active;
	double x;			// current pos of particle
	double y;
	double z;
	double xv;			// accel vectors for particle
	double yv;
	double zv;
	double xc;			// center location for both world spawn and garvity source
	double yc;
	double zc;
	double mass;		// spc of particle
	double lifetime;	
	double r;			// RGB values for color, at some point the color will mean something. (such as temp or speed or mass)
	double g;
	double b;
	int quad;			// used for non-refranced system
} particles;










#endif