
#ifndef CONALG_HPP
#define CONALG_HPP

#include "tools.hpp"


std::vector<int> clarke_wright(const std::vector<double>& array_x, const std::vector<double>& array_y) {
  std::srand(std::time(0));
  unsigned int n = array_x.size();
  unsigned int central_point = std::rand() % array_x.size();
  std::vector<int> tour(n);

  struct edge {
    int savings;
    unsigned int point1;
    unsigned int point2;
  };
  
  unsigned int no_of_edges = ((n * (n - 1)) / 2) - (n-1);
  unsigned int edge_index = 0;
  std::vector<edge> edge_vec(no_of_edges);
  
  for (unsigned int i=0; i < n-1; ++i) {
    if (i == central_point) continue;
    for(unsigned int j=i+1; j < n; ++j) {
      if (j == central_point) continue;
      edge edgy;
      edgy.savings = calculate_savings(array_x, array_y, central_point, i, j);
      edgy.point1 = i;
      edgy.point2 = j;
      
      edge_vec[edge_index] = edgy;
      ++edge_index;
    }
  }

  std::sort(edge_vec.begin(), edge_vec.end(),
	    [] (edge const& a, edge const& b) { return a.savings > b.savings; });

  std::vector<std::vector<unsigned int>> tour_graph(n);

  unsigned int added_edges = 0;
  for(unsigned int k=0;  k < edge_vec.size(); ++k) {
    edge current_edge = edge_vec[k];
    unsigned int point1 = current_edge.point1;
    unsigned int point2 = current_edge.point2;

    std::vector<unsigned int>& node = tour_graph[point1];
    std::vector<unsigned int>& node2 = tour_graph[point2];

    if (added_edges == n-2) {
      break;
    }
    if(node.size() > 1 || node2.size() > 1) {
      continue;
    }
    
    if(!disc(tour_graph, point2, point1)) {
      continue;
    }

    node.push_back(point2);
    node2.push_back(point1);
    ++added_edges;
  }

  for (unsigned int i = 0; i < tour_graph.size(); ++i) {
    if(tour_graph[i].size() == 1){
      tour_graph[central_point].push_back(i);
      tour_graph[i].push_back(central_point);
      break;
    }
  }

  
  int point = central_point;
  std::vector<bool> visited(n);
  visited[central_point] = true;
  
  tour[0] = point;
  for(unsigned int i = 1; i < tour_graph.size(); ++i) {
    std::vector<unsigned int>& node = tour_graph[point];
    for(unsigned int j = 0; j < node.size();++j) {
      if(!visited[node[j]]) {
	visited[node[j]] = true;
	point = node[j];
	break;
      }
    }
    tour[i] = point;	
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
