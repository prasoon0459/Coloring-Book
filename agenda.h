#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#include<vector>

/* @brief holds all necessary information about a shading agenda*/

enum Vertical_Direction{UP,DOWN};

struct Point {
    GLfloat x;/**< x coordinate */
    GLfloat y;/**< y coordinate */
};

struct Color {
    GLfloat r;/**< red */
    GLfloat g;/**< green*/
    GLfloat b;/**< blue */
};

struct HorizontalLine{
    GLfloat x_left;/**left boundary*/
    GLfloat x_right;/**< right boundary  */
    GLfloat y;/**< vriacl level*/
};

class agenda{
    public:
        HorizontalLine line;
        Vertical_Direction direction;
        Color originColor;

    agenda(HorizontalLine line, Vertical_Direction direction,Color originColor)
                :line(line),direction(direction),originColor(originColor) {};
};
