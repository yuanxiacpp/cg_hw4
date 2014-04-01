using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#include "figio.h"


int main(int argc, char* argv[]) {
  if (argc != 6) {
    cerr << "Usage: " << argv[0]
	 << "<background1> <background2> <composite1> <composite2> <output>" 
	 << endl;
    return 1;
  }

  return 0;
}
