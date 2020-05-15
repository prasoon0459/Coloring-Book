#include <iostream>
#include "png_image.h"
using namespace std;
/**
@brief constructor
*/
Png_Image::Png_Image(){
	w = 0;
	h = 0;
}
/**
@brief destructor
*/
Png_Image::~Png_Image(){}
/** @brief constructor
@param character pointer
*/
Png_Image::Png_Image(char *path){
	if (path[0] != '\0')
		load(path);
}
/**

@param character pointer
*/
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
/**
@brief Function to return width as an integer
*/
int Png_Image::getWidth(){
	 return w;
}
/**
@brief Function to get height as an integer
*/
int Png_Image::getHeight(){
	 return h;
}
/**
@brief Function to get colour
@param x which is x coordinate
@param y which is y coordinate
@param r which is red
@param g which is green
@param b which is blue
*/
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

