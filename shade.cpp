/**
 * \file Implementation of the shading algorithm and the drawing of the colour palette.
 */

#include "shade.h"

/*@brief all the colors in color palette*/

Color RED1=         Color {0.95f,0.26f,0.21f};
Color PINK1=        Color {0.91f,0.12f,0.38f};
Color PURPLE1=      Color {0.60f,0.15f,0.68f};
Color DEEP_PURPLE1= Color {0.40f,0.22f,0.71f};
Color INDIGO1=      Color {0.24f,0.31f,0.70f};
Color BLUE1=        Color {0.12f,0.58f,0.94f};
Color LIGHT_BLUE1 = Color {0.01f,0.38f,0.95f};
Color CYAN1=        Color {0.0f,0.73f,0.83f};
Color TEAL1=        Color {0.0f,0.58f,0.53f};
Color GREEN1=       Color {0.29f,0.68f,0.31f};
Color LIGHT_GREEN1= Color {0.54f,0.76f,0.28f};
Color LIME1=        Color {0.80f,0.85f,0.22f};
Color YELLOW1=      Color {1.0f,0.98f,0.23f};
Color AMBER1=       Color {1.0f,0.75f,0.03f};
Color ORANGE1=      Color {1.0f,0.59f,0.0f};
Color DEEP_ORANGE1= Color {1.0f,0.33f,0.13f};
Color BROWN1=       Color {0.24f,0.15f,0.13f};
Color GREY1=        Color {0.61f,0.61f,0.61f};
Color WHITE1=       Color {1.0f,1.0f,1.0f};
Color BLACK1=       Color {0.0f,0.0f,0.0f};

/*@brief agenda lists in both vertical directions*/

vector <agenda> * agendaListUP=new vector <agenda>();
vector <agenda> * agendaListDOWN=new vector <agenda>();

/*@brief lists of colors*/
vector<Color> colors1{ RED1,PINK1,PURPLE1,DEEP_PURPLE1,INDIGO1,
            BLUE1,LIGHT_BLUE1,CYAN1,TEAL1,GREEN1};
vector<Color> colors2{LIGHT_GREEN1,LIME1,YELLOW1,AMBER1,
            ORANGE1,DEEP_ORANGE1,BROWN1,GREY1,WHITE1,BLACK1};


vector<agenda> *agenda_cDir=new vector <agenda>();


/**
 * @brief Function to get color of the pixel
 * @param p pixel of which color is to be found
 * @return color of the pixel
 */
