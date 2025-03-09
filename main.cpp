#include <GL/glut.h>
#include <iostream>
#include <cmath>

int shape = 1;
int pyramidType = 1;
float angle = 0.0;

void drawText(const char *text, int length, int x, int y) {
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRasterPos2i(x, y);
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
    delete[] matrix;
}

void drawCube() {
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
}

void drawPyramid3() {
    glBegin(GL_TRIANGLES);
    
    // Sisi depan
    glColor3ub(252, 148, 175);
    glVertex3f(0.0, 1.0, 0.0);  // Titik puncak
    glVertex3f(-1.0, -1.0, 1.0); // Kiri bawah
    glVertex3f(1.0, -1.0, 1.0);  // Kanan bawah
    
    // Sisi kanan
    glColor3ub(199, 21, 133);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(0.0, -1.0, -1.0);
    
    // Sisi kiri
    glColor3ub(219, 112, 147);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    
    // Alas segitiga
    glColor3ub(255, 182, 193);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(0.0, -1.0, -1.0);
    
    glEnd();
}

void drawPyramid4() {
    
}

void drawPyramid5() {
    
}

void drawPyramid6() {
    
}


void drawSphere() {
    glColor3f(1.0, 0.5, 0.0);
    glutSolidSphere(0.7, 50, 50);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angle, 1.0f, 1.0f, 0.0f);
    
    switch (shape) {
        case 1: drawCube(); break;
        case 2: 
            switch (pyramidType) {
                case 1: drawPyramid3(); break;
                case 2: drawPyramid4(); break;
                case 3: drawPyramid5(); break;
                case 4: drawPyramid6(); break;
            }
            break;
        case 3: drawSphere(); break;
    }
    
    char text[] = "Press 1: Cube | Press 2: Pyramid (A: Triangular, B: Square, C: Pentagonal, D: Hexagonal) | Press 3: Sphere";
    drawText(text, sizeof(text) - 1, 10, 470);
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '1') shape = 1;
    if (key == '2') shape = 2;
    if (key == '3') shape = 3;
    
    if (shape == 2) {
        if (key == 'a' || key == 'A') pyramidType = 1; // Triangular Pyramid
        if (key == 'b' || key == 'B') pyramidType = 2; // Square Pyramid
        if (key == 'c' || key == 'C') pyramidType = 3; // Pentagonal Pyramid
        if (key == 'd' || key == 'D') pyramidType = 4; // Hexagonal Pyramid
    }
    
    glutPostRedisplay();
}

void update(int value) {
    angle += 1.0f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("GrafKom dan Mulmed 3 D");

    glEnable(GL_DEPTH_TEST);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}

