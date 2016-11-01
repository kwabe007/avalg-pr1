#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include"debugmacro.h"
#include"conalg.hpp"
#include"optalg.hpp"


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

  //set the stream to read data points from
  std::istream& instream = std::cin;

  // arrays to be filled with data points
  std::vector<double> array_x;
  std::vector<double> array_y;
  setup_arrays(instream,array_x,array_y);

  std::vector<int> tour = greedy_tour(array_x, array_y);
  std::vector<int> improved_tour = opttour(array_x, array_y, tour);


  for (unsigned int i = 0; i < improved_tour.size(); ++i) {
    std::cout << improved_tour[i] << std::endl;
  }
  
  
  return 0;
}
