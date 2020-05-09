#include <iostream>
#include "png_image.h"
using namespace std;

Png_Image::Png_Image(){
	w = 0;
	h = 0;
}

Png_Image::~Png_Image(){}

Png_Image::Png_Image(char *path){
	if (path[0] != '\0')
		load(path);
}

void Png_Image::load(char *path){
	vector<unsigned char> pngTemp;
	lodepng::load_file(pngTemp, path);
	unsigned error = lodepng::decode(img, w, h, pngTemp);
	if (error){
		cout << "png Error: " << error << " " << lodepng_error_text(error) << endl;
		system("pause");
		exit(0);
	}
}
int Png_Image::getWidth(){
	 return w;
}
int Png_Image::getHeight(){
	 return h;
}
void Png_Image::getRGB(int x, int y, int &r, int &g, int &b)
 {
	if (x < 0 || y < 0 || x > w || y > h)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	if ((h > 0) && (w > 0))
	{
		r = img[4 * y*w + 4 * x + 0];
		g = img[4 * y*w + 4 * x + 1];
		b = img[4 * y*w + 4 * x + 2];
	}
 }

