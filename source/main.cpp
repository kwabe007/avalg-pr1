#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include"debugmacro.h"


/*DEBUG BITS
BIT0 = variable contents*/

unsigned int GLOBAL_DEBUG_BITS = BIT0;

//calculates euclidean distance of two (x,y)-points rounded to the nearest integer.
int dist(const std::vector<double>& array_x, const std::vector<double>& array_y, int index1, int index2) {

  double x1 = array_x[index1];
  double x2 = array_x[index2];
  double y1 = array_y[index1];
  double y2 = array_y[index2];

  double distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
  int rounded_distance = std::round(distance);
  return rounded_distance;
}

//Greedy Tour algorithm
std::vector<int> greedy_tour(const std::vector<double>& array_x, const std::vector<double>& array_y) {
  unsigned int n = array_x.size();
  std::vector<int>tour(n);
  std::vector<bool> used(n);
  tour[0] = 0;
  used[0] = true;
  int best;
  
  for(unsigned int i = 1; i < n-1; ++i) {
    best = -1;
    for (unsigned int j = 0; j < n; ++j) {
      if (!used[j] && (best == -1 || dist(array_x, array_y, tour[i-1], j) < dist(array_x, array_y,tour[i-1],best)))
	best = j;
    }
    tour[i] = best;
    used[best] = true;
  }

  //this was added so we also assign the last point in the tour (for example point 7 in the kattis-sample)
  for(unsigned int i = 1; i < n; ++i) {
    if(used[i] == false){
      tour[n-1] = i;
      break;
    }
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

  //set the stream to read data points from
  std::istream& instream = std::cin;

  // arrays to be filled with data points
  std::vector<double> array_x;
  std::vector<double> array_y;
  setup_arrays(instream,array_x,array_y);

  std::vector<int> tour = greedy_tour(array_x, array_y);
  for (unsigned int i = 0; i < tour.size(); ++i) {
    std::cout << tour[i] << std::endl;
  }
  return 0;
}
