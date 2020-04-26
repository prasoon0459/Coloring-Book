#include "shade.h"
#include "pngImage.h"
#include <string.h>

bool flag=false;
PngImage image;
Color shadingColor=Color{1,1,1};

GLdouble width=1000,height=1000;
GLdouble imgHt, imgWd;

void init() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,width, 0, height, -1.0, 1.0);
}

/*void resize(int newheight, int newwidth) {

    width=newwidth;
    height=newheight;

    // const float ar = (float) width / (float) height;
    // glViewport(0, 0, width, height);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(0,newwidth, 0, newheight, -1.0, 1.0);
}*/

void makeDrawing(){

    glBegin(GL_POINTS);
    Point drwgSP=Point{(GLfloat)(width-160-imgWd)/2,(GLfloat)(height+imgHt)/2};
    for (int j = 0; j < image.getHeight(); j++){
        for (int i = 0; i < image.getWidth(); i++){
            int r, g, b;
            image.getRGB(i, j, r, g, b);
            glColor3f((float)r / 255, (float)g / 255, (float)b / 255);
            glVertex2f(drwgSP.x+i, drwgSP.y-j);
        }
    }
    glEnd();
}

void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    makeColorPalette(width, height);
    makeDrawing();
    glutSwapBuffers();
    glFlush();

    return;
}

void onMouseClick(int button, int state, int x, int y){
    flag=!flag;                     //some weird reason.. it is getting executed twice on one click..
    if(flag){                       //probably once when u click and once when u release the mouse key..thts why this flag
        flag=true;
        Point p=Point{(GLfloat) x,(GLfloat)(height-y)};
        if(p.x>width-120&&p.x<width-20&&p.y>height-580&&p.y<height-80){
            shadingColor=getPixelColor(p);
            cout<<"color chosen "<<shadingColor.colorString()<<endl;
        }
        else if(p.x<width-140||p.y<height-600){
            if(shadingColor==getPixelColor(p)){
                cout<<"done same color"<<endl;
                return;
            }
            cout<<"shading started "<<p.x<<' '<<p.y<<endl;
            shade(p,shadingColor);
            cout<<"done"<<endl;
        }
        return;
    }
}

int main(int argc, char** argv){

    string str ;
    cout<<"Please ener path to the PNG file :"<<endl;
    cin>>str;
    char * ptr=new char[str.length()+1];
    strcpy(ptr,str.c_str());
    image.loadImage(ptr);
    imgHt=image.getHeight();
    imgWd=image.getWidth();

    // cout<<"img w "<<imgWd<<endl;
    // cout<<"img h "<<imgHt<<endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(width , height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Open GL");
    init();
    //glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glutMainLoop();
    return 0;

}