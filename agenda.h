/**
 * @file Header file containing definitions of basic data structures.
 */
#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#include<vector>


enum Vertical_Direction{UP,DOWN}; //< holds all necessary information about a shading agenda

/**
 * Point in the window.
 */
struct Point {
    GLfloat x; /**< x coordinate of the point */
    GLfloat y; /**< y coordinate of the point*/
};

/**
 * Stores the colour in RGB format.
 */
struct Color {
    GLfloat r;/**< red */
    GLfloat g;/**< green*/
    GLfloat b;/**< blue */
};

/**
 * Endpoints of a horizontal line.
 */
struct HorizontalLine{
    GLfloat x_left;/**left boundary*/
    GLfloat x_right;/**< right boundary  */
    GLfloat y;/**< vriacl level*/
};

/**
 * Stores the colour in RGB format.
 */
class agenda{
    public:
        HorizontalLine line;
        Vertical_Direction direction;
        Color originColor;

    agenda(HorizontalLine line, Vertical_Direction direction,Color originColor)
                :line(line),direction(direction),originColor(originColor) {};
};
