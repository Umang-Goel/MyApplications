#include <iostream>
#include<stdio.h>
#include <cmath>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include <stdarg.h>
#include<time.h>
#include<AL/al.h>
#include<AL/alc.h>
#include<AL/alut.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define empty 1000.0f
#define laser_vel 0.17f
#define maxlaser 10
#define floor_len 100
#define LEN 8192
#define x_fact 718
#define y_fact 720
#define cen_x 651
#define cen_y 373
#define BACK 0
#define FIRE 1
#define INTRO 2
#define SPIDER 3
#define END 4
#define NUM_BUFFERS 5
#define NUM_SOURCES 5

int w;
int h;
float prev_x;
float xcord[10];
float ycord[10];
float vel[10];
int color[10];
int curr;
int floor_ct = 0;
int stop = 0;
int lpressed = 0;
int rpressed = 0;
int fl = 0;
float box_len=4.0f;
float box_hgt=4.0f;
float rad;
float floor_sp[2][floor_len];
int toggle=1;
float basket_len;	//=box_len*0.12;
float rbasket_x;	//= -box_len/2;
float gbasket_x;	//=box_len/2 - basket_len;
float basket_y;		//=box_hgt*0.15;
float canon_len;	//=box_len*0.1;
float canon_x;		//=-canon_len/2;
float canon_y;		//=canon_len*0.9f;
float canon_lower;	// = -box_len/2;
float canon_upper;	// = box_len/2 - canon_len*0.2;
float laser_len;	//= box_hgt*0.1;
float lasers_x[maxlaser];
float lasers_y[maxlaser];
float angles[maxlaser];
float l_angle;
float r_upper;
float r_lower;
float g_upper;
float g_lower;
unsigned char selected='b';
int score=0;
float angle=0.0;
float timer=1.1f;
int mousex;
int mousey;
float x_pres;
int min_sp_vel;
int max_sp_vel;
int difficulty;
int maxlen;
double a,b;

void drawScene();
void update(int value);
void update2(int value);
void drawBox(float len, float hgt);
void drawBaseRect();
void drawBall();
void drawBasket(float a,float b,float x,float y,int flag);
void drawCanon(int fl);
void drawLaser();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void windowMouse(int button, int state, int x, int y);
void windowPmotion(int x,int y);
void generate_spider();
void draw_spider(float rad);
float mini(float x,float y);
void CheckReflection(int x);
void CheckCollision(int x);
void printv(va_list args, const char* format);
void print(const char* format, ...);
void printAt(int x, int y, const char* format, ...);
void errCheck(char* where);
void drag(int x,int y);
void get_cord(int x,int y);
//void output(int x, int y, float r, float g, float b, int score);//, char *string)

// Buffers hold sound data.
ALuint Buffers[NUM_BUFFERS];

// Sources are points of emitting sound.
ALuint Sources[NUM_SOURCES];

// Position of the source sounds.
ALfloat SourcesPos[NUM_SOURCES][3];

// Velocity of the source sounds.
ALfloat SourcesVel[NUM_SOURCES][3];


// Position of the listener.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// Velocity of the listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

