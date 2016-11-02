#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include"tools.hpp"



std::vector<int> opttour(const std::vector<double>& array_x, const std::vector<double>& array_y, std::vector<int>& tour){
  
  bool same = false;
  while(!same){
    same=true;
    for(unsigned int i =0; i<tour.size() - 1;i++){
      for(unsigned int j=i+1; j<tour.size();j++){

	// calculate the total distance between point i and j and their respective neighbours as these distances are the only ones that will be affected by a swap
	int distance_before_swap = 0;
	distance_before_swap += get_dist_to_neighbours(array_x,array_y,tour,i);
	distance_before_swap += get_dist_to_neighbours(array_x,array_y,tour,j);
			  
	int swap1 = tour[i];
	tour[i] = tour[j];
	tour[j] = swap1;

	int distance_after_swap = 0;
	distance_after_swap += get_dist_to_neighbours(array_x,array_y,tour,i);
	distance_after_swap += get_dist_to_neighbours(array_x,array_y,tour,j);

	if (distance_after_swap < distance_before_swap) {
	  same=false;
	} else {
	  swap1 = tour[i];
	  tour[i] = tour[j];
	  tour[j] = swap1;
	}
				
      }

    }

  }
  return tour;
}
