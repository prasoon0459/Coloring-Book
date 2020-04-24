#include "agenda.h"

void setPixelColor(Point p, Color color);
Color getPixelColor(Point p);
bool operator==(const Color& lhs, const Color& rhs);
bool adjPoints_boundary(HorizontalLine line, Color color, Point * pt);
HorizontalLine shadeHorizontally(Point sp);
void shade_vertically( Vertical_Direction dir, Point starting_point,Color shadingColor);
void makeColorPalette(GLdouble width,GLdouble height);
void draw_Polygon(Point p,int height, int width, Color color);
void draw_FilledPolygon(Point p,Color color);