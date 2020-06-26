/**
 * \file function prototypes of all functions used in png_image.cpp
 */

#include <vector>
#include "lodepng.h"
using namespace std;
class Png_Image
{
public:
	Png_Image();
	Png_Image(char *pathname);
	~Png_Image();
	void load(char *pathname);
	int getWidth();
	int getHeight();
	void getRGB(int x, int y, int &r, int &g, int &b);
private:	
	vector<unsigned char> img;
	unsigned int w, h;
};