ALboolean LoadALData()
{
	// Variables to load into.

	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	// Load wav data into buffers.

	alGenBuffers(NUM_BUFFERS, Buffers);

	if (alGetError() != AL_NO_ERROR)
	{
		return AL_FALSE;
	}

	alutLoadWAVFile((ALbyte*)"background.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[BACK], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile((ALbyte*)"intro.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[INTRO], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile((ALbyte*)"fire.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[FIRE], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile((ALbyte*)"killing.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[SPIDER], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile((ALbyte*)"end.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[END], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	// Bind buffers into audio sources.

	alGenSources(NUM_SOURCES, Sources);

	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alSourcei (Sources[BACK], AL_BUFFER,   Buffers[BACK]  );
	alSourcef (Sources[BACK], AL_PITCH,    1.0              );
	alSourcef (Sources[BACK], AL_GAIN,     1.0              );
	alSourcefv(Sources[BACK], AL_POSITION, SourcesPos[BACK]);
	alSourcefv(Sources[BACK], AL_VELOCITY, SourcesVel[BACK]);
	alSourcei (Sources[BACK], AL_LOOPING,  AL_TRUE          );

	alSourcei (Sources[INTRO], AL_BUFFER,   Buffers[INTRO]  );
	alSourcef (Sources[INTRO], AL_PITCH,    1.0            );
	alSourcef (Sources[INTRO], AL_GAIN,     1.0            );
	alSourcefv(Sources[INTRO], AL_POSITION, SourcesPos[INTRO]);
	alSourcefv(Sources[INTRO], AL_VELOCITY, SourcesVel[INTRO]);
	alSourcei (Sources[INTRO], AL_LOOPING,  AL_FALSE       );

	alSourcei (Sources[SPIDER], AL_BUFFER,   Buffers[SPIDER]  );
	alSourcef (Sources[SPIDER], AL_PITCH,    1.0            );
	alSourcef (Sources[SPIDER], AL_GAIN,     1.0            );
	alSourcefv(Sources[SPIDER], AL_POSITION, SourcesPos[SPIDER]);
	alSourcefv(Sources[SPIDER], AL_VELOCITY, SourcesVel[SPIDER]);
	alSourcei (Sources[SPIDER], AL_LOOPING,  AL_FALSE       );

	alSourcei (Sources[END], AL_BUFFER,   Buffers[END]  );
	alSourcef (Sources[END], AL_PITCH,    1.0            );
	alSourcef (Sources[END], AL_GAIN,     1.0            );
	alSourcefv(Sources[END], AL_POSITION, SourcesPos[END]);
	alSourcefv(Sources[END], AL_VELOCITY, SourcesVel[END]);
	alSourcei (Sources[END], AL_LOOPING,  AL_FALSE       );

	alSourcei (Sources[FIRE], AL_BUFFER,   Buffers[FIRE]  );
	alSourcef (Sources[FIRE], AL_PITCH,    1.0            );
	alSourcef (Sources[FIRE], AL_GAIN,     1.0            );
	alSourcefv(Sources[FIRE], AL_POSITION, SourcesPos[FIRE]);
	alSourcefv(Sources[FIRE], AL_VELOCITY, SourcesVel[FIRE]);
	alSourcei (Sources[FIRE], AL_LOOPING,  AL_FALSE       );
	// Do another error check and return.

	if( alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	return AL_TRUE;
}

void SetListenerValues()
{
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

void KillALData()
{
	alDeleteBuffers(NUM_BUFFERS, &Buffers[0]);
	alDeleteSources(NUM_SOURCES, &Sources[0]);
	alutExit();
}



//alSourcefv(Sources[BACK], AL_POSITION, SourcesPos[BACK]);
//alSourcePlay(Sources[BACK]);


int main(int argc, char **argv) {

	// Initialize GLUT

	alutInit(NULL, 0);
	alGetError();
	if (LoadALData() == AL_FALSE)
	{
		return 0;
	}
	SetListenerValues();
	atexit(KillALData);

	alSourcefv(Sources[INTRO], AL_POSITION, SourcesPos[INTRO]);
	alSourcePlay(Sources[INTRO]);

	alSourcefv(Sources[BACK], AL_POSITION, SourcesPos[BACK]);
	alSourcePlay(Sources[BACK]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	w = glutGet(GLUT_SCREEN_WIDTH);
	h = glutGet(GLUT_SCREEN_HEIGHT);
	//	int windowWidth = w * 2 / 3;
	//	int windowHeight = h * 2 / 3;
	int windowWidth = w ;
	int windowHeight = h ;
	int x;
	curr=0;
	if(argc < 4)
	{
		printf("Required more arguments\n");
		return 0;
	}
//	scanf("%f",&box_len);
//		scanf("%f",&box_hgt);
	box_len = atof(argv[1]);
	box_hgt = atof(argv[2]);
//	box_len = 16;box_hgt = 16;
	difficulty = atof(argv[3]);
	if(difficulty > 7)
	{
		printf("difficulty can be from 0-7\n");
		return 0;
	}
	min_sp_vel = (difficulty - 3)/2 ;
	min_sp_vel = (min_sp_vel <= 0)?1:min_sp_vel;
	max_sp_vel = difficulty / 2 + difficulty % 2;
	max_sp_vel = (max_sp_vel == 0)?1:max_sp_vel;
	maxlen = difficulty;
	if(maxlen == 0 )
		maxlen = 1;

	if(box_len<10 || box_hgt<10)
	{
		box_len=((box_len<10)?10:box_len);
		box_hgt=((box_hgt<10)?10:box_hgt);
		printf("Minimum width & height can be 10\n");
	}
	if(box_len>20 || box_hgt>16)
	{
		box_len=((box_len>20)?20:box_len);
		box_hgt=((box_hgt>16)?16:box_hgt);
	}
	box_len /= 4;
	box_hgt /= 4;
	rad = 0.0375f*mini(box_hgt,box_len);
	rad *= 0.8;
	printf("box_len/2 %f\n",box_len/2);

	for(x=0;x<maxlen;x++)
	{
		xcord[x]=empty;ycord[x]=empty;vel[x]=empty;
	}
	for(x=0;x<floor_len;x++)
		floor_sp[0][x] = empty;
	for(x=0;x<maxlen;x++)
	{
		generate_spider();
		curr++;
		//xcord[x]=empty;ycord[x]=empty;vel[x]=empty;
	}

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("Catch Me If U Can");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(windowMouse);
	glutPassiveMotionFunc(windowPmotion);
	glutMotionFunc(drag);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);

	glutMainLoop();
	return 0;
}

void initRendering() {
	toggle=1;
	basket_len=box_len*0.12;
	rbasket_x= -box_len/2;
	gbasket_x=box_len/2 - basket_len;
	basket_y=box_hgt*0.12;
	canon_len=box_len*0.1;
	canon_x=-canon_len/2;
	canon_y=canon_len*0.9f;
	canon_lower = -box_len/2;
	canon_upper = box_len/2 ;
	r_lower = -box_len/2;
	r_upper = box_len/2; 
	g_lower = -box_len/2;
	g_upper = box_len/2 ;
	laser_len = box_hgt*0.1;
	int x;
	//timer = 1.1f;
	for(x=0;x<maxlaser;x++)
		lasers_x[x]=empty;
	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   // Setting a background color
}

void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	int x,flag;

	//drawing the world
	glTranslatef(0.0f, 0.0f, -5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	drawBox(box_len,box_hgt);

	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glEnd();
	glPopMatrix();
	//drawing Base Reactangle
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	drawBaseRect();
	glPopMatrix();

	if(stop == 1)
		printAt(w/2,h/2,"Game Over");
	printAt(3*w/4,3*h/4,"Score : \n %d\n",score);
	printAt(0,0,"A %lf B %lf",a,b);


	//drawin/g Spiders
	for(x=0;x<maxlen;x++)
	{
		if(xcord[x] == empty)
			continue;
		glPushMatrix();
		glTranslatef( xcord[x], ycord[x], 0.0f);
		if( color[x]==0 )
			glColor3f(1.0f, 0.0f, 0.0f);	//color[x]=0 ==>  'Red' & color[x]=1 ==>  'Green'
		else if( color[x]==1 )
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(0.0f, 0.0f, 0.0f);
		draw_spider(rad);	//Spider Currently as Circles
		glPopMatrix();
	}

	for(x=0;x<floor_len;x++)
	{
		if(floor_sp[0][x] == empty)
			continue;
		glPushMatrix();
		glTranslatef( floor_sp[0][x], -box_len/2 + rad/0.8, 0.0f);
		if( int(floor_sp[1][x]) == 0 )
			glColor3f(1.0f, 0.0f, 0.0f);	//color[x]=0 ==>  'Red' & color[x]=1 ==>  'Green'
		else if( int(floor_sp[1][x]) ==1 )
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(0.0f, 0.0f, 0.0f);
		draw_spider(rad);	//Spider Currently as Circles
		glPopMatrix();
	}

	//Basket1 (Red)
	glPushMatrix();
	if(selected == 'r')
	{
		//	glColor3f(0.0f,0.0f,0.0f);
		flag=1;
	}
	else
	{
		flag=0;
	}
	glColor3f(1.0,0.0,0.0);
	drawBasket(rbasket_x, basket_y, basket_len, box_len,flag);		
	glPopMatrix();

	//Basket 2 (Green)
	glPushMatrix();
	if(selected == 'g')
	{
		//	glColor3f(0.0f,0.0f,0.0f);
		flag=1;
	}
	else
	{
		flag=0;
	}
	glColor3f(0.0f,1.0f,0.0f);
	drawBasket(gbasket_x, basket_y, basket_len, box_len,flag);
	glPopMatrix();

	//Cannon
	glPushMatrix();
	if(selected == 'b')
	{
		//	glColor3f(0.0f,0.0f,0.0f);
		flag=1;
	}
	//		glTranslatef(canon_x+canon_len/2,-box_hgt/2+canon_y*0.75,0.0f);
	//		glRotatef(angle,0.0f,0.0f,1.0f);
	//		drawCanon(1);
	else
	{
		flag =0;
	}
	glColor3f(0.0f,0.0f,1.0f);
	glTranslatef(canon_x+canon_len/2,-box_hgt/2+canon_y*0.75,0.0f);
	glRotatef(angle,0.0f,0.0f,1.0f);
	drawCanon(flag);
	glPopMatrix();



	//Laser
	//	if(l_pres == 1)
	for(x=0;x<maxlaser;x++)
	{
		if(lasers_x[x]!=empty)
		{
			glLineWidth(3.0);
			glPushMatrix();
			glColor3f(1.0f,0.0f,0.0f);
			glTranslatef(lasers_x[x],lasers_y[x],0.0f);
			glRotatef(angles[x],0.0f,0.0f,1.0f);
			drawLaser();
			glPopMatrix();
			glLineWidth(1.0);
		}
	}
	glPopMatrix();
	glutSwapBuffers();
}

void drawBasket(float basket_x,float basket_y,float len,float box_len,int flag)
{
	if(flag == 0)
	{
		glLineWidth(3.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	glBegin(GL_QUADS);
	glVertex3f(basket_x,-box_hgt/2 + 0.02*box_hgt,0.0f);	
	glVertex3f(basket_x+len,-box_hgt/2 + 0.02*box_hgt,0.0f);
	glVertex3f(basket_x+len,-box_hgt/2+basket_y + 0.02*box_hgt,0.0f);
	glVertex3f(basket_x,-box_hgt/2+basket_y + 0.02*box_hgt,0.0f);
	glEnd();
	float radi = basket_len/2;
	glTranslatef(basket_x+len/2,-box_hgt/2 + basket_y + 0.02*box_hgt,0.0f);
	if(flag == 1)
		glColor3f(0.0,0.0,1.0);
	glRotatef(80,1.0,0.0,0.0);
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(radi * cos(DEG2RAD(i)), radi * sin(DEG2RAD(i)));
	}
	glEnd();
	if(flag == 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1.0);
	}
}

void drawCanon(int flag)
{
	float  len = 0.8*canon_len;
	float hgt = 0.7*canon_y;
	//	glBegin(GL_QUADS);
	if(flag==0)
	{
		glLineWidth(3.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	glBegin(GL_QUADS);
	glVertex3f(-len/2,0.0,0.0);
	glVertex3f(len/2,0.0,0.0);
	glVertex3f(len/2,hgt,0.0);
	glVertex3f(-len/2,hgt,0.0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-0.15*len,hgt,0.0);
	glVertex3f(0.15*len,hgt,0.0);
	if(timer >= 1.0f)
		glColor3f(1.0,0.0,0.0);
	glVertex3f(0.15*len,1.1*canon_y,0.0);
	glVertex3f(-0.15*len,1.1*canon_y,0.0);
	glEnd();
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex3f(-len/2,hgt/2,0.0);
	glVertex3f(-len/2-0.05*len,hgt/2,0.0);
	glVertex3f(len/2,hgt/2,0.0);
	glVertex3f(len/2+0.05*len,hgt/2,0.0);
	glEnd();
	glLineWidth(1.0);
	glBegin(GL_QUADS);
	glVertex3f(len/2+0.05*len,0.0,0.0);
	glVertex3f(len/2+0.05*len,canon_y,0.0);
	glVertex3f(len/2+0.05*len+0.05*len,canon_y,0.0);
	glVertex3f(len/2+0.05*len+0.05*len,0.0,0.0);
	glVertex3f(-len/2-0.05*len,0.0,0.0);
	glVertex3f(-len/2-0.05*len,canon_y,0.0);
	glVertex3f(-len/2-0.05*len-0.05*len,canon_y,0.0);
	glVertex3f(-len/2-0.05*len-0.05*len,0.0,0.0);
	glEnd();
	if(flag==0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1.0);
	}
}

void drawLaser()
{
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,laser_len,0.0f);
	glEnd();
}

void drawBaseRect()
{
	glBegin(GL_LINES);
	glVertex3f(-box_len/2,-box_hgt*0.4,0.0f);
	glVertex3f(box_len/2,-box_hgt*0.4,0.0f);
	glEnd();
}

void update(int value)
{
	int x;int flag,add;
	float d1,d2,d3;
	for(x=0;x<maxlen;x++)
	{
		flag=0;add=1;
		d1 = xcord[x] - canon_x;
		d3 = xcord[x] - gbasket_x;
		d2 = xcord[x] - rbasket_x;
		if( ycord[x] - rad <= -box_hgt/2)
		{
			if( abs(d1) < rad || abs(d1 - canon_len) < rad || (xcord[x]<canon_x+canon_len && xcord[x]>canon_x))
			{
				add = 0;
			}
			if(add ==1 && (abs(d2) < rad || abs(d2 - basket_len) < rad || (xcord[x]<rbasket_x+basket_len && xcord[x]>rbasket_x) ) )
				add = 0;
			if(add ==1 && (abs(d3) < rad || abs(d3 - basket_len) < rad || (xcord[x]<gbasket_x+basket_len && xcord[x]>gbasket_x) ) )
				add = 0;
		}
		if( ycord[x] - rad <= -box_hgt/2 && add == 1)
		{
			if(xcord[x] +rad > canon_lower && xcord[x] + rad< canon_x )
				canon_lower = xcord[x] + rad;
			if(xcord[x] -rad < canon_upper && xcord[x] - rad > canon_x+canon_len )
				canon_upper = xcord[x] - rad;
			if(xcord[x] +rad > r_lower && xcord[x] +rad < rbasket_x)
				r_lower = xcord[x] + rad;
			if(xcord[x] -rad < r_upper && xcord[x] - rad > rbasket_x+basket_len)
				r_upper = xcord[x] - rad;
			if(xcord[x] +rad> g_lower && xcord[x] + rad < gbasket_x)
				g_lower = xcord[x] + rad;
			if(xcord[x] -rad < g_upper && xcord[x] - rad > gbasket_x+basket_len)
				g_upper = xcord[x] -rad;
		}
		if(canon_x < canon_lower)
			canon_x = canon_lower ;
		if(canon_x + canon_len > canon_upper)
			canon_x = canon_upper -canon_len;
		if(rbasket_x < r_lower)
			rbasket_x = r_lower ;
		if(rbasket_x + basket_len >= r_upper)
			rbasket_x = r_upper -basket_len;
		if(gbasket_x < g_lower)
			gbasket_x = g_lower ;
		if(gbasket_x + basket_len > g_upper)
			gbasket_x = g_upper -basket_len;

		if( (abs(d1) < rad/2 || abs(d1 - canon_len) < rad/2 || (xcord[x]<canon_x+canon_len && xcord[x]>canon_x)) && (ycord[x] - rad <= -box_hgt/2+canon_y) )
		{
			alSourcefv(Sources[END], AL_POSITION, SourcesPos[END]);
			alSourcePlay(Sources[END]);

			stop = 1;
		}

		if( (xcord[x] + rad <= rbasket_x + basket_len + basket_len*0.1) && (xcord[x] -rad >= rbasket_x -basket_len*0.1) && (ycord[x] -rad >= -box_hgt/2 + basket_y/2 +0.02*box_hgt) && (ycord[x] -rad <= -box_hgt/2 + basket_y + 0.02*box_hgt) )
		{
			flag = 1;
			if(color[x] == 0)
				score++;
			else
				score --;
			//output(box_len/2 + 0.1f,0.0f);
			//			printf("Score %d\n",score);
		}
		else if( (xcord[x] + rad <= gbasket_x + basket_len +basket_len*0.1) && (xcord[x] -rad >= gbasket_x - basket_len*0.1) && (ycord[x] -rad >= -box_hgt/2 + basket_y/2 + 0.02*box_hgt) && (ycord[x] -rad <= -box_hgt/2 + basket_y + 0.02*box_hgt))
		{
			flag = 1;
			if(color[x] == 1)
				score++;
			else
				score --;
			//			printf("a\n");
		}
		if(flag==1)
		{
			xcord[x]=empty;
			curr--;
		}
		if(ycord[x] <= -box_len/2 && xcord[x]!=empty)
		{
			int y;
			if(add == 1 && floor_ct < floor_len)
			{
				for(y=0;y<floor_len && floor_sp[0][y]!=empty;y++);
				floor_sp[0][y] = xcord[x];
				floor_sp[1][y] = color[x];
				floor_ct ++;
				if(floor_ct == floor_len)
					stop = 1;
				score -= 5;
			}
			xcord[x] = empty;
			curr--;
		}
	}

	while(curr<maxlen)
	{
		generate_spider();
		curr++;
	}

	for(x=0;x<maxlen;x++)
	{
		ycord[x] -= vel[x];
	}

	int sign;float laser_x,laser_y;
	for(x=0;x<maxlaser;x++)
	{
		if(lasers_x[x]!=empty)
		{
			laser_x = lasers_x[x];
			laser_y = lasers_y[x];
			l_angle = angles[x];
			if(laser_x <= -box_len/2 || laser_x >= box_len/2 || laser_y >= box_hgt/2)
				laser_x=empty; //l_pres=0;

			sign=(l_angle>0)?-1:1;
			if(laser_x != empty)
			{
				laser_y += abs(laser_vel*cos(DEG2RAD(abs(l_angle))));
				laser_x += ( sign*laser_vel*sin(DEG2RAD(abs(l_angle))) );
			}
			lasers_x[x] = laser_x;
			lasers_y[x] = laser_y;
			if(laser_x != empty)
			{
				CheckReflection(x);
				CheckCollision(x);
			}
		}
	}

	timer += 0.02;
	if(toggle==1 && stop == 0)
		glutTimerFunc(10, update, 0);
	else
		glutTimerFunc(10, update2, 0);
}

void CheckReflection(int pos)
{
	float laser_x = lasers_x[pos];
	float laser_y = lasers_y[pos];
	float l_angle = angles[pos];
	int sign=(l_angle>0)?-1:1;
	float x= laser_x + laser_len*sign*sin(DEG2RAD(abs(l_angle)));
	if(x <= -box_len/2 || x>= box_len/2)
	{
		laser_x += ( laser_len*sign*sin(DEG2RAD(abs(l_angle))) );
		laser_y += laser_len*abs(cos(DEG2RAD(abs(l_angle))));
		if(laser_x >= box_len/2)
			laser_x = box_len/2;
		if(laser_x <= -box_len/2)
			laser_x = -box_len/2;
		laser_x += (0.01*sign*-1);
		l_angle *= -1;
	}
	angles[pos] = l_angle;
	lasers_x[pos] = laser_x;
	lasers_y[pos] = laser_y;
}

void CheckCollision(int pos)
{
	float laser_x = lasers_x[pos];
	float laser_y = lasers_y[pos];
	float xlaser,ylaser,tmp;
	int sign=(l_angle>0)?-1:1;int x;
	xlaser = laser_x + laser_len*sign*sin(DEG2RAD(abs(l_angle)));
	ylaser = laser_y + laser_len*cos(DEG2RAD(abs(l_angle)));
	for(x=0;x<maxlen;x++)
	{
		tmp=(xlaser-xcord[x])*(xlaser-xcord[x]) + (ylaser - ycord[x])*(ylaser - ycord[x]);
		tmp=sqrt(tmp);
		if(tmp < rad)
		{
			alSourcefv(Sources[SPIDER], AL_POSITION, SourcesPos[SPIDER]);
			alSourcePlay(Sources[SPIDER]);

			lasers_x[pos] = empty;
			xcord[x]=empty;
			curr --;
			if(color[x] == 2)
				score++;
		}
	}
}	 

void update2(int value)
{
	if(toggle==1 && stop == 0)
		glutTimerFunc(10, update, 0);
	else
		glutTimerFunc(10, update2, 0);
}


void generate_spider()
{

	int x,tmpx,tmpv,blen,sign,y,ct;
	float min;
	blen=(int)(box_len/2);
	blen *= 10;
	//	printf("blen %d \n",blen);
	for(x=0;x<maxlen && xcord[x]!=empty;x++);
	if(max_sp_vel == min_sp_vel)
		tmpv = 1;
	else
		tmpv=rand()%3 + min_sp_vel;
	vel[x]=1.0f*tmpv;
	vel[x] /= (100*8/box_hgt);
	ycord[x] = box_hgt/2 -rad;	
	color[x] = rand()%3;
	ct=0;
	while(1)
	{
		ct++;
		tmpx=rand()%blen +1;
		xcord[x]=(1.0f*tmpx)/10;
		xcord[x] -= rad;
		sign=rand()%2;
		xcord[x]=xcord[x]*((sign==1)?1:-1);
		for(y=0;y<maxlen;y++)
		{
			if(xcord[x]!=empty && y!=x && abs(xcord[x]-xcord[y])<=2*rad)
			{
				min=mini(vel[x],vel[y]);
				break;
			}
		}
		if(ct==100 && y!=maxlen)
		{
			vel[x] = min -0.00001f;
		}

		if(y==maxlen || ct==100)
			break;
	}
}

void draw_spider(float rad) {
	float x = sin(DEG2RAD(150))*1.5*rad;
	float y = cos(DEG2RAD(150))*1.5*rad;
	float x1 = sin(DEG2RAD(30))*0.6*rad;
	float y1 = cos(DEG2RAD(30))*0.6*rad;
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
	glLineWidth(2.5f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(x,y,0.0f);
	glVertex3f(x,y-0.3*rad,0.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(-x,y,0.0f);
	glVertex3f(-x,y-0.3*rad,0.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(x,-y,0.0f);
	glVertex3f(x,-y+0.3*rad,0.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(-x,-y,0.0f);
	glVertex3f(-x,-y+0.3*rad,0.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,0.1*rad,0.0f);
	glVertex3f(1.5*rad,0.2*rad,0.0f);
	glVertex3f(1.5*rad+x1,0.2*rad+y1,0.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,0.2*rad,0.0f);
	glVertex3f(-1.5*rad,0.2*rad,0.0f);
	glVertex3f(-1.5*rad-x1,0.2*rad+y1,0.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,-0.2*rad,0.0f);
	glVertex3f(1.5*rad,-0.2*rad,0.0f);
	glVertex3f(1.5*rad+x1,-0.2*rad-y1,0.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,-0.2*rad,0.0f);
	glVertex3f(-1.5*rad,-0.2*rad,0.0f);
	glVertex3f(-1.5*rad-x1,-0.2*rad-y1,0.0f);
	glEnd();
	glLineWidth(1.0f);
}

void drawBox(float len, float hgt) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2f(-len / 2, -hgt / 2);
	glVertex2f(len / 2, -hgt / 2);
	glVertex2f(len / 2, hgt / 2);
	glVertex2f(-len / 2, hgt / 2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void printv(va_list args, const char* format)
{
	char buf[LEN];
	char* ch=buf;
	vsnprintf(buf,LEN,format,args);
	while (*ch)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void print(const char* format, ...)
{
	va_list args;
	va_start(args,format);
	printv(args,format);
	va_end(args);
}

void printAt(int x, int y, const char* format, ...)
{
	va_list args;
	glWindowPos2i(x,y);
	va_start(args,format);
	printv(args,format);
	va_end(args);
}

/*
 *  Convenience method to print out OpenGL errors to stderr
 */
void errCheck(char* where)
{
	int err = glGetError();
	if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27 || key=='q') {
		exit(0);     // escape key is pressed
	}
	if( key == 'p')		//toggle = 1 ==> Play  & toggle = 0 ==> Pause
	{
		toggle=1-toggle;
	}
	if( (toggle == 1 && stop == 0) && (key == 'r' || key == 'g' || key == 'b') )
	{
		selected=key;
	}
	if((toggle == 1 && stop == 0) &&  key == ' ' && selected == 'b' && timer >= 1.0f)
	{
		for(x=0;x<maxlaser && lasers_x[x]!=empty;x++);
		if(x<maxlaser)
		{
			alSourcefv(Sources[FIRE], AL_POSITION, SourcesPos[FIRE]);
			alSourcePlay(Sources[FIRE]);

			lasers_x[x] = canon_x+canon_len/2;
			lasers_y[x] = -box_hgt/2+canon_y*0.75;
			//		l_pres=1;
			angles[x] = angle;
			timer = 0.0f;
		}
	}
}

void handleKeypress2(int key, int x, int y) {
	float basket_x,upper_lim,lower_lim,sel_len;
	float speed=0.025*box_len;
	if( toggle == 1 && stop == 0)
	{
		if(selected == 'r')
		{
			basket_x = rbasket_x;
			upper_lim = r_upper;
			lower_lim = r_lower;
			sel_len = basket_len;
		}
		else if(selected == 'g')
		{
			basket_x = gbasket_x;
			upper_lim = g_upper;
			lower_lim = g_lower;
			sel_len = basket_len;
		}
		else if(selected == 'b')
		{
			basket_x = canon_x;
			upper_lim = canon_upper;
			lower_lim = canon_lower;
			sel_len = canon_len;
		}

		if (key == GLUT_KEY_LEFT)
		{
			if(basket_x - speed >= lower_lim)
				basket_x -= speed;
			else
				basket_x = lower_lim;
		}

		if (key == GLUT_KEY_RIGHT)
		{
			if(basket_x + speed + sel_len <= upper_lim)
				basket_x += speed;
			else
				basket_x = upper_lim - sel_len;
		}

		if(selected == 'r')
			rbasket_x = basket_x;
		else if(selected == 'g')
			gbasket_x = basket_x;
		else if(selected == 'b')
			canon_x = basket_x;

		if (key == GLUT_KEY_UP && selected=='b')
			angle += 10.0;
		if (key == GLUT_KEY_DOWN && selected=='b')
			angle -= 10.0;
		if(angle > 75)
			angle = 75;
		if(angle < -75)
			angle = -75;
	}
}

void windowMouse(int btn, int state, int x, int y)
{
	double pres_x,pres_y;
	//	if (pressed ==0 && btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//	pres_x = ((x-cen_x)*box_len)/x_fact;
//	pres_y = ((-y+cen_y)*box_hgt)/y_fact;
	get_cord(x,y);
	pres_x = a;
	pres_y = -b;

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && toggle == 1 && stop == 0)
	{
		lpressed = 1;
		if((pres_x >= rbasket_x - 0.1*basket_len && pres_x <= rbasket_x + 1.1*basket_len) && (pres_y<=-box_hgt/2+basket_y+0.02*box_hgt+0.2*basket_y && pres_y>=-box_hgt/2+0.02*box_hgt - 0.1*basket_y))
		{
			selected = 'r';fl = 1;
		}
		if((pres_x >= gbasket_x - 0.1*basket_len && pres_x <= gbasket_x + 1.1*basket_len) && (pres_y<=-box_hgt/2+basket_y+0.02*box_hgt+0.2*basket_y && pres_y>=-box_hgt/2+0.02*box_hgt - 0.1*basket_y))
		{
			selected = 'g';fl = 1;
		}
		if((pres_x >= canon_x - 0.1*canon_len && pres_x <= canon_x + 1.1*canon_len) && (pres_y<=-box_hgt/2+canon_y+0.02*box_hgt+0.2*canon_y && pres_y>=-box_hgt/2+0.02*box_hgt - 0.1*canon_y))
		{
			selected = 'b';fl = 1;
		}
	}
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP && toggle == 1 && stop == 0)
	{
		lpressed = 0;fl = 0;
	}

	if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && toggle == 1 && stop == 0)
	{
		if((pres_x >= canon_x - 0.1*canon_len && pres_x <= canon_x + 1.1*canon_len) && (pres_y<=-box_hgt/2+canon_y+0.02*box_hgt+0.2*canon_y && pres_y>=-box_hgt/2+0.02*box_hgt - 0.1*canon_y))
		{
			selected = 'b';rpressed = 1;
			prev_x = x;
		}
	}
	if(btn == GLUT_RIGHT_BUTTON && state == GLUT_UP && toggle == 1 && stop == 0)
		rpressed = 0;
	glutPostRedisplay();

}

void get_cord(int x,int y)
{
	double c; 
	glPushMatrix(); 
	glLoadIdentity(); 
	glTranslatef(0.0f, 0.0f, -5.0f); 
	GLdouble modelMatrix[16]; 
	glGetDoublev(GL_MODELVIEW_MATRIX,modelMatrix); 
	GLdouble projMatrix[16]; 
	glGetDoublev(GL_PROJECTION_MATRIX,projMatrix); 
	int viewport[4]; 
	glGetIntegerv(GL_VIEWPORT,viewport); 
	gluUnProject( x, y, 0, modelMatrix, projMatrix, viewport, &a, &b, &c ); 
	glPopMatrix();
	a *= 50;
	b *= 50;
}

void windowPmotion(int x, int y)
{
	mousex = x;
	mousey = y;
	glutPostRedisplay();
}

void drag(int x,int y)
{
	double basket_x,upper_lim,lower_lim,sel_len,pres_x,dif;
	get_cord(x,y);
	pres_x = a;

	if(lpressed == 1 && fl == 1 && toggle == 1 && stop == 0)
	{
		pres_x = ((x-cen_x)*box_len)/x_fact;
		if(selected == 'r')
		{
			upper_lim = r_upper;
			lower_lim = r_lower;
			sel_len = basket_len;
		}
		else if(selected == 'g')
		{
			upper_lim = g_upper;
			lower_lim = g_lower;
			sel_len = basket_len;
		}
		else if(selected == 'b')
		{
			upper_lim = canon_upper;
			lower_lim = canon_lower;
			sel_len = canon_len;
		}

	//	pres_x = ((x-cen_x)*box_len)/x_fact;

		basket_x =  pres_x;
		if(basket_x < lower_lim )
			basket_x = lower_lim;
		if(basket_x + sel_len >  upper_lim)
			basket_x = upper_lim - sel_len;

		if(selected == 'r')
			rbasket_x = basket_x;
		else if(selected == 'g')
			gbasket_x = basket_x;
		else if(selected == 'b')
			canon_x = basket_x;
	}
	if(rpressed == 1 && toggle == 1 && stop == 0)
	{
		dif = (prev_x-x)/2;
		angle += dif;
		if(angle <= -75 )
			angle = -75;
		if(angle >= 75)
			angle = 75;
		prev_x = x;
	}

	glutPostRedisplay();
}
float abs(float x){
	return ((x>=0.0f)?x:-x);
}

float mini(float x,float y){
	return ((x<y)?x:y);
}
