#include "particle.h"
using namespace std;

int rotation = 1000; // speed at which particles spawn at, with each of the four colors moving in a diffrent direction. start is 1000

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

particles particle[PARTICLECOUNT];  // Into an array with the lot of em!

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int FixedInitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	zoom = 0.0;		// camera int;
		
	quadratic = gluNewQuadric();				// Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )
	//   OLD, SET LOCATION WAY
	int loop = 0;															// PARTICLE SYSTEM START!!
	for(i = 0; i < PARTICLECOUNT; i ++)			//startup section, make them active, spawn them, and fire them into the arena
	{
		particle[i].active = true;				// every time I generate one, I make one sign negitive, thereby placing one in all 4 sectors in 4 runs
		loop += 1;
		if(loop == 1)
		{		
		particle[i].x = ((rand() % spawnrad) - spawndist);
		particle[i].y = ((rand() % spawnrad) - spawndist);
		particle[i].xv = 0.0;
		particle[i].yv = 0.0 + rotation; 
		particle[i].r = 0.0;
		particle[i].g = 0.0;
		particle[i].b = 1.0;
		/*
		particle[i].x = ((rand() % spawnrad) + spawndist/2);	// restricts spawn to an area in the top right hand side of the screen
		particle[i].y = ((rand() % spawnrad) + spawndist/2);	// spawn rad restricts the range of random numbers, while spandist moves the whole area around 
		particle[i].xv = 0.0; // this is the speed vectors for the particles, by making this group move down, and the other groups move in other directions
		particle[i].yv = 0.0 - rotation;	// I can make all the particles sprial around the gravity source in a clockwise direction
		particle[i].r = 1.0;				// diffrent colors for each group, because I am just that aweosme.
		particle[i].g = 1.0;
		particle[i].b = 0.0;*/
		}
		if(loop == 2)
		{
		particle[i].x = ((rand() % spawnrad) - spawndist);			// note that the signs have changed for adding/subtracting spawndist, that allows
		particle[i].y = ((rand() % spawnrad) + spawndist/2);		// one varible to control distance placement for all 4 sectors
		particle[i].xv = 0.0 + rotation;
		particle[i].yv = 0.0;	
		particle[i].r = 0.0;
		particle[i].g = 0.0;
		particle[i].b = 1.0;
		}   
		if(loop == 3)
		{
		particle[i].x = ((rand() % spawnrad) - spawndist);
		particle[i].y = ((rand() % spawnrad) - spawndist);
		particle[i].xv = 0.0;
		particle[i].yv = 0.0 + rotation; 
		particle[i].r = 1.0;
		particle[i].g = 0.0;
		particle[i].b = 1.0;
		}
		if(loop == 4)
		{			
		particle[i].x = ((rand() % spawnrad) - spawndist);
		particle[i].y = ((rand() % spawnrad) - spawndist);
		particle[i].xv = 0.0;
		particle[i].yv = 0.0 + rotation; 
		particle[i].r = 1.0;
		particle[i].g = 0.0;
		particle[i].b = 0.0;

		/*particle[i].x = ((rand() % spawnrad) + spawndist/2);		
		particle[i].y = ((rand() % spawnrad) - spawndist);
		particle[i].xv = 0.0 - rotation; 
		particle[i].yv = 0.0;
		particle[i].r = 0.0;
		particle[i].g = 1.0;
		particle[i].b = 0.0;*/
		loop = 0;
		}
		particle[i].z = -100.0;
		particle[i].zv = 0.0;	
		particle[i].xc = 0.0;	// center gravity source (Star(); placement) 
		particle[i].yc = 0.0;
		particle[i].zc = -100.0;
		particle[i].mass = 10;
		particle[i].lifetime = lifeset;
	}
	return TRUE;
}