Color getPixelColor(Point p) {
    Color color;
    glReadPixels(p.x, p.y, 1 , 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

/**
 * @brief Function called when == operator used between two Color objects o check if they are same
 * @param lhs 1st object
 * @param rhs 2nd object
 * @return true if colors are equal, false if not
*/
bool operator==(const Color& lhs, const Color& rhs){
    return (lhs.r==rhs.r)&&(lhs.g==rhs.g)&&(lhs.b==rhs.b);
}

/**
 * @brief Function to set color of the pixel
 * @param p pixel of which color is to be set
 * @param color the color which is to be set
 */
void setPixelColor(Point p, Color color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
    glFlush();
}

/**
 * @brief Function to find whether the point is on the Agenda list
 * @param p point which is to be checked
 * @return true if point is in agenda, false if not
 */
bool onAgenda(Point p){
    for(agenda a: *agendaListUP){
        if(p.y==a.line.y && p.x<a.line.x_right && p.x>a.line.x_left){
            return true;
        }
    }
    for(agenda a: *agendaListDOWN){
        if(p.y==a.line.y && p.x<a.line.x_right && p.x>a.line.x_left){
            return true;
        }
    }
    return false;
}

/**
 * @brief function to find if the next line is boundary
 * @param color color of the origin - interior color
 * @param pt a pointer to the starting point
 * @param dir current vertical direction
 * @return true if next line is boundary line in current vertical direction, false if not
*/
bool adjPoints_boundary(HorizontalLine line, Color color, Point * pt, Vertical_Direction dir){

    int y=dir==UP?line.y+1:line.y-1;
    for(GLfloat x=line.x_left+1; x<line.x_right; x++){
        Point p=Point{(GLfloat) x,(GLfloat) y};
        if((getPixelColor(p)==color)){
            if(!onAgenda(p)){
                pt->x=p.x;
                pt->y=p.y;
                return false;
            }   
        }
    }
    return true;
}

/**
 * @brief Function to draw one horizontal line
 * @param line the line which needs to be shaded 
 * @param color color by which the line is to be shaded
 */
void drawLine(HorizontalLine line,Color color){
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_LINES);
    glVertex2f(line.x_left, line.y);
    glVertex2f(line.x_right, line.y);
    glEnd();
    glFlush();
}

/**
 * @brief Function to look for S-Turns
 * @param line previously shaded line
 * @param intColor interior color
 * @param dir current vertical direction
 */
void lookforSTurns(HorizontalLine line,Color intColor, Vertical_Direction dir){
    GLfloat y=dir==UP?line.y+1:line.y-1;
    HorizontalLine imgBndryLine;
    imgBndryLine.y=y;
    GLfloat x=line.x_left;
    while(x<=line.x_right){
        if(getPixelColor({x,y})==intColor){
            imgBndryLine.x_left=x;
            while((getPixelColor({x,y})==intColor)){
		cout<<"";
                x++;
            }
            imgBndryLine.x_right=x-1;
            dir==UP?(agendaListUP->push_back(agenda{imgBndryLine,UP,intColor})):(agendaListDOWN->push_back(agenda{imgBndryLine,DOWN,intColor}));
        }
        else{
	    cout<<"";
	    x++;
	}
    }
}

/**
 * @brief Function to look for U-Turns
 * @param line currently shaded line
 * @param intColor interior color
 * @param dir current vertical direction
 */
void lookforUTurns(HorizontalLine line,Color intColor, Vertical_Direction dir){
    
    GLfloat y=dir==DOWN?line.y+1:line.y-1;
    HorizontalLine imgBndryLine;
    imgBndryLine.y=y;
    GLfloat x=line.x_left;
    while(x<=line.x_right){
        if(getPixelColor({x,y})==intColor){
            imgBndryLine.x_left=x;
            while((getPixelColor({x,y})==intColor)){
            	cout<<"";
                x++;
            }
            imgBndryLine.x_right=x-1;
            dir==UP?(agendaListDOWN->push_back(agenda{imgBndryLine,DOWN,intColor})):(agendaListUP->push_back(agenda{imgBndryLine,UP,intColor}));
        }
        else x++;
    }
}

/**
 * @brief Function to find the horizontal boundaries of a point
 * @param sp starting point from which boundary is to be found
 * @param intcolor interior color
 * @return Horizontal Line for the current starting point
 */
HorizontalLine findBndry(Point sp, Color intColor){
	
	HorizontalLine line;
    Point cp=sp;
    line.y=sp.y;
    while ((getPixelColor(cp)==intColor)){
    	cout<<"";
        cp.x--;
    }
    line.x_left=cp.x+1;
    cp.x=sp.x+1;
    while ((getPixelColor(cp)==intColor)){
    	cout<<"";
        cp.x++;
    }
    line.x_right=cp.x;
    return line;
}

/**
 * @brief Function to shade a horizontal line
 * @param sp starting point on the line
 * @param shadingColor color by which the line is o be shaded
 * @param interiorColor interior color
 * @return Horizontal Line which is shaded
 */
HorizontalLine shadeHorizontally(Point sp,Color shadingColor,Color interiorColor){
    
    HorizontalLine line=findBndry(sp,interiorColor);
    drawLine(line,shadingColor);
    return line;
}

/**
 * @brief Function to shade vertically from a starting point
 * @param dir current vertical direction
 * @param starting_point starting point on the line
 * @param shadingColor color by which the line is o be shaded
 * @param origin_color interior color
 */
void shade_vertically( Vertical_Direction dir, Point starting_point, Color shadingColor,Color origin_color){
    Point st_point=starting_point;
    HorizontalLine line;
    Point* next_sp=&st_point;
    HorizontalLine prvsLine;
    int c=0;
    do{
        line=shadeHorizontally(Point{next_sp->x,next_sp->y},shadingColor,origin_color);
        if(c){
            lookforSTurns(prvsLine,origin_color,dir);
            lookforUTurns(line,origin_color,dir);
        }
        prvsLine=line;
        c++;
    }while(!adjPoints_boundary(line, origin_color,next_sp,dir));
}

/**
 * @brief Function to start shading from a statrting point
 * @param p starting point on the line
 * @param shadingColor color by which the line is o be shaded
 */
void shade(Point p, Color shadingColor){
	
    Color intColor=getPixelColor(p);
    Vertical_Direction cDir=UP;
    HorizontalLine aline= findBndry(p,intColor);
    agendaListUP->push_back({aline,UP,intColor});
    
    HorizontalLine bline= findBndry({p.x,p.y-1},intColor);
    agendaListDOWN->push_back({bline,DOWN,intColor});
    agenda_cDir=agendaListUP;
    while(!(agendaListUP->empty()&&agendaListDOWN->empty())){
        if(agenda_cDir->empty()) cDir=cDir==UP?DOWN:UP;
        agenda_cDir=cDir==UP?agendaListUP:agendaListDOWN;
        agenda a=agenda_cDir->back();
        agenda_cDir->pop_back();
        shade_vertically(cDir,{a.line.x_left,a.line.y},shadingColor,a.originColor);
    }
}

/**
 * @brief Function to print the color palette title
 * @param str the text which is to be printed
 * @param color color of the text
 * @param width width of the window
 * @param height height of the window
 */
void printTitle(string str, Color color, GLdouble width,GLdouble height){

    glColor3f( color.r,color.g,color.b );
    glRasterPos2f(width-140, height-40);
    int len, i;
    len = (int)str.length();
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str.at(i));
    }
}

