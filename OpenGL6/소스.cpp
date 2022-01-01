#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


//원구에 띠무늬 텍스쳐 입히기

GLfloat mat_diffuse[] = { 0.25, 0.25, 1., 0. };  //확산반사에 대한 물체색
GLfloat mat_specular[] = { 1., 1., 1., 0. };      //경면반사에 대한 물체색


GLfloat light_position[] = { 10., 10., 20., 1. };   //광원의 위치
													

GLfloat ref_plane[] = { 1.5, 1.5, 1.5, 0. };   //텍스쳐 기준평면
GLUquadricObj* qobj;                                //물체 포인터
unsigned int MyTextureObject;                       //텍스쳐 객체면

static int SpinAngle = 0;

#define stripeImageWidth    20	
GLubyte stripeImage[5 * stripeImageWidth];          //텍스쳐 배열

void MyStripeImage() {                              //텍스쳐 생성함수

	for (int j = 0; j < stripeImageWidth; j++) {
		stripeImage[5 * j] = 0;
		stripeImage[5 * j + 1] = 255;
		stripeImage[5 * j + 2] = 0;
		stripeImage[5 * j + 3] = 255;
		stripeImage[5 * j + 4] = 0;
	}
}

void MyDisplay() {


	GLfloat MyLightPosition[] = { 0,0, 1.5 ,1 };


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_1D, MyTextureObject);


	glPushMatrix();
		glTranslatef(0, 0, -5);	//무지개 원구를 z축방향으로 -5만큼 이동함
		glPushMatrix();
			glRotatef(SpinAngle, 0, 1, 0);	//클릭할때마다y축 방향을 광원이 회전한다
			glLightfv(GL_LIGHT0, GL_POSITION, MyLightPosition);//광원의 위치 설정을 해준다
			glTranslatef(0, 0, 1.5);//광원이 z축으로 -3.5(-5+1.5)위치에 있으므로
						//광원위치에 있도록 이동해준다
		
			glDisable(GL_LIGHTING);//광원을 그리기 위해서 일단은 조명을 끈다
			
			glutWireSphere(0.06, 10, 10);//광원을 그린다
			//참고로 광원도 무지개색이다
			glEnable(GL_LIGHTING);//다시 조명을 킨다

			
		glPopMatrix();
		gluSphere(qobj, 1.0, 40, 40);	//이후 무지개 원구를 그린다
	glPopMatrix();


	glutSwapBuffers();

}



void MyMouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			SpinAngle = (SpinAngle + 15) % 360;
		glutPostRedisplay();
		}
	break;
		default:
	break;
	}

}


void Init() {

	

	GLfloat MyLightPosition[] = { 0,0, 1.5 ,1 };

	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	//전면에 분산광
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);	//전면에 반사광
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
	//glLightfv(GL_LIGHT0, GL_POSITION, MyLightPosition);	// 초기 광원 위치 할당


	glEnable(GL_LIGHTING);	//조명 기능 활성화
	glEnable(GL_LIGHT0);	//0번 광원 활성화 ,GL_LIGHT0은 관원의 아이디를 의미함 
	glEnable(GL_DEPTH_TEST);		//깊이 정보 활성화
	glShadeModel(GL_SMOOTH);	//구로 세이딩

	MyStripeImage();		//원구에 무늬 입히기
	glGenTextures(1, &MyTextureObject);
	glBindTexture(GL_TEXTURE_1D, MyTextureObject);
	glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, ref_plane);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_1D);
}

void MyReshape(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40., (GLfloat)w / (GLfloat)h, 1., 10.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void main(int argc, char **argv) {

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(400, 400);		//윈도우창 설정

	glutCreateWindow("과제6_16011024_주수헌");

	Init();

	glutReshapeFunc(MyReshape);
	glutDisplayFunc(MyDisplay);

	glutMouseFunc(MyMouse);



	glutMainLoop();
}
