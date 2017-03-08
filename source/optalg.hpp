#ifndef OPTALG_HPP
#define OPTALG_HPP

#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<algorithm>
#include"tools.hpp"



std::vector<int>& opttour(const std::vector<double>& array_x, const std::vector<double>& array_y, std::vector<int>& tour){
  int counter =0;
  bool same = false;

  /*
    if(counter < 90){
    for(unsigned int ikl=0;ikl<tour.size();ikl++){std::cout << tour[ikl];}
    std::cout << std::endl;} */


  while(!same){

    same=true;
    counter++;

    for(unsigned int i =0; i<tour.size()-1;i++){
      for(unsigned int j=i+1;j<tour.size();j++){

	// calculate the total distance between point i and j and their respective neighbours as these distances are the only ones that will be affected by a swap
	int distance_before_swap = 0; //tourDist(array_x,array_y,tour);
	distance_before_swap += get_dist_to_neighbours(array_x,array_y,tour,i);
	distance_before_swap += get_dist_to_neighbours(array_x,array_y,tour,j);

	unsigned int left = i;
	unsigned int right =j;

	while(left < right){
	  int swap1 = tour[right];
	  tour[right] = tour[left];
	  tour[left] = swap1;
	  right--;
	  left++;
	}
	/*
	  unsigned int nrOfS = j-i-2+(j-i)%2;
	  for(unsigned int l = 0;l<nrOfS;l++){
	  int swap1 = tour[j-l];
	  tour[j-l] = tour[i+l];
	  tour[i+l] = swap1;

	  }  
	*/
	int distance_after_swap = 0; //tourDist(array_x,array_y,tour);
	distance_after_swap += get_dist_to_neighbours(array_x,array_y,tour,i);
	distance_after_swap += get_dist_to_neighbours(array_x,array_y,tour,j);
	int diff = distance_before_swap - distance_after_swap;

	if (diff > 0) {
	  same=false;

	} else {
	  left = i;
	  right = j;
	  while(left < right){
	    int swap1 = tour[right];
	    tour[right] = tour[left];
	    tour[left] = swap1;
	    right--;
	    left++;

	  }


	}


      }

    }
    //std::cout << 10001 << std::endl;

  }

  return tour;
}

std::vector<int>& whacktour(const std::vector<double>& array_x, const std::vector<double>& array_y, std::vector<int>& tour){

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

#endif
