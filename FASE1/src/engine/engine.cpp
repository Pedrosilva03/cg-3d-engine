#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float cameraPosX = 5.0f;
float cameraPosY = 5.0f;
float cameraPosZ = 5.0f;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawCylinder(float radius, float height, int slices) {
	float angle;
	float x, y, z;
	float angleIncrement = (2 * M_PI) / slices;

	// Draw the upper circle
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, height * 0.5f, 0.0f);  // Center of the circle
	for (int i = 0; i <= slices; ++i) {
		angle = i * angleIncrement;
		x = radius * cos(angle);
		z = radius * sin(angle);
		glVertex3f(x, height * 0.5f, z);
	}
	glEnd();

	// Draw the lower circle
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, -height * 0.5f, 0.0f);  // Center of the circle
	for (int i = slices; i >= 0; --i) {
		angle = i * angleIncrement;
		x = radius * cos(angle);
		z = radius * sin(angle);
		glVertex3f(x, -height * 0.5f, z);
	}
	glEnd();

	// Draw the side faces
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= slices; ++i) {
		angle = i * angleIncrement;
		x = radius * cos(angle);
		z = radius * sin(angle);
		glVertex3f(x, height * 0.5f, z);
		glVertex3f(x, -height * 0.5f, z);
	}
	glEnd();
}


void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, -10.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();

	drawCylinder(1, 2, 10);

	// End of frame
	glutSwapBuffers();
}


void processSpecialKeys(int key, int xx, int yy) {
	// Put code to process special keys here
	switch (key) {
	case GLUT_KEY_UP:
		cameraPosY += 1.0f;
		break;
	case GLUT_KEY_DOWN:
		cameraPosY -= 1.0f;
		break;
	case GLUT_KEY_LEFT:
		cameraPosX -= 1.0f;
		break;
	case GLUT_KEY_RIGHT:
		cameraPosX += 1.0f;
		break;
	}

	// Update the camera position
	gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	// Request redraw
	glutPostRedisplay();
}

void processKeys(unsigned char key, int xx, int yy) {
	// Put code to process regular keys here
	switch (key) {
	case 27: // Escape key
		exit(0);
		break;
	case 'w':
	case 'W':
		cameraPosZ -= 1.0f; // Move the camera forward
		break;
	case 's':
	case 'S':
		cameraPosZ += 1.0f; // Move the camera backward
		break;
	case 'a':
	case 'A':
		cameraPosX -= 1.0f; // Move the camera left (along the x-axis)
		break;
	case 'd':
	case 'D':
		cameraPosX += 1.0f; // Move the camera right (along the x-axis)
		break;
	case 'q':
	case 'Q':
		cameraPosY += 1.0f; // Move the camera up (along the y-axis)
		break;
	case 'z':
	case 'Z':
		cameraPosY -= 1.0f; // Move the camera down (along the y-axis)
		break;
		// Add more cases for other keys if needed
	}

	// Update the camera position
	gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	// Request redraw
	glutPostRedisplay();
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}