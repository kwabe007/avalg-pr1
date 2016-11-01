#ifndef TOOLS_HPP
#define TOOLS_HPP

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


#endif
