
#include <GL/glut.h>
#include <stdlib.h>

// Definitions //

/* For the camera, remember the previous weeks assigments */
#define y_min 30
#define ro_min 200

int rotate = 0;

float eyeX = 0;
float eyeY = y_min;
float eyeZ = ro_min;

/* Angulos */
float angMercurio = 0;
float angVenus = 1;
float angTerra = 2;
float angLua = 3;
float angMarte = 4;
float angJupiter = 5;

/* Raios */
#define rSol ( 12.0f )
#define rLua ( rSol / 10 )
#define rPadrao ( rSol / 4 ) // Padrão 
#define rMercurio ( rPadrao )
#define rVenus ( rPadrao )
#define rTerra ( rPadrao )
#define rMarte ( rPadrao )
#define rJupiter ( rPadrao )

/* Distancia */
#define dPadrao ( 20 )

#define dSol ( 0 )

#define dMercurio ( dSol + ( dPadrao ))
#define dVenus ( dSol + ( dPadrao * 2 ))
#define dTerra ( dSol + ( dPadrao * 3 ))
#define dLua ( 8 )
#define dMarte ( dSol + ( dPadrao * 4 ))
#define dJupiter ( dSol + ( dPadrao * 5 ))

/* Velocidade */
float vMercurio = 3.0f;
float vVenus = 2.8f;
float vTerra = 2.3f;
float vLua = 10.0f;
float vMarte = 2.5f;
float vJupiter = 2.0f;

// Método de inserção de planetas genericamente
void push_planeta( float raio, float angulo, float distancia, float r, float g, float b ){
	float matSpecular[] = {1.f, 1.f, 1.f, 1.f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128);

	glPushMatrix();
	glColor3f( r, g ,b );
	glRotatef( angulo, 0.0f, 1.0f, 0.0f );
	glTranslatef( distancia, 0.0f, 0.0f );
	
	glNormal3f(1.f, 0.f, 0.f);
	glutSolidSphere( raio, 30, 17 );
}


// Método que incrementa valor ao angulo diretamente na memória
void incrementAngle(float *angle, float value){
	 	*angle += value;
	 	if ( *angle >= 360 )
            angle = 0;
}

// Planet Draws //
/* Sol */
void drawSol(){
	glColor3f( 1, 1, 0 );
	glutSolidSphere( rSol, 30, 17 );
}

/* Mercúrio */
void drawMercurio(){
	push_planeta( rMercurio, angMercurio, dMercurio, 1.0f, 0, 0 );
	glPopMatrix();
}

/* Venus */
void drawVenus(){
	push_planeta( rVenus, angVenus, dVenus, 0.8f, 0.4f, 0.2f );
	glPopMatrix();
}

/* Terra */
void drawTerra(){
	push_planeta( rTerra, angTerra, dTerra, 0.2f, 0.2f, 1.0f );
		push_planeta( rLua, angLua, dLua, 0.5f, 0.5f, 0.5f );
		glPopMatrix();
	glPopMatrix();
}

/* Marte */
void drawMarte(){
	push_planeta( rMarte, angMarte, dMarte, 0.6f, 0, 0 );
	glPopMatrix();
}

/* Jupiter */
void drawJupiter(){
	push_planeta( rJupiter, angJupiter, dJupiter, 0.5f, 0, 0 );
		push_planeta( rLua, angLua, dLua, 0.5f, 0.5f, 0.5f );
		glPopMatrix();
	glPopMatrix();
}

/* GLUT callback Handlers */

static void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glLoadIdentity();
	
	gluLookAt( eyeX, eyeY, eyeZ, 0, 0, 0, 0, 1, 0 );
	
	// Draw planetary system
	glPushMatrix();
 	  drawSol();
	  drawMercurio();
	  drawVenus();
	  drawTerra();
	  drawMarte();
	  drawJupiter();

    glPopMatrix();
	
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y){
    switch (key){
        case 27 : 
        case 'q':
            exit(0);
            break;
        case 'w':
            rotate = 1;
            break;
    }

    glutPostRedisplay();
}

void TimerFunction( int value ){
	if (rotate != 0) {
        incrementAngle( &angMercurio, vMercurio);
        incrementAngle( &angVenus, vVenus);
        incrementAngle( &angLua, vLua);
        incrementAngle( &angTerra, vTerra);
        incrementAngle( &angMarte, vMarte);
        incrementAngle( &angJupiter, vJupiter);
    }
    glutPostRedisplay();  glColor3d(1,0,0);
    glutTimerFunc( 33, TimerFunction, 1 );
}

void resize(int w, int h){
	GLfloat fAspect;
	
	if (h == 0) h = 1; 			// Evita divisão por zero
		
  glViewport(0, 0, w, h); // Define viewport para dimensões da janela
	fAspect = (GLfloat)w/(GLfloat)h; 	// Relação de aspecto da janela
	glMatrixMode(GL_PROJECTION); 			// Ponto de vista do sistema de coordenadas
	glLoadIdentity();
	gluPerspective(60.0f, fAspect, 1.0, 1600.0); // Campo de visão d 45 graus
	glMatrixMode(GL_MODELVIEW); 			// Redefinição da matriz
	glLoadIdentity();
}

/* Program entry point */

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Sistema solar");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutTimerFunc(250, TimerFunction, 1);

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glClearColor( 0, 0, 0, 1 );
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	float glGlobalAmb[] = {0.5f, 0.5f, 0.5f, 1.f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glGlobalAmb);

	float light0[4][4] = {
		{0.1f, 0.1f, 0.1f, 1.f},
		{0.8f, 0.8f, 0.8f, 1.f},
		{1.f, 1.f, 1.f, 1.f},
		{0.f, 0.f, 1.f, 1.f}
	};

	glLightfv(GL_LIGHT0, GL_AMBIENT, &light0[0][0]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &light0[1][0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &light0[2][0]);
	glLightfv(GL_LIGHT0, GL_POSITION, &light0[3][0]);

    glutMainLoop();

    return 0;
}