#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include"debugmacro.h"

// calculates distance of entire tour
int tourDist(const std::vector<double>& array_x, const std::vector<double>& array_y, const std::vector<int> tour){
	unsigned int d = 0;
	for(unsigned i = 0; i<tour.size()-1; i++){
		d += dist(array_x,array_y,tour[i],tour[i+1]);
	}

	return dist;
}


std::vector<int> opttour(const std::vector<double>& array_x, const std::vector<double>& array_y, const std::vector<int> tour){
	std::vector<int> imptour = std::vector<int>(tour.size());
	bool same = false;
	std::vector<int> bestTour = tour;
	int oldDist = tourDist(array_x,array_y,tour) 
	while(!same){
		same=true;
		for(unsigned int i =0; i<tour.size();i++){
			for(unsigned int j=i+1; j<tour.size();j++){
				int swap1 = tour[i];
				int swap2 = tour[j];
				tour[i] = swap2;
				tour[j] = swap1;
				newDist = tourDist(array_x,array_y,tour);
				if(oldDist<newDist){
					oldDist=newDist;
					bestTour = tour;
					same=false;
				}
			}

		}

	}
	return bestTour;	
}