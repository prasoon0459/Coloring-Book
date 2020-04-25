#include "shade.h"


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

vector <agenda> agendaList;

vector<Color> colors1{ RED1,PINK1,PURPLE1,DEEP_PURPLE1,INDIGO1,
            BLUE1,LIGHT_BLUE1,CYAN1,TEAL1,GREEN1};

vector<Color> colors2{LIGHT_GREEN1,LIME1,YELLOW1,AMBER1,
            ORANGE1,DEEP_ORANGE1,BROWN1,GREY1,WHITE1,BLACK1};

Color getPixelColor(Point p) {
    Color color;
    glReadPixels(p.x, p.y, 1 , 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

bool operator==(const Color& lhs, const Color& rhs){
    return (lhs.r==rhs.r)&&(lhs.g==rhs.g)&&(lhs.b==rhs.b);
}

void setPixelColor(Point p, Color color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(p.x, p.y);
    glEnd();
    glFlush();
}

bool onAgenda(Point p){
    for(agenda a: agendaList){
        if(p.y==a.line.y && p.x<a.line.x_right && p.x>a.line.x_left){
            return true;
        }
    }
    return false;
}

bool adjPoints_boundary(HorizontalLine line, Color color, Point * pt, Vertical_Direction dir){

    int y=dir==UP?line.y+1:line.y-1;
    for(int x=line.x_left+1; x<line.x_right; x++){
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

void drawLine(HorizontalLine line,Color color){
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_LINES);
    glVertex2i(line.x_left+1, line.y);
    glVertex2i(line.x_right, line.y);
    glEnd();
    glFlush();
}

HorizontalLine shadeHorizontally(Point sp,Color shadingColor){
    
    HorizontalLine line;
    Color interiorColor=getPixelColor(sp);
    Point cp;
    cp.x=sp.x-1;
    cp.y=sp.y;
    line.y=sp.y;
    while ((getPixelColor(cp)==interiorColor)){
        //setPixelColor(cp,shadingColor);
        cp.x--;
    }
    line.x_left=cp.x;
    cp.x=sp.x;
    while ((getPixelColor(cp)==interiorColor)){
        //setPixelColor(cp,shadingColor);
        cp.x++;
    }
    line.x_right=cp.x;
    drawLine(line,shadingColor);
    cout<<"shaded line "<<line.x_left+1<<' '<<line.x_right-1<<' '<<line.y<<endl;
    return line;// line include one bndry pt in both dirs
}

void lookforTurns(HorizontalLine line,Color intColor, Vertical_Direction dir){
    //look for s-turns y=y+1
    cout << "look for s turns "<<line.x_left<<' '<<line.x_right<<' '<<line.y<<' '<<dir<<endl<<endl;
    GLfloat y=line.y+1;
    bool LINE_INPROGRESS=false;
    HorizontalLine imgBndryLine;
    imgBndryLine.y=y;
    GLfloat x=line.x_left;
    while(x<=line.x_right){
        cout<<"checking for x = "<<x<<" y = "<<y<<endl;
        if(getPixelColor({x,y})==intColor&&!LINE_INPROGRESS){

            cout<<"came in if "<<"x "<<x<<" y "<<y<<' '<< getPixelColor({x,y}).colorString()<<' '<<intColor.colorString() <<endl;
            imgBndryLine.x_left=x;
            LINE_INPROGRESS=true;
            while((getPixelColor({x,y})==intColor)){
                x++;
            }
            imgBndryLine.x_right=x-1;
            LINE_INPROGRESS=false;
            cout << "agenda added "<<imgBndryLine.x_left<<' '<<imgBndryLine.x_right<<' '<<imgBndryLine.y<<' '<<dir<<endl<<endl;
            agendaList.push_back(agenda{imgBndryLine,dir});
        }
        else x++;
    }

    //look for u turns



}

void shade_vertically( Vertical_Direction dir, Point starting_point, Color shadingColor){
    cout<<"shading ver from "<<starting_point.x<<' '<<starting_point.y<<endl;
    Color origin_color=getPixelColor(starting_point);
    Point st_point=starting_point;
    HorizontalLine line;
    Point* next_sp=&st_point;
    HorizontalLine prvsLine;
    int c=0;
    do{
        line=shadeHorizontally(Point{next_sp->x,next_sp->y},shadingColor);
        if(c)lookforTurns(prvsLine,origin_color,dir);
        prvsLine=line;
        c++;
    }while(!adjPoints_boundary(line, origin_color,next_sp,dir));

}

void shade(Point p, Color shadingColor){

    Vertical_Direction currentDir=UP;

    shade_vertically(UP,p,shadingColor);
    shade_vertically(DOWN,{p.x,p.y-1},shadingColor);

    while(!agendaList.empty()){
        int length=agendaList.size();
        agenda a=agendaList.back();
        agendaList.pop_back();
        shade_vertically(currentDir,{a.line.x_left,a.line.y},shadingColor);

    }

}

void printTitle(string str, Color color, GLdouble width,GLdouble height){

    glColor3f( color.r,color.g,color.b );
    glRasterPos2f(width-140, height-40);
    int len, i;
    len = (int)str.length();
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str.at(i));
    }

}

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

void draw_Polygon(Point p,int height, int width, Color color){


    glColor3f(color.r,color.g,color.b);

    glBegin(GL_LINES);
    glVertex2i(p.x, p.y);
    glVertex2i(p.x+width, p.y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(p.x+width, p.y);
    glVertex2i(p.x+width, p.y-height);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(p.x+width, p.y-height);
    glVertex2i(p.x, p.y-height);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(p.x, p.y-height);
    glVertex2i(p.x, p.y+1);
    glEnd();

}

void draw_FilledPolygon(Point p,Color color){

    glColor3f(color.r,color.g,color.b);
    glBegin(GL_POLYGON);

    glVertex2i(p.x, p.y);
    glVertex2i(p.x+50, p.y);
    glVertex2i(p.x+50, p.y-50);
    glVertex2i(p.x, p.y-50);

    glEnd();

}


