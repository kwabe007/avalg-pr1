#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <vector>
#include <tuple>
#include <algorithm>

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

// calculates distance of entire tour
int tourDist(const std::vector<double>& array_x, const std::vector<double>& array_y, const std::vector<int>& tour){
	unsigned int d = 0;
	for(unsigned i = 0; i < tour.size()-1; i++){
		unsigned int result = dist(array_x,array_y,tour[i],tour[i+1]);
		d += result;
	}

	return d;
}

// calculates the sum distance between a point given by index and its two neighbours (or one neighbour if it's a start or end point)
int get_dist_to_neighbours(const std::vector<double>& array_x, const std::vector<double>& array_y, const std::vector<int>& tour, unsigned int tour_index){

  int distance = 0;

  if (tour_index > 0) {
    distance += dist(array_x, array_y, tour[tour_index], tour[tour_index - 1]);
  }
  
  
  if (tour_index < tour.size() - 1){
    distance += dist(array_x, array_y, tour[tour_index], tour[tour_index + 1]);
  }
  return distance;
  
}
//recursive part of the disc function
bool disc_rec(const std::vector<std::vector<unsigned int>>& matrix, unsigned int current_vec, unsigned int goal, std::vector<bool>& searched) {

  bool found = true;
  
  const std::vector<unsigned int>& vector = matrix[current_vec];
  
  for(unsigned int i = 0; i < vector.size(); ++i) {

    if(vector[i] == goal) {
      return false;
    }
    else if (searched[vector[i]] != true) {
	searched[vector[i]] = true;
	found = disc_rec(matrix, vector[i], goal, searched);
	if (found == false) {
	  return false;
	}
    }

  }
  
  return true;
}


//checks if two points are connected by a path in the given edge-matrix
bool disc(const std::vector<std::vector<unsigned int>>& matrix, unsigned int i, unsigned int j) {

  std::vector<bool> searched(matrix.size());
  bool disconnected = disc_rec(matrix, i, j, searched);
  
  return disconnected;
}


std::vector<std::vector<unsigned int>> get_mst(const std::vector<double>& array_x, const std::vector<double>& array_y){

  std::vector<std::tuple<int, unsigned int, unsigned int>> edge_vec;
  
  for(unsigned int i = 0; i < array_x.size()-1; ++i) {
    for (unsigned int j = i+1; j < array_x.size(); ++j) {
      std::tuple<int, unsigned int, unsigned int> edge(dist(array_x,array_y,i,j), i, j);
      edge_vec.push_back(edge);      
    }
  }

  //sort with a lambda for comparison so tuple a < tuple b is based on tuple.dist
  std::sort(edge_vec.begin(), edge_vec.end(),
	    [] (std::tuple<int, unsigned int, unsigned int> const& a, std::tuple<int, unsigned int, unsigned int> const& b) { return std::get<0>(a) < std::get<0>(b); });
  std::vector<std::vector<unsigned int>> matrix(array_x.size());

  for(unsigned int k = 0; k < edge_vec.size(); ++k) {
    unsigned int i = std::get<1>(edge_vec[k]);
    unsigned int j = std::get<2>(edge_vec[k]);

    if(disc(matrix, i, j)) {
      matrix[i].push_back(j);
      matrix[j].push_back(i);
    }

  }

      
  
  return matrix;
  
}

//calculate the savings as (sum of distance from central to i and j respectively) - distance between points given by i and j 
int calculate_savings(const std::vector<double>& array_x, const std::vector<double>& array_y, unsigned int central, unsigned int i, unsigned int j) {

  int distance_central_i = dist(array_x,array_y, central, i);
  int distance_central_j = dist(array_x,array_y, central, j);
  
  int sum_distance_to_central = distance_central_i + distance_central_j;
  int distance_between_i_j = dist(array_x,array_y, i, j);
  int savings = sum_distance_to_central - distance_between_i_j;
  
  return savings;
}

#endif
