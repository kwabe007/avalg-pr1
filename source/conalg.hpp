#ifndef CONALG_HPP
#define CONALG_HPP

#include "tools.hpp"

//MST heuristic algorithm

std::vector<int> mst_heuristic(const std::vector<double>& array_x, const std::vector<double>& array_y) {
  unsigned int n = array_x.size();
  std::vector<int>tour(n);
  std::vector<bool> used(n);

  return tour;
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


#endif
