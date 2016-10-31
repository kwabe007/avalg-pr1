#include<iostream>
#include<fstream>
#include<vector>
#include"debug/debugmacro.h"


/*DEBUG BITS
BIT0 = variable contents*/

unsigned int GLOBAL_DEBUG_BITS = BIT0;


//Fill arrays with data point values from input stream
void setup_arrays(std::istream& in, std::vector<double>& array_x, std::vector<double>& array_y) {
  int n;
  in >> n;
  for (int i  = 0; i < n; ++i) {
    double x, y;
    in >> x;
    array_x.push_back(x);
    in >> y;
    array_y.push_back(y);
  }
}

int main (int argc, char* argv[]) {

  std::ifstream infile;
  if (argc > 1) {
    infile.open(argv[1]);
  } else {
    std::cout << "No input file given as argument..." << std::endl;
  }

  
  // arrays to be filled with data points
  std::vector<double> data_point_array_x;
  std::vector<double> data_point_array_y;


  setup_arrays(infile,data_point_array_x,data_point_array_y);
   
   
  return 0;
}