int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	zoom = 0.0;		// camera int;
		
	quadratic = gluNewQuadric();				// Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )

	//NEW RANDOM PLACEMENT INIT
	for(i = 0; i < PARTICLECOUNT; i ++)
	{
		GLfloat r = ((rand() % 70));
		GLfloat g = ((rand() % 70));
		GLfloat b = ((rand() % 70));
		r = r / 100;
		g = g / 100;
		b = b / 100;

		particle[i].active = true;
		particle[i].x = (rand() % spawnrad) - (rand() % spawnrad);
		particle[i].y = (rand() % spawnrad) - (rand() % spawnrad);
		particle[i].xv = (rand() % rotation) - (rand() % rotation);
		particle[i].yv = (rand() % rotation) - (rand() % rotation); 
		particle[i].r = r;
		particle[i].g = g;
		particle[i].b = b;
		
		particle[i].z = -100.0;
		particle[i].zv = 0.0;	
		particle[i].xc = 0.0;	// center gravity source (Star(); placement) 
		particle[i].yc = 0.0;
		particle[i].zc = -100.0;
		particle[i].mass = 10;
		particle[i].lifetime = lifeset;
		
	}


	return TRUE;										// Initialization Went OK
}

int drawparticle_type1(GLvoid)
{
			glColor3f(particle[i].r, particle[i].g, particle[i].b);				// DRAW THOSE PARTICLES!
			glBegin(GL_POINTS);			// the particles are just wee little dots at the moment. texure them someday.
			glVertex3f(particle[i].x, particle[i].y, particle[i].z);
			glEnd();
			return true;
}

int star()
{	
	glColor3f(0.7f,0.0f,0.3);
	glTranslatef(0.0f,0.0f,-90.0f);
	gluDisk(quadratic,0.0f,2.0f,32,32);		// draw a disc for the star
	glEnd();
	return true;
}
int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	glTranslatef(0.0f, 0.0f, zoom);

	for(i = 0; i < PARTICLECOUNT; i++)
	{

		if(particle[i].active == true)
		{
			if(particle[i].x >= 0 && particle[i].y >= 0)  // quad tests and temp corrections for non-refranced maths
			{
				particle[i].quad = 1;
			}	
			else if(particle[i].x < 0 && particle[i].y >= 0)
			{
				particle[i].quad = 2;
			}
			else if(particle[i].x < 0 && particle[i].y < 0)
			{
				particle[i].quad = 3;
			}
			else if(particle[i].x >= 0 && particle[i].y < 0)
			{
				particle[i].quad = 4;
			}


			// fist off, find mean distance to star gravity source
			// find distance, the pyth equation keeps everything positive (a^2 + b^2 = c^2) 
			dist = (sqrt((particle[i].x * particle[i].x) + (particle[i].y * particle[i].y))); 
			// take distance info, use to find new movement vector.
			particle[i].xv += ((particle[i].x / dist ) * ((1/dist * dist) * (gravity * particle[i].mass)));   // dont forget the inverse square law!
			particle[i].yv += ((particle[i].y / dist ) * ((1/dist * dist) * (gravity * particle[i].mass)));

			// this section of code will allow particle - particle interactions
			// first off, we are going to do this the hard way, with a for loop running, checking each particle aginst every other one.
			// but the idea after that is pretty niffty, basicly correct each particle into quad one and compute the diffrences for x and y
			// then we take that new x,y cord, flip it back into the correct quad and call it a new vector target, then we multiply with old vector
			// and BAM, particle/particle interactions.  we never actully compute the new place for the current particle because sooner or later that
			// particle will be computed in another particles loop, infact it MUST due to the fact it ever computed other particles at all.
			
			/*
			for(loop = 0; loop < PARTICLECOUNT; loop++)
			{
				// for now its every particle against every otherone, but after a time we will draw a range via a function of mass.
				if(loop != i) // keep loop from testing current particle and drawing a null vector on itself 
				{
					if(particle[loop].quad = 1) 
					// take a particle in a certain quad, adjust to quad one values, find diffx, diffy, turn into vector, 
					// and revert vector to correct quad
					{
						if(particle[loop].x >= particle[i].x) // keep diffx, diffy positive		
						{
							diffx = particle[loop].x - particle[i].x; 
						}
						else
						{
							diffx = particle[i].x - particle[loop].x;
						}
						if(particle[loop].y >= particle[i].y) // keep diffx, diffy positive		
						{
							diffy = particle[loop].y - particle[i].y;
						}
						else
						{
							diffy = particle[i].y - particle[loop].y;  // YOU LEFT OFF RIGHT HERE!!!!!11!!11!1ONE
						}
					}
					else if(particle[loop].quad = 2) // quad two = -x, +y, ergo only correct x to positive
					{
						if(particle[loop].x >= particle[i].x) // keep diffx, diffy positive		
						{
							diffx = particle[loop].x - particle[i].x; 
						}
						else
						{
							diffx = particle[i].x - particle[loop].x;
						}
						if(particle[loop].y >= particle[i].y) // keep diffx, diffy positive		
						{
							diffy = particle[loop].y - particle[i].y; 
						}
						else
						{
							diffy = particle[i].y - particle[loop].y;
						}
					}
					else if(particle[loop].quad = 3)
					{
						if(particle[loop].x >= particle[i].x) // keep diffx, diffy positive		
						{
							diffx = particle[loop].x - particle[i].x; 
						}
						else
						{
							diffx = particle[i].x - particle[loop].x;
						}
						if(particle[loop].y >= particle[i].y) // keep diffx, diffy positive		
						{
							diffy = particle[loop].y - particle[i].y; 
						}
						else
						{
							diffy = particle[i].y - particle[loop].y;
						}
					}
					else if(particle[loop].quad = 4)
					{
						if(particle[loop].x >= particle[i].x) // keep diffx, diffy positive		
						{
							diffx = particle[loop].x - particle[i].x; 
						}
						else
						{
							diffx = particle[i].x - particle[loop].x;
						}
						if(particle[loop].y >= particle[i].y) // keep diffx, diffy positive		
						{
							diffy = particle[loop].y - particle[i].y; 
						}
						else
						{
							diffy = particle[i].y - particle[loop].y;
						}
					}
				}
			}
	*/
			if((particle[i].x < 3 && particle[i].x > -3) && (particle[i].y < 3 && particle[i].y > -3))			
				// colision at center point, this is needed to destory particles on colision, will
			{	// later be dynamicly upgraded to destroy particles on contact with each other
				particle[i].active = false;	
			}

			particle[i].x += particle[i].xv / slowdown;		// movement update (REQUIRED) 
			particle[i].y += particle[i].yv / slowdown;			

			if(particle[i].active == true) drawparticle_type1();	
		}
	}

	star();				// star placement and rendering code, no math

	return TRUE;										
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","Error",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
//	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
//	{
		fullscreen=true;							// Windowed Mode
