using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#include "figio.h"


const unsigned int max_h = 10000;
const unsigned int max_w = 10000;

unsigned char* readTiff(const char *filename, int &w, int &h);

int main(int argc, char* argv[]) {
  if (argc != 4) {
	cerr << "Usage: " << argv[0] 
		 << "<background> <foreground> <output>" << endl;
	return 1;
  }

  int w = max_w;
  int h = max_h;
  
  unsigned char* bg = readTiff(argv[1], w, h);
  unsigned char* fg = readTiff(argv[2], w, h);

  unsigned char* output = new unsigned char[w*h*4];

  for (int j = 0; j < h; j++)
	for (int i = 0; i < w; i++) {
	  int index = 4*(j*w+i);

	  double alpha = fg[index+3] / 255.0;
	  
	  output[index] = alpha*fg[index] + (1-alpha)*bg[index];
	  output[index+1] = alpha*fg[index+1] + (1-alpha)*bg[index+1];
	  output[index+2] = alpha*fg[index+2] + (1-alpha)*bg[index+2];
	  output[index+3] = 255;
	  
	}


  if (!save_tiff_with_alpha(argv[3], output, w, h)) {
	cerr << "Could not write to output file " << argv[3] << endl;
	return -1;
  }

  return 0;
}

unsigned char* readTiff(const char* filename, int &w, int &h) {
  unsigned char* im = new unsigned char[max_w*max_h*4];
  if (!load_tiff_with_alpha(filename, im, w, h)) {
	cout << "Could not read input file: " << filename << endl;
	return NULL;
  }
  return im;
}
