#include <GL/freeglut.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
using namespace std; // optional but fine for this small project


int state = 0; // 0 = Red, 1 = Yellow, 2 = Green

void drawCircle(float cx, float cy, float r, int num_segments, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw box
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3f,  0.8f);
        glVertex2f( 0.3f,  0.8f);
        glVertex2f( 0.3f, -0.8f);
        glVertex2f(-0.3f, -0.8f);
    glEnd();

    // Draw lights
    float redOn[3] = {0.9f, 0.0f, 0.0f};
    float yellowOn[3] = {0.9f, 0.9f, 0.0f};
    float greenOn[3] = {0.0f, 0.8f, 0.0f};
    float off[3] = {0.1f, 0.1f, 0.1f};

    // Red light
    drawCircle(0.0f, 0.45f, 0.15f, 50, (state == 0 ? redOn[0] : off[0]),
                                            (state == 0 ? redOn[1] : off[1]),
                                            (state == 0 ? redOn[2] : off[2]));
    // Yellow light
    drawCircle(0.0f, 0.0f, 0.15f, 50, (state == 1 ? yellowOn[0] : off[0]),
                                        (state == 1 ? yellowOn[1] : off[1]),
                                        (state == 1 ? yellowOn[2] : off[2]));
    // Green light
    drawCircle(0.0f, -0.45f, 0.15f, 50, (state == 2 ? greenOn[0] : off[0]),
                                         (state == 2 ? greenOn[1] : off[1]),
                                         (state == 2 ? greenOn[2] : off[2]));

    glutSwapBuffers();
}

void timer(int value) {
    // Change light state every few seconds
    if (state == 0)
        state = 1; // Red -> Yellow
    else if (state == 1)
        state = 2; // Yellow -> Green
    else
        state = 0; // Green -> Red

    glutPostRedisplay();
    glutTimerFunc(3000, timer, 0); // 3 seconds per light
}

void init() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 700);
    glutCreateWindow("Dynamic Traffic Signal");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(3000, timer, 0);
    glutMainLoop();
    return 0;
}
