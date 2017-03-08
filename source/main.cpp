#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
//#include"debugmacro.h"
#include <ctime>
#include"conalg.hpp"
#include"optalg.hpp"


/*DEBUG BITS
BIT0 = variable contents*/

//unsigned int GLOBAL_DEBUG_BITS = BIT0;



//Fill arrays with data point values from input stream
void setup_arrays(std::istream& in, std::vector<double>& array_x, std::vector<double>& array_y) {
  
  for (unsigned int i  = 0; i < array_x.size(); ++i) {
    double x, y;
    in >> x;
    array_x[i] = x;
    in >> y;
    array_y[i] = y;
  }
}

int main (int argc, char* argv[]) {

  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  //set the stream to read data points from
  std::istream& instream = std::cin;

  unsigned int n;
  instream >> n;

  // arrays to be filled with data points
  std::vector<double> array_x(n);
  std::vector<double> array_y(n);
  setup_arrays(instream,array_x,array_y);

 //*std::clock_t begin = std::clock();
  
  std::vector<int> tour(clarke_wright(array_x, array_y));

  rotate_tour(array_x, array_y, tour);

  tour = opttour(array_x, array_y, tour);

  rotate_tour(array_x, array_y, tour);

  tour = whacktour(array_x, array_y, tour);

  rotate_tour(array_x, array_y, tour);

  

  //std::clock_t end_const = std::clock();
  
  //std::vector<int> improved_tour = opttour(array_x, array_y, tour);

  //std::clock_t end_2opt = std::clock();*/

  
  for (unsigned int i = 0; i < tour.size(); ++i) {
    std::cout << tour[i] << std::endl;
    }

  /*std::clock_t clocks_const = end_const-begin;

  std::clock_t clocks_2opt = end_2opt-end_const;

  std::cerr << "distance of 2opt-tour: " << tourDist(array_x,array_y, tour) << std::endl;

  std::cerr << "construction, clock: " << clocks_const << "est. time: " << std::endl;

  std::cerr << "2opt, clock: " << clocks_2opt << "est. time: " << std::endl;*/

  
  return 0;
}
