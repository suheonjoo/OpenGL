#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int Width, Height;

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 2, 3.0, 0.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 2.0);

}



void MyDisplay() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.4, 0.5, 0.0, -0.5, -1.0, 0.0, 1.0, 0.0);

	//은면, 후면 존재
	glViewport(0, 0, (GLsizei)Width / 2, (GLsizei)Height / 2);	//좌하단
	glutSolidTeapot(0.58);


	//은면제거
	glEnable(GL_DEPTH_TEST);	//은면제거모드 실행
	glViewport((GLsizei)Width / 2, 0, (GLsizei)Width / 2, (GLsizei)Height / 2);//우하단
	glutSolidTeapot(0.58);



	//후면제거
	glEnable(GL_CULL_FACE);	//후면제거 모드 활성화
	glDisable(GL_DEPTH_TEST);	//은면제거모드 비활성화
	glFrontFace(GL_CW);		//'정점을 시계방향으로 제시한 면'을 표면을 설정
	glCullFace(GL_BACK);	//최종적 후면제거 실행함수
	glViewport(0, (GLsizei)Height / 2, (GLsizei)Width / 2, (GLsizei)Height / 2);//좌상단
	glutSolidTeapot(0.58);


	//은면제거 후면제거
	glEnable(GL_DEPTH_TEST);	//은면제거모드 다시 활성화
	glViewport((GLsizei)Width / 2, (GLsizei)Height / 2, (GLsizei)Width / 2, (GLsizei)Height / 2);//우상단
	glutSolidTeapot(0.58);



	glFlush();
}

void MyReshape(int w, int h) {

	Width = w;
	Height = h;


}

int main(int argc, char** argv) {

	Width = 400;
	Height = 400;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);


	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("과제4 16011024 주수헌");	//윈도우 생성

	glClearColor(0.5, 0.5, 0.5, 0.0);
	InitLight();



	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}

