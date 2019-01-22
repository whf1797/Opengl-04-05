//
//  main.cpp
//  Opengl-04-05
//
//  Created by 王洪飞 on 2019/1/18.
//  Copyright © 2019 王洪飞. All rights reserved.
//

#include "GLTools.h"
#include "glut/glut.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

struct screenPt {
    GLint x;
    GLint y;
};
void delay(int seconds);
typedef enum {
    limacon = 1,
    cardioid,
    threeLeaf,
    fourLeaf,
    sprial
}curveName;

GLsizei winWidth = 600, winHeight = 500;

void init(){
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 600, 0, 500);
}

void lineSegment(screenPt pt1, screenPt pt2){
    glBegin(GL_LINES);
    glVertex2i(pt1.x, pt1.y);
    glVertex2i(pt2.x, pt2.y);
    glEnd();
}

void drawCurve(GLint curveNum){
    const GLdouble twoPi = 6.283185;
    const GLint a = 175, b = 60;
    
    GLfloat r = 0, theta,dtheta = 1.0/float(a);
    GLint x0 = 200, y0 = 250;
    
    screenPt curvePt[2];
    glColor3f(0.0, 0.0, 0.0);
    
    curvePt[0].x = x0;
    curvePt[0].y = y0;
    switch (curveNum) {
        case limacon:curvePt[0].x += a + b;break;
        case cardioid: curvePt[0].x += a + a;break;
        case threeLeaf:curvePt[0].x += a;break;
        case fourLeaf:curvePt[0].x += a;break;
        case sprial: break;
        default:
            break;
    }
    
    theta = dtheta;
    while (theta < twoPi) {
        switch (curveNum) {
            case limacon:
                r = a * cos(theta) + b;
                break;
                case cardioid:
                r = a * (1 + cos(theta));break;
                case threeLeaf:
                r = a * cos(2*theta);break;
                case fourLeaf:
                r = a * cos(2*theta);break;
                case sprial:
                r = (a/4.0)*theta;break;
            default:
                break;
        }
        
        curvePt[1].x = x0 + r * cos(theta);
        curvePt[1].y = y0 + r * sin(theta);
        lineSegment(curvePt[0], curvePt[1]);
        curvePt[0].x = curvePt[1].x;
        curvePt[0].y = curvePt[1].y;
        theta+= dtheta;
        
    }
    
    
    
}

void delay(int seconds)

{
    
    clock_t start = clock();
    
    clock_t lay = (clock_t)seconds * CLOCKS_PER_SEC;
    
    while ((clock()-start) < lay)
        
        ;
    
}

void winReshapeFcn(GLint newWidth,GLint newHeight){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, (GLdouble)newWidth, 0, (GLdouble)newHeight);
    glClear(GL_COLOR_BUFFER_BIT);
}

void displayfunc(){
    GLint curveNum;
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << "\n enter the integer value corresponding to\n";
    std::cout << "one of the following curve name \n";
    std::cout << "press any other key to exit \n";
    std::cout << "\n n1-limacon , 2-cardioid , 3-threefleaf, 4 fourleaf, 5-spiral: ";
    std::cin >> curveNum;
    if (curveNum ==1 || curveNum == 2 || curveNum == 3 || curveNum == 4 || curveNum == 5) {
        printf("draw curve");
        drawCurve(curveNum);
    } else {
        exit(0);
    }
    glFlush();
}


int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("abcdefg");
    init();
    glutDisplayFunc(displayfunc);
    glutReshapeFunc(winReshapeFcn);
    glewInit();
    
    glutMainLoop();
    
    return 0;
}
