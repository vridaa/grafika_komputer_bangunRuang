#include <GL/glut.h>
#include <iostream>
#include <cmath>

int shape = 1;
int pyramidType = 1;
float angle = 0.0;

void drawText(const char *text, int length, int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRasterPos2i(x, y);
    for (int i = 0; i < length; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
    delete[] matrix;
}

void drawCube()
{
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
}

void drawPyramid3()
{
    glBegin(GL_TRIANGLES);

    // Sisi depan
    glColor3ub(252, 148, 175);
    glVertex3f(0.0, 1.0, 0.0);   // Titik puncak
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

void drawPyramid4()
{
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0); // Rotasi agar limas berputar

    glBegin(GL_TRIANGLES);

    // Warna selang-seling (biru muda dan biru tua)
    float colors[2][3] = {
        {0.0, 0.3, 1.0}, // Biru muda
        {0.0, 0.0, 0.6}  // Biru tua
    };

    // Puncak limas
    float peak[3] = {0.0, 1.5, 0.0};

    // Titik alas
    float base[4][3] = {
        {-1.0, 0.0, 1.0},
        {1.0, 0.0, 1.0},
        {1.0, 0.0, -1.0},
        {-1.0, 0.0, -1.0}};

    // Membuat sisi segitiga dari limas
    for (int i = 0; i < 4; i++)
    {
        int next = (i + 1) % 4;

        glColor3f(colors[i % 2][0], colors[i % 2][1], colors[i % 2][2]);
        glVertex3fv(peak);
        glVertex3fv(base[i]);
        glVertex3fv(base[next]);
    }

    glEnd();

    // Menggambar alas limas (persegi)
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.2, 0.8); // Biru gelap
    glVertex3fv(base[0]);
    glVertex3fv(base[1]);
    glVertex3fv(base[2]);
    glVertex3fv(base[3]);
    glEnd();

    glPopMatrix();
}

void drawPyramid5()
{
}

void drawPyramid6()
{
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0); // Rotasi agar limas berputar

    glBegin(GL_TRIANGLES);

    float radius = 1.0;
    float height = 1.5;

    // Warna selang-seling
    float colors[2][3] = {
        {0.8, 0.2, 0.9}, // Warna pertama
        {0.7, 0.2, 0.8}  // Warna kedua
    };

    // Membuat sisi segitiga dari limas
    for (int i = 0; i < 6; i++)
    {
        float theta1 = i * M_PI / 3.0;
        float theta2 = (i + 1) * M_PI / 3.0;

        float x1 = radius * cos(theta1);
        float z1 = radius * sin(theta1);
        float x2 = radius * cos(theta2);
        float z2 = radius * sin(theta2);

        glColor3f(colors[i % 2][0], colors[i % 2][1], colors[i % 2][2]); // Selang-seling warna
        glVertex3f(0.0, height, 0.0); // Titik puncak
        glVertex3f(x1, 0.0, z1);      // Titik pertama alas
        glVertex3f(x2, 0.0, z2);      // Titik kedua alas
    }

    glEnd();

    // Alas hexagonal
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.0, 0.8);

    for (int i = 0; i < 6; i++)
    {
        float theta = i * M_PI / 3.0;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(x, 0.0, z);
    }

    glEnd();

    glPopMatrix();
}

float rotationAngle = 0.0; // Variable to control rotation

void drawSphere()
{
    glPushMatrix();

    // Apply rotation
    glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Rotate around Y-axis

    // Draw four different colored quadrants
    for (int i = 0; i < 4; i++)
    {
        // Set solid color for each quadrant
        switch (i)
        {
        case 0:
            glColor3f(1.0, 0.0, 0.0); // Red
            break;
        case 1:
            glColor3f(0.0, 1.0, 0.0); // Green
            break;
        case 2:
            glColor3f(0.0, 0.0, 1.0); // Blue
            break;
        case 3:
            glColor3f(1.0, 1.0, 0.0); // Yellow
            break;
        }

        // Draw a quarter of a sphere
        glPushMatrix();
        // Rotate to position this quadrant (90 degrees each)
        glRotatef(i * 90, 0.0, 1.0, 0.0);

        // Create one quadrant of the sphere
        glBegin(GL_TRIANGLES);
        for (int lat = 0; lat < 50; lat++)
        {
            for (int lon = 0; lon < 13; lon++)
            { // 50/4 � 12.5, using 13 to ensure full coverage
                float lat1 = M_PI * lat / 50;
                float lat2 = M_PI * (lat + 1) / 50;
                float lon1 = 2 * M_PI * lon / 50;
                float lon2 = 2 * M_PI * (lon + 1) / 50;

                // Calculate vertices of triangles
                // Vertex 1
                float x1 = 0.7 * sin(lat1) * cos(lon1);
                float y1 = 0.7 * cos(lat1);
                float z1 = 0.7 * sin(lat1) * sin(lon1);

                // Vertex 2
                float x2 = 0.7 * sin(lat2) * cos(lon1);
                float y2 = 0.7 * cos(lat2);
                float z2 = 0.7 * sin(lat2) * sin(lon1);

                // Vertex 3
                float x3 = 0.7 * sin(lat2) * cos(lon2);
                float y3 = 0.7 * cos(lat2);
                float z3 = 0.7 * sin(lat2) * sin(lon2);

                // Vertex 4
                float x4 = 0.7 * sin(lat1) * cos(lon2);
                float y4 = 0.7 * cos(lat1);
                float z4 = 0.7 * sin(lat1) * sin(lon2);

                // First triangle
                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);

                // Second triangle
                glVertex3f(x1, y1, z1);
                glVertex3f(x3, y3, z3);
                glVertex3f(x4, y4, z4);
            }
        }
        glEnd();
        glPopMatrix();
    }

    glPopMatrix();

    // Update rotation angle for animation
    rotationAngle += 0.5; // Adjust speed as needed
    if (rotationAngle > 360.0)
        rotationAngle -= 360.0;
}

void animate()
{
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angle, 1.0f, 1.0f, 0.0f);

    switch (shape)
    {
    case 1:
        drawCube();
        break;
    case 2:
        switch (pyramidType)
        {
        case 1:
            drawPyramid3();
            break;
        case 2:
            drawPyramid4();
            break;
        case 3:
            drawPyramid5();
            break;
        case 4:
            drawPyramid6();
            break;
        }
        break;
    case 3:
        drawSphere();
        break;
    }

    char text[] = "Press 1: Cube | Press 2: Pyramid (A: Triangular, B: Square, C: Pentagonal, D: Hexagonal) | Press 3: Sphere";
    drawText(text, sizeof(text) - 1, 10, 470);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
        shape = 1;
    if (key == '2')
        shape = 2;
    if (key == '3')
        shape = 3;

    if (shape == 2)
    {
        if (key == 'a' || key == 'A')
            pyramidType = 1; // Triangular Pyramid
        if (key == 'b' || key == 'B')
            pyramidType = 2; // Square Pyramid
        if (key == 'c' || key == 'C')
            pyramidType = 3; // Pentagonal Pyramid
        if (key == 'd' || key == 'D')
            pyramidType = 4; // Hexagonal Pyramid
    }

    glutPostRedisplay();
}

void update(int value)
{
    angle += 1.0f;
    if (angle > 360)
        angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutIdleFunc(animate);
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
