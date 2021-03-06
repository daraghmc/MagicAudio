// Bare bones demonstration of 3D positional audio
// using OpenGL as the visualizer.
// 
// The x-axis points horizontally, positive to the right.
// The z-axis points vertically, positive down.
// The y-axis is perpendicular to the screen, positive outwards.
//
// The listener is represented by the blue cube at
// the origin. The sound source is a sphere rotating about the 
// listener, in a cylindrical orbit, with the cylinder's base orthogonal 
// to the x-z plane.
// 
// The camera is positioned on the positive y-azis, at the origin of the x-z plane,
// and looking down at the origin.

#include<Windows.h>    
#include<gl/GL.h>    
#include<gl/GLU.h>    
#include "../include/gl/glut.h"

#include<stdio.h>    
#include<conio.h>    
#include<stdio.h>   
#include<string.h>    
#include <time.h>
#define _USE_MATH_DEFINES
#include<math.h>  

#include "MAAudioRenderer.pkg"
#include "MADxAudioRenderer.pkg"

using namespace MagicAudio;

// Constant values
static const float ORBITAL_RADIUS = 5.0f;
static const float ORBITAL_FREQ = 0.1f;
static const float DOPPLER = 1.0f;
static const float ROLLOFF = 0.1f;

// Globals
float g_sourceX = 0.0f;
float g_sourceZ = 0.0f;
float g_sourceY = 0.0f;
clock_t g_startTime = 0;
double g_lastUpdateTime = 0;

Pointer<SoundRenderer> g_soundRenderer;
Pointer<Listener3D> g_listener;
Pointer<Sound3D> g_source;

// Set up the audio system
void InitializeAudio(HWND hwnd)
{
	AudioFormat kFormat;
	kFormat.iSampleRate = 22050;
	kFormat.iChannels = 2;
	kFormat.iBytesPerSample = 2;
	kFormat.b3D = true;

	g_soundRenderer = new DxSoundRenderer;
	g_soundRenderer->Initialize((int)hwnd, &kFormat);

	g_listener = new Listener3D;
	// Set the Top and Front vectors of the listener.
	// Top points up from the centre of the listener's "head",
	// Front is orthogonal to Top and pointing towards the
	// front of the listener's head. In this case, we position
	// the listener's head to look along the z-axis
	// with the Top vector pointing up along the positive y-axis.
	// Note that DirectSound uses a left-handed co-ordinate system.
	// while OpenGL is right-handed. The listener's Front vector is 
	// pointing along DirectSound's positive z-axis (in this case,
	// towards the top of the screen). The x- and y-axis directions
	// then correspond to OpenGl's. 
	g_listener->SetTop(Vector3f::UNIT_Y);
	g_listener->SetFront(Vector3f::UNIT_Z);
	g_listener->SetPosition(Vector3f::ZERO);
	g_listener->SetRolloff(ROLLOFF);
	g_listener->SetDoppler(DOPPLER);

	g_soundRenderer->SetAll(g_listener);

	g_source = new Sound3D;
	g_source->SetName(L"positionaldemo.maf");
	g_source->SetVolume(100);
	g_source->SetMode(Sound3D::MODE_ABSOLUTE);
	g_source->SetLooping(true);
	g_soundRenderer->Load(g_source);
	g_soundRenderer->Play(g_source);
}

// Set up OpenGL scene properties
void InitOpenGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	float lightDirection[] = { 0.0f, -1.0f, 0.0f, 0.0f};
	float lightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
}

// Render the objects in the OpenGL scene
void RenderObjects(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the listener
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
	glEnable(GL_COLOR_MATERIAL);
	glutSolidCube(0.4f);
	glPopMatrix();

	glPushMatrix();
	// Draw the sound source
	glTranslatef(g_sourceX, g_sourceY, g_sourceZ);
	glColor3f(0.0f, 1.0f, 0.0f);
	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
	glEnable(GL_COLOR_MATERIAL);
	glutSolidSphere(0.4f, 50, 50);
	glPopMatrix();

	glutSwapBuffers();
}

// Set up the viewport, projection and camera to account for the 
// current window size
void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Camera is at (x,y,z) = (0, 12, 0), pointing at (0, 0, 0)
	gluLookAt(0.0, 12.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
}

void Idle(void)
{
	static bool firstPass = true;
	if (firstPass)
	{
		// Workaround to get window handle required by audio system.
		// Since GLUT doesn't give direct access to the handle of the
		// window it creates, we retrieve it via our previously set
		// window title
		HWND hWnd = FindWindowA(NULL, "Positional Audio Demo");
		InitializeAudio(hWnd);
		firstPass = false;
	}
	
	// Limit the frame rate to 100Hz
	double now = ((double)clock() - g_startTime) / CLOCKS_PER_SEC;
	if (now - g_lastUpdateTime > 0.01f)
	{
		Vector3f prevSourcePos(g_sourceX, g_sourceY, -g_sourceZ);

		// Update the position of the source
		double angle = 2 * M_PI * ORBITAL_FREQ * now;
		g_sourceX = ORBITAL_RADIUS * (float)sin(angle);
		g_sourceZ = ORBITAL_RADIUS * (float)cos(angle);
		g_sourceY = ORBITAL_RADIUS * (float)sin(angle);
		glutPostRedisplay();	

		// Reflect the z-coord in the x-axis to account for the
		// difference in handed-ness between DirectSound and OpenGL
		Vector3f newSourcePos = Vector3f(g_sourceX, g_sourceY, -g_sourceZ);
		// Velocity calculated using a first order difference approximation to ds/dt,
		// where s denotes position vector
		Vector3f vel = (newSourcePos - prevSourcePos) / (float)(now - g_lastUpdateTime);
		g_source->SetVelocity(vel);
		g_source->SetPosition(newSourcePos);
		g_soundRenderer->SetPosition(g_source);

		g_lastUpdateTime = now;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(250, 50);
	glutCreateWindow("Positional Audio Demo");
	InitOpenGL();
	glutDisplayFunc(RenderObjects);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutSetWindowTitle("Positional Audio Demo");
	g_startTime = clock();

	glutMainLoop();
	
	return 0;
}