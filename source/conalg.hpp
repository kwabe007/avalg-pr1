#ifndef CONALG_HPP
#define CONALG_HPP

#include "tools.hpp"



void get_tour_rec(const std::vector<std::vector<unsigned int>>& mst_tree, std::vector<int>& tour, std::vector<bool>& visited, unsigned int i) {
  tour.push_back((int)i);
  visited[i] = true;
  for (unsigned int j = 0; j < mst_tree[i].size(); ++j) {
    if (!visited[mst_tree[i][j]]) {
      get_tour_rec(mst_tree, tour, visited, mst_tree[i][j]);
    }
      
  }
  
  return;
}

//MST heuristic algorithm

std::vector<int> mst_heuristic(const std::vector<double>& array_x, const std::vector<double>& array_y) {

  std::vector<std::vector<unsigned int>> mst_tree (get_mst(array_x, array_y));
  unsigned int n = mst_tree.size();
  std::vector<bool> visited(n);
  std::vector<int> tour;


  for (unsigned int i = 0; i < n; ++i) {
    if(mst_tree[i].size() == 1) {
      get_tour_rec(mst_tree, tour, visited, i);
      break;
    }
  }
  


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
