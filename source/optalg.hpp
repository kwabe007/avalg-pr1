#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include"tools.hpp"



std::vector<int> opttour(const std::vector<double>& array_x, const std::vector<double>& array_y, std::vector<int>& tour){
	int oldDist = tourDist(array_x,array_y,tour);
	int newDist = 0;
	bool same = false;
	while(!same){
		same=true;
		for(unsigned int i =0; i<tour.size();i++){
			for(unsigned int j=i+1; j<tour.size();j++){
				int swap1 = tour[i];
				tour[i] = tour[j];
				tour[j] = swap1;
				newDist = tourDist(array_x,array_y,tour);
				if(oldDist>newDist){
					oldDist=newDist;
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
