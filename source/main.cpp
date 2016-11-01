#include<iostream>
#include<fstream>
#include<vector>
#include"debug/debugmacro.h"


/*DEBUG BITS
BIT0 = variable contents*/

unsigned int GLOBAL_DEBUG_BITS = BIT0;

//calculates euclidean distance of two (x,y)-points rounded to the nearest integer.
int dist(const std::vector<double>& array_x, const std::vector<double>& array_y, int index1, int index2) {
  
  return 1;
}

//Greedy Tour algorithm
std::vector<int> greedy_tour(const std::vector<double>& array_x, const std::vector<double>& array_y) {
  unsigned int n = array_x.size();
  std::vector<int>tour(n);
  std::vector<bool> used(n);
  int best;
  
  for(unsigned int i = 1; i < n-1; ++i) {
    best = -1;
    for (unsigned int j = 0; j < n; ++j) {
      if (!used[j] && (best = -1 || dist(array_x, array_y, tour[i-1], j) < dist(array_x, array_y,tour[i-1],best)))
	best = j;
    }
    tour[i] = best;
    used[best] = true;
  }

  return tour;	  
}

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
  std::vector<double> array_x;
  std::vector<double> array_y;
  setup_arrays(infile,array_x,array_y);

  
  
   
   
  return 0;
}
