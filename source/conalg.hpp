
#ifndef CONALG_HPP
#define CONALG_HPP

#include "tools.hpp"


std::vector<int> clarke_wright(const std::vector<double>& array_x, const std::vector<double>& array_y) {
  std::vector<int> tour;
  std::srand(std::time(0));
  unsigned int n = array_x.size();
  unsigned int central_point = 6;//std::rand() % array_x.size();

  struct edge {
    int savings;
    unsigned int point1;
    unsigned int point2;
  };

  std::vector<edge> edge_vec;
  
  for (unsigned int i=0; i < n-1; ++i) {
    if (i == central_point) continue;
    for(unsigned int j=i+1; j < n; ++j) {
      if (j == central_point) continue;
      edge edgy;
      edgy.savings = calculate_savings(array_x, array_y, central_point, i, j);
      edgy.point1 = i;
      edgy.point2 = j;
      
      edge_vec.push_back(edgy);
    }
  }

  

  std::vector<std::vector<int>> tour_graph(n);
  for(unsigned int k=0;  k < edge_vec.size(); ++k) {
    edge current_edge = edge_vec[k];
    std::vector<int>& node = tour_graph[current_edge.point1];
    std::vector<int>& node2 = tour_graph[current_edge.point2];
    
    if(node.size() > 1 || node2.size() > 1) {
      continue;
    }

    node.push_back(current_edge.point1);
    node2.push_back(current_edge.point2);

  }

  
  
  return tour;
}

//recursive function for filling out a tour from an mst_tree
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