/**
 * @brief Function to make the color palette
 * @param width width of the window
 * @param height height of the window
 */
void makeColorPalette(GLdouble width,GLdouble height){
    printTitle("Choose Color",BLACK1, width, height);

    draw_Polygon({(GLfloat)(width-160),(GLfloat)(height-1)},600,160,BLACK1);
    Point p=Point{(GLfloat)(width-130),(GLfloat)(height-60)};
    int disp=50;
    for( Color color : colors1){
        draw_FilledPolygon(p,color);
        p.y=p.y-disp;
    }
    p=Point{(GLfloat)(width-80),(GLfloat)(height-60)};
    for( Color color : colors2){
        draw_FilledPolygon(p,color);
        p.y=p.y-disp;
    }
    draw_Polygon({(GLfloat)(width-130),(GLfloat)(height-60)},500,100,BLACK1);
}

/**
 * @brief Function to draw a unfilled rectangle
 * @param p top left point of rectangle
 * @param height height of the window
 * @param width width of the window
 * @param color boundry color of rectangle
 */
void draw_Polygon(Point p,int height, int width, Color color){


    glColor3f(color.r,color.g,color.b);

    glBegin(GL_LINES);
    glVertex2f(p.x, p.y);
    glVertex2f(p.x+width, p.y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(p.x+width, p.y);
    glVertex2f(p.x+width, p.y-height);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(p.x+width, p.y-height);
    glVertex2f(p.x, p.y-height);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(p.x, p.y-height);
    glVertex2f(p.x, p.y+1);
    glEnd();
}

/**
 * @brief Function to draw a filled square of size 50x50 for individual colors in color palette
 * @param p top left point of square
 * @param color filling color of square
 */
void draw_FilledPolygon(Point p,Color color){

    glColor3f(color.r,color.g,color.b);
    glBegin(GL_POLYGON);

    glVertex2f(p.x, p.y);
    glVertex2f(p.x+50, p.y);
    glVertex2f(p.x+50, p.y-50);
    glVertex2f(p.x, p.y-50);

    glEnd();
}
