using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#include "figio.h"

//api to handle matrix inverse and multiply. From hw assignment of numerical class
#include "matrix.h"

const unsigned int max_h = 10000;
const unsigned int max_w = 10000;

unsigned char* readTiff(const char *filename, int &w, int &h);


int main(int argc, char* argv[]) {
  if (argc != 6) {
    cerr << "Usage: " << argv[0]
	 << "<background1> <background2> <composite1> <composite2> <output>" 
	 << endl;
    return 1;
  }
  int w = max_w;
  int h = max_h;

  unsigned char* k1 = readTiff(argv[1], w, h);
  unsigned char* k2 = readTiff(argv[2], w, h);
  unsigned char* c1 = readTiff(argv[3], w, h);
  unsigned char* c2 = readTiff(argv[4], w, h);

  unsigned char* output = new unsigned char[w*h*4];


  for (int j = 0; j < h; j++) 
	for (int i = 0; i < w; i++) {
	  int index = 4*(j*w+i);

	  int rk1 = k1[index];
	  int gk1 = k1[index+1];
	  int bk1 = k1[index+2];
	 
	  int rk2 = k2[index];
	  int gk2 = k2[index+1];
	  int bk2 = k2[index+2];

	  int delta_r1 = c1[index] - k1[index];
	  int delta_g1 = c1[index+1] - k1[index+1];
	  int delta_b1 = c1[index+2] - k1[index+2];
	  
	  int delta_r2 = c2[index] - k2[index];
	  int delta_g2 = c2[index+1] - k2[index+1];
	  int delta_b2 = c2[index+2] - k2[index+2];
	  

	  double mat[16] = {0};
	  mat[0] = 2;
	  mat[3] = -(rk1 + rk2);
	  mat[5] = 2;
	  mat[7] = -(gk1 + gk2);
	  mat[10] = 2;
	  mat[11] = -(bk1 + bk2);
	  mat[12] = -(rk1 + rk2);
	  mat[13] = -(gk1 + gk2);
	  mat[14] = -(bk1 + bk2);
	  mat[15] = rk1*rk1 + gk1*gk1 + bk1*bk1 + rk2*rk2 + gk2*gk2 + bk2*bk2;	  


	  /*
	  for (int cc = 0; cc < 4; cc++) {
		for (int dd = 0; dd < 4; dd++)
		  cout << mat[cc*4+dd] << " ";
		cout << endl;
		
	  }
	  cout << endl << endl;
	  */
	  
	  double mat_inv[16] = {0};
	  double u[16] = {0};

	  inv_double_gs(mat, 4, u, mat_inv); 

	  
	  
	  
	  //for (int cc = 0; cc < 4; cc++) {
	  //	for (int dd = 0; dd < 4; dd++)
	  //	  cout << mat_inv[cc*4+dd] << " ";
	  //	cout << endl;
	  //	
	  //}
	  //cout << endl << endl;

	  double left[4] = {0};
	  left[0] = delta_r1 + delta_r2;
	  left[1] = delta_g1 + delta_g2;
	  left[2] = delta_b1 + delta_b2;
	  left[3] = -(rk1 * delta_r1 + gk1*delta_g1 + bk1*delta_b1 + rk2*delta_r2 + gk2*delta_g2 + bk2*delta_b2);


	  
	  //for (int dx = 0; dx < 4; dx++)
	  //	cout << left[dx] << " ";
	  //cout << endl << endl;

	  double *result = (double*)malloc(1*4*sizeof(double));

	  memcpy(result, multiply(left, mat_inv, 1, 4, 4), 1*4*sizeof(double));

	  //for (int dx = 0; dx < 4; dx++)
	  //	cout << result[dx] << " ";
	  //cout << endl << endl;


	  for (int dx = 0; dx < 4; dx++) {
		if (dx == 3)
		  result[dx] *= 255;
		unsigned char val = 0;
		if (result[dx] < 0)
		  val = 0;
		else if (result[dx] > 255)
		  val = 255;
		else
		  val = (unsigned char)result[dx];

		//cout << (int)val << ", ";
		output[index+dx] = val;
	  }
	  //cout << endl;

	  //getchar();
	  
	}


  
  
  if (!save_tiff_with_alpha(argv[5], output, w, h)) {
	cerr << "Could not write output file " << argv[5] << endl;
	return 1;
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