//	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("My Awesome Particle System, Thanks Nehe!",1920,1080,32,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("My Awesome Particle System, Thanks Nehe!",1920,1080,32,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
			
			if (keys[VK_F2])						// Is F1 Being Pressed?
			{
				keys[VK_F2]=FALSE;					// If So Make Key FALSE
				rotation = 1000;
				FixedInitGL();							// RESET ALL PARTICLE POS!			
			}
			if (keys[VK_F5])						// Is F1 Being Pressed?
			{
				keys[VK_F5]=FALSE;					// If So Make Key FALSE
				rotation = 100;
				InitGL();							// RESET ALL PARTICLE POS!			
			}
			if (keys[VK_F6])						// Is F1 Being Pressed?
			{
				keys[VK_F6]=FALSE;					// If So Make Key FALSE
				rotation = 1000;
				InitGL();							// RESET ALL PARTICLE POS!			
			}
			if (keys[VK_F7])						// Is F1 Being Pressed?
			{
				keys[VK_F7]=FALSE;					// If So Make Key FALSE
				rotation = 10000;
				InitGL();							// RESET ALL PARTICLE POS!			
			}
			if (keys[VK_F8])						// Is F1 Being Pressed?
			{
				keys[VK_F8]=FALSE;					// If So Make Key FALSE
				rotation = 100000;
				InitGL();							// RESET ALL PARTICLE POS!			
			}
			if (keys[VK_ADD])						// Is F1 Being Pressed?
			{
				keys[VK_ADD]=FALSE;					// If So Make Key FALSE
				zoom += 1;							// ZOOM IN
			}
			if (keys[VK_SUBTRACT])						// Is F1 Being Pressed?
			{
				keys[VK_SUBTRACT]=FALSE;					// If So Make Key FALSE
				zoom -= 1;									//ZOOM OUT
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
