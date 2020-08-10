#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using std::vector;
using std::map;
using std::max_element;

/**
 * A thief finds much more loot than his bag can fit. Help him to find the most valuable combination
 * of items assuming that any fraction of a loot item can be put into his bag.
 * The goal of this code problem is to implement an algorithm for the fractional knapsack problem
*/


struct Data { // data for each entry to vector 'sorted value per unit weight'
  double vpuw;
  int weight;
};
double get_optimal_value(int capacity, vector<Data> &sorted);
vector<Data> sortInputs(vector<Data>vpuw, int n);

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  vector<Data> unsorted(n); // vector of values per unit weight

  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
    unsorted[i].vpuw = (double)values[i]/weights[i];
    unsorted[i].weight = weights[i];
  }

  vector<Data> sorted = sortInputs(unsorted, n);

  // for (int i = 0; i < sorted.size(); i++) {
  //   std::cout << sorted[i].vpuw << "   " << sorted[i].weight << std::endl;
  // }

  double optimal_value = get_optimal_value(capacity, sorted);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}


// sort the values per unit weight of each input line
// this is allegedly a bubble sort, check out
vector<Data> sortInputs(vector<Data> data, int size) {
  Data temp;
  for(int i = 0; i < size; i++) {		
		for(int j = i+1; j < size; j++) {
			if(data[i].vpuw < data[j].vpuw) {
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	}
  return data;
  
  // vector<int> sortedIndexes(size);
  // for (int i = 0; i < size; i++) {
  //   int vpuwIndex = max_element(vpuw.begin(), vpuw.end()) - vpuw.begin(); // index of max elem
  //   sortedIndexes[i] = vpuwIndex;
  //   vpuw.erase(vpuw.begin() + vpuwIndex); // remove found max elem
  // }
  // return sortedIndexes;
}

// pass vector by reference to avoid copy operation, might be costly
double get_optimal_value(int capacity, vector<Data> &sorted) {
  double value = 0.0;
  for (int i = 0; i < sorted.size(); i++) {
    if (capacity == 0) {
      return value;
    }
    // the weight to multiply with. If capacity is less than the usual weight, use whatever capacity is left
    int w = std::min(sorted[i].weight, capacity);
    value += sorted[i].vpuw * w; // value per unit weight by weight
    capacity -= w;
  }

  return value;
}
