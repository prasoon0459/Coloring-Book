#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#include<vector>

enum Vertical_Direction{UP,DOWN};

struct Point {
    GLfloat x;
    GLfloat y;
};

struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    string colorString(){
        return to_string(r)+" "+to_string(g)+" "+to_string(b);
    }
};

struct HorizontalLine{
    GLfloat x_left;
    GLfloat x_right;
    GLfloat y;
};

class agenda{
    public:
        HorizontalLine line;
        Vertical_Direction direction;

    agenda(HorizontalLine line, Vertical_Direction direction):line(line),direction(direction){};
};

